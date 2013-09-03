/* *********************************************************
*
*   Last Modified by:    $Author: dbaumgaertner $
*   Date:                $Date: 2013-08-30 16:07:50 $
*   Revision:            $Revision: 1.1.1.1 $
*
* ***********************************************************/


#if !defined(KRATOS_NEW_TRILINOS_STRUCTURAL_MESHMOVING_STRATEGY )
#define  KRATOS_NEW_TRILINOS_STRUCTURAL_MESHMOVING_STRATEGY


/* System includes */


/* External includes */
#include "boost/smart_ptr.hpp"


/* Project includes */
#include "includes/define.h"
#include "includes/model_part.h"
#include "solving_strategies/strategies/solving_strategy.h"
#include "solving_strategies/strategies/residualbased_linear_strategy.h"
#include "solving_strategies/schemes/residualbased_incrementalupdate_static_scheme.h"
#include "../ALEapplication/ale_application.h"
#include "../ALEapplication/custom_elements/structural_meshmoving_element_2d.h"
#include "../ALEapplication/custom_elements/structural_meshmoving_element_3d.h"

/* Trilinos includes */
#include "custom_strategies/builder_and_solvers/trilinos_block_builder_and_solver.h"
#include "custom_strategies/schemes/trilinos_residualbased_incrementalupdate_static_scheme.h"
#include "custom_utilities/parallel_fill_communicator.h"


namespace Kratos
{

/**@name Kratos Globals */
/*@{ */


/*@} */
/**@name Type Definitions */
/*@{ */

/*@} */


/**@name  Enum's */
/*@{ */


/*@} */
/**@name  Functions */
/*@{ */



/*@} */
/**@name Kratos Classes */
/*@{ */

/// Short class definition.
/**   Detail class definition.

\URL[Example of use html]{ extended_documentation/no_ex_of_use.html}

\URL[Example of use pdf]{ extended_documentation/no_ex_of_use.pdf}

\URL[Example of use doc]{ extended_documentation/no_ex_of_use.doc}

\URL[Example of use ps]{ extended_documentation/no_ex_of_use.ps}


\URL[Extended documentation html]{ extended_documentation/no_ext_doc.html}

\URL[Extended documentation pdf]{ extended_documentation/no_ext_doc.pdf}

\URL[Extended documentation doc]{ extended_documentation/no_ext_doc.doc}

\URL[Extended documentation ps]{ extended_documentation/no_ext_doc.ps}


*/
template<class TSparseSpace,
         class TDenseSpace, //= DenseSpace<double>,
         class TLinearSolver //= LinearSolver<TSparseSpace,TDenseSpace>
         >
class TrilinosStructuralMeshMovingStrategy
    : public SolvingStrategy<TSparseSpace,TDenseSpace,TLinearSolver>
{
public:
    /**@name Type Definitions */
    /*@{ */

    /** Counted pointer of ClassName */
    KRATOS_CLASS_POINTER_DEFINITION( TrilinosStructuralMeshMovingStrategy );

    typedef SolvingStrategy<TSparseSpace,TDenseSpace,TLinearSolver> BaseType;

    typedef typename BaseType::TDataType TDataType;

    //typedef typename BaseType::DofSetType DofSetType;

    typedef typename BaseType::DofsArrayType DofsArrayType;

    typedef typename BaseType::TSystemMatrixType TSystemMatrixType;

    typedef typename BaseType::TSystemVectorType TSystemVectorType;

    typedef typename BaseType::LocalSystemVectorType LocalSystemVectorType;

    typedef typename BaseType::LocalSystemMatrixType LocalSystemMatrixType;



    /*@} */
    /**@name Life Cycle
    */
    /*@{ */

    /** Constructor.
    */
    TrilinosStructuralMeshMovingStrategy(
        Epetra_MpiComm& Comm,
        ModelPart& model_part,
        typename TLinearSolver::Pointer pNewLinearSolver,
        int dimension = 3,
        int velocity_order = 1,
        bool reform_dof_at_every_step = true
    )
        : SolvingStrategy<TSparseSpace,TDenseSpace,TLinearSolver>(model_part)
    {
        KRATOS_TRY

        // Passed variables
        mdimension = dimension;
        mvel_order = velocity_order;
        mreform_dof_at_every_step = reform_dof_at_every_step;

        // Definitions for trilinos
        int guess_row_size;
        guess_row_size = 15;

        bool CalculateReactions = false;
        bool ReformDofAtEachIteration = false;
        bool CalculateNormDxFlag = false;

        //Generating Mesh Part
        GenerateMeshPart(dimension);

        typedef Scheme< TSparseSpace,  TDenseSpace > SchemeType;
        typename SchemeType::Pointer pscheme = typename SchemeType::Pointer( new TrilinosResidualBasedIncrementalUpdateStaticScheme< TSparseSpace,  TDenseSpace >() );

        typedef typename BuilderAndSolver<TSparseSpace,TDenseSpace,TLinearSolver>::Pointer BuilderSolverTypePointer;

        BuilderSolverTypePointer builderSolver = BuilderSolverTypePointer(new TrilinosBlockBuilderAndSolver<TSparseSpace,TDenseSpace,TLinearSolver>(Comm, guess_row_size, pNewLinearSolver) );

        mstrategy = typename BaseType::Pointer( new ResidualBasedLinearStrategy<TSparseSpace,  TDenseSpace, TLinearSolver >(*mpMeshModelPart,pscheme,pNewLinearSolver,builderSolver,CalculateReactions,ReformDofAtEachIteration,CalculateNormDxFlag)  );
        mstrategy->SetEchoLevel(2);

        KRATOS_CATCH("")
    }



    /** Destructor.
    */
    virtual ~TrilinosStructuralMeshMovingStrategy() {}

    /** Destructor.
    */


    //*********************************************************************************
    //*********************************************************************************
    double Solve()
    {
        KRATOS_TRY

        // Mesh has to be regenerated in each solving step
        ReGenerateMeshPart();

        ProcessInfo& rCurrentProcessInfo = (mpMeshModelPart)->GetProcessInfo();

        // Updating the time
        rCurrentProcessInfo[TIME] = BaseType::GetModelPart().GetProcessInfo()[TIME];
        rCurrentProcessInfo[DELTA_TIME] = BaseType::GetModelPart().GetProcessInfo()[DELTA_TIME];

        // Solve for mesh movement
        mstrategy->Solve();

        // Update FEM database
        CalculateMeshVelocities();
        BaseType::MoveMesh();

        // Clearing the system if needed
        if(mreform_dof_at_every_step == true)
            mstrategy->Clear();

        return 0.0;

        KRATOS_CATCH("")
    }


    //*********************************************************************************
    //*********************************************************************************
    void CalculateMeshVelocities()
    {
        KRATOS_TRY;

        double DeltaTime = (*mpMeshModelPart).GetProcessInfo()[DELTA_TIME];
        double coeff = 1/DeltaTime;
        if( mvel_order == 1) //mesh velocity calculated as (x(n+1)-x(n))/Dt
        {
            for(ModelPart::NodeIterator i = (*mpMeshModelPart).NodesBegin() ;
                    i != (*mpMeshModelPart).NodesEnd() ; ++i)
            {
                array_1d<double,3>& mesh_v = (i)->FastGetSolutionStepValue(MESH_VELOCITY);
                array_1d<double,3>& disp = (i)->FastGetSolutionStepValue(DISPLACEMENT);
                array_1d<double,3>& dispold = (i)->FastGetSolutionStepValue(DISPLACEMENT,1);
                noalias(mesh_v) =  disp - dispold;
                mesh_v *= coeff;
            }
        }
        else //mesh velocity calculated as (3*x(n+1)-4*x(n)+x(n-1))/(2*Dt)
        {
            double c1 = 1.50*coeff;
            double c2 = -2.0*coeff;
            double c3 = 0.50*coeff;

            for(ModelPart::NodeIterator i = (*mpMeshModelPart).NodesBegin() ;
                    i != (*mpMeshModelPart).NodesEnd() ; ++i)
            {
                array_1d<double,3>& mesh_v = (i)->FastGetSolutionStepValue(MESH_VELOCITY);
                noalias(mesh_v) =  c1 * (i)->FastGetSolutionStepValue(DISPLACEMENT);
                noalias(mesh_v) += c2 * (i)->FastGetSolutionStepValue(DISPLACEMENT,1);
                noalias(mesh_v) += c3 * (i)->FastGetSolutionStepValue(DISPLACEMENT,2);
            }
        }

        KRATOS_CATCH("")
    }

    virtual void SetEchoLevel(int Level)
    {
        mstrategy->SetEchoLevel(Level);
    }

    void MoveNodes()
    {
        CalculateMeshVelocities();
        BaseType::MoveMesh();
    }

    /*@} */
    /**@name Operators
    */
    /*@{ */

    /*@} */
    /**@name Operations */
    /*@{ */


    /*@} */
    /**@name Access */
    /*@{ */


    /*@} */
    /**@name Inquiry */
    /*@{ */


    /*@} */
    /**@name Friends */
    /*@{ */


    /*@} */

protected:
    /**@name Protected static Member Variables */
    /*@{ */


    /*@} */
    /**@name Protected member Variables */
    /*@{ */


    /*@} */
    /**@name Protected Operators*/
    /*@{ */


    /*@} */
    /**@name Protected Operations*/
    /*@{ */



    /*@} */
    /**@name Protected  Access */
    /*@{ */


    /*@} */
    /**@name Protected Inquiry */
    /*@{ */


    /*@} */
    /**@name Protected LifeCycle */
    /*@{ */



    /*@} */

private:
    /**@name Static Member Variables */
    /*@{ */


    /*@} */
    /**@name Member Variables */
    /*@{ */
    ModelPart::Pointer mpMeshModelPart;

    typename BaseType::Pointer mstrategy;

    int mdimension;
    int mvel_order;
    bool mreform_dof_at_every_step;

    /*@} */
    /**@name Private Operators*/
    /*@{ */

    /*@} */
    /**@name Private Operations*/
    /*@{ */

    void GenerateMeshPart(int dimension)
    {
        // Initialize auxiliary model part storing the mesh elements
        mpMeshModelPart = ModelPart::Pointer( new ModelPart("MeshPart",1) );

        // Initializing mesh nodes
        mpMeshModelPart->Nodes() = BaseType::GetModelPart().Nodes();

        // Setup new auxiliary model part
        mpMeshModelPart->GetNodalSolutionStepVariablesList() = BaseType::GetModelPart().GetNodalSolutionStepVariablesList();
        mpMeshModelPart->SetBufferSize(BaseType::GetModelPart().GetBufferSize());
        mpMeshModelPart->SetProcessInfo(BaseType::GetModelPart().pGetProcessInfo());
        mpMeshModelPart->SetProperties(BaseType::GetModelPart().pProperties());

        // Create a communicator for the new model part and copy the partition information about nodes.
        Communicator& rReferenceComm = BaseType::GetModelPart().GetCommunicator();
        typename Communicator::Pointer pMeshMPIComm = typename Communicator::Pointer( new MPICommunicator( &(BaseType::GetModelPart().GetNodalSolutionStepVariablesList()) ) );
        pMeshMPIComm->SetNumberOfColors( rReferenceComm.GetNumberOfColors() ) ;
        pMeshMPIComm->NeighbourIndices() = rReferenceComm.NeighbourIndices();
        pMeshMPIComm->LocalMesh().SetNodes( rReferenceComm.LocalMesh().pNodes() );
        pMeshMPIComm->InterfaceMesh().SetNodes( rReferenceComm.InterfaceMesh().pNodes() );
        pMeshMPIComm->GhostMesh().SetNodes( rReferenceComm.GhostMesh().pNodes() );

        // Setup communication plan
        for (unsigned int i = 0; i < rReferenceComm.GetNumberOfColors(); i++)
        {
            pMeshMPIComm->pInterfaceMesh(i)->SetNodes( rReferenceComm.pInterfaceMesh(i)->pNodes() );
            pMeshMPIComm->pLocalMesh(i)->SetNodes( rReferenceComm.pLocalMesh(i)->pNodes() );
            pMeshMPIComm->pGhostMesh(i)->SetNodes( rReferenceComm.pGhostMesh(i)->pNodes() );
        }
        mpMeshModelPart->SetCommunicator( pMeshMPIComm );

        // Creating mesh elements
        ModelPart::ElementsContainerType& MeshElems = mpMeshModelPart->Elements();
        Element::Pointer pElem;

        if(dimension == 2)
            for(ModelPart::ElementsContainerType::iterator it =  BaseType::GetModelPart().ElementsBegin();
                    it != BaseType::GetModelPart().ElementsEnd(); it++)
            {
                pElem = Element::Pointer(new StructuralMeshMovingElem2D(
                                             (*it).Id(),
                                             (*it).pGetGeometry(),
                                             (*it).pGetProperties() ) );
                MeshElems.push_back(pElem);
            }
        else if(dimension == 3)
            for(ModelPart::ElementsContainerType::iterator it =  BaseType::GetModelPart().ElementsBegin();
                    it != BaseType::GetModelPart().ElementsEnd(); it++)
            {
                pElem = Element::Pointer(new StructuralMeshMovingElem3D(
                                             (*it).Id(),
                                             (*it).pGetGeometry(),
                                             (*it).pGetProperties() ) );
                MeshElems.push_back(pElem);
            }

        // Optimize communicaton plan
        ParallelFillCommunicator CommunicatorGeneration( *mpMeshModelPart );
        CommunicatorGeneration.Execute();
    }

    void ReGenerateMeshPart()
    {
        std::cout << "regenerating elements for the mesh motion scheme" << std::endl;

        //reinitializing new auxiliary model part
        mpMeshModelPart->Nodes().clear();
        mpMeshModelPart->Nodes() = BaseType::GetModelPart().Nodes();

        // Create a communicator for the new model part and copy the partition information about nodes.
        Communicator& rReferenceComm = BaseType::GetModelPart().GetCommunicator();
        typename Communicator::Pointer pMeshMPIComm = typename Communicator::Pointer( new MPICommunicator( &(BaseType::GetModelPart().GetNodalSolutionStepVariablesList()) ) );
        pMeshMPIComm->SetNumberOfColors( rReferenceComm.GetNumberOfColors() ) ;
        pMeshMPIComm->NeighbourIndices() = rReferenceComm.NeighbourIndices();
        pMeshMPIComm->LocalMesh().SetNodes( rReferenceComm.LocalMesh().pNodes() );
        pMeshMPIComm->InterfaceMesh().SetNodes( rReferenceComm.InterfaceMesh().pNodes() );
        pMeshMPIComm->GhostMesh().SetNodes( rReferenceComm.GhostMesh().pNodes() );

        // Setup communication plan
        for (unsigned int i = 0; i < rReferenceComm.GetNumberOfColors(); i++)
        {
            pMeshMPIComm->pInterfaceMesh(i)->SetNodes( rReferenceComm.pInterfaceMesh(i)->pNodes() );
            pMeshMPIComm->pLocalMesh(i)->SetNodes( rReferenceComm.pLocalMesh(i)->pNodes() );
            pMeshMPIComm->pGhostMesh(i)->SetNodes( rReferenceComm.pGhostMesh(i)->pNodes() );
        }
        mpMeshModelPart->SetCommunicator( pMeshMPIComm );

        // Creating mesh elements
        ModelPart::ElementsContainerType& MeshElems = mpMeshModelPart->Elements();
        Element::Pointer pElem;

        MeshElems.clear();
        MeshElems.reserve( MeshElems.size() );

        // Removing existing mesh conditions
        mpMeshModelPart->Conditions().clear();

        if(mdimension == 2)
            for(ModelPart::ElementsContainerType::iterator it =  BaseType::GetModelPart().ElementsBegin();
                    it != BaseType::GetModelPart().ElementsEnd(); it++)
            {
                pElem = Element::Pointer(new StructuralMeshMovingElem2D(
                                             (*it).Id(),
                                             (*it).pGetGeometry(),
                                             (*it).pGetProperties() ) );
                MeshElems.push_back(pElem);
            }
        else if(mdimension == 3)
            for(ModelPart::ElementsContainerType::iterator it =  BaseType::GetModelPart().ElementsBegin();
                    it != BaseType::GetModelPart().ElementsEnd(); it++)
            {
                pElem = Element::Pointer(new StructuralMeshMovingElem3D(
                                             (*it).Id(),
                                             (*it).pGetGeometry(),
                                             (*it).pGetProperties() ) );
                MeshElems.push_back(pElem);
            }

            // Optimize communicaton plan
            ParallelFillCommunicator CommunicatorGeneration( *mpMeshModelPart );
            CommunicatorGeneration.Execute();
    }

    /*@} */
    /**@name Private  Access */
    /*@{ */


    /*@} */
    /**@name Private Inquiry */
    /*@{ */


    /*@} */
    /**@name Un accessible methods */
    /*@{ */

    /** Copy constructor.
    */
    TrilinosStructuralMeshMovingStrategy(const TrilinosStructuralMeshMovingStrategy& Other);


    /*@} */

}; /* Class TrilinosStructuralMeshMovingStrategy */

/*@} */

/**@name Type Definitions */
/*@{ */


/*@} */

}  /* namespace Kratos.*/

#endif /* KRATOS_NEW_STRUCTURAL_MESHMOVING_STRATEGY  defined */

