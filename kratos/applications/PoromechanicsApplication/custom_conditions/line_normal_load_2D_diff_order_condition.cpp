//   
//   Project Name:        KratosPoromechanicsApplication $
//   Last Modified by:    $Author:    Ignasi de Pouplana $
//   Date:                $Date:            January 2016 $
//   Revision:            $Revision:                 1.0 $
//

// Project includes
#include "custom_conditions/line_normal_load_2D_diff_order_condition.hpp"

#include "poromechanics_application.h"

namespace Kratos
{

// Default Constructor
LineNormalLoad2DDiffOrderCondition::LineNormalLoad2DDiffOrderCondition() : GeneralUPwDiffOrderCondition() {}

//----------------------------------------------------------------------------------------

//Constructor 1
LineNormalLoad2DDiffOrderCondition::LineNormalLoad2DDiffOrderCondition(IndexType NewId, GeometryType::Pointer pGeometry) : GeneralUPwDiffOrderCondition(NewId, pGeometry) {}

//----------------------------------------------------------------------------------------

//Constructor 2
LineNormalLoad2DDiffOrderCondition::LineNormalLoad2DDiffOrderCondition(IndexType NewId, GeometryType::Pointer pGeometry, PropertiesType::Pointer pProperties) : GeneralUPwDiffOrderCondition(NewId, pGeometry, pProperties) {}

//----------------------------------------------------------------------------------------

//Destructor
LineNormalLoad2DDiffOrderCondition::~LineNormalLoad2DDiffOrderCondition() {}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Condition::Pointer LineNormalLoad2DDiffOrderCondition::Create(IndexType NewId, NodesArrayType const& ThisNodes, PropertiesType::Pointer pProperties) const
{
    return Condition::Pointer(new LineNormalLoad2DDiffOrderCondition(NewId, GetGeometry().Create(ThisNodes), pProperties));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void LineNormalLoad2DDiffOrderCondition::CalculateConditionVector(ConditionVariables& rVariables, unsigned int PointNumber)
{
    KRATOS_TRY

    const SizeType NumUNodes = GetGeometry().PointsNumber();
    double NormalStress = 0;
    double TangentialStress = 0;
    double dx_dxi = rVariables.JContainer[PointNumber](0,0), dy_dxi = rVariables.JContainer[PointNumber](1,0);
    rVariables.ConditionVector = ZeroVector(2);

    for ( SizeType i = 0; i < NumUNodes; i++ )
    {
        NormalStress     += rVariables.Nu[i]*GetGeometry()[i].FastGetSolutionStepValue(NORMAL_CONTACT_STRESS);
        TangentialStress += rVariables.Nu[i]*GetGeometry()[i].FastGetSolutionStepValue(TANGENTIAL_CONTACT_STRESS);
    }

    rVariables.ConditionVector[0] = TangentialStress * dx_dxi - NormalStress     * dy_dxi;
    rVariables.ConditionVector[1] = NormalStress     * dx_dxi + TangentialStress * dy_dxi;

    KRATOS_CATCH( "" )
}

//----------------------------------------------------------------------------------------

void LineNormalLoad2DDiffOrderCondition::CalculateIntegrationCoefficient(ConditionVariables& rVariables, unsigned int PointNumber, double weight)
{
    KRATOS_TRY

    rVariables.IntegrationCoefficient = GetProperties()[THICKNESS] * weight;

    KRATOS_CATCH( "" )
}

//----------------------------------------------------------------------------------------

void LineNormalLoad2DDiffOrderCondition::CalculateAndAddConditionForce(VectorType& rRightHandSideVector, ConditionVariables& rVariables)
{
    const SizeType NumUNodes = GetGeometry().PointsNumber();
    SizeType Index;

    for ( SizeType i = 0; i < NumUNodes; i++ )
    {
        Index = i * 2;
        
        rRightHandSideVector[Index]   += rVariables.Nu[i] * rVariables.ConditionVector[0] * rVariables.IntegrationCoefficient;
        rRightHandSideVector[Index+1] += rVariables.Nu[i] * rVariables.ConditionVector[1] * rVariables.IntegrationCoefficient;
    }
}

} // Namespace Kratos.
