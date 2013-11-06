//
//   Project Name:        KratosSolidMechanicsApplication $
//   Last modified by:    $Author:            JMCarbonell $
//   Date:                $Date:                July 2013 $
//   Revision:            $Revision:                  0.0 $
//
//

// System includes
#include <iostream>

// External includes
#include<cmath>

// Project includes
#include "includes/properties.h"
#include "custom_constitutive/hyperelastic_plastic_U_P_plane_strain_2D_law.hpp"

#include "solid_mechanics_application.h"

namespace Kratos
{

//******************************CONSTRUCTOR*******************************************
//************************************************************************************

HyperElasticPlasticUPPlaneStrain2DLaw::HyperElasticPlasticUPPlaneStrain2DLaw()
    : HyperElasticPlasticUP3DLaw()
{

}


//******************************CONSTRUCTOR*******************************************
//************************************************************************************

HyperElasticPlasticUPPlaneStrain2DLaw::HyperElasticPlasticUPPlaneStrain2DLaw(FlowRulePointer pFlowRule, YieldCriterionPointer pYieldCriterion, HardeningLawPointer pHardeningLaw)
    : HyperElasticPlasticUP3DLaw()
{
}

//******************************COPY CONSTRUCTOR**************************************
//************************************************************************************

HyperElasticPlasticUPPlaneStrain2DLaw::HyperElasticPlasticUPPlaneStrain2DLaw(const HyperElasticPlasticUPPlaneStrain2DLaw& rOther)
    : HyperElasticPlasticUP3DLaw(rOther)
{

}

//********************************CLONE***********************************************
//************************************************************************************

ConstitutiveLaw::Pointer HyperElasticPlasticUPPlaneStrain2DLaw::Clone() const
{
    HyperElasticPlasticUPPlaneStrain2DLaw::Pointer p_clone(new HyperElasticPlasticUPPlaneStrain2DLaw(*this));
    return p_clone;
}

//*******************************DESTRUCTOR*******************************************
//************************************************************************************

HyperElasticPlasticUPPlaneStrain2DLaw::~HyperElasticPlasticUPPlaneStrain2DLaw()
{
}



//************* COMPUTING  METHODS
//************************************************************************************
//************************************************************************************

//***********************COMPUTE TOTAL STRAIN*****************************************
//************************************************************************************

void HyperElasticPlasticUPPlaneStrain2DLaw::CalculateGreenLagrangeStrain( const Matrix & rRightCauchyGreen,
        Vector& rStrainVector )
{

    //E= 0.5*(FT*F-1)
    rStrainVector[0] = 0.5 * ( rRightCauchyGreen( 0, 0 ) - 1.00 );
    rStrainVector[1] = 0.5 * ( rRightCauchyGreen( 1, 1 ) - 1.00 );
    rStrainVector[2] = rRightCauchyGreen( 0, 1 );

}


//***********************COMPUTE TOTAL STRAIN*****************************************
//************************************************************************************

void HyperElasticPlasticUPPlaneStrain2DLaw::CalculateAlmansiStrain( const Matrix & rLeftCauchyGreen,
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


//***********************COMPUTE ISOCHORIC CONSTITUTIVE MATRIX************************
//************************************************************************************

void HyperElasticPlasticUPPlaneStrain2DLaw::CalculateIsochoricConstitutiveMatrix (const MaterialResponseVariables & rElasticVariables,
        const Matrix & rIsoStressMatrix,
        Matrix& rConstitutiveMatrix)
{

    rConstitutiveMatrix.clear();


    for(unsigned int i=0; i<3; i++)
    {
        for(unsigned int j=0; j<3; j++)
        {
            rConstitutiveMatrix( i, j ) = IsochoricConstitutiveComponent(rConstitutiveMatrix( i, j ), rElasticVariables, rIsoStressMatrix,
                                          this->msIndexVoigt2D3C[i][0], this->msIndexVoigt2D3C[i][1], this->msIndexVoigt2D3C[j][0], this->msIndexVoigt2D3C[j][1]);
        }

    }


}

//***********************COMPUTE VOLUMETRIC CONSTITUTIVE MATRIX***********************
//************************************************************************************


void HyperElasticPlasticUPPlaneStrain2DLaw::CalculateVolumetricConstitutiveMatrix ( const MaterialResponseVariables & rElasticVariables,
								  Matrix& rConstitutiveMatrix)
{

    rConstitutiveMatrix.clear();


    Vector Factors = ZeroVector(3);
    Factors = CalculateDomainPressureFactors( rElasticVariables, Factors );

    for(unsigned int i=0; i<3; i++)
    {
        for(unsigned int j=0; j<3; j++)
        {
            rConstitutiveMatrix( i, j ) = VolumetricConstitutiveComponent(rConstitutiveMatrix( i, j ), rElasticVariables, Factors,
                                          this->msIndexVoigt2D3C[i][0], this->msIndexVoigt2D3C[i][1], this->msIndexVoigt2D3C[j][0], this->msIndexVoigt2D3C[j][1]);
        }

    }


}


//***********************COMPUTE PLASTIC CONSTITUTIVE MATRIX**************************
//************************************************************************************

void HyperElasticPlasticUPPlaneStrain2DLaw::CalculatePlasticConstitutiveMatrix (const MaterialResponseVariables & rElasticVariables,
									      FlowRule::RadialReturnVariables & rReturnMappingVariables,
									      Matrix& rConstitutiveMatrix)
{

    rConstitutiveMatrix.clear();

    Matrix IsoStressMatrix = rReturnMappingVariables.TrialIsoStressMatrix;

    //std::cout<< " TrialStressMatrix 2D "<<IsoStressMatrix<<std::endl;

    FlowRule::PlasticFactors ScalingFactors;
    mpFlowRule->CalculateScalingFactors( rReturnMappingVariables, ScalingFactors );

    for(unsigned int i=0; i<3; i++)
    {
        for(unsigned int j=0; j<3; j++)
        {
		rConstitutiveMatrix( i, j ) = PlasticConstitutiveComponent(rConstitutiveMatrix( i, j ), rElasticVariables, IsoStressMatrix, ScalingFactors,
                                          this->msIndexVoigt2D3C[i][0], this->msIndexVoigt2D3C[i][1], this->msIndexVoigt2D3C[j][0], this->msIndexVoigt2D3C[j][1]);
        }

    }


}



//***********************COMPUTE ISOCHORIC CONSTITUTIVE MATRIX PULL-BACK**************
//************************************************************************************

void HyperElasticPlasticUPPlaneStrain2DLaw::CalculateIsochoricConstitutiveMatrix (const MaterialResponseVariables & rElasticVariables,
								     const Matrix & rInverseDeformationGradientF,
								     const Matrix & rIsoStressMatrix,
								     Matrix& rConstitutiveMatrix)
{

    rConstitutiveMatrix.clear();

    for(unsigned int i=0; i<3; i++)
    {
        for(unsigned int j=0; j<3; j++)
        {
	  rConstitutiveMatrix( i, j ) = IsochoricConstitutiveComponent(rConstitutiveMatrix( i, j ), rElasticVariables, rInverseDeformationGradientF, rIsoStressMatrix,
                                          this->msIndexVoigt2D3C[i][0], this->msIndexVoigt2D3C[i][1], this->msIndexVoigt2D3C[j][0], this->msIndexVoigt2D3C[j][1]);
        }

    }


}

//***********************COMPUTE VOLUMETRIC CONSTITUTIVE MATRIX PULL-BACK*************
//************************************************************************************


void HyperElasticPlasticUPPlaneStrain2DLaw::CalculateVolumetricConstitutiveMatrix ( const MaterialResponseVariables & rElasticVariables,
								       const Matrix & rInverseDeformationGradientF,
								       Matrix& rConstitutiveMatrix)
{

    rConstitutiveMatrix.clear();

    Vector Factors = ZeroVector(3);
    Factors = CalculateDomainPressureFactors( rElasticVariables, Factors );

    for(unsigned int i=0; i<3; i++)
    {
        for(unsigned int j=0; j<3; j++)
        {
	  rConstitutiveMatrix( i, j ) = VolumetricConstitutiveComponent(rConstitutiveMatrix( i, j ), rElasticVariables, rInverseDeformationGradientF, Factors,
                                          this->msIndexVoigt2D3C[i][0], this->msIndexVoigt2D3C[i][1], this->msIndexVoigt2D3C[j][0], this->msIndexVoigt2D3C[j][1]);
        }

    }


}


//***********************COMPUTE PLASTIC CONSTITUTIVE MATRIX PULL-BACK****************
//************************************************************************************

void HyperElasticPlasticUPPlaneStrain2DLaw::CalculatePlasticConstitutiveMatrix (const MaterialResponseVariables & rElasticVariables,
								   const Matrix & rInverseDeformationGradientF,
								   FlowRule::RadialReturnVariables & rReturnMappingVariables,
								   Matrix& rConstitutiveMatrix)
{

    rConstitutiveMatrix.clear();

    Matrix IsoStressMatrix = rReturnMappingVariables.TrialIsoStressMatrix;

    FlowRule::PlasticFactors ScalingFactors;
    mpFlowRule->CalculateScalingFactors( rReturnMappingVariables, ScalingFactors );


    for(unsigned int i=0; i<3; i++)
    {
        for(unsigned int j=0; j<3; j++)
        {
	  rConstitutiveMatrix( i, j ) = PlasticConstitutiveComponent(rConstitutiveMatrix( i, j ), rElasticVariables, rInverseDeformationGradientF, IsoStressMatrix, ScalingFactors,
									   this->msIndexVoigt2D3C[i][0], this->msIndexVoigt2D3C[i][1], this->msIndexVoigt2D3C[j][0], this->msIndexVoigt2D3C[j][1]);
        }

    }


}

//*************************CONSTITUTIVE LAW GENERAL FEATURES *************************
//************************************************************************************

void HyperElasticPlasticUPPlaneStrain2DLaw::GetLawFeatures(Features& rFeatures)
{
    	//Set the type of law
	rFeatures.mOptions.Set( PLANE_STRAIN_LAW );
	rFeatures.mOptions.Set( FINITE_STRAINS );
	rFeatures.mOptions.Set( ISOTROPIC );
	rFeatures.mOptions.Set( U_P_LAW );

	//Set strain measure required by the consitutive law
	rFeatures.mStrainMeasures.push_back(StrainMeasure_Deformation_Gradient);
	
	//Set the strain size
	rFeatures.mStrainSize = GetStrainSize();

	//Set the spacedimension
	rFeatures.mSpaceDimension = WorkingSpaceDimension();

}



} // Namespace Kratos
