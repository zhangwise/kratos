// System includes
#include <iostream>

// External includes
#include<cmath>

// Project includes
#include "includes/properties.h"
#include "custom_constitutive/non_linear_hencky_plastic_plane_strain_2D_law.hpp"

#include "pfem_solid_mechanics_application.h"

//Molt important, el tema de constructors... etc
namespace Kratos
{


NonLinearHenckyElasticPlasticPlaneStrain2DLaw::NonLinearHenckyElasticPlasticPlaneStrain2DLaw()
   : NonLinearHenckyElasticPlastic3DLaw()
{

}

NonLinearHenckyElasticPlasticPlaneStrain2DLaw::NonLinearHenckyElasticPlasticPlaneStrain2DLaw(FlowRulePointer pFlowRule, YieldCriterionPointer pYieldCriterion, HardeningLawPointer pHardeningLaw)
   : NonLinearHenckyElasticPlastic3DLaw()
{

}



// ************* COPY CONSTRUCTOR ******************
NonLinearHenckyElasticPlasticPlaneStrain2DLaw::NonLinearHenckyElasticPlasticPlaneStrain2DLaw(const NonLinearHenckyElasticPlasticPlaneStrain2DLaw&  rOther)
  : NonLinearHenckyElasticPlastic3DLaw(rOther)
{

}


ConstitutiveLaw::Pointer NonLinearHenckyElasticPlasticPlaneStrain2DLaw::Clone() const
{
    NonLinearHenckyElasticPlasticPlaneStrain2DLaw::Pointer p_clone(new NonLinearHenckyElasticPlasticPlaneStrain2DLaw(*this));
    return p_clone;
}
 
NonLinearHenckyElasticPlasticPlaneStrain2DLaw::~NonLinearHenckyElasticPlasticPlaneStrain2DLaw()
{
}

//***********************COMPUTE TOTAL STRAIN*****************************************
//************************************************************************************

void NonLinearHenckyElasticPlasticPlaneStrain2DLaw::CalculateGreenLagrangeStrain( const Matrix & rRightCauchyGreen,
        Vector& rStrainVector )
{

    //E= 0.5*(FT*F-1)
    rStrainVector[0] = 0.5 * ( rRightCauchyGreen( 0, 0 ) - 1.00 );
    rStrainVector[1] = 0.5 * ( rRightCauchyGreen( 1, 1 ) - 1.00 );
    rStrainVector[2] = rRightCauchyGreen( 0, 1 );

}


//***********************COMPUTE TOTAL STRAIN*****************************************
//************************************************************************************

void NonLinearHenckyElasticPlasticPlaneStrain2DLaw::CalculateAlmansiStrain( const Matrix & rLeftCauchyGreen,
        Vector& rStrainVector )
{

    // e= 0.5*(1-invbT*invb)
    Matrix InverseLeftCauchyGreen ( rLeftCauchyGreen.size1() , rLeftCauchyGreen.size2() );
    double det_b=0;
    MathUtils<double>::InvertMatrix( rLeftCauchyGreen, InverseLeftCauchyGreen, det_b);

    rStrainVector.clear();
    rStrainVector[0] = 0.5 * ( 1.0 - InverseLeftCauchyGreen( 0, 0 ) );
    rStrainVector[1] = 0.5 * ( 1.0 - InverseLeftCauchyGreen( 1, 1 ) );
    rStrainVector[2] = -InverseLeftCauchyGreen( 0, 1 );


}


Matrix NonLinearHenckyElasticPlasticPlaneStrain2DLaw::SetConstitutiveMatrixToAppropiateDimension(const Matrix& rElastoPlasticTangentMatrix)
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

//*************************CONSTITUTIVE LAW GENERAL FEATURES *************************
//************************************************************************************
void NonLinearHenckyElasticPlasticPlaneStrain2DLaw::GetLawFeatures(Features& rFeatures)
{
    	//Set the type of law
	rFeatures.mOptions.Set( PLANE_STRAIN_LAW );
	rFeatures.mOptions.Set( FINITE_STRAINS );
	rFeatures.mOptions.Set( ISOTROPIC );

	//Set strain measure required by the consitutive law
	rFeatures.mStrainMeasures.push_back(StrainMeasure_Deformation_Gradient);
	
	//Set the strain size
	rFeatures.mStrainSize = GetStrainSize();

	//Set the spacedimension
	rFeatures.mSpaceDimension = WorkingSpaceDimension();

}



} //end namespace kratos
