//
//   Project Name:        KratosPfemSolidMechanicsApplication $
//   Last modified by:    $Author:                JMCarbonell $
//   Date:                $Date:                    July 2013 $
//   Revision:            $Revision:                      0.0 $
//
//

#if !defined(KRATOS_COMPOSITE_CONDITION_H_INCLUDED )
#define  KRATOS_COMPOSITE_CONDITION_H_INCLUDED



// System includes
#include <iostream>
#include <iomanip>

// External includes
#include "boost/smart_ptr.hpp"


// Project includes
#include "includes/define.h"
#include "includes/condition.h"
#include "includes/serializer.h"
#include "includes/ublas_interface.h"
#include "includes/variables.h"
#include "includes/constitutive_law.h"
#include "utilities/math_utils.h"

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

/// Updated Total Lagrangian element for 2D and 3D geometries.

/**
 * Implements an Updated Lagrangian Condition based on the reference (or previous) configuration
 * This works for arbitrary geometries in 2D and 3D
 */

class CompositeCondition
    : public Condition
{
public:


    ///@name Type Definitions
    ///@{
    typedef Condition ConditionType;

    /// Conditions container. A vector set of Conditions with their Id's as key.
    typedef PointerVectorSet<ConditionType, IndexedObject> ConditionsContainerType;

    /** Iterator over the Conditions. This iterator is an indirect
    iterator over Conditions::Pointer which turn back a reference to
    Condition by * operator and not a pointer for more convenient
    usage. */
    typedef typename ConditionsContainerType::iterator ConditionIterator;

    /** Const iterator over the Conditions. This iterator is an indirect
    iterator over Conditions::Pointer which turn back a reference to
    Condition by * operator and not a pointer for more convenient
    usage. */
    typedef typename ConditionsContainerType::const_iterator ConditionConstantIterator;


    /// Counted pointer of CompositeCondition
    KRATOS_CLASS_POINTER_DEFINITION(CompositeCondition);

    ///@}
    ///@name Life Cycle
    ///@{


    /// Default constructors.
    CompositeCondition(IndexType NewId, GeometryType::Pointer pGeometry);
    CompositeCondition(IndexType NewId, GeometryType::Pointer pGeometry, PropertiesType::Pointer pProperties);

    ///Copy constructor
    CompositeCondition(CompositeCondition const& rOther);


    /// Destructor.
    virtual ~CompositeCondition();

    ///@}
    ///@name Operators
    ///@{

    /// Assignment operator.
    CompositeCondition& operator=(CompositeCondition const& rOther);


    ///@}
    ///@name Operations
    ///@{


   SizeType NumberOfChildren() const
    {
        return mpChildConditions->size();
    }

    /** Inserts a condition in the composite.
    */
    void AddChild(typename ConditionType::Pointer pNewChildCondition)
    {
      bool set = false;

      for (ConditionIterator cn = mpChildConditions->begin() ; cn != mpChildConditions->end(); ++cn)
	{
	  if(pNewChildCondition->Id() == cn->Id())
	    set=true;
	}

      if(!set)
        mpChildConditions->insert(mpChildConditions->begin(), pNewChildCondition);
    }

    /** Returns the Condition::Pointer  corresponding to it's identifier */
    typename ConditionType::Pointer pGetChild(IndexType ChildConditionId)
    {
        return (*mpChildConditions)(ChildConditionId);
    }

    /** Returns a reference condition corresponding to it's identifier */
    ConditionType& GetChild(IndexType ChildConditionId)
    {
        return (*mpChildConditions)[ChildConditionId];
    }

    /** Remove the condition with given Id from composite.
    */
    void RemoveChild(IndexType ChildConditionId)
    {
        mpChildConditions->erase(ChildConditionId);
    }

    /** Remove given condition from composite.
    */
    void RemoveChild(ConditionType& ThisChildCondition)
    {
        mpChildConditions->erase(ThisChildCondition.Id());
    }

    /** Remove given condition from composite.
    */
    void RemoveChild(typename ConditionType::Pointer pThisChildCondition)
    {
        mpChildConditions->erase(pThisChildCondition->Id());
    }

    ConditionIterator ChildConditionsBegin()
    {
        return mpChildConditions->begin();
    }

    ConditionConstantIterator ChildConditionsBegin() const
    {
        return mpChildConditions->begin();
    }

    ConditionIterator ChildConditionsEnd()
    {
        return mpChildConditions->end();
    }

    ConditionConstantIterator ChildConditionsEnd() const
    {
        return mpChildConditions->end();
    }

    ConditionsContainerType& ChildConditions()
    {
        return *mpChildConditions;
    }

    typename ConditionsContainerType::Pointer pChildConditions()
    {
        return mpChildConditions;
    }

    void SetChildConditions(typename ConditionsContainerType::Pointer pOtherChildConditions)
    {
        mpChildConditions = pOtherChildConditions;
    }

    typename ConditionsContainerType::ContainerType& ChildConditionsArray()
    {
        return mpChildConditions->GetContainer();
    }

    /**
     * creates a new condition pointer
     * @param NewId: the ID of the new element
     * @param ThisNodes: the nodes of the new element
     * @param pProperties: the properties assigned to the new element
     * @return a Pointer to the new element
     */
    Condition::Pointer Create(IndexType NewId, NodesArrayType const& ThisNodes, PropertiesType::Pointer pProperties) const;


    /**
     * clones the selected condition variables, creating a new one
     * @param NewId: the ID of the new condition
     * @param ThisNodes: the nodes of the new condition
     * @param pProperties: the properties assigned to the new condition
     * @return a Pointer to the new condition
     */
    Condition::Pointer Clone(IndexType NewId, 
			     NodesArrayType const& ThisNodes) const;


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

    /**
      * this is called during the assembling process in order
      * to calculate the elemental mass matrix
      * @param rMassMatrix: the elemental mass matrix
      * @param rCurrentProcessInfo: the current process info instance
      */
    void MassMatrix(MatrixType& rMassMatrix, ProcessInfo& rCurrentProcessInfo);

    /**
      * this is called during the assembling process in order
      * to calculate the elemental damping matrix
      * @param rDampMatrix: the elemental damping matrix
      * @param rCurrentProcessInfo: the current process info instance
      */
    void DampMatrix(MatrixType& rDampMatrix, ProcessInfo& rCurrentProcessInfo);


    //on integration points:
    /**
     * Calculate a double Variable on the Condition Constitutive Law
     */
    void CalculateOnIntegrationPoints(const Variable<double>& rVariable, std::vector<double>& rOutput, const ProcessInfo& rCurrentProcessInfo);

    /**
     * Calculate a Vector Variable on the Condition Constitutive Law
     */
    void CalculateOnIntegrationPoints(const Variable<Vector>& rVariable, std::vector<Vector>& rOutput, const ProcessInfo& rCurrentProcessInfo);

    /**
     * Calculate a Matrix Variable on the Condition Constitutive Law
     */
    void CalculateOnIntegrationPoints(const Variable<Matrix >& rVariable, std::vector< Matrix >& rOutput, const ProcessInfo& rCurrentProcessInfo);


    void Calculate(const Variable<double>& rVariable, double& rOutput, const ProcessInfo& rCurrentProcessInfo);

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

    /**
     * Variables
     */

    typename ConditionsContainerType::Pointer mpChildConditions;

    ///@}
    ///@name Private Operators
    ///@{

    ///@}
    ///@name Private Operations
    ///@{

    //check problem type definition and if coincides return active true
    bool IsActive(ConditionIterator iChildCondition, const ProcessInfo& rCurrentProcessInfo);

    //set specific data value to condition children
    template<class TVariableType> void SetValueToChildren(const TVariableType& rThisVariable){

      for (ConditionIterator cn = mpChildConditions->begin() ; cn != mpChildConditions->end(); ++cn)
	{
	  typename TVariableType::Type const& rValue = this->GetValue(rThisVariable);
	  cn->SetValue(rThisVariable,rValue);	      
	}
      
    }
    ///@}
    ///@name Private  Access
    ///@{
    ///@}

    ///@}
    ///@name Serialization
    ///@{
    friend class Serializer;

    // A private default constructor necessary for serialization

    CompositeCondition() : Condition()
    {
    }

    virtual void save(Serializer& rSerializer) const;
 
    virtual void load(Serializer& rSerializer);



    ///@name Private Inquiry
    ///@{
    ///@}
    ///@name Un accessible methods
    ///@{
    ///@}

}; // Class CompositeCondition

///@}
///@name Type Definitions
///@{
///@}
///@name Input and output
///@{
/// input stream function
/*  inline std::istream& operator >> (std::istream& rIStream,
    CompositeCondition& rThis);
*/
/// output stream function
/*  inline std::ostream& operator << (std::ostream& rOStream,
    const CompositeCondition& rThis)
    {
    rThis.PrintInfo(rOStream);
    rOStream << std::endl;
    rThis.PrintData(rOStream);

    return rOStream;
    }*/
///@}

} // namespace Kratos.
#endif // KRATOS_COMPOSITE_CONDITION_H_INCLUDED  defined 
