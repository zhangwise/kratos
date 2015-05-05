//
//   Project Name:        Kratos
//   Last Modified by:    $Author: clabra $
//   Date:                $Date: 2007-03-29 19:37:47 $
//   Revision:            $Revision: 1.2 $
//
//

#if !defined(KRATOS_DEM_FEM_SEARCH_H_INCLUDED )
#define  KRATOS_DEM_FEM_SEARCH_H_INCLUDED

// System includes
#include <string>
#include <iostream> 

// include kratos definitions
#include "includes/define.h"

// Project includes
#include "utilities/openmp_utils.h"

// Configures
#include "rigid_face_geometrical_object_configure.h"
// Search
#include "spatial_containers/bins_dynamic_objects.h"
#include "spatial_containers/bins_dynamic.h"

// External includes

/* Timer defines */
#include "utilities/timer.h"
#ifdef CUSTOMTIMER
#define KRATOS_TIMER_START(t) Timer::Start(t);
#define KRATOS_TIMER_STOP(t) Timer::Stop(t);
#else
#define KRATOS_TIMER_START(t)
#define KRATOS_TIMER_STOP(t)
#endif

namespace Kratos
{

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

class DEM_FEM_Search : public SpatialSearch
{
    public:
      ///@name Type Definitions
      ///@{
    
      /// Pointer definition of OMP_DEMSearch
      KRATOS_CLASS_POINTER_DEFINITION(DEM_FEM_Search);
      
      typedef PointType*                                PtrPointType;
      typedef std::vector<PtrPointType>*                PointVector;
      typedef std::vector<PtrPointType>::iterator       PointIterator;
      
      typedef double*                                   DistanceVector;
      typedef double*                                   DistanceIterator;
      
//       //Configure Types
//       typedef RigidFaceConfigure<3>                        ElementConfigureType;   //Element
//       //Bin Types
//       typedef BinsObjectDynamic<ElementConfigureType>   BinsType;
// 	  
	  //Configure Types
	  typedef RigidFaceGeometricalObjectConfigure<3>        RigidFaceGeometricalConfigureType;     	
      //Bin Types
	  typedef BinsObjectDynamic<RigidFaceGeometricalConfigureType>   GeometricalBinsType;
    typedef PointerVectorSet<GeometricalObject, IndexedObject>     GeometricalObjectType;
    //typedef PointerVector<GeometricalObject>     GeometricalObjectType;
	  
	  
     
      
      ///@}
      ///@name Life Cycle 
      ///@{
      
      /// Default constructor.
      DEM_FEM_Search(){
      }

      /// Destructor.
      ~DEM_FEM_Search(){
      }
      
  void SearchRigidFaceForDEMInRadiusExclusiveImplementation (
          ElementsContainerType   const& rElements,
          ConditionsContainerType const& rConditions,
          const RadiusArrayType & Radius, 
          VectorResultConditionsContainerType& rResults, 
          VectorDistanceType& rResultsDistance )
      {     
          KRATOS_TRY
          
          int MaxNumberOfElements = rConditions.size();

          ElementsContainerType::ContainerType& elements_sear   = const_cast<ElementsContainerType::ContainerType&>  (rElements.GetContainer());
          ConditionsContainerType::ContainerType& conditions_bins = const_cast<ConditionsContainerType::ContainerType&>(rConditions.GetContainer());

          GeometricalObjectType::ContainerType SearElementPointerToGeometricalObjecPointerTemporalVector;
          GeometricalObjectType::ContainerType BinsConditionPointerToGeometricalObjecPointerTemporalVector;

          SearElementPointerToGeometricalObjecPointerTemporalVector.reserve(elements_sear.size());
          BinsConditionPointerToGeometricalObjecPointerTemporalVector.reserve(conditions_bins.size());
              
          for(ElementsContainerType::ContainerType::iterator it = elements_sear.begin(); it != elements_sear.end(); it++)
              SearElementPointerToGeometricalObjecPointerTemporalVector.push_back(*it);
          
          for(ConditionsContainerType::ContainerType::iterator it = conditions_bins.begin(); it != conditions_bins.end(); it++)
              BinsConditionPointerToGeometricalObjecPointerTemporalVector.push_back(*it);
                 
          // This is used to generate the bins with all the particles. This does not need to be enabled unless you have
          //  a really good reason for it
              
          //for(ElementsContainerType::ContainerType::iterator it = elements_sear.begin(); it != elements_sear.end(); it++)
          //    BinsElementPointerToGeometricalObjecPointerTemporalVector.push_back(*it); 

          GeometricalBinsType bins(BinsConditionPointerToGeometricalObjecPointerTemporalVector.begin(), BinsConditionPointerToGeometricalObjecPointerTemporalVector.end());
          
//           bins.PrintData(std::cout);
          
          #pragma omp parallel
          {
              GeometricalObjectType::ContainerType  localResults(MaxNumberOfElements);
              DistanceType                          localResultsDistances(MaxNumberOfElements);
              std::size_t                           NumberOfResults = 0;
              
              #pragma omp for
              for(int i = 0; i < static_cast<int>(elements_sear.size()); i++)
              {
                  GeometricalObjectType::ContainerType::iterator   ResultsPointer          = localResults.begin();
                  DistanceType::iterator                           ResultsDistancesPointer = localResultsDistances.begin();

                  NumberOfResults = bins.SearchObjectsInRadiusExclusive(SearElementPointerToGeometricalObjecPointerTemporalVector[i],Radius[i],ResultsPointer,ResultsDistancesPointer,MaxNumberOfElements);

                  rResults[i].reserve(NumberOfResults);
                  
                  for(GeometricalObjectType::ContainerType::iterator it = localResults.begin(); it != localResults.begin() + NumberOfResults; it++)
                  {
                      Condition::Pointer elem = boost::dynamic_pointer_cast<Condition>(*it);
                      rResults[i].push_back(elem);
                  }

                  rResultsDistance[i].insert(rResultsDistance[i].begin(),localResultsDistances.begin(),localResultsDistances.begin()+NumberOfResults);
              }
          }
          
          KRATOS_CATCH("")
      }

      /// Turn back information as a string.
      virtual std::string Info() const
      {
          std::stringstream buffer;
          buffer << "DEM_FEM_Search" ;
          
          return buffer.str();
      }
      
      /// Print information about this object.
      virtual void PrintInfo(std::ostream& rOStream) const {rOStream << "DEM_FEM_Search";}

      /// Print object's data.
      virtual void PrintData(std::ostream& rOStream) const {}
      
            
      ///@}      
      ///@name Friends
      ///@{
      
            
      ///@}
      
    protected:
      ///@name Protected static Member Variables 
      ///@{ 
        
        
      ///@} 
      ///@name Protected member Variables 
      ///@{
        
        
        
      ///@} 
      ///@name Protected Operators
      ///@{ 
        
        
      ///@} 
      ///@name Protected Operations
      ///@{ 
        
        
      ///@} 
      ///@name Protected  Access 
      ///@{ 
        
        
      ///@}      
      ///@name Protected Inquiry 
      ///@{ 
        
        
      ///@}    
      ///@name Protected LifeCycle 
      ///@{ 
      
            
      ///@}
      
    private:
      ///@name Static Member Variables 
      ///@{ 
        
        
      ///@} 
      ///@name Member Variables 
      ///@{ 
        
        
      ///@} 
      ///@name Private Operators
      ///@{ 
        
        
      ///@} 
      ///@name Private Operations
      ///@{ 
        
        
      ///@} 
      ///@name Private  Access 
      ///@{ 
        
        
      ///@}    
      ///@name Private Inquiry 
      ///@{ 
        
        
      ///@}    
      ///@name Un accessible methods 
      ///@{ 
      
      /// Assignment operator.
     DEM_FEM_Search& operator=(DEM_FEM_Search const& rOther)
      {
          return *this;
      }

      /// Copy constructor.
      DEM_FEM_Search(DEM_FEM_Search const& rOther)
      {
          *this = rOther;
      }

       
        
        
    }; // Class DEM_FEMSearch

  
}  // namespace Kratos.

#endif // KRATOS_DEM_FEM_SEARCH_H_INCLUDED  defined 


