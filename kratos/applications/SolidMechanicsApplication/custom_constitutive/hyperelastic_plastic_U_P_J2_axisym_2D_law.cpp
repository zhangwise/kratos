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
#include "custom_constitutive/custom_flow_rules/linear_associative_plastic_flow_rule.hpp"
#include "custom_constitutive/custom_yield_criteria/mises_huber_yield_criterion.hpp"
#include "custom_constitutive/custom_hardening_laws/linear_isotropic_kinematic_hardening_law.hpp"
#include "custom_constitutive/hyperelastic_plastic_J2_plane_strain_2D_law.hpp"

#include "solid_mechanics_application.h"

namespace Kratos
{

//******************************CONSTRUCTOR*******************************************
//************************************************************************************

HyperElasticPlasticUPJ2Axisym2DLaw::HyperElasticPlasticUPJ2Axisym2DLaw()
    : HyperElasticPlasticUPAxisym2DLaw()
{
  mpFlowRule       = FlowRule::Pointer( new LinearAssociativePlasticFlowRule() );
  mpYieldCriterion = YieldCriterion::Pointer( new MisesHuberYieldCriterion() );
  mpHardeningLaw   = HardeningLaw::Pointer( new NonLinearIsotropicKinematicHardeningLaw() );
}


//******************************CONSTRUCTOR*******************************************
//************************************************************************************

HyperElasticPlasticUPJ2Axisym2DLaw::HyperElasticPlasticUPJ2Axisym2DLaw(FlowRulePointer pFlowRule, YieldCriterionPointer pYieldCriterion, HardeningLawPointer pHardeningLaw)
{
  mpFlowRule        =  pFlowRule;
  mpYieldCriterion  =  YieldCriterion::Pointer( new MisesHuberYieldCriterion() );
  mpHardeningLaw    =  pHardeningLaw;
}

//******************************COPY CONSTRUCTOR**************************************
//************************************************************************************

HyperElasticPlasticUPJ2Axisym2DLaw::HyperElasticPlasticUPJ2Axisym2DLaw(const HyperElasticPlasticUPJ2Axisym2DLaw& rOther)
    : HyperElasticPlasticUPAxisym2DLaw(rOther)
{

}

//********************************CLONE***********************************************
//************************************************************************************

ConstitutiveLaw::Pointer HyperElasticPlasticUPJ2Axisym2DLaw::Clone() const
{
    HyperElasticPlasticUPJ2Axisym2DLaw::Pointer p_clone(new HyperElasticPlasticUPJ2Axisym2DLaw(*this));
    return p_clone;
}

//*******************************DESTRUCTOR*******************************************
//************************************************************************************

HyperElasticPlasticUPJ2Axisym2DLaw::~HyperElasticPlasticUPJ2Axisym2DLaw()
{
}


} // Namespace Kratos
