//
//   Project Name:        KratosPfemSolidMechanicsApplication $
//   Last modified by:    $Author:                JMCarbonell $
//   Date:                $Date:                    July 2013 $
//   Revision:            $Revision:                      0.0 $
//
//

#if !defined(KRATOS_CONTACT_DOMAIN_CONDITION_H_INCLUDED )
#define  KRATOS_CONTACT_DOMAIN_CONDITION_H_INCLUDED


// System includes
#include <iostream>
#include <iomanip>

// External includes
#include "boost/smart_ptr.hpp"


// Project includes
#include "utilities/math_utils.h"
#include "includes/define.h"
#include "includes/element.h"
#include "includes/serializer.h"
#include "includes/ublas_interface.h"
#include "includes/variables.h"
#include "includes/constitutive_law.h"

#include "includes/condition.h"

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


class ContactDomainCondition
    : public Condition
{
public:


    ///@name Type Definitions
    ///@{
    ///Reference type definition for constitutive laws
    typedef ConstitutiveLaw ConstitutiveLawType;
    ///Pointer type for constitutive laws
    typedef ConstitutiveLawType::Pointer ConstitutiveLawPointerType;
    ///Type definition for integration methods
    typedef GeometryData::IntegrationMethod IntegrationMethod;
    ///Tensor order 1 definition
    typedef array_1d<double, 3>    VectorType;
    ///NodeType
    typedef Node < 3 > NodeType;
    ///Geometry Type
    typedef Geometry<NodeType> GeometryType;
    ///Element Type
    typedef Element::ElementType ElementType;


protected:

    /**
     * Parameters to be used in the Condition as they are. Direct interface to Parameters Struct
     */


    typedef struct
    {
        double L;    //base side lentgh
        double A;    //distance 2-3
        double B;    //distance 1-2

    } BaseLengths;


    typedef struct
    {
        VectorType Normal;        //normal direction
        VectorType Tangent;       //tangent direction
	   
    } SurfaceVector;


    typedef struct
    {
        double Normal;        //normal component 
        double Tangent;       //tangent component
        	   
    } SurfaceScalar;


    typedef struct
    {
        Flags           Options;               //calculation options

        //Geometrical gaps:
        SurfaceScalar   CurrentGap;             //normal and tangential gap

        //The stabilization factor or penalty factor
        double          ContactFactor;

        //Friction:
        double          FrictionCoefficient;   //total friction coeffitient mu
	double          TangentialGapSign;     //sign or direction of the tangential gap

        SurfaceScalar   Multiplier;            //Lagrange Multipliyer normal and tangent
        SurfaceScalar   Penalty;               //Penalty Parameter normal and tangent


        //variables of the contact element 2D
        Vector          dN_dn;      //Discrete variacion of the shape function  in the current normal direction
        Vector          dN_dt;      //Discrete variacion of the shape function  in the current tangent direction
        Vector          dN_drn;     //Discrete variacion of the shape function  in the reference normal direction

        std::vector<Vector >       Nsigma;
        std::vector<Vector >       Tsigma;

        //Geometric variables
        SurfaceVector        CurrentSurface;    

        std::vector<BaseLengths>   CurrentBase;    //Current Base Lengths variables
        std::vector<BaseLengths>   ReferenceBase;  //Reference Base Lengths variables

        //Resultant mechanical tractions
        SurfaceScalar              CurrentTensil;  //Tangential and Normal modulus of the traction vector components
      

    } ContactParameters;


    typedef struct
    {
        double  detF;
        double  detJ;
        Vector  StrainVector;
        Vector  StressVector;
        Vector  N;
        Matrix  F;
        Matrix  DN_DX;
        Matrix  ConstitutiveMatrix;

	ContactParameters Contact;
	    
        //Axisymmetric
        double  CurrentRadius;
        double  ReferenceRadius;

	//variables including all integration points
        const GeometryType::ShapeFunctionsGradientsType* pDN_De;
	const Matrix* pNcontainer;

        GeometryType::JacobiansType j;
	    
        /**
         * sets the value of a specified pointer variable
	 */

        void SetShapeFunctionsGradients(const GeometryType::ShapeFunctionsGradientsType &rDN_De)
        {
            pDN_De=&rDN_De;
        };

        void SetShapeFunctions(const Matrix& rNcontainer)
        {
            pNcontainer=&rNcontainer;
        };

	    
	/**
         * returns the value of a specified pointer variable
         */

	const GeometryType::ShapeFunctionsGradientsType& GetShapeFunctionsGradients()
        {
            return *pDN_De;
        };

        const Matrix& GetShapeFunctions()
        {
            return *pNcontainer;
        };   

    } GeneralVariables;


    typedef struct
    {
        //Iteration counter:
        int             IterationCounter;      //the number of the step iteration

        //The stabilization parameter and penalty parameter
        double          StabilizationFactor;
	double          PenaltyFactor;

        //Geometrical gaps:
        SurfaceScalar        PreStepGap;             //effective normal and tangential gap in previous time step configuration

	//Geometric variables
        SurfaceVector        PreStepSurface;    
        SurfaceVector        ReferenceSurface;

        //Contact condition conectivities
        std::vector<unsigned int> nodes;
	std::vector<unsigned int> order;
        std::vector<unsigned int> slaves;

        //Resultant mechanical tractions
	VectorType           TractionVector;       //Traction Vector in the reference configuration

	//Pointer Variables
        GeometryType*         mpMasterGeometry;
        ElementType*          mpMasterElement;
        Condition*            mpMasterCondition;
        NodeType*             mpMasterNode;

	/**
         * sets the value of a specified pointer variable
	 */

	void SetMasterGeometry  (GeometryType& rGeometry){ mpMasterGeometry = &rGeometry; } 
        void SetMasterElement   (ElementType& rElement){ mpMasterElement = &rElement; } 
        void SetMasterCondition (ConditionType& rCondition){ mpMasterCondition = &rCondition; } 
        void SetMasterNode      (NodeType& rNode){ mpMasterNode = &rNode; } 

	/**
         * returns the value of a specified pointer variable
         */

        GeometryType& GetMasterGeometry()   { return (*mpMasterGeometry); } 
	ElementType& GetMasterElement()     { return (*mpMasterElement); } 
	ConditionType& GetMasterCondition() { return (*mpMasterCondition); } 
	NodeType& GetMasterNode()           { return (*mpMasterNode); } 


    } ContactVariables;




public:

    /// Counted pointer of ContactDomainCondition
    KRATOS_CLASS_POINTER_DEFINITION(ContactDomainCondition);

    KRATOS_DEFINE_LOCAL_FLAG( COMPUTE_RHS_VECTOR );
    KRATOS_DEFINE_LOCAL_FLAG( COMPUTE_LHS_MATRIX );

    KRATOS_DEFINE_LOCAL_FLAG( COMPUTE_FRICTION_FORCES );
    KRATOS_DEFINE_LOCAL_FLAG( COMPUTE_FRICTION_STIFFNESS );

    ///@}
    ///@name Life Cycle
    ///@{


    /// Default constructors.
    ContactDomainCondition() : Condition() {};

    ContactDomainCondition(IndexType NewId, GeometryType::Pointer pGeometry);
 
    ContactDomainCondition(IndexType NewId, GeometryType::Pointer pGeometry, PropertiesType::Pointer pProperties);

    ///Copy constructor
    ContactDomainCondition(ContactDomainCondition const& rOther);


    /// Destructor.
    virtual ~ContactDomainCondition();

    ///@}
    ///@name Operators
    ///@{

    /// Assignment operator.
    ContactDomainCondition& operator=(ContactDomainCondition const& rOther);


    ///@}
    ///@name Operations
    ///@{

    /**
     * creates a new total lagrangian updated element pointer
     * @param NewId: the ID of the new element
     * @param ThisNodes: the nodes of the new element
     * @param pProperties: the properties assigned to the new element
     * @return a Pointer to the new element
     */
    Condition::Pointer Create(IndexType NewId, NodesArrayType const& ThisNodes, PropertiesType::Pointer pProperties) const;

    //************* GETTING METHODS

    /**
     * Returns the currently selected integration method
     * @return current integration method selected
     */
    IntegrationMethod GetIntegrationMethod();

    /**
     * Sets on rConditionalDofList the degrees of freedom of the considered element geometry
     */
    void GetDofList(DofsVectorType& rConditionalDofList, ProcessInfo& rCurrentProcessInfo);

    /**
     * Sets on rResult the ID's of the element degrees of freedom
     */
    void EquationIdVector(EquationIdVectorType& rResult, ProcessInfo& rCurrentProcessInfo);

    /**
     * Sets on rValues the nodal displacements
     */
    void GetValuesVector(Vector& rValues, int Step = 0);

    /**
     * Sets on rValues the nodal velocities
     */
    void GetFirstDerivativesVector(Vector& rValues, int Step = 0);

    /**
     * Sets on rValues the nodal accelerations
     */
    void GetSecondDerivativesVector(Vector& rValues, int Step = 0);



    //on integration points:
    /**
     * Access for variables on Integration points.
     * This gives access to variables stored in the constitutive law on each integration point.
     * Specialisations of element.h (e.g. the TotalLagrangian) must specify the actual
     * interface to the constitutive law!
     * Note, that these functions expect a std::vector of values for the
     * specified variable type that contains a value for each integration point!
     * SetValueOnIntegrationPoints: set the values for given Variable.
     * GetValueOnIntegrationPoints: get the values for given Variable.
     */

    //SET
    /**
     * Set a Vector Value on the Condition Constitutive Law
     */
    void SetValueOnIntegrationPoints(const Variable<double>& rVariable, std::vector<double>& rValues, const ProcessInfo& rCurrentProcessInfo);
    /**
     * Set a Vector Value on the Condition Constitutive Law
     */
    void SetValueOnIntegrationPoints(const Variable<Vector>& rVariable, std::vector<Vector>& rValues, const ProcessInfo& rCurrentProcessInfo);

    /**
     * Set a Matrix Value on the Condition Constitutive Law
     */
    void SetValueOnIntegrationPoints(const Variable<Matrix>& rVariable, std::vector<Matrix>& rValues, const ProcessInfo& rCurrentProcessInfo);

    //GET:
    /**
     * Set on rVariable a double Value from the Condition Constitutive Law
     */
    void GetValueOnIntegrationPoints(const Variable<double>& rVariable, std::vector<double>& rValues, const ProcessInfo& rCurrentProcessInfo);

    /**
     * Set on rVariable a Vector Value from the Condition Constitutive Law
     */
    void GetValueOnIntegrationPoints(const Variable<Vector>& rVariable, std::vector<Vector>& rValues, const ProcessInfo& rCurrentProcessInfo);

    /**
     * Set on rVariable a Matrix Value from the Condition Constitutive Law
     */
    void GetValueOnIntegrationPoints(const Variable<Matrix>& rVariable, std::vector<Matrix>& rValues, const ProcessInfo& rCurrentProcessInfo);



    //************* STARTING - ENDING  METHODS

    /**
     * Called to initialize the element.
     * Must be called before any calculation is done
     */
    void Initialize();


    /**
     * Called at the beginning of each solution step
     */
    void InitializeSolutionStep(ProcessInfo& CurrentProcessInfo);

    /**
     * this is called for non-linear analysis at the beginning of the iteration process
     */
    void InitializeNonLinearIteration(ProcessInfo& CurrentProcessInfo);

    /**
     * Called at the end of eahc solution step
     */
    void FinalizeSolutionStep(ProcessInfo& CurrentProcessInfo);



    //************* COMPUTING  METHODS

    /**
     * this is called during the assembling process in order
     * to calculate all elemental contributions to the global system
     * matrix and the right hand side
     * @param rLeftHandSideMatrix: the elemental left hand side matrix
     * @param rRightHandSideVector: the elemental right hand side
     * @param rCurrentProcessInfo: the current process info instance
     */

    void CalculateLocalSystem(MatrixType& rLeftHandSideMatrix, VectorType& rRightHandSideVector, ProcessInfo& rCurrentProcessInfo);

    /**
     * this is called during the assembling process in order
     * to calculate the elemental right hand side vector only
     * @param rRightHandSideVector: the elemental right hand side vector
     * @param rCurrentProcessInfo: the current process info instance
     */
    void CalculateRightHandSide(VectorType& rRightHandSideVector, ProcessInfo& rCurrentProcessInfo);

    /**
     * this is called during the assembling process in order
     * to calculate the elemental left hand side vector only
     * @param rLeftHandSideVector: the elemental left hand side vector
     * @param rCurrentProcessInfo: the current process info instance
     */
    void CalculateLeftHandSide (MatrixType& rLeftHandSideMatrix, ProcessInfo& rCurrentProcessInfo);


    //on integration points:
    /**
     * Calculate a double Variable on the Condition Constitutive Law
     */
    void CalculateOnIntegrationPoints(const Variable<double>& rVariable, Vector& rOutput, const ProcessInfo& rCurrentProcessInfo);

    /**
     * Calculate a Vector Variable on the Condition Constitutive Law
     */
    void CalculateOnIntegrationPoints(const Variable<Vector>& rVariable, std::vector<Vector>& rOutput, const ProcessInfo& rCurrentProcessInfo);

    /**
     * Calculate a Matrix Variable on the Condition Constitutive Law
     */
    void CalculateOnIntegrationPoints(const Variable<Matrix >& rVariable, std::vector< Matrix >& rOutput, const ProcessInfo& rCurrentProcessInfo);


    //************************************************************************************
    //************************************************************************************
    /**
     * This function provides the place to perform checks on the completeness of the input.
     * It is designed to be called only once (or anyway, not often) typically at the beginning
     * of the calculations, so to verify that nothing is missing from the input
     * or that no common error is found.
     * @param rCurrentProcessInfo
     */
    int Check(const ProcessInfo& rCurrentProcessInfo);

    //std::string Info() const;

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
    //      virtual String Info() const;

    /// Print information about this object.
    //      virtual void PrintInfo(std::ostream& rOStream) const;

    /// Print object's data.
    //      virtual void PrintData(std::ostream& rOStream) const;
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

    /**
     * Currently selected integration methods
     */
    IntegrationMethod mThisIntegrationMethod;

    /**
     * Container for constitutive law instances on each integration point
     */
    std::vector<ConstitutiveLaw::Pointer> mConstitutiveLawVector;

    /**
     * Variables stored in the element during the computation
     */
   
    ContactVariables      mContactVariables;

    ///@}
    ///@name Protected Operators
    ///@{

    /**
     * Calculation of the Contact Master Nodes and Mechanical variables
     */
    virtual void SetMasterGeometry()
	{
		KRATOS_ERROR( std::invalid_argument, "Calling base class in contact domain", "" );

	};


    /**
     * Calculate Tau stabilization or Penalty factor
     */
    virtual void CalculateContactFactor(ProcessInfo& rCurrentProcessInfo)
	{
		KRATOS_ERROR( std::invalid_argument, "Calling base class in contact domain", "" );

	};

    /**
     * Calculation of the Contact Previous Gap
     */
    virtual void CalculatePreviousGap()
	{
		KRATOS_ERROR( std::invalid_argument, "Calling base class in contact domain", "" );

	};


    /**
     * Initialize Variables
     */
    virtual void InitializeGeneralVariables (GeneralVariables& rVariables, 
					     const ProcessInfo& rCurrentProcessInfo);
	
    /**
     * Calculates condition contributions
     * \f$ K^e = w\,B^T\,D\,B \f$ and
     * \f$ r^e \f$
     */
    virtual void CalculateConditionalSystem(MatrixType& rLeftHandSideMatrix,
                                            VectorType& rRightHandSideVector,
                                            ProcessInfo& rCurrentProcessInfo,
                                            Flags& rCalculationFlags);
    /**
     * Clear Nodal Forces
     */
    void ClearNodalForces ();

    /**
     * Clear Nodal Forces on Master Element
     */
    void ClearMasterElementNodalForces(ElementType& rMasterElement);


    /**
     * Set Master element information on integration points to Contact element information
     */
    void SetContactIntegrationVariable (Vector & rContactVariable, 
					std::vector<Vector> & rMasterVariables, 
					const unsigned int& rPointNumber );

    /**
     * Calculate Condition Kinematics
     */
    virtual void CalculateKinematics(GeneralVariables& rVariables, 
				     ProcessInfo& rCurrentProcessInfo, 
				     const unsigned int& rPointNumber);

    /**
     * Calculation of the Contact Multipliers or Penalty Factors
     */
    virtual void CalculateExplicitFactors(GeneralVariables& rVariables,
					  ProcessInfo& rCurrentProcessInfo)
	{
		KRATOS_ERROR( std::invalid_argument, "Calling base class in contact domain", "" );

	};
    /**
     * Tangent Matrix construction methods:
     */
    virtual void CalculateDomainShapeN(GeneralVariables& rVariables)
	{
		KRATOS_ERROR( std::invalid_argument, "Calling base class in contact domain", "" );

	};


    /**
     *  Parameters for friction law Tangent:
     */
    virtual VectorType & CalculateCurrentTangent(VectorType & rTangent);


    /**
     *  Parameters for friction law Relative Tangent Velocity:
     */
    virtual void CalculateRelativeVelocity(GeneralVariables& rVariables,
					   VectorType & TangentVelocity);

    /**
     *  Parameters for friction law Relative Tangent Displacement:
     */
    virtual void CalculateRelativeDisplacement(GeneralVariables& rVariables,
					       VectorType & TangentDisplacement);


    /**
     * Friction Parameters:
     */
    virtual void CalculateFrictionCoefficient(GeneralVariables& rVariables,
					      const VectorType & TangentVelocity);


    /**
     * Calculate Integration Weight:
     */
    virtual double& CalculateIntegrationWeight(double& rIntegrationWeight);


    /**
     * Initialize System Matrices
     */
    virtual void InitializeSystemMatrices(MatrixType& rLeftHandSideMatrix,
					  VectorType& rRightHandSideVector,
					  Flags& rCalculationFlags);


    /**
     * Calculate LHS
     */
    virtual void CalculateAndAddLHS(MatrixType& rLeftHandSideMatrix, 
				    GeneralVariables& rVariables, 
				    double& rIntegrationWeight);

    /**
     * Calculate RHS
     */
    virtual void CalculateAndAddRHS(VectorType& rRightHandSideVector,
				    GeneralVariables& rVariables, 
				    double& rIntegrationWeight);


    /**
     * Calculation of the Material Stiffness Matrix. Km = BT * D * B
     */
    virtual void CalculateAndAddKm(MatrixType& rLeftHandSideMatrix,
				   GeneralVariables& rVariables,
				   double& rIntegrationWeight);
	    
    /**
     * Calculation of the Material Stiffness Matrix by components
     */
    virtual void CalcContactStiffness (double &Kcont,GeneralVariables& rVariables,
				       unsigned int& ndi,unsigned int& ndj,
				       unsigned int& idir,unsigned int& jdir)
	{
		KRATOS_ERROR( std::invalid_argument, "Calling base class in contact domain", "" );

	};

    /**
     * Calculation of the Internal Forces Vector. Fi = B * sigma
     */
    virtual void CalculateAndAddContactForces(VectorType& rRightHandSideVector,
					      GeneralVariables& rVariables,
					      double& rIntegrationWeight);



    /**
     * Normal Force construction by components
     */
    virtual void CalculateNormalForce       (double &F,GeneralVariables& rVariables,
					     unsigned int& ndi,unsigned int& idir)
	{
		KRATOS_ERROR( std::invalid_argument, "Calling base class in contact domain", "" );

	};
    /**
     * Tangent Stick Force construction by components
     */
    virtual void CalculateTangentStickForce (double &F,GeneralVariables& rVariables,
					     unsigned int& ndi,unsigned int& idir)
	{
		KRATOS_ERROR( std::invalid_argument, "Calling base class in contact domain", "" );

	};
    /**
     * Tangent Slip Force construction by components
     */
    virtual void CalculateTangentSlipForce  (double &F,GeneralVariables& rVariables,
					     unsigned int& ndi,unsigned int& idir)
	{
		KRATOS_ERROR( std::invalid_argument, "Calling base class in contact domain", "" );

	};
    ///@}
    ///@name Protected Operations
    ///@{
    ///@}
    ///@name Protected  Access
    ///@{
    ///@}
    ///@name Serialization
    ///@{
    friend class Serializer;

    virtual void save(Serializer& rSerializer) const;

    virtual void load(Serializer& rSerializer);

    ///@}
    ///@name Protected Inquiry
    ///@{
    ///@}
    ///@name Protected LifeCycle
    ///@{
    ///@}

private:

    ///@name Private static Member Variables
    ///@{
    ///@}
    ///@name Private member Variables
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
    ///@name Serialization
    ///@{
    ///@}
    ///@name Private Inquiry
    ///@{
    ///@}
    ///@name Un accessible methods
    ///@{
    ///@}

}; // Class ContactDomainCondition

///@}
///@name Type Definitions
///@{
///@}
///@name Input and output
///@{
/// input stream function
/*  inline std::istream& operator >> (std::istream& rIStream,
    ContactDomainCondition& rThis);
*/
/// output stream function
/*  inline std::ostream& operator << (std::ostream& rOStream,
    const ContactDomainCondition& rThis)
    {
    rThis.PrintInfo(rOStream);
    rOStream << std::endl;
    rThis.PrintData(rOStream);

    return rOStream;
    }*/
///@}

} // namespace Kratos.
#endif // KRATOS_CONTACT_DOMAIN_CONDITION_H_INCLUDED  defined 
