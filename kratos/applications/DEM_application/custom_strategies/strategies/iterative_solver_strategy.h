//
// Author: Miquel Santasusana msantasusana@cimne.upc.edu
//


#if !defined(KRATOS_ITERATIVE_SOLVER_STRATEGY)
#define  KRATOS_ITERATIVE_SOLVER_STRATEGY

#include "custom_strategies/strategies/explicit_solver_strategy.h"
#include "DEM_definitions.h"

#define CUSTOMTIMER 0  // ACTIVATES AND DISABLES ::TIMER:::::


namespace Kratos
{

  template<
  class TSparseSpace,
  class TDenseSpace,
  class TLinearSolver>
  class IterativeSolverStrategy: public ExplicitSolverStrategy<TSparseSpace,TDenseSpace,TLinearSolver>
  {
      public:
      ///@name Type Definitions
      ///@{
        
      typedef ExplicitSolverStrategy<TSparseSpace,TDenseSpace,TLinearSolver>   BaseType;
   
      typedef typename BaseType::NodesArrayType                             NodesArrayType;
      typedef typename BaseType::ElementsArrayType                          ElementsArrayType;
      typedef typename BaseType::ElementsIterator                           ElementsIterator;
      typedef typename BaseType::ConditionsArrayType                        ConditionsArrayType;
      
      /*  Revisar charlie */
      
      typedef WeakPointerVector<Element> ParticleWeakVectorType; 
      typedef WeakPointerVector<Element >::iterator ParticleWeakIteratorType;
      typedef ParticleWeakVectorType::ptr_iterator ParticleWeakIteratorType_ptr;

      
      /// Pointer definition of ExplicitSolverStrategy
      KRATOS_CLASS_POINTER_DEFINITION(IterativeSolverStrategy);

      /// Default constructor.
      IterativeSolverStrategy(){}
     
      IterativeSolverStrategy(
                             ExplicitSolverSettings& settings,
                             const double max_delta_time,
                             const double n_step_search,
                             const double safety_factor,
                             const int delta_option,
                             const double search_tolerance,
                             const double coordination_number,
                             typename ParticleCreatorDestructor::Pointer p_creator_destructor,
                             typename DEM_FEM_Search::Pointer p_dem_fem_search,
                             typename DEMIntegrationScheme::Pointer pScheme,
                             typename SpatialSearch::Pointer pSpSearch)
      :ExplicitSolverStrategy<TSparseSpace,TDenseSpace,TLinearSolver>(settings, max_delta_time, n_step_search, safety_factor, delta_option, search_tolerance, coordination_number, p_creator_destructor, p_dem_fem_search, pScheme, pSpSearch)
      {                    
          BaseType::GetParticleCreatorDestructor()   = p_creator_destructor;                            
      }

      /// Destructor.
      virtual ~IterativeSolverStrategy()
      {
         Timer::SetOuputFile("TimesPartialRelease");
         Timer::PrintTimingInformation();
      }      
      
    
      virtual void Initialize()
      {
        
        KRATOS_TRY
        
        BaseType::Initialize();
           
        KRATOS_CATCH("")        
      }// Initialize()

      virtual double Solve()
      {
            
          KRATOS_TRY
          
          
           BaseType::Solve();
   

        KRATOS_CATCH("") 
          
        return 0.0;
          
      }//Solve()

  };//ClassIterativeSolverStrategy

     
}  // namespace Kratos.

#endif // KRATOS_FILENAME_H_INCLUDED  defined



