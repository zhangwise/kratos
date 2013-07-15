//   
//   Project Name:        KratosSolidMechanicsApplication $      
//   Last modified by:    $Author:            JMCarbonell $ 
//   Date:                $Date:                July 2013 $
//   Revision:            $Revision:                  0.0 $
//
//

#if !defined(KRATOS_SOLID_MECHANICS_APPLICATION_H_INCLUDED )
#define  KRATOS_SOLID_MECHANICS_APPLICATION_H_INCLUDED



// System includes
#include <string>
#include <iostream> 


// External includes 


// Project includes
#include "includes/define.h"
#include "includes/serializer.h"
#include "includes/constitutive_law.h"
#include "includes/kratos_application.h"

//conditions
#include "custom_conditions/point_force_2D_condition.hpp"
#include "custom_conditions/point_force_3D_condition.hpp"
#include "custom_conditions/point_moment_3D_condition.hpp"
#include "custom_conditions/line_force_3D_condition.hpp"
#include "custom_conditions/face_force_2D_condition.hpp"
#include "custom_conditions/face_force_3D_condition.hpp"

//elements
#include "custom_elements/beam_3D_element.hpp"
#include "custom_elements/isotropic_shell_element.hpp"
#include "custom_elements/total_lagrangian_3D_element.hpp"
#include "custom_elements/total_lagrangian_2D_element.hpp"
#include "custom_elements/spatial_lagrangian_3D_element.hpp"
#include "custom_elements/spatial_lagrangian_2D_element.hpp"
#include "custom_elements/updated_lagrangian_3D_element.hpp"
#include "custom_elements/updated_lagrangian_2D_element.hpp"

//constitutive laws
#include "custom_constitutive/linear_elastic_2D_law.hpp"
#include "custom_constitutive/hyperelastic_2D_law.hpp"

#include "containers/flags.h"
#include "includes/variables.h"
#include "includes/ublas_interface.h"

namespace Kratos
{
  ///@name Type	Definitions
  ///@{

  ///@name Kratos Globals
  ///@{ 


  //Define Variables

  //geometrical 
  KRATOS_DEFINE_VARIABLE( double, AREA );
  KRATOS_DEFINE_VARIABLE( double, IX );
  KRATOS_DEFINE_VARIABLE( double, IY );
  KRATOS_DEFINE_VARIABLE( double, IZ );
  KRATOS_DEFINE_VARIABLE( double, CROSS_AREA );
  KRATOS_DEFINE_VARIABLE( Matrix , GEOMETRIC_STIFFNESS );

  //constitutive law   
  KRATOS_DEFINE_VARIABLE(std::string, CONSTITUTIVE_LAW_NAME );
  KRATOS_DEFINE_VARIABLE(ConstitutiveLaw::Pointer, CONSTITUTIVE_LAW_POINTER );
  KRATOS_DEFINE_VARIABLE(Matrix, CONSTITUTIVE_MATRIX );
  KRATOS_DEFINE_VARIABLE(Matrix, DEFORMATION_GRADIENT );
  KRATOS_DEFINE_VARIABLE(double, DETERMINANT_F );
  KRATOS_DEFINE_VARIABLE(bool,   AXISYMMETRIC_LAW  );

  //material : hyperelastic_plastic
  KRATOS_DEFINE_VARIABLE(double, NORM_ISOCHORIC_STRESS );
  KRATOS_DEFINE_VARIABLE(double, PLASTIC_STRAIN );
  KRATOS_DEFINE_VARIABLE(double, DELTA_PLASTIC_STRAIN );
  KRATOS_DEFINE_VARIABLE(double, PLASTIC_POWER );
  KRATOS_DEFINE_VARIABLE(double, KINEMATIC_HARDENING );
  KRATOS_DEFINE_VARIABLE(double, HARDENING_EXPONENT );
  KRATOS_DEFINE_VARIABLE(double, REFERENCE_HARDENING );
  KRATOS_DEFINE_VARIABLE(double, INFINITY_HARDENING );

  //element
  //KRATOS_DEFINE_VARIABLE(Matrix, CAUCHY_STRESS_TENSOR );
  //KRATOS_DEFINE_VARIABLE(Matrix, PK2_STRESS_TENSOR );
  KRATOS_DEFINE_VARIABLE(Vector, CAUCHY_STRESS_VECTOR );
  KRATOS_DEFINE_VARIABLE(Vector, PK2_STRESS_VECTOR );

  //KRATOS_DEFINE_VARIABLE(Matrix, GREEN_LAGRANGE_STRAIN_TENSOR );
  KRATOS_DEFINE_VARIABLE(Matrix, ALMANSI_STRAIN_TENSOR );
  KRATOS_DEFINE_VARIABLE(Vector, GREEN_LAGRANGE_STRAIN_VECTOR );
  KRATOS_DEFINE_VARIABLE(Vector, ALMANSI_STRAIN_VECTOR );

  KRATOS_DEFINE_VARIABLE(double, VON_MISES_STRESS );


  //mechanical
  KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS( FORCE_INTERNAL );
  KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS( FORCE_EXTERNAL );
  KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS( FORCE_DYNAMIC );

  //nodal dofs
  KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS( IMPOSED_DISPLACEMENT );
  KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS( IMPOSED_ROTATION );


  //flags
  KRATOS_DEFINE_FLAG( FLUID );
  KRATOS_DEFINE_FLAG( STRUCTURE );
  KRATOS_DEFINE_FLAG( SOLID );
  KRATOS_DEFINE_FLAG( RIGID );
  KRATOS_DEFINE_FLAG( CONTACT );
    
  KRATOS_DEFINE_FLAG( BOUNDARY );
  KRATOS_DEFINE_FLAG( FREE_SURFACE );    
   
  KRATOS_DEFINE_FLAG( INTERFACE );
    
  KRATOS_DEFINE_FLAG( ENGAGED );
  KRATOS_DEFINE_FLAG( ISOLATED );
    
  KRATOS_DEFINE_FLAG( REFINE );
  KRATOS_DEFINE_FLAG( INSERTED );
  KRATOS_DEFINE_FLAG( RELEASE );


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
  class KratosSolidMechanicsApplication : public KratosApplication
  {
  public:


    ///@name Type Definitions
    ///@{
		

    /// Pointer definition of KratosSolidMechanicsApplication
    KRATOS_CLASS_POINTER_DEFINITION(KratosSolidMechanicsApplication);


    ///@}
    ///@name Life Cycle 
    ///@{ 

    /// Default constructor.
    KratosSolidMechanicsApplication();

    /// Destructor.
    virtual ~KratosSolidMechanicsApplication(){}


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
	return "KratosSolidMechanicsApplication";
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
      KRATOS_WATCH("in my application");
      KRATOS_WATCH(KratosComponents<VariableData>::GetComponents().size() );
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



    //       static const ApplicationCondition  msApplicationCondition; 

    ///@} 
    ///@name Member Variables 
    ///@{ 

    //beams

    const Beam3DElement mBeamElement3D2N;


    //shells

    const IsotropicShellElement  mIsotropicShellElement3D3N;

    //solid 

    const TotalLagrangian2DElement mTotalLagrangianElement2D3N;
    const TotalLagrangian2DElement mTotalLagrangianElement2D4N;
    const TotalLagrangian2DElement mTotalLagrangianElement2D6N;
    const TotalLagrangian2DElement mTotalLagrangianElement2D8N;

    const TotalLagrangian3DElement mTotalLagrangianElement3D4N;
    const TotalLagrangian3DElement mTotalLagrangianElement3D6N;
    const TotalLagrangian3DElement mTotalLagrangianElement3D8N;
    const TotalLagrangian3DElement mTotalLagrangianElement3D10N;
    const TotalLagrangian3DElement mTotalLagrangianElement3D15N;
    const TotalLagrangian3DElement mTotalLagrangianElement3D20N;
    const TotalLagrangian3DElement mTotalLagrangianElement3D27N;

 
    const PointForce2DCondition    mPointForce2DCondition;
    const PointForce3DCondition    mPointForce3DCondition;
    const PointMoment3DCondition   mPointMoment3DCondition;

    const LineForce3DCondition    mLineForceCondition3D2N;

    const FaceForce2DCondition    mFaceForceCondition2D2N;

    const FaceForce3DCondition    mFaceForceCondition3D3N;
    const FaceForce3DCondition    mFaceForceCondition3D6N;
    const FaceForce3DCondition    mFaceForceCondition3D4N;
    const FaceForce3DCondition    mFaceForceCondition3D8N;
    const FaceForce3DCondition    mFaceForceCondition3D9N;

    const LinearElastic2DLaw          mLinearElastic2DLaw;
    const HyperElastic2DLaw            mHyperElastic2DLaw;

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
    KratosSolidMechanicsApplication& operator=(KratosSolidMechanicsApplication const& rOther);

    /// Copy constructor.
    KratosSolidMechanicsApplication(KratosSolidMechanicsApplication const& rOther);


    ///@}    

  }; // Class KratosSolidMechanicsApplication 

  ///@} 


  ///@name Type Definitions       
  ///@{ 


  ///@} 
  ///@name Input and output 
  ///@{ 

  ///@} 


}  // namespace Kratos.

#endif // KRATOS_SOLID_MECHANICS_APPLICATION_H_INCLUDED  defined 


