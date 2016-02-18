//   
//   Project Name:        KratosPoromechanicsApplication $
//   Last Modified by:    $Author:    Ignasi de Pouplana $
//   Date:                $Date:            January 2016 $
//   Revision:            $Revision:                 1.0 $
//

#if !defined(KRATOS_SMALL_STRAIN_U_PW_ELEMENT_H_INCLUDED )
#define  KRATOS_SMALL_STRAIN_U_PW_ELEMENT_H_INCLUDED

/* External includes */
#include "boost/smart_ptr.hpp"

/* Project includes */
#include "includes/define.h"
#include "includes/element.h"
#include "includes/serializer.h"
#include "includes/ublas_interface.h"
#include "includes/variables.h"
#include "includes/constitutive_law.h"
#include "custom_utilities/element_utilities.hpp"

namespace Kratos
{

class SmallStrainUPwElement : public Element
{

public:

    KRATOS_CLASS_POINTER_DEFINITION( SmallStrainUPwElement );
    
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // Default constructor
    SmallStrainUPwElement();
    
    // Constructor 1
    SmallStrainUPwElement(IndexType NewId, GeometryType::Pointer pGeometry);
    
    // Constructor 2
    SmallStrainUPwElement(IndexType NewId, GeometryType::Pointer pGeometry, PropertiesType::Pointer pProperties);
    
    // Destructor
    virtual ~SmallStrainUPwElement();

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    Element::Pointer Create(IndexType NewId, NodesArrayType const& ThisNodes, PropertiesType::Pointer pProperties) const;

    int Check(const ProcessInfo& rCurrentProcessInfo);

    void Initialize();
    
    void GetDofList(DofsVectorType& rElementalDofList, ProcessInfo& rCurrentProcessInfo);
    
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    void CalculateLocalSystem(MatrixType& rLeftHandSideMatrix, VectorType& rRightHandSideVector, ProcessInfo& rCurrentProcessInfo);

    void CalculateMassMatrix(MatrixType& rMassMatrix, ProcessInfo& rCurrentProcessInfo);

    void EquationIdVector(EquationIdVectorType& rResult, ProcessInfo& rCurrentProcessInfo);

    void GetSecondDerivativesVector(Vector& rValues, int Step = 0);

    void CalculateRightHandSide(VectorType& rRightHandSideVector, ProcessInfo& rCurrentProcessInfo);
    
    void FinalizeSolutionStep(ProcessInfo& rCurrentProcessInfo);
    
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    void SetValueOnIntegrationPoints(const Variable<double>& rVariable, std::vector<double>& rValues, const ProcessInfo& rCurrentProcessInfo);
    
    void SetValueOnIntegrationPoints(const Variable<Vector>& rVariable, std::vector<Vector>& rValues, const ProcessInfo& rCurrentProcessInfo);
    
    void SetValueOnIntegrationPoints(const Variable<Matrix>& rVariable, std::vector<Matrix>& rValues, const ProcessInfo& rCurrentProcessInfo);

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    void GetValueOnIntegrationPoints(const Variable<double>& rVariable, std::vector<double>& rValues, const ProcessInfo& rCurrentProcessInfo);
    
    void GetValueOnIntegrationPoints(const Variable<Vector>& rVariable, std::vector<Vector>& rValues, const ProcessInfo& rCurrentProcessInfo);
    
    void GetValueOnIntegrationPoints(const Variable<Matrix>& rVariable, std::vector<Matrix>& rValues, const ProcessInfo& rCurrentProcessInfo);
    
    void GetValueOnIntegrationPoints( const Variable<ConstitutiveLaw::Pointer>& rVariable, std::vector<ConstitutiveLaw::Pointer>& rValues,const ProcessInfo& rCurrentProcessInfo );

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    void CalculateOnIntegrationPoints(const Variable<double>& rVariable, std::vector<double>& rOutput, const ProcessInfo& rCurrentProcessInfo);

    void CalculateOnIntegrationPoints(const Variable<Vector>& rVariable, std::vector<Vector>& rOutput, const ProcessInfo& rCurrentProcessInfo);
    
    void CalculateOnIntegrationPoints(const Variable<Matrix >& rVariable, std::vector< Matrix >& rOutput, const ProcessInfo& rCurrentProcessInfo);
    
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

protected:

    struct ElementalVariables
    {
        //Variables at all integration points
        Matrix NContainer;
        GeometryType::ShapeFunctionsGradientsType DN_DXContainer;
        Vector detJContainer;

        //Variables at each integration point
        Vector Np; //Contains the shape functions at every node
        Matrix GradNpT; //Contains the derivatives of the shape functions
        Matrix B;
        double IntegrationCoefficient;
        Vector StrainVector;
        Matrix ConstitutiveMatrix;
        Vector StressVector; //It is the "Effective Stress Vector": sigma'_ij = sigma_ij + alpha*pw*delta_ij
        
        //Variables needed for consistency with the general constitutive law
        double detF;
        Matrix F;
        
        //Nodal variables
        Vector BodyAcceleration;
        Vector DisplacementVector;
        Vector VelocityVector;
        Vector PressureVector;
        Vector PressureDtVector;
        
        //Properties and processinfo variables
        double BiotCoefficient;
        double BiotModulusInverse;
        double DynamicViscosity;
        Matrix IntrinsicPermeability;
        double NewmarkCoefficient1;
        double NewmarkCoefficient2;
        
        //FIC element variables
        double ShearModulus;
        double ElementLength;
        bool SecondOrderStrainDerivatives;
        std::vector<Vector> NodalShapeFunctionsDerivatives; //Contains the vector of nodal shape function derivatives for every shape function
        std::vector<Vector> ShapeFunctionsSecondOrderDerivatives; //Contains the vector of shape function second order derivatives for every shape function
        Matrix StrainDerivativeTerm;
    };
    
    // Member Variables
    
    GeometryData::IntegrationMethod mThisIntegrationMethod;

    std::vector<ConstitutiveLaw::Pointer> mConstitutiveLawVector;
    
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    void CalculateAll(MatrixType& rLeftHandSideMatrix, VectorType& rRightHandSideVector, ProcessInfo& rCurrentProcessInfo, 
                                bool CalculateLHSMatrixFlag, bool CalculateResidualVectorFlag);

    virtual void InitializeElementalVariables (ElementalVariables& rVariables, const ProcessInfo& rCurrentProcessInfo);
    
    void InitializeNodalVariables (ElementalVariables& rVariables);
    
    void InitializeProperties (ElementalVariables& rVariables);
    
    virtual void CalculateKinematics(ElementalVariables& rVariables, unsigned int PointNumber);

    void SetElementalVariables(ElementalVariables& rVariables,ConstitutiveLaw::Parameters& rConstitutiveParameters);
    
    void CalculateIntegrationCoefficient(double& rIntegrationCoefficient, double detJ, double weight);


    virtual void CalculateAndAddLHS(MatrixType& rLeftHandSideMatrix, ElementalVariables& rVariables);
    
    void CalculateAndAddStiffnessMatrix(MatrixType& rLeftHandSideMatrix, ElementalVariables& rVariables);
    
    void CalculateAndAddCouplingMatrix(MatrixType& rLeftHandSideMatrix, ElementalVariables& rVariables);
    
    void CalculateAndAddCompressibilityMatrix(MatrixType& rLeftHandSideMatrix, ElementalVariables& rVariables);
    
    void CalculateAndAddPermeabilityMatrix(MatrixType& rLeftHandSideMatrix, ElementalVariables& rVariables);
    
    
    virtual void CalculateAndAddRHS(VectorType& rRightHandSideVector, ElementalVariables& rVariables);
    
    void CalculateAndAddStiffnessForce(VectorType& rRightHandSideVector, ElementalVariables& rVariables);
    
    void CalculateAndAddMixBodyForce(VectorType& rRightHandSideVector, ElementalVariables& rVariables);
    
    void CalculateAndAddCouplingTerms(VectorType& rRightHandSideVector, ElementalVariables& rVariables);
    
    void CalculateAndAddCompressibilityFlow(VectorType& rRightHandSideVector, ElementalVariables& rVariables);
    
    void CalculateAndAddPermeabilityFlow(VectorType& rRightHandSideVector, ElementalVariables& rVariables);
    
    void CalculateAndAddFluidBodyFlow(VectorType& rRightHandSideVector, ElementalVariables& rVariables);
    
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

private:
    
    // Serialization
    
    friend class Serializer;
    
    virtual void save(Serializer& rSerializer) const
    {
        KRATOS_SERIALIZE_SAVE_BASE_CLASS( rSerializer, Element )
    }

    virtual void load(Serializer& rSerializer)
    {
        KRATOS_SERIALIZE_LOAD_BASE_CLASS( rSerializer, Element )
    }
    
    
}; // Class SmallStrainUPwElement

} // namespace Kratos

#endif // KRATOS_SMALL_STRAIN_U_PW_ELEMENT_H_INCLUDED  defined 
