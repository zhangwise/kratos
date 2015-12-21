//
// Author: Miquel Santasusana msantasusana@cimne.upc.edu
//


#if !defined(KRATOS_CYLINDER_CONTINUUM_PARTICLE_H_INCLUDED )
#define  KRATOS_CYLINDER_CONTINUUM_PARTICLE_H_INCLUDED

// System includes
#include <string>
#include <iostream>


// External includes


// Project includes
#include "includes/define.h"
#include "discrete_element.h"
#include "spheric_continuum_particle.h"



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
  class CylinderContinuumParticle: public SphericContinuumParticle
    {
    public:

      KRATOS_CLASS_POINTER_DEFINITION(CylinderContinuumParticle);

      typedef WeakPointerVector<Element> ParticleWeakVectorType;  //M: l'he afegit jo.. esta be aquesta?
      typedef ParticleWeakVectorType::ptr_iterator ParticleWeakIteratorType_ptr;
      typedef WeakPointerVector<Element >::iterator ParticleWeakIteratorType;

      CylinderContinuumParticle( IndexType NewId, GeometryType::Pointer pGeometry );
      CylinderContinuumParticle( IndexType NewId, NodesArrayType const& ThisNodes);
      CylinderContinuumParticle( IndexType NewId, GeometryType::Pointer pGeometry,  PropertiesType::Pointer pProperties );

      Element::Pointer Create(IndexType NewId, NodesArrayType const& ThisNodes, PropertiesType::Pointer pProperties) const;

      /// Destructor.
      virtual ~CylinderContinuumParticle();


      virtual std::string Info() const
      {
          std::stringstream buffer;
          buffer << "CylinderContinuumParticle" ;
          return buffer.str();
      }

      /// Print information about this object.
      virtual void PrintInfo(std::ostream& rOStream) const {rOStream << "CylinderContinuumParticle";}

      /// Print object's data.
      virtual void PrintData(std::ostream& rOStream) const {}

      void ContactAreaWeighting();

    protected:

      CylinderContinuumParticle();
      
      void Initialize();
//      void AddNeighbourContributionToStressTensor(double GlobalElasticContactForce[3],
//                                                array_1d<double,3> &other_to_me_vect,
//                                                const double &distance,
//                                                const double &radius_sum,
//                                                const double &calculation_area,
//                                                ParticleWeakIteratorType neighbour_iterator,
//                                                ProcessInfo& rCurrentProcessInfo,
//                                                double &rRepresentative_Volume);
      void ComputeBallToBallContactForce(array_1d<double, 3>& rElasticForce,
                                         array_1d<double, 3>& rContactForce,
                                         array_1d<double, 3>& InitialRotaMoment,
                                         ProcessInfo& rCurrentProcessInfo,
                                         double dt,
                                         const bool multi_stage_RHS);



      //ParticleWeakVectorType mrNeighbours;

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


      ///@}
      ///@name Serialization
      ///@{

      friend class Serializer;

      virtual void save(Serializer& rSerializer) const
      {
          KRATOS_SERIALIZE_SAVE_BASE_CLASS(rSerializer, DiscreteElement );
      }

      virtual void load(Serializer& rSerializer)
      {
          KRATOS_SERIALIZE_LOAD_BASE_CLASS(rSerializer, DiscreteElement );
      }

 

    }; 

  ///@}

  ///@name Type Definitions
  ///@{


  ///@}
  ///@name Input and output
  ///@{


  /// input stream function
  inline std::istream& operator >> (std::istream& rIStream,
                    CylinderContinuumParticle& rThis){ return rIStream;}

  /// output stream function
  inline std::ostream& operator << (std::ostream& rOStream,
                    const CylinderContinuumParticle& rThis)
    {
      rThis.PrintInfo(rOStream);
      rOStream << std::endl;
      rThis.PrintData(rOStream);

      return rOStream;
    }
  ///@}

  ///@} addtogroup block

}  // namespace Kratos.

#endif // KRATOS_SPHERIC_PARTICLE_H_INCLUDED  defined


