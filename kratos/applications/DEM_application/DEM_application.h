//
//   Project Name:        Kratos
//   Last Modified by:    $Author:  $
//   Date:                $Date:  $
//   Revision:            $Revision: 1.2 $
//
//


#if !defined(KRATOS_DEM_APPLICATION_H_INCLUDED )
#define  KRATOS_DEM_APPLICATION_H_INCLUDED


// System includes
#include <string>
#include <iostream>


// External includes


// Project includes
#include "includes/define.h"
#include "includes/kratos_application.h"
#include "includes/kratos_flags.h"
#include "containers/flags.h"


#include "includes/variables.h"
#include "custom_elements/cylinder_particle.h"
#include "custom_elements/cylinder_continuum_particle.h"
#include "custom_elements/spheric_particle.h"
#include "custom_elements/spheric_continuum_particle.h"
#include "custom_elements/DEM_FEM_Particle.h"
#include "custom_elements/Particle_Contact_Element.h"
#include "custom_elements/cluster3D.h"
#include "custom_elements/linecluster3D.h"
#include "custom_conditions/mapping_condition.h"
#include "custom_conditions/dem_wall.h"
#include "custom_conditions/RigidFace.h"
#include "custom_conditions/RigidEdge.h"

#include "DEM_application_variables.h"

//constitutive laws
#include "custom_constitutive/DEM_discontinuum_constitutive_law.h"
#include "custom_constitutive/DEM_continuum_constitutive_law.h"

const long double pi = 3.141592653589793238462643383279;  //this one is used in the forward_euler_scheme... does it have to be here?

namespace Kratos
{


class KratosDEMApplication : public KratosApplication
{
public:
    ///@name Type Definitions
    ///@{


    /// Pointer definition of KratosDEMSpheresApplication
    KRATOS_CLASS_POINTER_DEFINITION(KratosDEMApplication);

    ///@}
    ///@name Life Cycle
    ///@{

    /// Default constructor.
    KratosDEMApplication();

    /// Destructor.
    virtual ~KratosDEMApplication() {}


    ///@}
    ///@name Operators
    ///@{


    ///@}
    ///@name Operations
    ///@{

    virtual void Register();



    ///@}
    ///@name Access
    ///@{


    ///@}
    ///@name Inquiry
    ///@{


    ///@}
    ///@name Input and output
    ///@{

    /// Turn back information as a string.
    virtual std::string Info() const
    {
        return "KratosDEMApplication";
    }

    /// Print information about this object.
    virtual void PrintInfo(std::ostream& rOStream) const
    {
        rOStream << Info();
        PrintData(rOStream);
    }

    ///// Print object's data.
    virtual void PrintData(std::ostream& rOStream) const
    {
        //KRATOS_WATCH("in KratosDEMApplication");
        //KRATOS_WATCH(KratosComponents<VariableData>::GetComponents().size() );
        rOStream << "Variables:" << std::endl;
        KratosComponents<VariableData>().PrintData(rOStream);
        rOStream << std::endl;
        rOStream << "Elements:" << std::endl;
        KratosComponents<Element>().PrintData(rOStream);
        rOStream << std::endl;
        rOStream << "Conditions:" << std::endl;
        KratosComponents<Condition>().PrintData(rOStream);
    }


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
    const CylinderParticle mCylinderParticle2D;
    const CylinderContinuumParticle mCylinderContinuumParticle2D;
    const SphericParticle mSphericParticle3D;
    const SphericContinuumParticle mSphericContinuumParticle3D;

    //const DEM_FEM_Particle mDEM_FEM_Particle2D;
    const DEM_FEM_Particle mDEM_FEM_Particle3D;
    
    const Particle_Contact_Element mParticleContactElement;
    const VariablesList mVariablesList;
	
    const RigidFace3D  mRigidFace3D3N;
    const RigidFace3D  mRigidFace3D4N;
    const RigidEdge3D  mRigidEdge3D2N;
    const Cluster3D  mCluster3D;
    const LineCluster3D  mLineCluster3D;
    const MAPcond    mMapCon3D3N;

    //       static const ApplicationCondition  msApplicationCondition;

    ///@}
    ///@name Member Variables
    ///@{
//      const Elem2D   mElem2D;
//      const Elem3D   mElem3D;


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
    KratosDEMApplication& operator=(KratosDEMApplication const& rOther);

    /// Copy constructor.
    KratosDEMApplication(KratosDEMApplication const& rOther);


    ///@}

}; // Class KratosDEMApplication

///@}

///@name Type Definitions
///@{


///@}
///@name Input and output
///@{

///@}


}  // namespace Kratos.

#endif // KRATOS_DEM_APPLICATION_H_INCLUDED  defined 


