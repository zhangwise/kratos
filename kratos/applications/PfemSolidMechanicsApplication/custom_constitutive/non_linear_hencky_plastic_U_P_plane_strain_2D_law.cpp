// System includes
#include <iostream>

// External includes
#include<cmath>

// Project includes
#include "includes/properties.h"
#include "custom_constitutive/hyperelastic_plastic_3D_law.hpp"

#include "custom_constitutive/non_linear_hencky_plastic_U_P_3D_law.hpp"
#include "custom_constitutive/non_linear_hencky_plastic_U_P_plane_strain_2D_law.hpp"
#include "solid_mechanics_application.h"

namespace Kratos
{



// CONSTRUCTORS
NonLinearHenckyElasticPlasticUPPlaneStrain2DLaw::NonLinearHenckyElasticPlasticUPPlaneStrain2DLaw()
   : NonLinearHenckyElasticPlasticUP3DLaw()
{

}

NonLinearHenckyElasticPlasticUPPlaneStrain2DLaw::NonLinearHenckyElasticPlasticUPPlaneStrain2DLaw(FlowRulePointer pFlowRule, YieldCriterionPointer pYieldCriterion, HardeningLawPointer pHardeningLaw)
   : NonLinearHenckyElasticPlasticUP3DLaw()
{

}

// ************* COPY CONSTRUCTOR ******************
NonLinearHenckyElasticPlasticUPPlaneStrain2DLaw::NonLinearHenckyElasticPlasticUPPlaneStrain2DLaw(const NonLinearHenckyElasticPlasticUPPlaneStrain2DLaw&  rOther)
  : NonLinearHenckyElasticPlasticUP3DLaw(rOther)
{

}

 
NonLinearHenckyElasticPlasticUPPlaneStrain2DLaw::~NonLinearHenckyElasticPlasticUPPlaneStrain2DLaw()
{
}






// I HAVE TO DELETE THE DEFINITION FROM THE HPP IN ORDER TO REMOVE THE TO FOLLOWING FUNCTIONS; THAT ARE COPY PASTE; THEY ARE ALREADY DEFINED BY INHERITANCE !!!!
void NonLinearHenckyElasticPlasticUPPlaneStrain2DLaw::CalculateGreenLagrangeStrain( const Matrix & rRightCauchyGreen,
        Vector& rStrainVector )
{

    //E= 0.5*(FT*F-1)
    rStrainVector[0] = 0.5 * ( rRightCauchyGreen( 0, 0 ) - 1.00 );
    rStrainVector[1] = 0.5 * ( rRightCauchyGreen( 1, 1 ) - 1.00 );
    rStrainVector[2] = rRightCauchyGreen( 0, 1 );

}



//***********************COMPUTE TOTAL STRAIN*****************************************
//************************************************************************************
void NonLinearHenckyElasticPlasticUPPlaneStrain2DLaw::CalculateAlmansiStrain( const Matrix & rLeftCauchyGreen,
        Vector& rStrainVector )
{

    // e = 0.5*(1-invFT*invF) or e = 0.5*(1-inv(b))

    //Calculating the inverse of the jacobian
    Matrix InverseLeftCauchyGreen ( rLeftCauchyGreen.size1() , rLeftCauchyGreen.size2() );
    double det_b=0;
    MathUtils<double>::InvertMatrix( rLeftCauchyGreen, InverseLeftCauchyGreen, det_b);

    rStrainVector.clear();
    rStrainVector[0] = 0.5 * ( 1.0 - InverseLeftCauchyGreen( 0, 0 ) );
    rStrainVector[1] = 0.5 * ( 1.0 - InverseLeftCauchyGreen( 1, 1 ) );
    rStrainVector[2] = -InverseLeftCauchyGreen( 0, 1 );
}


Matrix NonLinearHenckyElasticPlasticUPPlaneStrain2DLaw::SetConstitutiveMatrixToAppropiateDimension(const Matrix& rElastoPlasticTangentMatrix)
{
     Matrix Result = ZeroMatrix(3);

     Result(0, 0) = rElastoPlasticTangentMatrix(0, 0);
     Result(0, 1) = rElastoPlasticTangentMatrix(0, 1);
     Result(1, 0) = rElastoPlasticTangentMatrix(1, 0);
     Result(1, 1) = rElastoPlasticTangentMatrix(1, 1);


     Result(2, 0) = rElastoPlasticTangentMatrix(3, 0);
     Result(2, 1) = rElastoPlasticTangentMatrix(3, 1);
     Result(2, 2) = rElastoPlasticTangentMatrix(3, 3);


     Result(0, 2) = rElastoPlasticTangentMatrix(0, 3);
     Result(1, 2) = rElastoPlasticTangentMatrix(1, 3);


     return Result;

}




} //end namespace kratos

