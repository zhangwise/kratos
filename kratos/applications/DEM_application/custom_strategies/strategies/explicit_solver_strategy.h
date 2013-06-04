//
//   Project Name:        Kratos
//   Last Modified by:    $Author: Nelson Lafontaine $
//   Date:                $Date: 2008-10-13 08:56:42 $
//   Revision:            $Revision: 1.5 $
//
//

#if !defined(KRATOS_EXPLICIT_SOLVER_STRATEGY)
#define  KRATOS_EXPLICIT_SOLVER_STRATEGY

// /* External includes */
// #include "boost/smart_ptr.hpp"

// System includes

// Project includes
#include "utilities/timer.h"
#include "custom_utilities/create_and_destroy.h"

//#include "custom_elements/spheric_particle.h"
#include "custom_elements/spheric_swimming_particle.h"
#include "custom_elements/Particle_Contact_Element.h"

#include "includes/variables.h"
#include "DEM_application.h"

/* System includes */
#include <limits>
#include <iostream>
#include <iomanip>
#include <iostream>

/* External includes */
#ifdef _OPENMP
#include <omp.h>
#endif

//#define CUSTOMTIMER 0  // ACTIVATES AND DISABLES ::TIMER:::::

#include "boost/smart_ptr.hpp"

/* Project includes */
#include "includes/define.h"
#include "utilities/openmp_utils.h"
#include "includes/model_part.h"
#include "solving_strategies/strategies/solving_strategy.h"
#include "solving_strategies/schemes/scheme.h"
#include "geometries/line_3d_2.h"
#include "custom_strategies/schemes/integration_scheme.h"

/* Search */
#include "spatial_containers/spatial_search.h"

namespace Kratos
{
  ///@addtogroup ApplicationNameApplication
  ///@{

  ///@name Kratos Globals
  ///@{

  ///@}
  ///@name Type Definitions
  ///@{

  ///@}
  ///@name  Enum's
  ///@{

  ///@}
  ///@name  Functions
  ///@{

  ///@}
  ///@name Kratos Classes
  ///@{

  /// Short class definition.
  /** Detail class definition.
  */
  template<
  class TSparseSpace,
  class TDenseSpace,
  class TLinearSolver>
  class ExplicitSolverStrategy: public  SolvingStrategy<TSparseSpace,TDenseSpace,TLinearSolver>
     {
      public:
      ///@name Type Definitions
      ///@{

      typedef SolvingStrategy<TSparseSpace,TDenseSpace,TLinearSolver>   BaseType;
      typedef ModelPart::NodesContainerType                             NodesArrayType;
      typedef ModelPart::ElementsContainerType                          ElementsArrayType;
      typedef ElementsArrayType::iterator                               ElementsIterator;
      typedef ModelPart::ConditionsContainerType                        ConditionsArrayType;

      typedef ModelPart::NodesContainerType::ContainerType              NodesContainerType;
      typedef ModelPart::ElementsContainerType::ContainerType           ElementsContainerType;
      typedef ModelPart::ConditionsContainerType::ContainerType         ConditionsContainerType;

      typedef SpatialSearch::ResultElementsContainerType                ResultElementsContainerType;
      typedef SpatialSearch::VectorResultElementsContainerType          VectorResultElementsContainerType;

      typedef SpatialSearch::RadiusArrayType                            RadiusArrayType;
      typedef SpatialSearch::DistanceType                               DistanceType;
      typedef SpatialSearch::VectorDistanceType                         VectorDistanceType;

      /// Pointer definition of ExplicitSolverStrategy
      KRATOS_CLASS_POINTER_DEFINITION(ExplicitSolverStrategy);

      ///@}
      ///@name Life Cycle
      ///@{

      /// Default constructor.
      ExplicitSolverStrategy(){}

      ExplicitSolverStrategy(ModelPart& rModelPart,
                             const double enlargement_factor,
                             const double max_delta_time,
                             const double n_step_search,
                             const double safety_factor,
                             const bool MoveMeshFlag,
                             typename IntegrationScheme::Pointer pScheme,
                             typename SpatialSearch::Pointer pSpSearch
      ): SolvingStrategy<TSparseSpace,TDenseSpace,TLinearSolver>(rModelPart, MoveMeshFlag)//, mcontacts_model_part(contacts_model_part)//inicialitzacio de variables const. no poden inicialitzarse a l'esquerra d'un igual. //les referencies tambe aqui
      {
          this->GetElementsAreInitialized()      = false;
          this->GetInitializeWasPerformed()      = false;
          //mComputeTime                 = false;
          this->GetEnlargementFactor()           = enlargement_factor;
          this->GetScheme()                     = pScheme;
          this->GetSpSearch()                   = pSpSearch;
          this->GetMaxTimeStep()                 = max_delta_time;
          this->GetNStepSearch()                 = n_step_search;
          this->GetSafetyFactor()                = safety_factor;
      }

      /// Destructor.
      virtual ~ExplicitSolverStrategy()
      {
        Timer my_timer;
        my_timer.PrintTimingInformation();
      }

      virtual void Initialize()
      {
          KRATOS_TRY

          ModelPart& rModelPart            = BaseType::GetModelPart();
          ProcessInfo& rCurrentProcessInfo = rModelPart.GetProcessInfo();

          int NumberOfElements = rModelPart.GetCommunicator().LocalMesh().ElementsArray().end() - rModelPart.GetCommunicator().LocalMesh().ElementsArray().begin();

          mResults.resize(NumberOfElements);
          mResultsDistances.resize(NumberOfElements);
          mRadius.resize(NumberOfElements);

          // Omp initializations
          this->GetNumberOfThreads() = OpenMPUtils::GetNumThreads();

          // 0. Set search radius
          SetSearchRadius(rModelPart, rCurrentProcessInfo[SEARCH_RADIUS_EXTENSION],0);

          // 1. Search Neighbours with tolerance (Not in mpi.)
          bool extension_option            = false;
          this->GetBoundingBoxOption()               = rCurrentProcessInfo[BOUNDING_BOX_OPTION];
          extension_option                 = rCurrentProcessInfo[CASE_OPTION];

          // 2. Search Neighbours with tolerance (afther first repartition process)
          SearchInitialNeighbours(rModelPart, extension_option);
          InitializeSolutionStep();
          // 3. Finding overlapping of initial configurations
          if (rCurrentProcessInfo[CLEAN_INDENT_OPTION]){
              CalculateInitialMaxIndentations();
          }

          // 4. Initializing elements and perform the repartition
          if (this->GetElementsAreInitialized() == false){
              InitializeElements();
          }

          this->GetInitializeWasPerformed() = true;

          // 5. Set Initial Contacts
          SetInitialContacts(); // Empty function

          // 6. Compute initial time step
          InitialTimeStepCalculation();

	  // 7. Calculate bounding box
	  this->GetParticleCreatorDestructor().CalculateSurroundingBoundingBox(rModelPart, this->GetEnlargementFactor());

	  KRATOS_CATCH("")

      }// Initialized()

      virtual double Solve()
      {
          KRATOS_TRY

          ModelPart& rModelPart            = BaseType::GetModelPart();
          ProcessInfo& rCurrentProcessInfo = rModelPart.GetProcessInfo();

          bool extension_option            = false;

          if (rCurrentProcessInfo[CASE_OPTION]){
              extension_option             = true;
          }

          int time_step = rCurrentProcessInfo[TIME_STEPS];

          //STRATEGY:
          // 1. Here we initialize member variables that depend on the rCurrentProcessInfo
          InitializeSolutionStep();

          // 2. Get and Calculate the forces
          GetForce();

          // 3. Motion Integration
          PerformTimeIntegrationOfMotion(); //llama al scheme, i aquesta ja fa el calcul dels despaçaments i tot

          // 4. Synchronize
          SynchronizeSolidMesh(rModelPart);

          // 5. Neighbouring search. Every N times. + destruction of particles outside the bounding box

          if (rCurrentProcessInfo[ACTIVATE_SEARCH] == 1){

              if ((time_step + 1)%this->GetNStepSearch() == 0 && time_step > 0){

                  if (this->GetBoundingBoxOption() == 1){
                      BoundingBoxUtility();
                  }

                  SearchNeighbours(rModelPart, extension_option); //extension option false;
              }

          }

          FinalizeSolutionStep();

          return 0.00;

          KRATOS_CATCH("")
      }//Solve()

      void InitialTimeStepCalculation()
      {
          KRATOS_TRY

          ModelPart& rModelPart             = BaseType::GetModelPart();
          ProcessInfo& rCurrentProcessInfo  = rModelPart.GetProcessInfo();
          ElementsArrayType& pElements      = rModelPart.GetCommunicator().LocalMesh().Elements();

          ElementsIterator it_begin = pElements.ptr_begin();
          ElementsIterator it_end   = pElements.ptr_end();

          double& process_info_delta_time = rCurrentProcessInfo[DELTA_TIME];
          double temp_time_step           = this->GetMaxTimeStep();
          double elem_critical_time_step  = 0.0;

          for (ElementsIterator it = it_begin; it != it_end; it++){
              it->Calculate(DELTA_TIME, elem_critical_time_step, rCurrentProcessInfo);

              if (elem_critical_time_step < temp_time_step){
                  temp_time_step = elem_critical_time_step;
              }

          }

          temp_time_step /= this->GetSafetyFactor();
          process_info_delta_time = temp_time_step;
          KRATOS_WATCH(this->GetMaxTimeStep())
          std::cout<< "****************** Calculated time step is " << temp_time_step << " ******************" << std::endl;

          KRATOS_CATCH("")
      }

      void GetForce()
      {
          KRATOS_TRY

          //M: aixo es una xapuza

          ModelPart& rModelPart             = BaseType::GetModelPart();
          ProcessInfo& rCurrentProcessInfo  = rModelPart.GetProcessInfo();
          ElementsArrayType& pElements      = rModelPart.GetCommunicator().LocalMesh().Elements();

          OpenMPUtils::CreatePartition(this->GetNumberOfThreads(), pElements.size(), this->GetElementPartition());

          Vector rhs_elem;

          #pragma omp parallel for private(rhs_elem)
          for (int k = 0; k < this->GetNumberOfThreads(); k++){

              if(rhs_elem.size() != 6){
                rhs_elem.resize(6);
              }

              typename ElementsArrayType::iterator it_begin   = pElements.ptr_begin() + this->GetElementPartition()[k];
              typename ElementsArrayType::iterator it_end     = pElements.ptr_begin() + this->GetElementPartition()[k+1];

              for (ElementsArrayType::iterator it = it_begin; it != it_end; ++it){
                  Element::GeometryType& geom = it->GetGeometry();

                  (it)->CalculateRightHandSide(rhs_elem, rCurrentProcessInfo);
                  array_1d<double,3>& applied_force  = geom(0)->FastGetSolutionStepValue(TOTAL_FORCES);
                  array_1d<double,3>& applied_moment = geom(0)->FastGetSolutionStepValue(PARTICLE_MOMENT);

                  for(int i = 0; i < 3; i++){
                      applied_force[i]  = rhs_elem[i];
                      applied_moment[i] = rhs_elem[3 + i];
                      }

              } //loop over particles

          }// loop threads OpenMP

          KRATOS_CATCH("")
      }

      void PerformTimeIntegrationOfMotion()
      {
          KRATOS_TRY

          ModelPart& rModelPart = BaseType::GetModelPart();

          this->GetScheme()->Calculate(rModelPart);

          KRATOS_CATCH("")
      }

      void InitializeSolutionStep()
      {
          KRATOS_TRY

          //SPHERE MODEL PART

          ModelPart& rModelPart             = BaseType::GetModelPart();
          ProcessInfo& rCurrentProcessInfo  = rModelPart.GetProcessInfo();
          ElementsArrayType& pElements      = rModelPart.GetCommunicator().LocalMesh().Elements();

          OpenMPUtils::CreatePartition(this->GetNumberOfThreads(), pElements.size(), this->GetElementPartition());

          #pragma omp parallel for

          for (int k = 0; k < this->GetNumberOfThreads(); k++){
              typename ElementsArrayType::iterator it_begin = pElements.ptr_begin() + this->GetElementPartition()[k];
              typename ElementsArrayType::iterator it_end   = pElements.ptr_begin() + this->GetElementPartition()[k + 1];

              for (ElementsArrayType::iterator it = it_begin; it != it_end; ++it){
                  (it)->InitializeSolutionStep(rCurrentProcessInfo); //we use this function to call the set initial contacts and the add continuum contacts.
              } // loop over particles

          }// loop threads OpenMP

        KRATOS_CATCH("")
      }

      void BoundingBoxUtility()
      {
          KRATOS_TRY

          ModelPart& rModelPart = BaseType::GetModelPart();
          this->GetParticleCreatorDestructor().DestroyDistantParticles(rModelPart);

          KRATOS_CATCH("")
      }

      void MoveMesh(){}

      void FinalizeSolutionStep()
      {
          KRATOS_TRY

          ModelPart& rModelPart             = BaseType::GetModelPart();
          ProcessInfo& rCurrentProcessInfo  = rModelPart.GetProcessInfo();
          ElementsArrayType& pElements      = rModelPart.GetCommunicator().LocalMesh().Elements();

          OpenMPUtils::CreatePartition(this->GetNumberOfThreads(), pElements.size(), this->GetElementPartition());

          #pragma omp parallel for //private(index)

          for (int k = 0; k < this->GetNumberOfThreads(); k++){
              typename ElementsArrayType::iterator it_begin = pElements.ptr_begin() + this->GetElementPartition()[k];
              typename ElementsArrayType::iterator it_end   = pElements.ptr_begin() + this->GetElementPartition()[k + 1];

              for (ElementsArrayType::iterator it = it_begin; it != it_end; ++it){
                (it)->FinalizeSolutionStep(rCurrentProcessInfo); //we use this function to call the set initial contacts and the add continuum contacts.
              } //loop over particles

          }// loop threads OpenMP

          KRATOS_CATCH("")
      }

      void FixVelocities()
      {
          KRATOS_TRY

          KRATOS_WATCH("")
          KRATOS_WATCH("FIXING VELOCITIES!")

          ModelPart& rModelPart             = BaseType::GetModelPart();
          ProcessInfo& rCurrentProcessInfo  = rModelPart.GetProcessInfo();
          ElementsArrayType& pElements      = rModelPart.GetCommunicator().LocalMesh().Elements();

          OpenMPUtils::CreatePartition(this->GetNumberOfThreads(), pElements.size(), this->GetElementPartition());

          #pragma omp parallel for

          for (int k = 0; k < this->GetNumberOfThreads(); k++){
              typename ElementsArrayType::iterator it_begin = pElements.ptr_begin() + this->GetElementPartition()[k];
              typename ElementsArrayType::iterator it_end   = pElements.ptr_begin() + this->GetElementPartition()[k + 1];

              for (ElementsArrayType::iterator it = it_begin; it != it_end; ++it){

                  if (it->GetGeometry()(0)->GetSolutionStepValue(GROUP_ID) == 1){
                      (it)->GetGeometry()(0)->Fix(VELOCITY_Y);
                      (it)->GetGeometry()(0)->FastGetSolutionStepValue(VELOCITY_Y) = rCurrentProcessInfo[FIXED_VEL_TOP];
                  }

                  if (it->GetGeometry()(0)->GetSolutionStepValue(GROUP_ID) == 2){
                      (it)->GetGeometry()(0)->Fix(VELOCITY_Y);
                      (it)->GetGeometry()(0)->FastGetSolutionStepValue(VELOCITY_Y) = rCurrentProcessInfo[FIXED_VEL_BOT];
                  }

              } // for over particles

          }// for threads OpenMP

          KRATOS_CATCH("")
      }

      void FreeVelocities()
      {
          KRATOS_TRY

          ModelPart& rModelPart             = BaseType::GetModelPart();
          ProcessInfo& rCurrentProcessInfo  = rModelPart.GetProcessInfo();
          ElementsArrayType& pElements      = rModelPart.GetCommunicator().LocalMesh().Elements();

          OpenMPUtils::CreatePartition(this->GetNumberOfThreads(), pElements.size(), this->GetElementPartition());

          #pragma omp parallel for

          for (int k = 0; k < this->GetNumberOfThreads(); k++){
              typename ElementsArrayType::iterator it_begin = pElements.ptr_begin() + this->GetElementPartition()[k];
              typename ElementsArrayType::iterator it_end   = pElements.ptr_begin() + this->GetElementPartition()[k + 1];

              for (ElementsArrayType::iterator it = it_begin; it != it_end; ++it){

                  if (it->GetGeometry()(0)->GetSolutionStepValue(GROUP_ID) == 1){
                    (it)->GetGeometry()(0)->Free(VELOCITY_Y);
                    rCurrentProcessInfo[FIXED_VEL_TOP] = (it)->GetGeometry()(0)->FastGetSolutionStepValue(VELOCITY_Y); //cutre way yeah!
                    //I only store one value for every ball in the group ID
                    (it)->GetGeometry()(0)->FastGetSolutionStepValue(VELOCITY_Y) = 0.0;
                  }

                  if (it->GetGeometry()(0)->GetSolutionStepValue(GROUP_ID) == 2){
                    (it)->GetGeometry()(0)->Free(VELOCITY_Y);
                    rCurrentProcessInfo[FIXED_VEL_BOT] = (it)->GetGeometry()(0)->FastGetSolutionStepValue(VELOCITY_Y); //cutre way yeah!
                    //I only store one value for every ball in the group ID
                    (it)->GetGeometry()(0)->FastGetSolutionStepValue(VELOCITY_Y) = 0.0;
                  }

              } // loop over particles

          }// loop threads OpenMP

          KRATOS_CATCH("")
      }


      void CalculateEnergies(){}


    void InitializeElements()
    {
        KRATOS_TRY

        ModelPart& rModelPart               = BaseType::GetModelPart();
        ProcessInfo& rCurrentProcessInfo    = rModelPart.GetProcessInfo();
        ElementsArrayType& pElements        = rModelPart.GetCommunicator().LocalMesh().Elements();

        int trihedron_OPTION = rCurrentProcessInfo[TRIHEDRON_OPTION];

        OpenMPUtils::CreatePartition(this->GetNumberOfThreads(), pElements.size(), this->GetElementPartition());

        #pragma omp parallel for //private(index, MassMatrix)  //M. proba de compilar sense mass matrix??
        for (int k = 0; k < this->GetNumberOfThreads(); k++){
            typename ElementsArrayType::iterator it_begin = pElements.ptr_begin() + this->GetElementPartition()[k];
            typename ElementsArrayType::iterator it_end   = pElements.ptr_begin() + this->GetElementPartition()[k + 1];

            for (ElementsArrayType::iterator it = it_begin; it != it_end; ++it){
            //  Element::GeometryType& geom = it->GetGeometry(); ///WARNING: COMMENTED AVOIDING WARNING COMPILATION
                (it)->Initialize();
              // 4. Set the Local Initial Axes for the trihedron Option

                if (trihedron_OPTION == 1){
                  double dummy =0.0;
                  (it)->Calculate(DUMMY_LOCAL_AXES, dummy, rCurrentProcessInfo);
                }

            }

        }

        this->GetElementsAreInitialized() = true;

        KRATOS_CATCH("")
    }

    virtual void SetInitialContacts(){}

    void SetSearchRadius(ModelPart& rModelPart, double radiusExtend, double new_extension = 0)
    {
        KRATOS_TRY

        ModelPart& rModelPart               = BaseType::GetModelPart();
        ElementsArrayType& pElements        = rModelPart.GetCommunicator().LocalMesh().Elements();

        for (SpatialSearch::ElementsContainerType::iterator particle_pointer_it = pElements.begin(); particle_pointer_it != pElements.end(); ++particle_pointer_it)
        {
            mRadius[particle_pointer_it - pElements.begin()] = (1.0 + radiusExtend) * particle_pointer_it->GetGeometry()(0)->GetSolutionStepValue(RADIUS); //if this is changed, then compobation before adding neighbours must change also.
        }

        KRATOS_CATCH("")
    }

    void KRATOS_CHECK_SIZE(const char* msg, int id)
    {
        KRATOS_TRY

        ModelPart& rModelPart               = BaseType::GetModelPart();
        ProcessInfo& rCurrentProcessInfo    = rModelPart.GetProcessInfo();
        ElementsArrayType& pElements        = rModelPart.GetCommunicator().LocalMesh().Elements();

        for (SpatialSearch::ElementsContainerType::iterator particle_pointer_it = pElements.begin(); particle_pointer_it != pElements.end(); ++particle_pointer_it)
        {
            if(particle_pointer_it->Id() == id)
            {
                std::cout << msg << " " << particle_pointer_it->GetValue(NEIGHBOUR_ELEMENTS).size() << std::endl; break;
            }
        }

        KRATOS_CATCH("")
    }

    virtual void SearchInitialNeighbours(ModelPart& rModelPart,bool extension_option)
    {
        KRATOS_TRY

        ModelPart& rModelPart               = BaseType::GetModelPart();
        ElementsArrayType& pElements        = rModelPart.GetCommunicator().LocalMesh().Elements();

        for(SpatialSearch::ElementsContainerType::iterator i = pElements.begin(); i!=pElements.end(); i++)
        {
            i->GetValue(NEIGHBOUR_ELEMENTS).clear();
        }

        this->GetSpSearch()->SearchElementsInRadiusExclusive(rModelPart,mRadius,mResults,mResultsDistances);

        OpenMPUtils::CreatePartition(this->GetNumberOfThreads(), pElements.size(), this->GetElementPartition());

        #pragma omp parallel for
        for (int k = 0; k < this->GetNumberOfThreads(); k++){
            typename ElementsArrayType::iterator it_begin = pElements.ptr_begin() + this->GetElementPartition()[k];
            typename ElementsArrayType::iterator it_end   = pElements.ptr_begin() + this->GetElementPartition()[k + 1];

            size_t ResultCounter = this->GetElementPartition()[k];

            for (SpatialSearch::ElementsContainerType::iterator particle_pointer_it = it_begin; particle_pointer_it != it_end; ++particle_pointer_it,++ResultCounter){

                for (SpatialSearch::ResultElementsContainerType::iterator neighbour_it = mResults[ResultCounter].begin(); neighbour_it != mResults[ResultCounter].end(); ++neighbour_it){
                    particle_pointer_it->GetValue(NEIGHBOUR_ELEMENTS).push_back(*neighbour_it);
                }

                mResults[ResultCounter].clear();
                mResultsDistances[ResultCounter].clear();
            }
        }

        KRATOS_CATCH("")
    }

    virtual void SearchNeighbours(ModelPart& rModelPart,bool extension_option)
    {
        KRATOS_TRY

        ModelPart& rModelPart               = BaseType::GetModelPart();
        ElementsArrayType& pElements        = rModelPart.GetCommunicator().LocalMesh().Elements();

        for(SpatialSearch::ElementsContainerType::iterator i = pElements.begin(); i != pElements.end(); i++){
            i->GetValue(NEIGHBOUR_ELEMENTS).clear();
        }

        this->GetSpSearch()->SearchElementsInRadiusExclusive(rModelPart,mRadius,mResults,mResultsDistances);

        OpenMPUtils::CreatePartition(this->GetNumberOfThreads(), pElements.size(), this->GetElementPartition());

        #pragma omp parallel for
        for (int k = 0; k < this->GetNumberOfThreads(); k++){
            typename ElementsArrayType::iterator it_begin = pElements.ptr_begin() + this->GetElementPartition()[k];
            typename ElementsArrayType::iterator it_end   = pElements.ptr_begin() + this->GetElementPartition()[k + 1];

            size_t ResultCounter = this->GetElementPartition()[k];

            for (SpatialSearch::ElementsContainerType::iterator particle_pointer_it = it_begin; particle_pointer_it != it_end; ++particle_pointer_it,++ResultCounter){

                for (SpatialSearch::ResultElementsContainerType::iterator neighbour_it = mResults[ResultCounter].begin(); neighbour_it != mResults[ResultCounter].end(); ++neighbour_it){
                    particle_pointer_it->GetValue(NEIGHBOUR_ELEMENTS).push_back(*neighbour_it);
                }

                mResults[ResultCounter].clear();
                mResultsDistances[ResultCounter].clear();
            }

        }

        KRATOS_CATCH("")
    }

    void CalculateInitialMaxIndentations(){

        KRATOS_TRY

        double tol                          = 10e-12 * this->GetParticleCreatorDestructor().GetDiameter();
        double initial_max_indentation      = 1.0 + tol;
        ModelPart& rModelPart               = BaseType::GetModelPart();
        ProcessInfo& rCurrentProcessInfo    = rModelPart.GetProcessInfo();
        rCurrentProcessInfo.SetValue(DISTANCE_TOLERANCE, tol);
        ElementsArrayType& pElements        = rModelPart.GetCommunicator().LocalMesh().Elements();
        Vector reduction_distances;
        reduction_distances.resize(rModelPart.Elements().size());

        OpenMPUtils::CreatePartition(this->GetNumberOfThreads(), pElements.size(), this->GetElementPartition());

        int elem_counter;

        #pragma omp parallel for private(elem_counter)
        for (int k = 0; k < this->GetNumberOfThreads(); k++){
            typename ElementsArrayType::iterator it_begin = pElements.ptr_begin() + this->GetElementPartition()[k];
            typename ElementsArrayType::iterator it_end   = pElements.ptr_begin() + this->GetElementPartition()[k + 1];
            elem_counter = 0;

            for (ElementsArrayType::iterator it = it_begin; it != it_end; ++it){

                if (!(it->GetGeometry()(0)->pGetDof(VELOCITY_X)->IsFixed())){
                    reduction_distances[k + elem_counter] = initial_max_indentation;
                }

                else {
                    reduction_distances[k + elem_counter] = 0.0;
                }

                elem_counter++;
            }

        }

        #pragma omp parallel for private(elem_counter)
        for (int k = 0; k < this->GetNumberOfThreads(); k++){
            typename ElementsArrayType::iterator it_begin = pElements.ptr_begin() + this->GetElementPartition()[k];
            typename ElementsArrayType::iterator it_end   = pElements.ptr_begin() + this->GetElementPartition()[k + 1];
            elem_counter = 0;

            for (ElementsArrayType::iterator it = it_begin; it != it_end; ++it){
                double max_indentation = reduction_distances[k + elem_counter];
                it->Calculate(MAX_INDENTATION, max_indentation, rCurrentProcessInfo);
                reduction_distances[k + elem_counter] = 0.5 * max_indentation;
                elem_counter++;
            }

        }

        #pragma omp parallel for private(elem_counter)
        for (int k = 0; k < this->GetNumberOfThreads(); k++){
            typename ElementsArrayType::iterator it_begin = pElements.ptr_begin() + this->GetElementPartition()[k];
            typename ElementsArrayType::iterator it_end   = pElements.ptr_begin() + this->GetElementPartition()[k + 1];
            elem_counter = 0;

            for (ElementsArrayType::iterator it = it_begin; it != it_end; ++it){
                double reduction = reduction_distances[k + elem_counter];

                if (reduction > tol){
                    (it)->GetGeometry()(0)->FastGetSolutionStepValue(RADIUS) -= reduction;
                }

                elem_counter++;
            }

        }

        KRATOS_CATCH("")
    } // CalculateInitialMaxIndentations()

    void PrepareContactModelPart(ModelPart& rModelPart, ModelPart& mcontacts_model_part)
    {
        mcontacts_model_part.GetCommunicator().SetNumberOfColors(rModelPart.GetCommunicator().GetNumberOfColors());
        mcontacts_model_part.GetCommunicator().NeighbourIndices() = rModelPart.GetCommunicator().NeighbourIndices();
    }

    void SynchronizeSolidMesh(ModelPart& rModelPart)
    {
        rModelPart.GetCommunicator().SynchronizeNodalSolutionStepsData();
        rModelPart.GetCommunicator().SynchronizeDofs();
    }
    
    //Getting member variables

    bool&   GetElementsAreInitialized(){return (mElementsAreInitialized);};
    bool&   GetInitializeWasPerformed(){return (mInitializeWasPerformed);};
    
    int&    GetNStepSearch(){return (mNStepSearch);};
    int&    GetBoundingBoxOption(){return (mBoundingBoxOption);};
    
    double& GetEnlargementFactor(){return (mEnlargementFactor);};
    double& GetMaxTimeStep(){return (mMaxTimeStep);};
    double& GetSafetyFactor(){return (mSafetyFactor);};
    
    Particle_Creator_Destructor& GetParticleCreatorDestructor(){return (mParticleCreatorDestructor);};

    int&    GetNumberOfThreads(){return (mNumberOfThreads);};
    vector<unsigned int>&    GetElementPartition(){return (mElementPartition);};
    
    typename IntegrationScheme::Pointer& GetScheme(){return (mpScheme);};
    typename SpatialSearch::Pointer& GetSpSearch(){return (mpSpSearch);};
    
    protected:

    VectorResultElementsContainerType   mResults;
    VectorDistanceType                  mResultsDistances;
    RadiusArrayType                     mRadius;

    bool                                mElementsAreInitialized;
    bool                                mInitializeWasPerformed;

    int                                 mNStepSearch;
    int                                 mBoundingBoxOption;

    double                              mEnlargementFactor;
    double                              mMaxTimeStep;
    double                              mSafetyFactor;

    Particle_Creator_Destructor         mParticleCreatorDestructor;

    int                                 mNumberOfThreads;
    vector<unsigned int>                mElementPartition;

    typename IntegrationScheme::Pointer mpScheme;
    typename SpatialSearch::Pointer     mpSpSearch;
    
 
    

  }; // Class ExplicitSolverStrategy



 /*
  /// input stream function
  inline std::istream& operator >> (std::istream& rIStream,
                    ExplicitSolverStrategy& rThis){return rIStream;}

  /// output stream function
  inline std::ostream& operator << (std::ostream& rOStream,
                    const ExplicitSolverStrategy& rThis)
    {
      rThis.PrintInfo(rOStream);
      rOStream << std::endl;
      rThis.PrintData(rOStream);

      return rOStream;
    }
    */
  ///@}

  ///@} addtogroup block

}  // namespace Kratos.

#endif // KRATOS_FILENAME_H_INCLUDED  defined




