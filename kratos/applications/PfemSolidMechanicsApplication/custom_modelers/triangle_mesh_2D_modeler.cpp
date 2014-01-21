//
//   Project Name:        KratosPfemSolidMechanicsApplication $
//   Last modified by:    $Author:                JMCarbonell $
//   Date:                $Date:                    July 2013 $
//   Revision:            $Revision:                      0.0 $
//
//

// System includes

// External includes


// Project includes
#include "custom_modelers/triangle_mesh_2D_modeler.hpp"

#include "pfem_solid_mechanics_application.h"


namespace Kratos
{


  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::SetInitialMeshData (int number_of_domains)
  {
    
    std::cout<<" INITIALIZE MESH DATA: [ number of domains = "<<number_of_domains<<" ]"<<std::endl;
    
    MeshingVariables Variables;
    Variables.Initialize();
    mVariables.push_back(Variables);
    mVariables.back().Initialize();
   
    if(number_of_domains>1){
      for(int i=1; i<=number_of_domains; i++)
	{
	  MeshingVariables Variables;
	  Variables.Initialize();
	  mVariables.push_back(Variables);
	  mVariables.back().Initialize();
	} 
    }
  
  }
  
  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::SetRemeshData (Element   const& rReferenceElement,
					     Condition const& rReferenceCondition,
					     bool remesh,
					     bool constrained,
					     bool mesh_smoothing,
					     bool jacobi_smoothing,
					     bool avoid_tip_elements,
					     double alpha,
					     double my_offset,
					     int    MeshId)
  {    
    
    if(mVariables.size() == 1 && MeshId != 0)
      std::cout<<" Something wrong with mesh ID "<<MeshId<<std::endl;

    mVariables[MeshId].SetReferenceElement   (rReferenceElement);
    mVariables[MeshId].SetReferenceCondition (rReferenceCondition);

    mVariables[MeshId].remesh      = remesh;
    mVariables[MeshId].constrained = constrained;

    mVariables[MeshId].mesh_smoothing   = mesh_smoothing;
    mVariables[MeshId].jacobi_smoothing = jacobi_smoothing;
    mVariables[MeshId].avoid_tip_elements = avoid_tip_elements;

    mVariables[MeshId].AlphaParameter=alpha;

    mVariables[MeshId].offset_factor =my_offset;

    mVariables[MeshId].refine         = false;
    mVariables[MeshId].BoundingBox.is_set = false;

    std::cout<<" SetRemeshData : [ refine: "<<mVariables[MeshId].refine<<" - "<<mVariables[MeshId].refine<<" remesh : "<<mVariables[MeshId].remesh<<" - "<<mVariables[MeshId].remesh<<" ] "<<std::endl;


  }

  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::SetRefineData (bool   refine,
					     double h_factor,
					     double dissipation,
					     double radius,
					     double error,
					     int    MeshId)
  {    

    if(mVariables.size() == 1 && MeshId != 0)
      std::cout<<" Something wrong with mesh ID "<<MeshId<<std::endl;

    //other reference variables (JuanManuel)
    double side_tolerance = 6; //3;

    mVariables[MeshId].refine                      = refine;

    mVariables[MeshId].Refine.size_factor          = h_factor;
    
    mVariables[MeshId].Refine.critical_dissipation = dissipation; //40;  400;

    mVariables[MeshId].Refine.critical_radius      = radius; //0.0004 m

    mVariables[MeshId].Refine.critical_side        = side_tolerance*radius;  //0.02;

    mVariables[MeshId].Refine.reference_error      = error;  //2;


    std::cout<<" CRITICAL RADIUS      : "<<mVariables[MeshId].Refine.critical_radius<<std::endl;
    std::cout<<" CRITICAL SIDE        : "<<mVariables[MeshId].Refine.critical_side<<std::endl;
    std::cout<<" CRITICAL DISSIPATION : "<<mVariables[MeshId].Refine.critical_dissipation<<std::endl;

  }

  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::SetRigidWall (RigidWallBoundingBox::Pointer pRigidWall)
  {
    for(unsigned int i=0; i<mVariables.size(); i++)
      {
	mVariables[i].rigid_wall_set =true;
	mVariables[i].RigidWalls.push_back(pRigidWall);
      }
  }


  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::SetRefiningBox (double radius,
					      Vector center,
					      Vector velocity)
    
  {
    for(unsigned int i=0; i<mVariables.size(); i++)
      {
	mVariables[i].BoundingBox.is_set =true;
	mVariables[i].BoundingBox.Radius=radius;
	mVariables[i].BoundingBox.Center=center;
	mVariables[i].BoundingBox.Velocity=velocity;

	std::cout<<" Bounding Box [ Radius: "<<radius<<" Center: "<<center<<" Velocity: "<<velocity<<" ] "<<std::endl;

      }
  }


  //*******************************************************************************************
  //*******************************************************************************************


  void TriangleMesh2DModeler::GenerateMesh(ModelPart& rModelPart)
  {

    unsigned int start=0;
    unsigned int NumberOfMeshes=rModelPart.NumberOfMeshes();
    if(NumberOfMeshes>1) 
      start=1;

    //By the way: set meshes options from bools
    for(unsigned int MeshId=start; MeshId<NumberOfMeshes; MeshId++)
      {
	std::cout<<" GetRemeshData : [ refine: "<<mVariables[MeshId].refine<<" - "<<mVariables[MeshId].refine<<" remesh : "<<mVariables[MeshId].remesh<<" - "<<mVariables[MeshId].remesh<<" ] "<<std::endl;

	if(mVariables[MeshId].remesh)
	  rModelPart.GetMesh(MeshId).Set( Modeler::REMESH );
	else
	  rModelPart.GetMesh(MeshId).Reset( Modeler::REMESH );

	if(mVariables[MeshId].refine)
	  rModelPart.GetMesh(MeshId).Set( Modeler::REFINE_MESH );
	
	if(mVariables[MeshId].constrained){
	  rModelPart.GetMesh(MeshId).Set( Modeler::CONSTRAINED_MESH );

	  //Update Boundary Normals before Constrained Meshing
	  // BoundaryNormalsCalculationUtilities BoundaryComputation;
	  // BoundaryComputation.CalculateBoundaryNormals(rModelPart,2);
	}

	    
      }

    //Sort Conditions
    unsigned int consecutive_index = 1;
    for(ModelPart::ConditionsContainerType::iterator ic = rModelPart.ConditionsBegin(); ic!=rModelPart.ConditionsEnd(); ic++)
      ic->SetId(consecutive_index++);

    rModelPart.Conditions().Sort();
    rModelPart.Conditions().Unique();


    // //Sort Elements
    // consecutive_index = 1;
    // for(ModelPart::ElementsContainerType::iterator ie = rModelPart.ElementsBegin(); ie!=rModelPart.ElementsEnd(); ie++)
    //   ie->SetId(consecutive_index++);

    // rModelPart.Elements().Sort();
    // rModelPart.Elements().Unique();

    // //Sort Nodes, set STRUCTURE NODES (RIGID TOOL NODES) AT END
    // consecutive_index = 1;
    // unsigned int reverse_index = rModelPart.Nodes().size();
    // for(ModelPart::NodesContainerType::iterator in = rModelPart.NodesBegin(); in!=rModelPart.NodesEnd(); in++){
    //   if(in->IsNot(STRUCTURE) ){
    //     in->SetId(consecutive_index++);
    //   }
    //   else{
    //     in->SetId(reverse_index--);
    //   }
    // }

    // rModelPart.Nodes().Sort();
    // rModelPart.Nodes().Unique();


    MeshDataTransferUtilities    MeshDataTransfer;
    LaplacianSmoothing   MeshGeometricSmooth(rModelPart);

	
    bool remesh_performed=false;
	
    std::cout<<" --------------                     -------------- "<<std::endl;
    std::cout<<" --------------       DOMAIN        -------------- "<<std::endl;
	
	
    ModelPart::MeshesContainerType Meshes = rModelPart.GetMeshes();
	  	  
    for(unsigned int MeshId=start; MeshId<NumberOfMeshes; MeshId++)
      {
	//set properties in all meshes
	if(rModelPart.NumberOfProperties(MeshId)!=rModelPart.NumberOfProperties())
	  rModelPart.GetMesh(MeshId).SetProperties(rModelPart.GetMesh().pProperties());

	//transfer DETERMINANT_F FOR VARIABLES SMOOTHING to nodes
	if(mVariables[MeshId].jacobi_smoothing){
	  MeshDataTransfer.TransferElementalValuesToNodes(DETERMINANT_F,rModelPart,MeshId);
	}
	    
	if(Meshes[MeshId].Is(Modeler::REMESH )){


	  if(Meshes[MeshId].Is( Modeler::CONSTRAINED_MESH ))
	    {
	      if(Meshes[MeshId].Is( Modeler::REFINE_MESH )){ 
		//Constrained Delaunay Triangulation
		std::cout<<" [ MESH: "<<MeshId<<" REFINE RCDT START]:"<<std::endl;
		GenerateRCDT(rModelPart,mVariables[MeshId],MeshId);	
		std::cout<<" [ MESH: "<<MeshId<<" REFINE RCDT END]"<<std::endl;	  
	      }
	      else{ 	
		//Generate Constrained Delaunay Triangulation
		std::cout<<" [ MESH: "<<MeshId<<" REMESH CDT ]:"<<std::endl;
		GenerateCDT(rModelPart,mVariables[MeshId],MeshId);		
		std::cout<<" [ MESH: "<<MeshId<<" REMESH END ]"<<std::endl;    		    
	      }
	    }
	  else
	    {
	      if(Meshes[MeshId].Is( Modeler::REFINE_MESH )){ 
		//Constrained Delaunay Triangulation
		std::cout<<" [ MESH: "<<MeshId<<" REFINE RDT START]:"<<std::endl;
		GenerateRDT(rModelPart,mVariables[MeshId],MeshId);	
		std::cout<<" [ MESH: "<<MeshId<<" REFINE RDT END]"<<std::endl;	  
	      }
	      else{
		//Generate Delaunay Triangulation
		std::cout<<" [ MESH: "<<MeshId<<" REMESH DT START ]:"<<std::endl;
		GenerateDT(rModelPart,mVariables[MeshId],MeshId);
		std::cout<<" [ MESH: "<<MeshId<<" REMESH DT END ]"<<std::endl;
	      }
	    }
		
	  std::cout<<" --------------                     -------------- "<<std::endl;
	  std::cout<<" --------------  REMESH PERFORMED   -------------- "<<std::endl;
	  std::cout<<" --------------                     -------------- "<<std::endl;

	  remesh_performed=true;
	}
	else{

	  if(mVariables[MeshId].mesh_smoothing){
	    std::cout<<" [ MESH: "<<MeshId<<" TRANSFER START ]:"<<std::endl;

	    rModelPart.GetMesh(MeshId).Set( Modeler::REMESH );  //transfer only done if the remesh option is active
	    PerformTransferOnly(rModelPart,mVariables[MeshId],MeshId);
	    remesh_performed=true;

	    std::cout<<" [ MESH: "<<MeshId<<" TRANSFER END ]"<<std::endl;
	  }
	  else{
	    std::cout<<" [ MESH: "<<MeshId<<" NO REMESH ]"<<std::endl;
	  }

	}

      }

    //Once all meshes are build, the main mesh Id=0 must be reassigned
    if(NumberOfMeshes>1){
      mModelerUtilities.BuildTotalMesh(rModelPart);
    }
    else{
      mModelerUtilities.CleanMeshFlags(rModelPart,0);
    }
	
    //remesh_performed = false; //deactivate searches
	   
    if(remesh_performed){


      //CHANGE ELEMENTS WITH ALL NODES IN BOUNDARY  (TIP ELEMENTS)
      for(unsigned int MeshId=start; MeshId<NumberOfMeshes; MeshId++)
	{
		
	  if(Meshes[MeshId].Is( Modeler::REMESH )){
	    ChangeTipElementsUtilities TipElements;
	    if(mVariables[MeshId].avoid_tip_elements){
	      //TipElements.SwapDiagonals(rModelPart,MeshId);
	    }
	  }
	}		
	    
	    
      //NEIGHBOURS SEARCH
      NodalNeighboursSearchProcess FindNeighbours(rModelPart);
      FindNeighbours.Execute();

      //NODAL_H SEARCH	    
      //FindNodalHProcess FindNodalH(rModelPart);
      //FindNodalH.Execute();

      //CONDITIONS MASTER_ELEMENTS and MASTER_NODES SEARCH
      BoundarySkinBuildProcess BoundarySkinProcess(rModelPart);
      for(unsigned int MeshId=start; MeshId<NumberOfMeshes; MeshId++)
	{
	  BoundarySkinProcess.SearchConditionMasters(MeshId);
	}

      //BOUNDARY NORMALS SEARCH // SHRINKAGE FACTOR
      //ComputeBoundaryNormals BoundUtils;
      BoundaryNormalsCalculationUtilities BoundaryComputation;
      BoundaryComputation.CalculateBoundaryNormals(rModelPart,2);

      //LAPLACIAN SMOOTHING
      for(unsigned int MeshId=start; MeshId<NumberOfMeshes; MeshId++)
	{
	  if(mVariables[MeshId].mesh_smoothing){
	    //MeshGeometricSmooth.ApplyMeshSmoothing(rModelPart,LaplacianSmoothing::SMOOTH_ALL,MeshId);
	  }
		  
	  if(mVariables[MeshId].jacobi_smoothing ){
	    //recover DETERMINANT_F FOR VARIABLES SMOOTHING from nodes
	    MeshDataTransfer.TransferNodalValuesToElements(DETERMINANT_F,rModelPart,MeshId);
	  }

	}

    }
	  
  }

  
  //*******************************************************************************************
  //*******************************************************************************************
  void TriangleMesh2DModeler::PerformTransferOnly(ModelPart& rModelPart,
					   MeshingVariables & rVariables,
					   ModelPart::IndexType MeshId)
  {

    KRATOS_TRY

      std::cout<<" [ [ [ ] ] ]"<<std::endl;
    std::cout<<" [ Trigen PFEM Transfer Only ]"<<std::endl;
    std::cout<<" [ PREVIOUS MESH (Elements: "<<rModelPart.NumberOfElements(MeshId)<<" Nodes: "<<rModelPart.NumberOfNodes(MeshId)<<" Conditions: "<<rModelPart.NumberOfConditions(MeshId)<<") ] MESH_ID: ["<<MeshId<<"]"<<std::endl;


    //*********************************************************************
    struct triangulateio in;
    struct triangulateio out;

	
    rVariables.idset=false;

    rVariables.MeshingOptions.Set(Modeler::SET_DOF);
    SetTriangulateNodes(rModelPart,rVariables,in,out,MeshId);
    rVariables.MeshingOptions.Reset(Modeler::SET_DOF);


    //*********************************************************************
    //input mesh: ELEMENTS
    in.numberoftriangles = rModelPart.Elements(MeshId).size();
    in.trianglelist = (int*) malloc(in.numberoftriangles * 3 * sizeof(int));
    in.neighborlist = (int*) malloc(in.numberoftriangles * 3 * sizeof(int));

    //copying the elements in the input file	    
    ModelPart::ElementsContainerType::iterator elem_begin = rModelPart.ElementsBegin(MeshId);

    int base=0;
    for(unsigned int el = 0; el<rModelPart.Elements(MeshId).size(); el++)
      {
	(elem_begin+el)->SetId(el+1);
	Geometry<Node<3> >& geom = (elem_begin+el)->GetGeometry();

	in.trianglelist[base]   = geom[0].Id();
	in.trianglelist[base+1] = geom[1].Id();
	in.trianglelist[base+2] = geom[2].Id();
	base+=3;
      }

	
    for(unsigned int el = 0; el<rModelPart.Elements(MeshId).size(); el++)
      {
	// Geometry<Node<3> >& geom = (elem_begin+el)->GetGeometry();
	WeakPointerVector<Element >& rE = (elem_begin+el)->GetValue(NEIGHBOUR_ELEMENTS);

	for(int pn=0; pn<3; pn++){
	  if( (elem_begin+el)->Id() == rE[pn].Id() )
	    in.neighborlist[el*3+pn] = 0;
	  else
	    in.neighborlist[el*3+pn] = rE[pn].Id();
	}
	      
      }
	  
    rVariables.RefiningOptions.Set(Modeler::SELECT_ELEMENTS);
    rVariables.RefiningOptions.Set(Modeler::PASS_ALPHA_SHAPE);	  

    SetModelElements(rModelPart,rVariables,in,MeshId);

    rVariables.RefiningOptions.Reset(Modeler::PASS_ALPHA_SHAPE);
    rVariables.RefiningOptions.Reset(Modeler::SELECT_ELEMENTS);

    //filling the neighbour list
    SetElementNeighbours(rModelPart,rVariables,MeshId);
	  
    //identifying boundary, creating model skin
    SetConditionsBoundary(rModelPart,rVariables,MeshId);

    //free memory
    free_pointio(in);
    //delete [] in.trianglelist;


    std::cout<<" [ NEW MESH (Elements: "<<rModelPart.Elements(MeshId).size()<<" Nodes: "<<rModelPart.Nodes(MeshId).size()<<" Conditions: "<<rModelPart.Conditions(MeshId).size()<<" ] "<<std::endl;
    std::cout<<" [ Finished Remeshing ] "<<std::endl;
    std::cout<<" [ [ [ ] ] ]"<<std::endl;


    KRATOS_CATCH( "" )
      }

  
  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::GenerateDT (ModelPart& rModelPart,
				   MeshingVariables &rVariables,
				   ModelPart::IndexType MeshId)
  {

    KRATOS_TRY
 
      std::cout<<" [ [ [ ] ] ]"<<std::endl;
    std::cout<<" [ Trigen PFEM DT Mesher ]"<<std::endl;
    std::cout<<" [ PREVIOUS MESH (Elements: "<<rModelPart.NumberOfElements(MeshId)<<" Nodes: "<<rModelPart.NumberOfNodes(MeshId)<<" Conditions: "<<rModelPart.NumberOfConditions(MeshId)<<") ] MESH_ID: ["<<MeshId<<"]"<<std::endl;
		  
    //int step_data_size = rModelPart.GetNodalSolutionStepDataSize();

    if(rVariables.refine){

      rVariables.RefiningOptions.Set(Modeler::REMOVE_NODES);
      rVariables.RefiningOptions.Set(Modeler::CRITERION_DISTANCE);
      ////////////////////////////////////////////////////////////
      RemoveCloseNodes (rModelPart,rVariables,MeshId);
      ////////////////////////////////////////////////////////////
      rVariables.RefiningOptions.Reset(Modeler::CRITERION_DISTANCE);
      rVariables.RefiningOptions.Reset(Modeler::REMOVE_NODES);
    }


    ////////////////////////////////////////////////////////////
    //Creating the containers for the input and output
    struct triangulateio in;
    struct triangulateio out;

    rVariables.idset=false;

    rVariables.MeshingOptions.Set(Modeler::SET_DOF);
    SetTriangulateNodes(rModelPart,rVariables,in,out,MeshId);
    rVariables.MeshingOptions.Reset(Modeler::SET_DOF);
    ////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////
    boost::timer auxiliary;

    rVariables.MeshingOptions.Set(Modeler::NEIGHBOURS_SEARCH);
    GenerateTriangulation(rVariables.MeshingOptions,rVariables.RefiningOptions,in,out);
    rVariables.MeshingOptions.Reset(Modeler::NEIGHBOURS_SEARCH);

    //print out the mesh generation time
    std::cout<<" [ MESH GENERATION (TIME = "<<auxiliary.elapsed()<<") ] "<<std::endl;
    ////////////////////////////////////////////////////////////

    if(rVariables.refine){
	  
      ////////////////////////////////////////////////////////////
      //Select Elements to be preserved after passing Alpha-Shape
      rVariables.RefiningOptions.Set(Modeler::PASS_ALPHA_SHAPE);
      rVariables.RefiningOptions.Set(Modeler::SELECT_ELEMENTS);
	  	  
      SelectMeshElements(rModelPart.Nodes(MeshId),rVariables,out); //passing alpha shape and returning the Elements preserved  

      rVariables.RefiningOptions.Reset(Modeler::SELECT_ELEMENTS);
      rVariables.RefiningOptions.Reset(Modeler::PASS_ALPHA_SHAPE);
      ////////////////////////////////////////////////////////////

      //free the memory used in the first step, preserve out
      free_pointio(in);
      free_triangleio(in);
 	  
      ////////////////////////////////////////////////////////////
      //PERFORM ADAPTIVE REMESHING:
      struct triangulateio mid_out;

      rVariables.idset=false;
	  
      //i.e. insert and remove nodes based upon mesh quality and prescribed sizes	  
      SetTriangulateNodes (rModelPart,rVariables,in,mid_out,MeshId);
	  
      rVariables.RefiningOptions.Set(Modeler::REFINE_ELEMENTS);
      RefineElements (rModelPart,rVariables,in,out,MeshId);
      rVariables.RefiningOptions.Reset(Modeler::REFINE_ELEMENTS);
      ////////////////////////////////////////////////////////////

      //free the memory used in the first step, free out
      clean_triangulateio(out);

      ////////////////////////////////////////////////////////////
      rVariables.MeshingOptions.Set(Modeler::REFINE_MESH);
      rVariables.RefiningOptions.Set(Modeler::REFINE_ADD_NODES); //optional

      GenerateTriangulation(rVariables.MeshingOptions,rVariables.RefiningOptions,in,out);

      rVariables.MeshingOptions.Reset(Modeler::REFINE_MESH);
      rVariables.RefiningOptions.Reset(Modeler::REFINE_ADD_NODES); //optional
      ////////////////////////////////////////////////////////////

      //Building the entities for new nodes:
      GenerateNewParticles(rModelPart,rVariables,in,out,MeshId);

      ////////////////////////////////////////////////////////////
    }
    else{

      rVariables.RefiningOptions.Set(Modeler::SELECT_ELEMENTS);
      rVariables.RefiningOptions.Set(Modeler::PASS_ALPHA_SHAPE);	  
    }


    //*********************************************************************
    //input mesh: NODES //to not perturb the node position because of the meshing
    out.numberofpoints = rModelPart.Nodes(MeshId).size();

    //writing the points coordinates in a vector and reordening the Id's
    ModelPart::NodesContainerType::iterator nodes_begin = rModelPart.NodesBegin(MeshId);

    //std::cout<<"  [ SET NODES: ";
    int base=0;
    for(unsigned int i = 0; i<rModelPart.Nodes(MeshId).size(); i++)
      {
	out.pointlist[base]   = (nodes_begin + i)->X();
	out.pointlist[base+1] = (nodes_begin + i)->Y();
	    
	base+=2;
      }
    //*********************************************************************

    ////////////////////////////////////////////////////////////
    SetModelElements(rModelPart,rVariables,out,MeshId);
    ////////////////////////////////////////////////////////////

    rVariables.RefiningOptions.Reset(Modeler::PASS_ALPHA_SHAPE);
    rVariables.RefiningOptions.Reset(Modeler::SELECT_ELEMENTS);
	
    //filling the neighbour list
    SetElementNeighbours(rModelPart,rVariables,MeshId);
	
    //identifying boundary, creating model skin
    SetConditionsBoundary(rModelPart,rVariables, MeshId);

    //sort elements
    //rModelPart.Elements().Sort();

    //free memory
    free_pointio(in);
    delete [] in.trianglelist;
    free_triangleio(out);

    std::cout<<" [ NEW MESH (Elements: "<<rModelPart.Elements(MeshId).size()<<" Nodes: "<<rModelPart.Nodes(MeshId).size()<<" Conditions: "<<rModelPart.Conditions(MeshId).size()<<" ] "<<std::endl;
    std::cout<<" [ Finished Remeshing ] "<<std::endl;
    std::cout<<" [ [ [ ] ] ]"<<std::endl;

    KRATOS_CATCH( "" )
      }



  //*******************************************************************************************
  //*******************************************************************************************
  void TriangleMesh2DModeler::GenerateCDT(ModelPart& rModelPart,
				   MeshingVariables & rVariables,
				   ModelPart::IndexType MeshId)
  {

    KRATOS_TRY

      std::cout<<" [ [ [ ] ] ]"<<std::endl;
    std::cout<<" [ Trigen PFEM Conforming Constrained Delaunay Mesher ]"<<std::endl;
    std::cout<<" [ PREVIOUS MESH (Elements: "<<rModelPart.NumberOfElements(MeshId)<<" Nodes: "<<rModelPart.NumberOfNodes(MeshId)<<" Conditions: "<<rModelPart.NumberOfConditions(MeshId)<<") ] MESH_ID: ["<<MeshId<<"]"<<std::endl;


    //*********************************************************************
    struct triangulateio in;
    struct triangulateio out;

    rVariables.idset=false;

    SetTriangulateNodes(rModelPart,rVariables,in,out,MeshId);

    //*********************************************************************
    //input mesh: ELEMENTS
    in.numberoftriangles = rModelPart.Elements(MeshId).size();
    in.trianglelist = (int*) malloc(in.numberoftriangles * 3 * sizeof(int));

    //copying the elements in the input file	    


    ModelPart::ElementsContainerType::iterator elem_begin = rModelPart.ElementsBegin(MeshId);

    int base=0;
    for(unsigned int el = 0; el<rModelPart.Elements(MeshId).size(); el++)
      {
	Geometry<Node<3> >& geom = (elem_begin+el)->GetGeometry();

	in.trianglelist[base]   = geom[0].Id();
	in.trianglelist[base+1] = geom[1].Id();
	in.trianglelist[base+2] = geom[2].Id();
	base+=3;
      }
	
    ////////////////////////////////////////////////////////////

    //read and regenerate the existing mesh ... to generate the boundaries
    struct triangulateio mid;
    clean_triangulateio(mid);

    rVariables.MeshingOptions.Set(Modeler::BOUNDARIES_SEARCH);
    GenerateTriangulation(rVariables.MeshingOptions,rVariables.RefiningOptions,in, mid);
    rVariables.MeshingOptions.Reset(Modeler::BOUNDARIES_SEARCH);

    // KRATOS_WATCH( in.numberofsegments )
    // KRATOS_WATCH( in.numberofpoints )
    // KRATOS_WATCH( in.numberoftriangles )
    // KRATOS_WATCH( in.numberofholes )

    //free the memory used in the first step
    free_pointio(in);
    free_triangleio(in);

    //uses the boundary list generated at the previous step to generate the "skin"
    mid.numberoftriangles = 0;
    delete [] mid.trianglelist; //delete only triangles

    rVariables.MeshingOptions.Set(Modeler::NEIGHBOURS_SEARCH);
    rVariables.MeshingOptions.Set(Modeler::CONSTRAINED_MESH);

    int fail = GenerateTriangulation(rVariables.MeshingOptions,rVariables.RefiningOptions,mid, out);

    if(fail){
      rVariables.MeshingOptions.Reset(Modeler::CONSTRAINED_MESH);
      fail = GenerateTriangulation(rVariables.MeshingOptions,rVariables.RefiningOptions,mid, out);
      rVariables.MeshingOptions.Set(Modeler::CONSTRAINED_MESH);
    }
    
    rVariables.MeshingOptions.Reset(Modeler::CONSTRAINED_MESH);
    rVariables.MeshingOptions.Reset(Modeler::NEIGHBOURS_SEARCH);

    // KRATOS_WATCH( out.numberofsegments )
    // KRATOS_WATCH( out.numberofpoints )
    // KRATOS_WATCH( out.numberoftriangles )
    // KRATOS_WATCH( out.numberofholes )
	
    ////////////////////////////////////////////////////////////

    SetModelElements(rModelPart,rVariables,out,MeshId);
		  
    ////////////////////////////////////////////////////////////
	
    //filling the neighbour list
    SetElementNeighbours(rModelPart,rVariables,MeshId);

    //identifying boundary, creating model skin
    SetConditionsBoundary(rModelPart,rVariables,MeshId);


    //free the memory used in the intermediate step
    //free_triangleio(mid);
    //free_pointio(mid);
    clean_triangulateio(mid);
    delete [] mid.trianglelist;

    //free the rest of the memory
    //free_triangleio(out);
    clean_triangulateio(out);
	

    std::cout<<" [ NEW MESH (Elements: "<<rModelPart.Elements(MeshId).size()<<" Nodes: "<<rModelPart.Nodes(MeshId).size()<<" Conditions: "<<rModelPart.Conditions(MeshId).size()<<" ] "<<std::endl;
    std::cout<<" [ Finished Remeshing ] "<<std::endl;
    std::cout<<" [ [ [ ] ] ]"<<std::endl;


    KRATOS_CATCH( "" )
      }



  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::GenerateRDT(ModelPart& rModelPart,
				    MeshingVariables & rVariables,
				    ModelPart::IndexType MeshId)
  {

    KRATOS_TRY


    std::cout<<" [ [ [ ] ] ]"<<std::endl;
    std::cout<<" [ Trigen PFEM DT Refine Mesher ]"<<std::endl;
    std::cout<<" [ PREVIOUS MESH (Elements: "<<rModelPart.NumberOfElements(MeshId)<<" Nodes: "<<rModelPart.NumberOfNodes(MeshId)<<" Conditions: "<<rModelPart.NumberOfConditions(MeshId)<<") ] MESH_ID: ["<<MeshId<<"]"<<std::endl;

		    
    //*********************************************************************

    //Needed in RefineElements
    ////////////////////////////////////////////////////////////
    SetDissipativeElements (rModelPart,rVariables,MeshId);  
    ////////////////////////////////////////////////////////////


    //*********************************************************************

    rVariables.RefiningOptions.Set(Modeler::REFINE_INSERT_NODES);
    rVariables.RefiningOptions.Set(Modeler::CRITERION_ENERGY);
    rVariables.RefiningOptions.Set(Modeler::REFINE_BOUNDARY);

    ////////////////////////////////////////////////////////////
    RefineBoundary (rModelPart,rVariables,MeshId);
    ////////////////////////////////////////////////////////////

    rVariables.RefiningOptions.Reset(Modeler::REFINE_BOUNDARY);
    rVariables.RefiningOptions.Reset(Modeler::CRITERION_ENERGY);
    rVariables.RefiningOptions.Reset(Modeler::REFINE_INSERT_NODES);

    //********************************************************************

    //we need to redefine tool_tip boundaries after refining them !!

    rVariables.RefiningOptions.Set(Modeler::REMOVE_NODES);
    rVariables.RefiningOptions.Set(Modeler::CRITERION_ERROR);
    rVariables.RefiningOptions.Set(Modeler::CRITERION_DISTANCE);
    rVariables.RefiningOptions.Set(Modeler::REMOVE_ON_BOUNDARY);

    ////////////////////////////////////////////////////////////
    RemoveCloseNodes (rModelPart,rVariables,MeshId);
    ////////////////////////////////////////////////////////////

    rVariables.RefiningOptions.Reset(Modeler::REMOVE_NODES);
    rVariables.RefiningOptions.Reset(Modeler::CRITERION_ERROR);
    rVariables.RefiningOptions.Reset(Modeler::CRITERION_DISTANCE);
    rVariables.RefiningOptions.Reset(Modeler::REMOVE_ON_BOUNDARY);


    ////////////////////////////////////////////////////////////
    //Creating the containers for the input and output
    struct triangulateio in;
    struct triangulateio out;

    rVariables.idset=false;

    rVariables.MeshingOptions.Set(Modeler::SET_DOF);
    SetTriangulateNodes(rModelPart,rVariables,in,out,MeshId);
    rVariables.MeshingOptions.Reset(Modeler::SET_DOF);
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    boost::timer auxiliary;

    rVariables.MeshingOptions.Set(Modeler::NEIGHBOURS_SEARCH);
    int fail = GenerateTriangulation(rVariables.MeshingOptions,rVariables.RefiningOptions,in,out);

    if(fail){
      std::cout<<" Mesher Failed first RCDT "<<std::endl;
    }

    rVariables.MeshingOptions.Reset(Modeler::NEIGHBOURS_SEARCH);

    if(in.numberofpoints!=out.numberofpoints){
      std::cout<<" [ MESH GENERATION FAILED: point insertion (initial = "<<in.numberofpoints<<" final = "<<out.numberofpoints<<") ] "<<std::endl;
    }

    //print out the mesh generation time
    std::cout<<" [ MESH GENERATION (TIME = "<<auxiliary.elapsed()<<") ] "<<std::endl;
    ////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////
    //Select Elements to be preserved after passing Alpha-Shape
    rVariables.RefiningOptions.Set(Modeler::PASS_ALPHA_SHAPE);
    rVariables.RefiningOptions.Set(Modeler::SELECT_ELEMENTS);
		
    SelectMeshElements(rModelPart.Nodes(MeshId),rVariables,out); //passing alpha shape and returning the Elements preserved

    rVariables.RefiningOptions.Reset(Modeler::SELECT_ELEMENTS);
    rVariables.RefiningOptions.Reset(Modeler::PASS_ALPHA_SHAPE);
    ////////////////////////////////////////////////////////////

    //free the memory used in the first step, preserve out
    free_pointio(in);
    free_triangleio(in);

    ////////////////////////////////////////////////////////////
    //PERFORM ADAPTIVE REMESHING:
    //1.- Select Triangles to Refine via changing the nodal_h
    struct triangulateio mid_out;

    rVariables.idset=true;
    SetTriangulateNodes (rModelPart,rVariables,in,mid_out,MeshId);

    ////////////////////////////////////////////////////////////
    rVariables.RefiningOptions.Set(Modeler::REFINE_ELEMENTS);
    rVariables.RefiningOptions.Set(Modeler::CRITERION_ENERGY);
    //rVariables.RefiningOptions.Set(Modeler::REFINE_BOUNDARY);
		
    RefineElements (rModelPart,rVariables,in,out,MeshId);

    //rVariables.RefiningOptions.Reset(Modeler::REFINE_BOUNDARY);
    rVariables.RefiningOptions.Reset(Modeler::REFINE_ELEMENTS);
    rVariables.RefiningOptions.Reset(Modeler::CRITERION_ENERGY);
    ////////////////////////////////////////////////////////////


    //free the memory used in the first step, free out
    clean_triangulateio(out);

    ////////////////////////////////////////////////////////////
    rVariables.MeshingOptions.Set(Modeler::REFINE_MESH);
    rVariables.RefiningOptions.Set(Modeler::REFINE_ADD_NODES); //optional

    fail = GenerateTriangulation(rVariables.MeshingOptions,rVariables.RefiningOptions,in,out);

    if(fail){
      std::cout<<" Mesher Failed second RCDT "<<std::endl;
    }

    rVariables.MeshingOptions.Reset(Modeler::REFINE_MESH);
    rVariables.RefiningOptions.Reset(Modeler::REFINE_ADD_NODES); //optional
    ////////////////////////////////////////////////////////////

    //Building the entities for new nodes:
    GenerateNewParticles(rModelPart,rVariables,in,out,MeshId);

    ////////////////////////////////////////////////////////////

    SetModelElements(rModelPart,rVariables,out,MeshId);

    ////////////////////////////////////////////////////////////

    //std::cout<<" Check After SetModelElements "<<std::endl;
    //mModelerUtilities.CheckParticles (rModelPart,MeshId);

    //filling the neighbour list
    SetElementNeighbours(rModelPart,rVariables,MeshId);

    //identifying boundary, creating model skin
    SetConditionsBoundary(rModelPart,rVariables,MeshId);


    //sort elements
    //rModelPart.Elements().Sort();

    //free memory
    free_pointio(in);
    delete [] in.trianglelist;
    free_triangleio(out);


    std::cout<<" [ NEW MESH (Elements: "<<rModelPart.Elements(MeshId).size()<<" Nodes: "<<rModelPart.Nodes(MeshId).size()<<" Conditions: "<<rModelPart.Conditions(MeshId).size()<<" ] "<<std::endl;
    std::cout<<" [ Finished Remeshing ] "<<std::endl;
    std::cout<<" [ [ [ ] ] ]"<<std::endl;

    KRATOS_CATCH( "" )
      }


  //*******************************************************************************************
  //*******************************************************************************************
  
  void TriangleMesh2DModeler::GenerateRCDT(ModelPart& rModelPart,
				     MeshingVariables & rVariables,
				     ModelPart::IndexType MeshId)
  {

    KRATOS_TRY


      std::cout<<" [ [ [ ] ] ]"<<std::endl;
    std::cout<<" [ Trigen PFEM CDT Refine Mesher ]"<<std::endl;
    std::cout<<" [ PREVIOUS MESH (Elements: "<<rModelPart.NumberOfElements(MeshId)<<" Nodes: "<<rModelPart.NumberOfNodes(MeshId)<<" Conditions: "<<rModelPart.NumberOfConditions(MeshId)<<") ] MESH_ID: ["<<MeshId<<"]"<<std::endl;

		    
    //*********************************************************************

    //Needed in RefineElements
    ////////////////////////////////////////////////////////////
    SetDissipativeElements (rModelPart,rVariables,MeshId);  
    ////////////////////////////////////////////////////////////


    rVariables.MeshingOptions.Set(Modeler::CONSTRAINED_MESH);

    //*********************************************************************

    rVariables.RefiningOptions.Set(Modeler::REFINE_INSERT_NODES);
    rVariables.RefiningOptions.Set(Modeler::CRITERION_ENERGY);
    rVariables.RefiningOptions.Set(Modeler::REFINE_BOUNDARY);

    ////////////////////////////////////////////////////////////
    RefineBoundary (rModelPart,rVariables,MeshId);
    ////////////////////////////////////////////////////////////

    rVariables.RefiningOptions.Reset(Modeler::REFINE_BOUNDARY);
    rVariables.RefiningOptions.Reset(Modeler::CRITERION_ENERGY);
    rVariables.RefiningOptions.Reset(Modeler::REFINE_INSERT_NODES);

    //*********************************************************************

    //we need to redefine tool_tip boundaries after refining them !!

    rVariables.RefiningOptions.Set(Modeler::REMOVE_NODES);
    rVariables.RefiningOptions.Set(Modeler::CRITERION_ERROR);
    rVariables.RefiningOptions.Set(Modeler::CRITERION_DISTANCE);
    rVariables.RefiningOptions.Set(Modeler::REMOVE_ON_BOUNDARY);

    ////////////////////////////////////////////////////////////
    RemoveCloseNodes (rModelPart,rVariables,MeshId);
    ////////////////////////////////////////////////////////////

    rVariables.RefiningOptions.Reset(Modeler::REMOVE_NODES);
    rVariables.RefiningOptions.Reset(Modeler::CRITERION_ERROR);
    rVariables.RefiningOptions.Reset(Modeler::CRITERION_DISTANCE);
    rVariables.RefiningOptions.Reset(Modeler::REMOVE_ON_BOUNDARY);


    ////////////////////////////////////////////////////////////
    //Creating the containers for the input and output
    struct triangulateio in;
    struct triangulateio out;

    rVariables.idset=false;

    rVariables.MeshingOptions.Set(Modeler::SET_DOF);
    SetTriangulateNodes(rModelPart,rVariables,in,out,MeshId); 
    rVariables.MeshingOptions.Reset(Modeler::SET_DOF);
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    boost::timer auxiliary;

    rVariables.MeshingOptions.Set(Modeler::NEIGHBOURS_SEARCH);

    int fail = GenerateTriangulation(rVariables.MeshingOptions,rVariables.RefiningOptions,in,out);

    if(fail){
      rVariables.MeshingOptions.Reset(Modeler::CONSTRAINED_MESH);
      fail = GenerateTriangulation(rVariables.MeshingOptions,rVariables.RefiningOptions,in, out);
      rVariables.MeshingOptions.Set(Modeler::CONSTRAINED_MESH);
    }

    rVariables.MeshingOptions.Reset(Modeler::NEIGHBOURS_SEARCH);

    if(in.numberofpoints!=out.numberofpoints){
      std::cout<<" [ MESH GENERATION FAILED: point insertion (initial = "<<in.numberofpoints<<" final = "<<out.numberofpoints<<") ] "<<std::endl;
    }

    if( rVariables.MeshingOptions.Is(Modeler::CONSTRAINED_MESH) )
      RecoverBoundaryPosition(rModelPart,rVariables,in,out,MeshId);

    //print out the mesh generation time
    std::cout<<" [ MESH GENERATION (TIME = "<<auxiliary.elapsed()<<") ] "<<std::endl;
    ////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////
    //Select Elements to be preserved after passing Alpha-Shape
    rVariables.RefiningOptions.Set(Modeler::PASS_ALPHA_SHAPE);
    rVariables.RefiningOptions.Set(Modeler::SELECT_ELEMENTS);
    rVariables.RefiningOptions.Set(Modeler::ENGAGED_NODES);

    SelectMeshElements(rModelPart.Nodes(MeshId),rVariables,out); //passing alpha shape and returning the Elements preserved

    rVariables.RefiningOptions.Reset(Modeler::ENGAGED_NODES);
    rVariables.RefiningOptions.Reset(Modeler::SELECT_ELEMENTS);
    rVariables.RefiningOptions.Reset(Modeler::PASS_ALPHA_SHAPE);
    ////////////////////////////////////////////////////////////

    //free the memory used in the first step, preserve out
    free_pointio(in);
    free_triangleio(in);

    ////////////////////////////////////////////////////////////
    //PERFORM ADAPTIVE REMESHING:
    //1.- Select Triangles to Refine via changing the nodal_h
    struct triangulateio mid_out;

    rVariables.idset=false;
    SetTriangulateNodes (rModelPart,rVariables,in,mid_out,MeshId);

    ////////////////////////////////////////////////////////////
    rVariables.RefiningOptions.Set(Modeler::REFINE_ELEMENTS);
    rVariables.RefiningOptions.Set(Modeler::CRITERION_ENERGY);
    rVariables.RefiningOptions.Set(Modeler::REFINE_BOUNDARY);

    RefineElements (rModelPart,rVariables,in,out,MeshId);

    rVariables.RefiningOptions.Reset(Modeler::REFINE_BOUNDARY);
    rVariables.RefiningOptions.Reset(Modeler::REFINE_ELEMENTS);
    rVariables.RefiningOptions.Reset(Modeler::CRITERION_ENERGY);
    ////////////////////////////////////////////////////////////


    //free the memory used in the first step, free out
    clean_triangulateio(out);

    ////////////////////////////////////////////////////////////
    //to generate it constrained it is necessary to change the strategy:
    //a. pass a set of nodes to triangulate ok
    //b. pass a set of segments == conditions to apply the constraint ok
    //c. pass a set of holes if domains are not totally convex. ok
	
    rVariables.MeshingOptions.Set(Modeler::NEIGHBOURS_SEARCH);
    rVariables.MeshingOptions.Set(Modeler::REFINE_MESH);
    rVariables.RefiningOptions.Set(Modeler::REFINE_ADD_NODES); //optional

    fail = GenerateTriangulation(rVariables.MeshingOptions,rVariables.RefiningOptions,in,out);

    if(fail){
      rVariables.MeshingOptions.Reset(Modeler::CONSTRAINED_MESH);
      fail = GenerateTriangulation(rVariables.MeshingOptions,rVariables.RefiningOptions,in, out);
      rVariables.MeshingOptions.Set(Modeler::CONSTRAINED_MESH);
    }

    rVariables.MeshingOptions.Reset(Modeler::REFINE_MESH);
    rVariables.RefiningOptions.Reset(Modeler::REFINE_ADD_NODES); //optional
    rVariables.MeshingOptions.Reset(Modeler::NEIGHBOURS_SEARCH);


    if( rVariables.MeshingOptions.Is(Modeler::CONSTRAINED_MESH) )
      RecoverBoundaryPosition(rModelPart,rVariables,in,out,MeshId);

    ////////////////////////////////////////////////////////////

    //Building the entities for new nodes:
    GenerateNewParticles(rModelPart,rVariables,in,out,MeshId);

    ////////////////////////////////////////////////////////////

    SetModelElements(rModelPart,rVariables,out,MeshId);

    ////////////////////////////////////////////////////////////

    //std::cout<<" Check After SetModelElements "<<std::endl;
    //mModelerUtilities.CheckParticles (rModelPart,MeshId);

    //filling the neighbour list
    SetElementNeighbours(rModelPart,rVariables,MeshId);

    //identifying boundary, creating model skin
    SetConditionsBoundary(rModelPart,rVariables,MeshId);


    rVariables.MeshingOptions.Reset(Modeler::CONSTRAINED_MESH);

    //sort elements
    //rModelPart.Elements().Sort();

    //free memory
    free_pointio(in);
    delete [] in.trianglelist;
    free_triangleio(out);


    std::cout<<" [ NEW MESH (Elements: "<<rModelPart.Elements(MeshId).size()<<" Nodes: "<<rModelPart.Nodes(MeshId).size()<<" Conditions: "<<rModelPart.Conditions(MeshId).size()<<" ] "<<std::endl;
    std::cout<<" [ Finished Remeshing ] "<<std::endl;
    std::cout<<" [ [ [ ] ] ]"<<std::endl;

    KRATOS_CATCH( "" )
      }
    

  //*******************************************************************************************
  //*******************************************************************************************


  void TriangleMesh2DModeler::clean_triangulateio(struct triangulateio& tr )
  {

    tr.pointlist                  = (REAL*) NULL;
    tr.pointattributelist         = (REAL*) NULL;
    tr.pointmarkerlist            = (int*) NULL;
    tr.numberofpoints             = 0;
    tr.numberofpointattributes    = 0;

    tr.trianglelist               = (int*) NULL;
    tr.triangleattributelist      = (REAL*) NULL;
    tr.trianglearealist           = (REAL*) NULL;
    tr.neighborlist               = (int*) NULL;
    tr.numberoftriangles          = 0;
    tr.numberofcorners            = 3; //for three node triangles
    tr.numberoftriangleattributes = 0;

    tr.segmentlist                = (int*) NULL;
    tr.segmentmarkerlist          = (int*) NULL;
    tr.numberofsegments           = 0;

    tr.holelist                   = (REAL*) NULL;
    tr.numberofholes              = 0;

    tr.regionlist                 = (REAL*) NULL;
    tr.numberofregions            = 0;

    tr.edgelist                   = (int*) NULL;
    tr.edgemarkerlist             = (int*) NULL;
    tr.normlist                   = (REAL*) NULL;
    tr.numberofedges              = 0;

  }

  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::clear_triangulateio(struct triangulateio& tr )
  {
    if(tr.pointlist != NULL) free(tr.pointlist );
    if(tr.pointattributelist != NULL) free(tr.pointattributelist );
    if(tr.pointmarkerlist != NULL) free(tr.pointmarkerlist   );
     
    if(tr.trianglelist != NULL) free(tr.trianglelist  );
    if(tr.triangleattributelist != NULL) free(tr.triangleattributelist );
    if(tr.trianglearealist != NULL) free(tr.trianglearealist );
    if(tr.neighborlist != NULL) free(tr.neighborlist   );

    if(tr.segmentlist != NULL) free(tr.segmentlist    );
    if(tr.segmentmarkerlist != NULL) free(tr.segmentmarkerlist   );

    if(tr.holelist != NULL) free(tr.holelist      );

    if(tr.regionlist != NULL) free(tr.regionlist  );

    if(tr.edgelist != NULL) free(tr.edgelist   );
    if(tr.edgemarkerlist != NULL) free(tr.edgemarkerlist   );
    if(tr.normlist != NULL) free(tr.normlist  );
  }

  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::free_triangleio(struct triangulateio& tr )
  {

    //always for "out":
    trifree (tr.trianglelist);

    delete [] tr.triangleattributelist;
    delete [] tr.trianglearealist;

    //in case of n switch not used
    //delete [] tr.neighborlist;

    //if p is switched then in and out are pointed:(free only once)
    //delete [] tr.segmentlist;
    //delete [] tr.segmentmarkerlist;

    delete [] tr.holelist;
    delete [] tr.regionlist;

    //delete [] tr.edgelist;
    //delete [] tr.edgemarkerlist;


  }

  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::free_pointio (struct triangulateio& tr )
  {
    delete [] tr.pointlist;
    delete [] tr.pointmarkerlist;
    delete [] tr.pointattributelist;
  }

  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::SetTriangulateNodes (ModelPart &rModelPart,
					    MeshingVariables & rVariables,
					    struct triangulateio &in,
					    struct triangulateio &out,
					    ModelPart::IndexType MeshId)
  {

    clean_triangulateio(in);
    clean_triangulateio(out);

    //*********************************************************************
    //input mesh: NODES
    in.numberofpoints = rModelPart.Nodes(MeshId).size();
    in.pointlist      = new REAL[in.numberofpoints * 2];

    if(!rVariables.idset){
      rVariables.PreIds.resize(in.numberofpoints+1);
      std::fill( rVariables.PreIds.begin(), rVariables.PreIds.end(), 0 );

      rVariables.NewIds.resize(rModelPart.Nodes().size()+1);
      std::fill( rVariables.NewIds.begin(), rVariables.NewIds.end(), 0 );
    }
	 
    //writing the points coordinates in a vector and reordening the Id's
    ModelPart::NodesContainerType::iterator nodes_begin = rModelPart.NodesBegin(MeshId);

    //std::cout<<"  [ SET NODES: ";
    int base=0;
    int direct = 1;
    for(unsigned int i = 0; i<rModelPart.Nodes(MeshId).size(); i++)
      {
	//if( (nodes_begin + i)->IsNot(STRUCTURE) ){
	//from now on it is consecutive
	if(!rVariables.idset){
	  //std::cout<<" "<<(nodes_begin + i)->Id()<<"(";
	  rVariables.NewIds[(nodes_begin + i)->Id()] = direct;
	  rVariables.PreIds[direct]=(nodes_begin + i)->Id();
	  (nodes_begin + i)->SetId(direct);
	}
	   
	if(rVariables.MeshingOptions.Is(Modeler::CONSTRAINED_MESH)){

	  if( (nodes_begin + i)->Is(BOUNDARY) ){
	       
	    array_1d<double, 3>&  Normal=(nodes_begin + i)->FastGetSolutionStepValue(NORMAL); //BOUNDARY_NORMAL must be set as nodal variable
	    double Shrink = (nodes_begin + i)->FastGetSolutionStepValue(SHRINK_FACTOR);   //SHRINK_FACTOR   must be set as nodal variable
	       
	    //if normal not normalized
	    //Shrink /=norm_2(Normal);
	    
	    array_1d<double, 3> Offset;

	    //std::cout<<" Shrink "<<Shrink<<" offset "<<rVariables.offset_factor<<std::endl;
	    Normal /= norm_2(Normal);
	    Offset[0] = ((-1)*Normal[0]*Shrink*rVariables.offset_factor*0.25);
	    Offset[1] = ((-1)*Normal[1]*Shrink*rVariables.offset_factor*0.25);

	    //std::cout<<" off[0] "<<Offset[0]<<" off[1] "<<Offset[0]<<std::endl;

	    in.pointlist[base]   = (nodes_begin + i)->X() + Offset[0];
	    in.pointlist[base+1] = (nodes_begin + i)->Y() + Offset[1];
	  }
	  else{
	    in.pointlist[base]   = (nodes_begin + i)->X();
	    in.pointlist[base+1] = (nodes_begin + i)->Y();
	  }

	}
	else{
	  in.pointlist[base]   = (nodes_begin + i)->X();
	  in.pointlist[base+1] = (nodes_begin + i)->Y();
	}
	   
	//std::cout<<(nodes_begin + i)->X()<<", "<<(nodes_begin + i)->Y()<<") ";
	    
	if(rVariables.MeshingOptions.Is(Modeler::SET_DOF))
	  {
	    Node<3>::DofsContainerType& node_dofs = (nodes_begin + i)->GetDofs();
	    for(Node<3>::DofsContainerType::iterator iii = node_dofs.begin(); iii != node_dofs.end(); iii++)
	      {
		iii->SetId(direct);
	      }
	  }
	    
	base+=2;
	direct+=1;
	// }
	//std::cout<<" node: (local:"<<(nodes_begin + i)->Id()<<", global: "<<rVariables.PreIds[(nodes_begin + i)->Id()]<<") "<<std::endl;
      }


    // std::cout<<"), "<<std::endl;
    //std::cout<<"    SET NODES ]; "<<std::endl;

    if(!rVariables.idset){
      rVariables.idset=true;
    }
    //*********************************************************************

    //SetFaces (segments)

    //PART 1: node list

    if(rVariables.MeshingOptions.Is(Modeler::CONSTRAINED_MESH)){

      //PART 2: faced list (we can have holes in facets != area holes)
      in.numberofsegments           = rModelPart.NumberOfConditions(MeshId);
      in.segmentmarkerlist          = new int[in.numberofsegments];
      in.segmentlist                = new int[in.numberofsegments*2];


      ModelPart::ConditionsContainerType::iterator conditions_begin = rModelPart.ConditionsBegin(MeshId);


      base = 0;
      for(unsigned int i = 0; i<rModelPart.Conditions(MeshId).size(); i++)
	{
	  Geometry< Node<3> >& rGeometry = (conditions_begin + i)->GetGeometry();
	  in.segmentlist[base]   = rGeometry[0].Id();
	  in.segmentlist[base+1] = rGeometry[1].Id();
	      
	  base+=2;
	}  

      //PART 3: (area) hole list

      //holes
      in.numberofholes              = 0;
      in.holelist                   = (REAL*) NULL;

      //PART 4: region attributes list
      in.numberofregions            = 1;
      in.regionlist                 = new REAL[in.numberofregions * 4];

      //regions
      double inside_factor = 2;
      Geometry< Node<3> >& rGeometry = (conditions_begin)->GetGeometry();
      array_1d<double, 3>&  Normal   = rGeometry[0].FastGetSolutionStepValue(NORMAL); 

      Normal /= norm_2(Normal);

      //inside point of the region:
      in.regionlist[0] = rGeometry[0][0]-((-1)*Normal[0]*rVariables.offset_factor*inside_factor);
      in.regionlist[1] = rGeometry[0][1]-((-1)*Normal[1]*rVariables.offset_factor*inside_factor);
	    
      //region attribute (regional attribute or marker "A" must be switched)
      in.regionlist[2] = MeshId; 

      //region maximum volume attribute (maximum area attribute "a" (with no number following) must be switched)
      in.regionlist[3] = -1;


    }
	
  }


  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::RefineElements (ModelPart &rModelPart,MeshingVariables &rVariables,struct triangulateio &in,struct triangulateio &out,ModelPart::IndexType MeshId)
  {

    std::cout<<" [ SELECT ELEMENTS TO REFINE : "<<std::endl;
    std::cout<<"   refine selection "<<std::endl;

    ProcessInfo& CurrentProcessInfo = rModelPart.GetProcessInfo();

    SpatialBoundingBox RefiningBox (rVariables.BoundingBox.Center,rVariables.BoundingBox.Radius,rVariables.BoundingBox.Velocity);


    if(rVariables.RefiningOptions.Is(Modeler::REFINE_ELEMENTS))
      {

	in.numberoftriangles=rVariables.Refine.NumberOfElements;

	in.trianglelist     = new int  [in.numberoftriangles * 3];
	in.trianglearealist = new REAL [in.numberoftriangles];

	ModelPart::NodesContainerType::iterator nodes_begin = rModelPart.NodesBegin(MeshId);

	//PREPARE THE NODAL_H as a variable to control the automatic point insertion
	//**************************************************************************

	if(rVariables.RefiningOptions.IsNot(Modeler::REFINE_BOUNDARY)){

	  for(unsigned int i = 0; i<rModelPart.Nodes(MeshId).size(); i++)
	    {
	      ////Assign a huge NODAL_H to the free surface nodes, so that there no nodes will be added
	      // if ( (nodes_begin + i)->Is(FREE_SURFACE))
	      // {
	      // 	double & nodal_h=(nodes_begin + i)->FastGetSolutionStepValue(NODAL_H);
	      // 	nodal_h*=2.0;
	      // }

	      //Assign a huge NODAL_H to the Boundary nodes, so that there no nodes will be added
	      if ( (nodes_begin + i)->Is(BOUNDARY))
		{
		  double & nodal_h=(nodes_begin + i)->FastGetSolutionStepValue(NODAL_H);
		  nodal_h*=2.0;
		}


	    }

	}

	//SET THE REFINED ELEMENTS AND THE AREA (NODAL_H)
	//*********************************************************************

	int id = 0; 
	double area_factor=0.95; //1
	    
	for(int el = 0; el< out.numberoftriangles; el++)
	  {
	    if(rVariables.PreservedElements[el])
	      {

		double prescribed_h      = 0;
		bool   dissipative       = false;
		bool   refine_size       = false;
		bool   boundary_size     = false;

		int    count_dissipative = 0;
		int    count_boundary_inserted = 0;
		int    count_boundary = 0;

		Geometry<Node<3> > vertices;

		for(int pn=0; pn<3; pn++)
		  {
		    in.trianglelist[id*3+pn]= out.trianglelist[el*3+pn];
		      
		    vertices.push_back(*(nodes_begin + out.trianglelist[el*3+pn]-1).base());

		    prescribed_h += (nodes_begin + out.trianglelist[el*3+pn]-1)->FastGetSolutionStepValue(NODAL_H);
		      
		    if((nodes_begin + out.trianglelist[el*3+pn]-1)->Is(TO_REFINE))
		      count_dissipative+=1;

		    if((nodes_begin + out.trianglelist[el*3+pn]-1)->Is(NEW_ENTITY))
		      count_boundary_inserted+=1;	      

		    if((nodes_begin + out.trianglelist[el*3+pn]-1)->Is(BOUNDARY))
		      count_boundary+=1;
		  }
		    
		// if(count_dissipative>0)
		//   std::cout<<" Count REFINE nodes "<<count_dissipative<<std::endl;
		//std::cout<<"   prescribed_h (el:"<<el<<") = "<<prescribed_h<<std::endl;
		  
		bool refine_candidate = true;
		if (rVariables.BoundingBox.is_set == true ){
		  refine_candidate = mModelerUtilities.CheckVerticesInBox(vertices,RefiningBox,CurrentProcessInfo);
		}
		  

		  		  
		double Area = 0;
		double element_radius = mModelerUtilities.CalculateCircRadius (vertices[0].X(),vertices[0].Y(),
							     vertices[1].X(),vertices[1].Y(),
							     vertices[2].X(),vertices[2].Y(),
							     Area);
		  
		if( refine_candidate ){


		  //********* PLASTIC POWER ENERGY REFINEMENT CRITERION (A)
		  if(count_dissipative>=2){
		    dissipative = true;
		    //std::cout<<" Dissipative True "<<std::endl;
		  }


		  //********* SIZE REFINEMENT CRITERION (B)

		  // if(dissipative)
		  //   std::cout<<" element_radius "<<element_radius<<" critical_radius "<<rVariables.Refine.critical_radius<<std::endl;

		  double boundary_margin = 1.0;
		  if( count_boundary >= 2 )
		    boundary_margin = 1.5;

		  if( element_radius > rVariables.Refine.critical_radius * boundary_margin ){
		    refine_size = true;
		    //std::cout<<" Critical Radius True "<<std::endl;
		  }

		  //refine_size = true;
		    
		  double boundary_insert_factor = 1.4;

		  if(count_boundary_inserted >= 1  &&  element_radius > rVariables.Refine.critical_radius*boundary_insert_factor ){  
		    boundary_size = true;
		  }


		  //Also a criteria for the critical_dissipation (set in nodes)
		  if(rVariables.RefiningOptions.Is(Modeler::CRITERION_ENERGY))
		    {

		      //********* PLASTIC POWER ENERGY REFINEMENT CRITERION (A)
		      if( (dissipative == true && refine_size == true) || (boundary_size == true) )
			{
			  //std::cout<<" Refine element on energy dissipation "<<std::endl;

			  //calculate the prescribed h
			  prescribed_h *= 0.3333;

			  //if h is the height of a equilateral triangle, the area is 1/2*h*h
			  //in.trianglearealist[id] = area_factor*0.5*(1.5*prescribed_h*1.5*prescribed_h);
			  in.trianglearealist[id] = area_factor*Area;
			}
		      else{

			//calculate the prescribed h
			prescribed_h *= 0.3333;

			//if h is the height of a equilateral triangle, the area is 1/2*h*h
			in.trianglearealist[id] = 0.5*(1.5*prescribed_h*1.5*prescribed_h);
			//in.trianglearealist[id] = 2*Area;
		      }
		    }
		  else
		    {
					    
		      //********* SIZE REFINEMENT CRITERION (B)
		      if( refine_size == true ){

			//calculate the prescribed h
			prescribed_h *= 0.3333;
				    
			//if h is the height of a equilateral triangle, the area is 1/2*h*h
			in.trianglearealist[id] = area_factor*0.5*(1.5*prescribed_h*1.5*prescribed_h);
		      }
		      else{

			//calculate the prescribed h
			prescribed_h *= 0.3333;

			//if h is the height of a equilateral triangle, the area is 1/2*h*h
			//in.trianglearealist[id] = 0.5*(1.5*prescribed_h*1.5*prescribed_h);
			in.trianglearealist[id] = Area;
		      }

		    }		    

		  //std::cout<<"   mod_prescribed_h (el:"<<el<<") = "<<prescribed_h<<" [ Triangle Area: "<<in.trianglearealist[id]<<" ]"<<std::endl;

		}
		else{


		  //calculate the prescribed h
		  prescribed_h *= 0.3333;
		    
		  //if h is the height of a equilateral triangle, the area is 1/2*h*h
		  //in.trianglearealist[id] = 0.5*(1.5*prescribed_h*1.5*prescribed_h);
		  in.trianglearealist[id] = 2*Area;

		}


		id += 1;					
		  	  
	      }



	  }



	//RESTORE THE NODAL_H ON BOUNDARY
	//*********************************************************************
	if(rVariables.RefiningOptions.IsNot(Modeler::REFINE_BOUNDARY)){

	  for(unsigned int i = 0; i<rModelPart.Nodes(MeshId).size(); i++)
	    {
	      // //Unassign the NODAL_H of the free surface nodes
	      // if ( (nodes_begin + i)->Is(FREE_SURFACE))
	      // {
	      // 	double & nodal_h=(nodes_begin + i)->FastGetSolutionStepValue(NODAL_H);
	      // 	nodal_h*=0.5;
	      // }

	      //Unassign the NODAL_H of the Boundary nodes
	      if ( (nodes_begin + i)->Is(BOUNDARY))
		{
		  double & nodal_h=(nodes_begin + i)->FastGetSolutionStepValue(NODAL_H);
		  nodal_h*=0.5;
		}


	    }
	}
      }

	
    //Check struct "in"
    //WriteTriangles(in);
    //WritePoints(in);

    std::cout<<"   SELECT ELEMENTS TO REFINE ]; "<<std::endl;
  }

  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::WriteTriangles  (struct triangulateio &in)
  { 
    for(int el = 0; el< in.numberoftriangles; el++)
      {
	std::cout<<"   TRIANGLE "<<el<<" : [ _";
	for(int pn=0; pn<3; pn++)
	  {
	    std::cout<<in.trianglelist[el*3+pn]<<"_";
	  }
	std::cout<<" ]   Area: "<<in.trianglearealist[el]<<std::endl;
      }   
  }

  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::WritePoints  (struct triangulateio &in)
  { 
    int base=0;
    for(int nd = 0; nd< in.numberofpoints; nd++)
      {
	std::cout<<"   Point "<<nd+1<<" : [ ";
	std::cout<<in.pointlist[base]<<" "<<in.pointlist[base+1]<<" ]"<<std::endl;;
	base+=2;
      }
  }

  //*******************************************************************************************
  //*******************************************************************************************

  int TriangleMesh2DModeler::GenerateTriangulation  (Flags &MeshingOptions,
					      Flags &RefiningOptions,
					      struct triangulateio &in,
					      struct triangulateio &out)
  {

    int fail=0;

    struct triangulateio vorout;

    //initilize all to avoid memory problems
    clean_triangulateio(vorout);

    //mesh options
    char  meshing_options[255];
    std::string meshing_info;
	
    //switches: https://www.cs.cmu.edu/~quake/triangle.switch.html


    if(MeshingOptions.Is(Modeler::CONSTRAINED_MESH) && MeshingOptions.Is(Modeler::NEIGHBOURS_SEARCH)){ //to mesh constrained delaunay
      strcpy (meshing_options, "pnBYYQ");
      meshing_info = "Constrained remeshing executed";
    }
    else if(MeshingOptions.Is(Modeler::BOUNDARIES_SEARCH) && MeshingOptions.Is(Modeler::NEIGHBOURS_SEARCH)){  //to get conectivities and boundaries only
      strcpy (meshing_options, "ncEBQ");
      meshing_info = "Boundaries-Neighbours remeshing executed";
    }
    else{

      if(MeshingOptions.Is(Modeler::BOUNDARIES_SEARCH)){  //to get conectivities and boundaries only
	strcpy (meshing_options, "rcEBQ");
	meshing_info = "Boundaries remeshing executed";
      }
	  
      if(MeshingOptions.Is(Modeler::NEIGHBOURS_SEARCH)){  //to get conectivities and neighbours only
	strcpy (meshing_options, "PneQ");
	meshing_info = "Neighbours remeshing executed";
      }

    }

    if(MeshingOptions.Is(Modeler::REFINE_MESH))
      {
	if(RefiningOptions.Is(Modeler::REFINE_INSERT_NODES)){ //to insert a set of given points and refine the mesh
	  strcpy (meshing_options, "riYYJQ");     // "riYYJQ"; //"riYYJQ" // "riJQ" //"riQ"
	  meshing_info = "Inserted remeshing executed";
	}
	else if(RefiningOptions.Is(Modeler::REFINE_ADD_NODES))  //to add_nodes automatically and refine the mesh ("q"-quality mesh and "a"-area constraint switches)
	  {
	    if( MeshingOptions.Is(Modeler::CONSTRAINED_MESH) )
	      {
		strcpy (meshing_options, "pYJq1.4arnC");  //"YYJaqrn" "YJq1.4arn" "Jq1.4arn"
		meshing_info = "Adaptive constrained remeshing executed";
	      }
	    else
	      {

		strcpy (meshing_options, "YJq1.4arnQ");  //"YYJaqrn" "YJq1.4arn" "Jq1.4arn"
		meshing_info = "Adaptive remeshing executed";
	      }


	  }
	else
	  //refine without adding nodes
	  {
	    strcpy (meshing_options, "YJrn");
	    meshing_info = "Non-Adaptive remeshing executed";
	  }

	    

      }

    if(MeshingOptions.Is(Modeler::RECONNECT)){  //to reconect a set of points only
      if(MeshingOptions.Is(Modeler::CONSTRAINED_MESH)){
	strcpy (meshing_options, "pBYYQ");
	meshing_info = "Constrained Reconnection remeshing executed";
      }
      else{
	strcpy (meshing_options, "QNP");
	meshing_info = "Reconnection remeshing executed";
      }
    }

    std::cout<<" [ REMESH: (in POINTS "<<in.numberofpoints<<") "<<std::endl;

    //perform the meshing
    try {
      triangulate (meshing_options,&in,&out,&vorout);
    }

    catch( int error_code ){

      switch(TriangleErrors(error_code))
	{
	case INPUT_MEMORY_ERROR:       fail=1;
	  break;
	case INTERNAL_ERROR:           fail=2;
	  break;
	case INVALID_GEOMETRY_ERROR:   fail=3;
	  break;
	default:                       fail=0;
	  //create new connections
	  std::cout<<" triangulation done "<<std::endl;
	  break;
	}
    }
    
    if(MeshingOptions.IsNot(Modeler::REFINE_MESH) && in.numberofpoints<out.numberofpoints){
      fail=3;
      std::cout<<"  fail error: [NODES ADDED] something is wrong with the geometry "<<std::endl;
    }
    
    std::cout<<"  -( "<<meshing_info<<" )- "<<std::endl;
    std::cout<<"  (out POINTS "<<out.numberofpoints<<") :  REMESH ]; "<<std::endl;
    std::cout<<std::endl;

    return fail;
  }

  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::RecoverBoundaryPosition   (ModelPart &rModelPart,
						  MeshingVariables & rVariables,
						  struct triangulateio &in,
						  struct triangulateio &out,
						  ModelPart::IndexType MeshId)
  {
    ModelPart::NodesContainerType::iterator nodes_begin = rModelPart.NodesBegin(MeshId);

    int base=0;
    for(unsigned int i = 0; i<rModelPart.Nodes(MeshId).size(); i++)
      { 
	   
	if( (nodes_begin + i)->Is(BOUNDARY) ){
	     
	  in.pointlist[base]   = (nodes_begin + i)->X();
	  in.pointlist[base+1] = (nodes_begin + i)->Y();
	     
	  out.pointlist[base]   = (nodes_begin + i)->X();
	  out.pointlist[base+1] = (nodes_begin + i)->Y();
	}
	   

	base+=2;
      }
  }

  //*******************************************************************************************
  //*******************************************************************************************

  //Select elements after the Delaunay Tesselation
  void TriangleMesh2DModeler::SelectMeshElements(ModelPart::NodesContainerType& rNodes,
					  MeshingVariables & rVariables,
					  struct triangulateio & out)
  {
    std::cout<<" [ SELECT MESH ELEMENTS: "<<std::endl;

    rVariables.PreservedElements.clear();
    rVariables.PreservedElements.resize(out.numberoftriangles);
    std::fill( rVariables.PreservedElements.begin(), rVariables.PreservedElements.end(), 0 );
	
    rVariables.Refine.NumberOfElements=0;
    
    bool box_side_element = false;
    bool wrong_added_node = false;
    if(rVariables.RefiningOptions.IsNot(Modeler::SELECT_ELEMENTS))
      {

	for(int el=0; el<out.numberoftriangles; el++)
	  {
	    rVariables.PreservedElements[el]=1;
	    rVariables.Refine.NumberOfElements+=1;
	  }
      }
    else
      {
	//std::cout<<" Start Element Selection "<<out.numberoftriangles<<std::endl;
	int el;
	int number=0;
	//#pragma omp parallel for reduction(+:number) private(el)
	for(el=0; el<out.numberoftriangles; el++)
	  {
	    Geometry<Node<3> > vertices;
	    //double Alpha   = 0;
	    //double nodal_h = 0;
	    //double param   = 0.3333333;

	    // int  numflying=0;
	    // int  numlayer =0;
	    //int  numfixed =0;

	    int  numfreesurf =0;
	    int  numboundary =0;

	    // std::cout<<" num nodes "<<rNodes.size()<<std::endl;
	    // std::cout<<" selected vertices [ "<<out.trianglelist[el*3]<<", "<<out.trianglelist[el*3+1]<<", "<<out.trianglelist[el*3+2]<<"] "<<std::endl;
	    box_side_element = false;
	    for(int pn=0; pn<3; pn++)
	      {
		//set vertices
		if(rVariables.PreIds[out.trianglelist[el*3+pn]]<0){
		  box_side_element = true;
		  break;
		}
		

		if( (unsigned int)out.trianglelist[el*3+pn] > rVariables.PreIds.size() ){
		  wrong_added_node = true;
		  std::cout<<" something is wrong: node out of bounds "<<std::endl;
		  break;
		}

		//vertices.push_back( *((rNodes).find( out.trianglelist[el*3+pn] ).base() ) );
		vertices.push_back(rNodes(out.trianglelist[el*3+pn]));

		//check flags on nodes
		if(vertices.back().Is(FREE_SURFACE))
		  numfreesurf++;

		if(vertices.back().Is(BOUNDARY))
		  numboundary++;

		// if(VertexPa[pn].match(_wall_))
		// 	numfixed++;

		// if(VertexPa[pn].match(_flying_))
		// 	numflying++;

		// if(VertexPa[pn].match(_layer_))
		// 	numlayer++;

		//nodal_h+=vertices.back().FastGetSolutionStepValue(NODAL_H);

	      }

	    if(box_side_element || wrong_added_node){
	      //std::cout<<" Box_Side_Element "<<std::endl;
	      continue;
	    }

	    //1.- to not consider wall elements
	    // if(numfixed==3)
	    //   Alpha=0;

	    //2.- alpha shape:
	    //Alpha  = nodal_h * param;
	    //Alpha *= Variables.AlphaParameter; //1.4; 1.35;

	    //2.1.- correction to avoid big elements on boundaries
	    // if(numflying>0){
	    //   Alpha*=0.8;
	    // }
	    // else{
	    //   if(numfixed+numsurf<=2){
	    //     //2.2.- correction to avoid voids in the fixed boundaries
	    //     if(numfixed>0)
	    // 	Alpha*=1.4;

	    //     //2.3.- correction to avoid voids on the free surface
	    //     if(numsurf>0)
	    // 	Alpha*=1.3;

	    //     //2.4.- correction to avoid voids in the next layer after fixed boundaries
	    //     if(numlayer>0 && !numsurf)
	    // 	Alpha*=1.2;
	    //   }

	    // }

	    //std::cout<<" ******** ELEMENT "<<el+1<<" ********** "<<std::endl;

	    double Alpha =  rVariables.AlphaParameter;
	    if(numboundary>=2)
	      Alpha*=1.8;
	
	    // std::cout<<" vertices for the contact element "<<std::endl;
	    // std::cout<<" (1): ["<<rVariables.PreIds[vertices[0].Id()]<<"] "<<vertices[0]<<std::endl;
	    // std::cout<<" (2): ["<<rVariables.PreIds[vertices[1].Id()]<<"] "<<vertices[1]<<std::endl;
	    // std::cout<<" (3): ["<<rVariables.PreIds[vertices[2].Id()]<<"] "<<vertices[2]<<std::endl;

	    // std::cout<<" vertices for the subdomain element "<<std::endl;
	    // std::cout<<" (1): ["<<vertices[0].Id()<<"] "<<vertices[0]<<std::endl;
	    // std::cout<<" (2): ["<<vertices[1].Id()<<"] "<<vertices[1]<<std::endl;
	    // std::cout<<" (3): ["<<vertices[2].Id()<<"] "<<vertices[2]<<std::endl;

	    // std::cout<<" Element "<<el<<" with alpha "<<rVariables.AlphaParameter<<"("<<Alpha<<")"<<std::endl;

	    bool accepted=false;

	    if(rVariables.RefiningOptions.Is(Modeler::CONTACT_SEARCH))
	      {
		accepted=mModelerUtilities.ShrankAlphaShape(Alpha,vertices,rVariables.offset_factor);
	      }
	    else
	      {
		accepted=mModelerUtilities.AlphaShape(Alpha,vertices);
	      }
		
	    //3.- to control all nodes from the same subdomain (problem, domain is not already set for new inserted particles on mesher)
	    // if(accepted)
	    // {
	    //   std::cout<<" Element passed Alpha Shape "<<std::endl;
	    //     if(rVariables.RefiningOptions.IsNot(Modeler::CONTACT_SEARCH))
	    //   	accepted=mModelerUtilities.CheckSubdomain(vertices);
	    // }

	    
	    //4.- to control that the element is inside of the domain boundaries
	    if(accepted)
	      {
		if(rVariables.RefiningOptions.Is(Modeler::CONTACT_SEARCH))
		  {
		    accepted=mModelerUtilities.CheckOuterCentre(vertices,rVariables.offset_factor);
		  }
		else
		  {
		    accepted=mModelerUtilities.CheckInnerCentre(vertices);
		  }
	      }

	    if(accepted)
	      {
		//std::cout<<" Element ACCEPTED after cheking Center "<<number<<std::endl;
		rVariables.PreservedElements[el] = 1;
		number+=1;
	      }

	  }

	rVariables.Refine.NumberOfElements=number;

      }

    //std::cout<<" Number of Preserved Elements "<<rVariables.Refine.NumberOfElements<<std::endl;

    if(rVariables.RefiningOptions.Is(Modeler::ENGAGED_NODES)){

      //check engaged nodes
      for(int el=0; el<out.numberoftriangles; el++)
	{
	  if( rVariables.PreservedElements[el]){
	    for(int pn=0; pn<3; pn++)
	      {
		//set vertices
		rNodes[out.trianglelist[el*3+pn]].Set(Modeler::ENGAGED_NODES);
	      }
	  }
	    
	}

      int count_release = 0;
      for(ModelPart::NodesContainerType::iterator i_node = rNodes.begin() ; i_node != rNodes.end() ; i_node++)
	{
	  if( i_node->IsNot(Modeler::ENGAGED_NODES)  ){
	    i_node->Set(TO_ERASE);
	    std::cout<<" NODE "<<i_node->Id()<<" RELEASE "<<std::endl;
	    if( i_node->IsNot(Modeler::ENGAGED_NODES) )
	      std::cout<<" ---//*******PROBLEMS : "<<i_node->Id()<<" IS BOUNDARY RELEASE "<<std::endl;
	    count_release++;
	  }
	      
	  i_node->Reset(Modeler::ENGAGED_NODES);
	}
	  
      std::cout<<"   NUMBER OF RELEASED NODES "<<count_release<<std::endl;

    }

    std::cout<<"   Generated_Elements :"<<out.numberoftriangles<<std::endl;
    std::cout<<"   Passed_AlphaShape  :"<<rVariables.Refine.NumberOfElements<<std::endl;
    std::cout<<"   SELECT MESH ELEMENTS ]; "<<std::endl;
 
  }

  //*******************************************************************************************
  //*******************************************************************************************
  
  //Set elements in model_part after the Delaunay Tesselation
  void TriangleMesh2DModeler::SetModelElements(ModelPart& rModelPart,
					MeshingVariables& rVariables,
					struct triangulateio &out,
					ModelPart::IndexType MeshId)
  {


    //*******************************************************************
    //clearing elements
    //rModelPart.Elements(MeshId).clear();

    //*******************************************************************
    //selecting elements
    rVariables.RefiningOptions.Set(Modeler::ENGAGED_NODES);
    SelectMeshElements(rModelPart.Nodes(MeshId),rVariables,out);
    rVariables.RefiningOptions.Reset(Modeler::ENGAGED_NODES);

    //*******************************************************************
    //setting new elements
    //(rModelPart.Elements(MeshId)).reserve(rVariables.Refine.NumberOfElements);

		
    //*******************************************************************
    //All nodes in boundary element change
    if(rVariables.avoid_tip_elements){ //is not working correctly some dispositions not considered
      std::cout<<"[   AVOID TIP ELEMENTS START ]"<<std::endl;

      ChangeTipElementsUtilities TipElements;
      //TipElements.SwapDiagonals(rModelPart,out,rVariables.PreservedElements,MeshId);

      std::cout<<"[   AVOID TIP ELEMENTS END ]"<<std::endl;
    }
    //*******************************************************************


    //properties to be used in the generation
    int number_properties = rModelPart.NumberOfProperties();
    Properties::Pointer properties = rModelPart.GetMesh(MeshId).pGetProperties(number_properties-1);
    ModelPart::NodesContainerType::iterator nodes_begin = rModelPart.NodesBegin(MeshId);

    // properties->PrintData(std::cout);
    // std::cout<<std::endl;

    const Element & rReferenceElement=rVariables.GetReferenceElement();

    PointPointerVector list_of_element_centers;
    std::vector<Geometry<Node<3> > > list_of_element_vertices;
    //find the center and "radius" of the element
    double xc, yc, zc=0, radius;


    //generate kratos elements (conditions are not touched)
    int id = 0;
    std::vector<std::vector<int> > EmptyNeighList;
    rVariables.NeighbourList.swap(EmptyNeighList); 
    rVariables.NeighbourList.clear(); //destroy all elements

    int faces = 0;
    for(int el = 0; el<out.numberoftriangles; el++)
      {
	if(rVariables.PreservedElements[el])
	  {
	    Geometry<Node<3> > vertices;
	    std::vector<int >  neighbours (3);
	
	    for(int pn=0; pn<3; pn++)
	      {
		//note that out.trianglelist, starts from node 1, not from node 0, it can be directly assigned to rVariables.PreIds.
		//vertices.push_back( *((model_nodes).find( rVariables.PreIds[out.trianglelist[el*3+pn]] ).base() ) );
		vertices.push_back(*(nodes_begin + out.trianglelist[el*3+pn]-1).base());
		//vertices.push_back(rModelPart.pGetNode(out.trianglelist[el*3+pn],MeshId));
		   
		if(vertices.back().Is(TO_ERASE))
		  std::cout<<" Problem, vertex RELEASED "<<vertices.back().Id()<<std::endl;
		  
		//std::cout<<" out.neighborlist "<<out.neighborlist[el*3+pn]<<std::endl;
		  		 
		if( out.neighborlist[el*3+pn]>0 )
		  {

		    if(rVariables.PreservedElements[ out.neighborlist[el*3+pn]-1 ])
		      {
			neighbours[pn]= out.neighborlist[el*3+pn];
		      }
		    else
		      {
			neighbours[pn]=-1;
			faces++;
		      }
		    
		  }
		else
		  {
		    neighbours[pn]=-1;
		    faces++;
		  }

		  

	      }


	    id += 1;

	    rVariables.PreservedElements[el] = id;
	    rVariables.NeighbourList.push_back(neighbours);
		
		
	    //std::cout<<" neigbours ["<<id<<"]: ("<<neighbours[0]<<", "<<neighbours[1]<<", "<<neighbours[2]<<") "<<std::endl;
		
	    //Pooyan: hacer transfer aqui: Tengo elementos antiguos, tengo nodos antiguos y nuevos creados: passar el out.numberoftriangles y el out.neighborlist;

	    //*******************************************************************
	    //1) Store Preserved elements in an array of vertices (Geometry<Node<3> > vertices;)

	    mMeshDataTransferUtilities.CalculateCenterAndSearchRadius( vertices[0].X(), vertices[0].Y(),
					    vertices[1].X(), vertices[1].Y(),
					    vertices[2].X(), vertices[2].Y(),
					    xc,yc,radius);

	    //std::cout<<" XC ["<<id<<"]: ("<<xc<<" "<<yc<<") "<<std::endl;
	    //std::cout<<" vertices "<<vertices[0].X()<<" "<<vertices[2].X()<<std::endl;
	    //*******************************************************************
		
	    PointPointerType p_center = PointPointerType( new PointType(id,xc,yc,zc) );

	    //*******************************************************************
	    //2) Create list_of_centers 

	    list_of_element_centers.push_back( p_center );
	    list_of_element_vertices.push_back( vertices );
		
	    //*******************************************************************
		
	    // std::cout<<" list of centers "<<list_of_element_centers.back()->X()<<" "<<list_of_element_centers.back()->Y()<<std::endl;
	    // std::cout<<" list of vertices ";
	    // std::cout.flush();
	    // std::cout<<" vertices "<<list_of_element_vertices.back()[0].X()<<" "<<list_of_element_vertices.back()[2].X()<<std::endl;
	    // std::cout.flush();

		

	  }
	else{
	  rVariables.PreservedElements[el] = -1;
	}
    
	    
	// if(rVariables.PreservedElements[el])
	//   {
	// 	std::cout<<" Neighbours ["<<id-1<<"] :";
	// 	for(int pn=0; pn<3; pn++)
	// 	  {
	// 	    std::cout<<" neighborlist ("<<pn<<") "<<rVariables.NeighbourList[id-1][pn]<<std::endl;
	// 	  }
	//   }

	//std::cout<<" PreIds ["<<el<<"] :"<<PreIds[el]<<std::endl;
		
      }

    std::cout<<" [ FACES "<<faces<<"]"<<std::endl;
	
    //*******************************************************************
    //5) Laplacian Smoothing
    //if(rVariables.smoothing && rVariables.remesh){
    if(rVariables.mesh_smoothing){
      LaplacianSmoothing  MeshGeometricSmooth(rModelPart);
      MeshGeometricSmooth.ApplyMeshSmoothing(rModelPart,rVariables.PreservedElements,out,list_of_element_vertices,MeshId);
    }
    //*******************************************************************


    //*******************************************************************
    //6) Pass  rReferenceElement and transfer variables
    MeshDataTransferUtilities    MeshDataTransfer;
    MeshDataTransfer.TransferData (rModelPart,rReferenceElement,list_of_element_centers,list_of_element_vertices,mMeshDataTransferUtilities.ELEMENT_TO_ELEMENT,MeshId);
    //*******************************************************************


    //*******************************************************************
    //std::cout<<" Number of Nodes "<<rModelPart.Nodes(MeshId).size()<<" Number Of Ids "<<rVariables.PreIds.size()<<std::endl;
	
    //7) Restore global ID's
    for(ModelPart::NodesContainerType::iterator in = rModelPart.NodesBegin(MeshId) ; in != rModelPart.NodesEnd(MeshId) ; in++)
      {
	//std::cout<<" node (local:"<<in->Id()<<", global:"<<rVariables.PreIds[ in->Id() ]<<")"<<std::endl;
	in->SetId( rVariables.PreIds[ in->Id() ] );
      }
    //*******************************************************************
	
	

  }

  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::RemoveCloseNodes(ModelPart& rModelPart, MeshingVariables& rVariables,ModelPart::IndexType MeshId)
  {
     
    std::cout<<" [ REMOVE CLOSE NODES: "<<std::endl;
    std::cout<<"   Nodes before erasing : "<<rModelPart.Nodes(MeshId).size()<<std::endl;

    bool any_node_removed = false;
	

    int error_remove = 0;
    int distance_remove = 0;
	
	
    //if the remove_node switch is activated, we check if the nodes got too close
    if (rVariables.RefiningOptions.Is(Modeler::REMOVE_NODES))
      {
	    	    
	////////////////////////////////////////////////////////////
	if (rVariables.RefiningOptions.Is(Modeler::CRITERION_ERROR))	      
	  {
	    MeshErrorCalculationUtilities MeshErrorDistribution;
	      
	    std::vector<double> NodalError;
	    std::vector<int>    nodes_ids;
		  
	    //OPTION_1
	    //MeshErrorDistribution.NodalErrorCalculation(rModelPart,NodalError,nodes_ids,MeshId,NORM_ISOCHORIC_STRESS);
	    //OPTION_2
	    MeshErrorDistribution.NodalErrorCalculation(rModelPart,NodalError,nodes_ids,MeshId,PLASTIC_STRAIN);

	    for(ModelPart::NodesContainerType::const_iterator in = rModelPart.NodesBegin(MeshId); in != rModelPart.NodesEnd(MeshId); in++)
	      {

		WeakPointerVector<Node<3> >& rN = in->GetValue(NEIGHBOUR_NODES);
		int erased_nodes =0;
		for(unsigned int i = 0; i < rN.size(); i++)
		  {
		    if(rN[i].Is(TO_ERASE))
		      erased_nodes += 1;
		  }


		if( in->IsNot(BOUNDARY) &&  in->IsNot(STRUCTURE) && erased_nodes < 1 )
		  {
		    double& MeanError = in->FastGetSolutionStepValue(MEAN_ERROR);
		    MeanError = NodalError[nodes_ids[in->Id()]];
		    
		    WeakPointerVector<Element >& neighb_elems = in->GetValue(NEIGHBOUR_ELEMENTS);
		    double mean_node_radius = 0;
		    for(WeakPointerVector< Element >::iterator ne = neighb_elems.begin(); ne!=neighb_elems.end(); ne++)
		      {
			mean_node_radius+= mModelerUtilities.CalculateCircRadius(ne->GetGeometry());
		      }
		    
		    mean_node_radius /= double(neighb_elems.size());
			

		    double radius_factor = 3;
		    if(NodalError[nodes_ids[in->Id()]] < rVariables.Refine.reference_error && mean_node_radius < radius_factor * rVariables.Refine.critical_radius)
		      {
			// std::cout<<"   Energy : node remove ["<<in->Id()<<"] : "<<NodalError[nodes_ids[in->Id()]]<<std::endl;
			in->Set(TO_ERASE);
			any_node_removed = true;
			error_remove++;
		      }
		  }
	      }

	  }
	//////////////////////////////////////////////////////////// 

	std::cout<<"   REMOVED DUE ERROR: "<<error_remove<<std::endl;

	////////////////////////////////////////////////////////////
	if (rVariables.RefiningOptions.Is(Modeler::REMOVE_ON_BOUNDARY))
	  {
	    RemoveNonConvexBoundary(rModelPart,rVariables,MeshId);
	  }
	//////////////////////////////////////////////////////////// 


	double inside_nodes_removed   = 0;
	double boundary_nodes_removed = 0;

	////////////////////////////////////////////////////////////
	if (rVariables.RefiningOptions.Is(Modeler::CRITERION_DISTANCE))	      
	  {

	    //defintions for spatial search
	    typedef Node<3>                                  PointType;
	    typedef Node<3>::Pointer                  PointPointerType;
	    typedef std::vector<PointPointerType>          PointVector;
	    typedef PointVector::iterator                PointIterator;
	    typedef std::vector<double>                 DistanceVector;
	    typedef std::vector<double>::iterator     DistanceIterator;

	    typedef Bucket<3, PointType, PointVector, PointPointerType, PointIterator, DistanceIterator > BucketType;
	    typedef Tree< KDTreePartition<BucketType> >     KdtreeType; //Kdtree

	    //bucket size definition:
	    unsigned int bucket_size = 20;


	    //create the list of the nodes to be check during the search
	    PointVector list_of_nodes;
	    list_of_nodes.reserve(rModelPart.NumberOfNodes(MeshId));
	    for(ModelPart::NodesContainerType::iterator i_node = rModelPart.NodesBegin(MeshId) ; i_node != rModelPart.NodesEnd(MeshId) ; i_node++)
	      {
		(list_of_nodes).push_back(*(i_node.base()));
	      }

	    KdtreeType nodes_tree(list_of_nodes.begin(),list_of_nodes.end(), bucket_size);
			
	    ////////////////////////////////////////////////////////////

	    //all of the nodes in this list will be preserved
	    unsigned int num_neighbours = 100;

	    PointVector    neighbours         (num_neighbours);
	    DistanceVector neighbour_distances(num_neighbours);


	    //radius means the distance, if the distance between two nodes is closer to radius -> mark for removing
	    double radius=0;
	    Node<3> work_point(0,0.0,0.0,0.0);
	    unsigned int n_points_in_radius;

	    double distance_factor = 0.4;
		

	    for(ModelPart::NodesContainerType::const_iterator in = rModelPart.NodesBegin(MeshId); in != rModelPart.NodesEnd(MeshId); in++)
	      {

		if( in->IsNot(NEW_ENTITY) )
		  {
		    //radius=rVariables.Refine.size_factor*in->FastGetSolutionStepValue(NODAL_H);
		    radius = rVariables.Refine.critical_radius * distance_factor;

		    work_point[0]=in->X();
		    work_point[1]=in->Y();
		    work_point[2]=in->Z();

		    n_points_in_radius = nodes_tree.SearchInRadius(work_point, radius, neighbours.begin(),neighbour_distances.begin(), num_neighbours);

		    if (n_points_in_radius>1)
		      {
			if (in->IsNot(BOUNDARY) && in->IsNot(STRUCTURE))
			  {
			    //look if we are already erasing any of the other nodes
			    double erased_nodes = 0;
			    for(PointIterator nn=neighbours.begin(); nn!=neighbours.begin() + n_points_in_radius ; nn++)
			      {
				if((*nn)->Is(TO_ERASE))
				  erased_nodes += 1;
			      }

			    if( erased_nodes < 1){ //we release the node if no other nodes neighbours are being erased
			      in->Set(TO_ERASE);
			      std::cout<<"  Distance Criterion Node to erase "<<in->Id()<<std::endl;
			      any_node_removed = true;
			      inside_nodes_removed++;
			      //distance_remove++;
			    }

			  }
			else if ( (in)->IsNot(STRUCTURE) && rVariables.RefiningOptions.Is(Modeler::REMOVE_ON_BOUNDARY) && (in)->IsNot(TO_ERASE)) //boundary nodes will be removed if they get REALLY close to another boundary node (0.2(=extra_factor) * h_factor)
			  {
			    double extra_factor = 0.001; //0.2;

			    //here we loop over the neighbouring nodes and if there are nodes
			    //with BOUNDARY flag and closer than 0.2*nodal_h from our node, we remove the node we are considering
			    unsigned int k = 0;
			    unsigned int counter = 0;
			    for(PointIterator nn=neighbours.begin(); nn!=neighbours.begin() + n_points_in_radius ; nn++)
			      {
				if ( (*nn)->Is(BOUNDARY) && (*nn)->IsNot(CONTACT) && neighbour_distances[k] < (extra_factor*radius) && neighbour_distances[k] > 0.0 )
				  {
				    //KRATOS_WATCH( neighbours_distances[k] )
				    if((*nn)->IsNot(TO_ERASE)){
				      std::cout<<" Removed Boundary Node on Distance ["<<neighbour_distances[k]<<"<"<<extra_factor*radius<<"] "<<std::endl;
				      counter += 1;
				    }
				  }
				k++;
			      }

			    if(counter > 0 && in->IsNot(NEW_ENTITY) && in->IsNot(CONTACT) ){ //Can be inserted in the boundary refine
			      in->Set(TO_ERASE);
			      std::cout<<"  Distance Criterion 2 Node to erase "<<in->Id()<<std::endl;
			      any_node_removed = true;
			      boundary_nodes_removed++;
			      //distance_remove ++;
			    }
					
			  }
		      }
			
		  }	
	      }
	  }
	// REMOVE ON DISTANCE
	////////////////////////////////////////////////////////////
			
	distance_remove =  inside_nodes_removed+ boundary_nodes_removed;
	std::cout<<"   REMOVED DUE DISTANCE: "<<distance_remove<<" ( inside: "<<inside_nodes_removed<<", boundary: "<<boundary_nodes_removed<<" ) "<<std::endl;

	if(any_node_removed)
	  mModelerUtilities.CleanRemovedNodes(rModelPart,MeshId);

      }

    std::cout<<"   Nodes after  erasing : "<<rModelPart.Nodes(MeshId).size()<<std::endl;
    std::cout<<"   REMOVE CLOSE NODES ]; "<<std::endl;
  }

  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::RemoveNonConvexBoundary(ModelPart& rModelPart, MeshingVariables& rVariables,ModelPart::IndexType MeshId)
  {

    KRATOS_TRY;
    std::cout<<"   [ REMOVE NON CONVEX BOUNDARY : "<<std::endl;
    std::cout<<"     Starting Conditions : "<<rModelPart.Conditions(MeshId).size()<<std::endl;

    double critical_angle = -140;
    std::vector<std::vector<Condition::Pointer> > node_shared_conditions(rModelPart.NumberOfNodes()+1); //all domain nodes
      
    //std::cout<<"     Shared Conditions Size "<<node_shared_conditions.size()<<std::endl;

    for(ModelPart::ConditionsContainerType::iterator ic = rModelPart.ConditionsBegin(MeshId); ic!= rModelPart.ConditionsEnd(MeshId); ic++)
      {	 
	if(ic->IsNot(NEW_ENTITY) && ic->IsNot(TO_ERASE)){
	  Geometry< Node<3> >& rConditionGeom = ic->GetGeometry();
	  for(unsigned int i=0; i<rConditionGeom.size(); i++){
	    //std::cout<<"["<<ic->Id()<<"] i "<<i<<" condition "<<rConditionGeom[i].Id()<<std::endl;
	    if(rConditionGeom[i].Is(TO_ERASE))
	      std::cout<<"     Released node condition: WARNING "<<std::endl;

	    node_shared_conditions[rConditionGeom[i].Id()].push_back(*(ic.base()));	  
	  }
	}
      }

    //std::cout<<"     Node Shared Conditions (Pair of Condition Nodes) is now set "<<std::endl;

    //angles 
    double condition_angle = 0;

    //vector of the neighbour conditions
    array_1d<double,3> S1;
    array_1d<double,3> S2;
    S1.clear();
    S2.clear();

    //normals of the neighbour conditions
    array_1d<double,3> N1;
    array_1d<double,3> N2;
    N1.clear();
    N2.clear();

    //nodes
    int i=0,j=0;
      
    //condition id and size
    unsigned int initial_cond_size = rModelPart.Conditions().size()+1; //total model part node size
    unsigned int id = 1;
    unsigned int new_id = 0;
    int removed_nodes =0;

    for(ModelPart::NodesContainerType::const_iterator in = rModelPart.NodesBegin(MeshId); in != rModelPart.NodesEnd(MeshId); in++)
      {

	if( in->Is(BOUNDARY) && in->IsNot(BLOCKED) && in->IsNot(NEW_ENTITY) )
	  {
	    unsigned int nodeId = in->Id();

	    if(node_shared_conditions[nodeId].size()>=2){

	      // std::cout<<"     nodeId "<<nodeId<<std::endl;
	      if(node_shared_conditions[nodeId][0]->IsNot(TO_ERASE) && node_shared_conditions[nodeId][1]->IsNot(TO_ERASE)){
		
		if(node_shared_conditions[nodeId][0]->GetGeometry()[0].Id() == in->Id()){
		  i = 1;
		  j = 0;
		}
		else{
		  i = 0;
		  j = 1;
		}
	      
		  
		//Node1*  neighbour conditions in 2D:   (Node0) ---[1]--- (Node1*)

		//normal condition [1]
		N1 = node_shared_conditions[nodeId][i]->GetValue(NORMAL);
		//normal condition [2]
		N2 = node_shared_conditions[nodeId][j]->GetValue(NORMAL);
	      
		// std::cout<<"     N1 "<<N1<<std::endl;
		// std::cout<<"     N2 "<<N2<<std::endl;
		

		Geometry< Node<3> >& rConditionGeom1 = node_shared_conditions[nodeId][i]->GetGeometry();
		Geometry< Node<3> >& rConditionGeom2 = node_shared_conditions[nodeId][j]->GetGeometry();
	      
		//node in id Node1;

		Node<3> & Node0 = rConditionGeom1[0]; // other node in condition [1]
		Node<3> & Node2 = rConditionGeom2[1]; // other node in condition [2]


		// std::cout<<"     Node0: "<<rConditionGeom1[0].Id()<<" Node 1: "<<rConditionGeom1[1].Id()<<std::endl;
		// std::cout<<"     Node1: "<<rConditionGeom2[0].Id()<<" Node 2: "<<rConditionGeom2[1].Id()<<std::endl;
		//segment condition [1]
		S1[0] = rConditionGeom1[1].X() - rConditionGeom1[0].X();
		S1[1] = rConditionGeom1[1].Y() - rConditionGeom1[0].Y();
	      
		//segment condition [2]
		S2[0] = rConditionGeom2[1].X() - rConditionGeom2[0].X();
		S2[1] = rConditionGeom2[1].Y() - rConditionGeom2[0].Y();
		  
		// std::cout<<"     S1 "<<S1<<std::endl;
		// std::cout<<"     S2 "<<S2<<std::endl;

		double distance_factor = 0.004;
		double radius= rVariables.Refine.critical_radius * distance_factor;

		bool remove_S1 = false;
		if(norm_2(S1)<radius)
		  remove_S1 = true;

		bool remove_S2 = false;
		if(norm_2(S2)<radius)
		  remove_S2 = true;

		if(remove_S1 || remove_S2){
		    
		  node_shared_conditions[nodeId][i]->Set(TO_ERASE); //release condition [1]
		  node_shared_conditions[nodeId][j]->Set(TO_ERASE); //release condition [2]
		  in->Set(TO_ERASE);    //release Node1*

		  Condition::Pointer NewCond = node_shared_conditions[nodeId][i];
		    
		  Node0.Set(BLOCKED);
		  Node2.Set(BLOCKED);

		  //create new condition Node0-NodeB
		  Condition::NodesArrayType face;
		  face.reserve(2);

		  face.push_back(rConditionGeom1(0));
		  face.push_back(rConditionGeom2(1));
		
		  new_id = initial_cond_size + id;
		  //properties to be used in the generation
		  Properties::Pointer properties = NewCond->pGetProperties();
		  Condition::Pointer pcond       = NewCond->Create(new_id, face, properties);
		  // std::cout<<"     ID"<<id<<" 1s "<<pcond1->GetGeometry()[0].Id()<<" "<<pcond1->GetGeometry()[1].Id()<<std::endl;

		  pcond->Set(NEW_ENTITY);

		  std::cout<<"     Condition INSERTED (Id: "<<new_id<<") ["<<rConditionGeom1[0].Id()<<", "<<rConditionGeom2[1].Id()<<"] "<<std::endl;

		  pcond->SetValue(NORMAL, NewCond->GetValue(NORMAL) );

		  pcond->SetValue(MASTER_NODES, NewCond->GetValue(MASTER_NODES) );
		  pcond->SetValue(CAUCHY_STRESS_VECTOR, NewCond->GetValue(CAUCHY_STRESS_VECTOR));
		  pcond->SetValue(DEFORMATION_GRADIENT, NewCond->GetValue(DEFORMATION_GRADIENT));

		  (rModelPart.Conditions(MeshId)).push_back(pcond);

		  removed_nodes += 1;
		  id +=1;

		   
		}
		else{

		  double projection_sides   = inner_prod(S1,S2);
		  double projection_normals = inner_prod(N1,N2);
		  double relative_angle = 0;

		  if(projection_normals!=0)
		    relative_angle = projection_sides/projection_normals;

		  // std::cout<<"     projection_sides "<<projection_sides<<std::endl;
		  // std::cout<<"     projection_normals "<<projection_normals<<std::endl;
		  // std::cout<<"     relative_angle "<<relative_angle<<std::endl;
		  
		  condition_angle = (180.0/3.14159) * std::acos(relative_angle);

		  if(inner_prod(S1,N2)<0) 
		    condition_angle *=(-1);


		  if(condition_angle<critical_angle){
		

		    //Path of neighbour conditions in 2D:   (NodeA) ---[0]--- (Node0) ---[1]--- (Node1*) ---[2]--- (Node2) ---[2]--- (Node2) ---[3]--- (NodeB)

		    //realease positions:
		    node_shared_conditions[nodeId][i]->Set(TO_ERASE); //release condition [1]
		    node_shared_conditions[nodeId][j]->Set(TO_ERASE); //release condition [2]

		    in->Set(TO_ERASE);    //release Node1*
		    Node2.Set(TO_ERASE);  //release Node2
		    
		    std::cout<<"     Node Release i "<<in->Id()<<std::endl;
		    std::cout<<"     Node Release j "<<Node2.Id()<<std::endl;

		    //set Node0 to a new position (between 0 and 2)
		    Node0.X() = 0.5 * ( Node0.X() + Node2.X() );
		    Node0.Y() = 0.5 * ( Node0.Y() + Node2.Y() );
		    Node0.Z() = 0.5 * ( Node0.Z() + Node2.Z() );

		    //assign data to dofs
		    unsigned int buffer_size = Node0.GetBufferSize();
		    unsigned int step_data_size = rModelPart.GetNodalSolutionStepDataSize();

		    for(unsigned int step = 0; step<buffer_size; step++)
		      {
			//getting the data of the solution step
			double* step_data = Node0.SolutionStepData().Data(step);

			double* node0_data = Node0.SolutionStepData().Data(step);
			double* node1_data = Node0.SolutionStepData().Data(step);

			//copying this data in the position of the vector we are interested in
			for(unsigned int j= 0; j<step_data_size; j++)
			  {
			    step_data[j] = 0.5*node0_data[j] + 0.5*node1_data[j];
			  }
		      }
			
		    //recover the original position of the node
		    const array_1d<double,3>& disp = Node0.FastGetSolutionStepValue(DISPLACEMENT);
		    Node0.X0() = Node0.X() - disp[0];
		    Node0.Y0() = Node0.Y() - disp[1];
		    Node0.Z0() = Node0.Z() - disp[2];
	
		    //search shared condition of Node0 and Node A
		    if(node_shared_conditions[Node0.Id()][0]->Id() == Node0.Id()){
		      i = 1;
		    }
		    else{
		      i = 0;
		    }
		
		    Geometry< Node<3> >& rConditionGeom0 = node_shared_conditions[Node0.Id()][i]->GetGeometry();
		    Node<3> & NodeA = rConditionGeom0[0];

		    //search shared condition of Node2 and Node B
		    if(node_shared_conditions[Node2.Id()][0]->Id() == Node2.Id()){
		      i = 0;
		    }
		    else{
		      i = 1;
		    }
		
		    //New conditions profile in 2D:  (NodeA) ---[0]--- (Node0**) ---[3]--- (NodeB)   where (Node0**) is (Node0) in another position

		    Condition::Pointer NewCond = node_shared_conditions[Node2.Id()][i];
		    NewCond->Set(TO_ERASE);
		    Geometry< Node<3> >& rConditionGeom3 = NewCond->GetGeometry();
		    Node<3> & NodeB = rConditionGeom3[1];

		    NodeA.Set(Modeler::ENGAGED_NODES);
		    NodeB.Set(Modeler::ENGAGED_NODES);

		    Node0.Set(Modeler::ENGAGED_NODES);
		
		
		    //create new condition Node0-NodeB
		    Condition::NodesArrayType face;
		    face.reserve(2);

		    face.push_back(rConditionGeom1(0));
		    face.push_back(rConditionGeom3(1));
		
		    new_id = initial_cond_size + id;
		    //properties to be used in the generation
		    Properties::Pointer properties = NewCond->pGetProperties();
		    Condition::Pointer pcond       = NewCond->Create(new_id, face, properties);
		    // std::cout<<" ID"<<id<<" 1s "<<pcond1->GetGeometry()[0].Id()<<" "<<pcond1->GetGeometry()[1].Id()<<std::endl;

		    pcond->Set(NEW_ENTITY);

		    std::cout<<"     Condition INSERTED (Id: "<<new_id<<") ["<<rConditionGeom1[0].Id()<<", "<<rConditionGeom3[1].Id()<<"] "<<std::endl;

		    pcond->SetValue(NORMAL, NewCond->GetValue(NORMAL) );

		    pcond->SetValue(MASTER_NODES, NewCond->GetValue(MASTER_NODES) );
		    pcond->SetValue(CAUCHY_STRESS_VECTOR, NewCond->GetValue(CAUCHY_STRESS_VECTOR));
		    pcond->SetValue(DEFORMATION_GRADIENT, NewCond->GetValue(DEFORMATION_GRADIENT));

		    (rModelPart.Conditions(MeshId)).push_back(pcond);

		    removed_nodes += 2;
		    id +=1;
		
		  }
		}
	      }
	    }
	  }
      }

    for(ModelPart::NodesContainerType::const_iterator in = rModelPart.NodesBegin(MeshId); in != rModelPart.NodesEnd(MeshId); in++)
      {
	in->Reset(BLOCKED);
      }
	      
    std::cout<<"     Ending   Conditions : "<<rModelPart.Conditions(MeshId).size()<<"  (Removed nodes: "<< removed_nodes<<" ) "<<std::endl;
    std::cout<<"     REMOVE NON CONVEX BOUNDARY ]; "<<std::endl;
    KRATOS_CATCH(" ")
      }

  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::SetDissipativeElements (ModelPart& rModelPart, MeshingVariables& rVariables,ModelPart::IndexType MeshId)
  {
      
    ProcessInfo& CurrentProcessInfo = rModelPart.GetProcessInfo();
      
    //set label refine in elements that must be refined due to dissipation
    for(ModelPart::ElementsContainerType::const_iterator iii = rModelPart.ElementsBegin(MeshId);
	iii != rModelPart.ElementsEnd(MeshId); iii++)
      {
	double plastic_power=0;
	std::vector<double> Value(1);
	(iii)->GetValueOnIntegrationPoints(PLASTIC_POWER,Value,CurrentProcessInfo);
	    
	plastic_power = Value[0] * iii->GetGeometry().Area();
	    
	// if(plastic_power>0)
	//   std::cout<<" Element ["<<iii->Id()<<" plastic_power "<<plastic_power<<" critical_dissipation "<<rVariables.Refine.critical_dissipation<<std::endl;

	if( plastic_power > rVariables.Refine.critical_dissipation)
	  {
	    //std::cout<<" Refine element "<<std::endl;
	    Geometry< Node<3> >& rGeom = iii->GetGeometry();
	    for(unsigned int i = 0; i<rGeom.size(); i++)
	      {
		if(rGeom[i].IsNot(BOUNDARY))
		  rGeom[i].Set(TO_REFINE);
	      }
	  }
		    
      }
	    
  }

  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::RefineBoundary(ModelPart& rModelPart, MeshingVariables& rVariables,ModelPart::IndexType MeshId)
  {

    KRATOS_TRY;

    std::cout<<" [ REFINE BOUNDARY : "<<std::endl;
    std::cout<<"   Nodes and Conditions : "<<rModelPart.Nodes(MeshId).size()<<", "<<rModelPart.Conditions(MeshId).size()<<std::endl;

    ProcessInfo& CurrentProcessInfo = rModelPart.GetProcessInfo();
    SpatialBoundingBox RefiningBox (rVariables.BoundingBox.Center,rVariables.BoundingBox.Radius,rVariables.BoundingBox.Velocity);


    unsigned int  conditions_size = 0;
    typedef Node<3>                         PointType;
    typedef std::vector<PointType>        PointVector;

    //if the insert switches are activated, we check if the boundaries got too coarse
    if (rVariables.RefiningOptions.Is(Modeler::REFINE_INSERT_NODES) && rVariables.RefiningOptions.Is(Modeler::REFINE_BOUNDARY) )
      {

	PointVector list_of_nodes;
	std::vector<Condition::Pointer> list_of_conditions;
	    
	conditions_size = rModelPart.Conditions(MeshId).size();
	list_of_nodes.reserve(conditions_size);
	list_of_conditions.reserve(conditions_size);

	// std::vector<int> nodes_ids;
	// nodes_ids.resize(rModelPart.Conditions().size()); //mesh 0
	// std::fill( nodes_ids.begin(), nodes_ids.end(), 0 );

	std::cout<<"   List of Conditions Reserved Size: "<<conditions_size<<std::endl;

	double alpha_radius = 0.6;
	double tool_radius= 0;
	double side_length= 0;
	double plastic_power=0;
	bool size_insert = false;
	bool radius_insert = false;
	bool energy_insert = false;
	bool mesh_size_insert = false;
	bool contact_active = false;
	bool contact_semi_active = false;
	bool tool_project = false;


	//counters:
	int total_contact_conditions = 0;
	int number_contacts_domain   = 0;
	int number_contacts_active   = 0;

	int contact_tip    = 0;
	int contact_size   = 0;
	    
	int exterior_bound = 0;
	int tip_bound      = 0;
	    

	Node<3> new_point(0,0.0,0.0,0.0);

	std::cout<<"   Contact Area Refine Start "<<std::endl;
	double contact_size_factor = 0.4; //tip_correction
	// double side_size_factor    = 0.5;

	//LOOP TO CONSIDER ONLY CONTACT CONDITIONS
	for(ModelPart::ConditionsContainerType::iterator ic = rModelPart.ConditionsBegin(); ic!= rModelPart.ConditionsEnd(); ic++)
	  {

	    size_insert    = false;
	    radius_insert  = false;
	    energy_insert  = false;
	    tool_project   = false;
	    contact_active = false;
	    side_length = 0;
	    tool_radius = 0;
	    plastic_power = 0;
	    Geometry< Node<3> > rConditionGeom;
	    array_1d<double,3> tip_center;

	    if( ic->Is(CONTACT) )   //Refine radius on the workpiece for the ContactDomain zone
	      {

		PointType  MasterNode;
		bool condition_found = false;
		Condition::Pointer MasterCondition  = mModelerUtilities.FindMasterCondition(*(ic.base()),MasterNode,rModelPart.Conditions(MeshId),condition_found);
		    

		if(condition_found){
		      
		  if( MasterCondition->IsNot(TO_ERASE) ){


		    // The order is determined to detect wall tip contact nodes on boundary
		    // independently if they are on active contact or not (they are marked as TO_SPLIT)

		    rConditionGeom  = MasterCondition->GetGeometry(); 

		    //to recover TIP definition on conditions   
			  
		    if( MasterNode.SolutionStepsDataHas( WALL_TIP_RADIUS ) ) //master node in tool -->  refine workpiece  // 
		      {
			    
			tool_radius = MasterNode.FastGetSolutionStepValue( WALL_TIP_RADIUS );
			tip_center  = MasterNode.FastGetSolutionStepValue( WALL_REFERENCE_POINT );
			    					    
			PointType center (0,tip_center[0],tip_center[1],tip_center[2]);
			array_1d<double, 3 > radius;
			radius[0]=rConditionGeom[0].X()-center.X();
			radius[1]=rConditionGeom[0].Y()-center.Y();
			radius[2]=rConditionGeom[0].Z()-center.Z();
			double distance1=norm_2(radius);

			radius[0]=rConditionGeom[1].X()-center.X();
			radius[1]=rConditionGeom[1].Y()-center.Y();
			radius[2]=rConditionGeom[1].Z()-center.Z();

			double distance2=norm_2(radius);
			    
			//If a node is detected in the wall tip is set TO_SPLIT
			//the criteria to splitting will be applied later in the nodes marked as TO_SPLIT

			if( (1-alpha_radius)*tool_radius < distance1 &&  distance1 < (1+alpha_radius)*tool_radius )
			  rConditionGeom[0].Set(TO_SPLIT);
			    
			if( (1-alpha_radius)*tool_radius < distance2 &&  distance2 < (1+alpha_radius)*tool_radius )
			  rConditionGeom[1].Set(TO_SPLIT);
			  
			

			array_1d<double, 3 > & ContactForceNormal1  = rConditionGeom[0].FastGetSolutionStepValue(CONTACT_FORCE);
			array_1d<double, 3 > & ContactForceNormal2  = rConditionGeom[1].FastGetSolutionStepValue(CONTACT_FORCE);
			if(norm_2(ContactForceNormal1)>0 && norm_2(ContactForceNormal2)>0){
			  contact_active = true;
			  number_contacts_active ++;
			}
		    
			side_length = mModelerUtilities.CalculateSideLength (rConditionGeom[0],rConditionGeom[1]);		    	     
			    
			if( side_length > rVariables.Refine.critical_side * contact_size_factor ){

			  std::cout<<"   //*** MASTER CONDITION "<<MasterCondition->Id()<<" ("<<rConditionGeom[0].Id()<<","<<rConditionGeom[1].Id()<<") ***// "<<std::endl;
			  std::cout<<"   {side_length "<<side_length<<" > critical_side "<<rVariables.Refine.critical_side<<"} "<<std::endl;
			  std::cout<<"   CENTER A: "<<tip_center<<" TOOL_NODE "<<MasterNode.Id()<<std::endl;
			  std::cout<<"   NODE1 "<<rConditionGeom[0].Id()<<" ("<<rConditionGeom[0].X()<<"; "<<rConditionGeom[0].Y()<<"; "<<rConditionGeom[0].Z()<<") "<<std::endl;
			  std::cout<<"   NODE2 "<<rConditionGeom[1].Id()<<" ("<<rConditionGeom[1].X()<<"; "<<rConditionGeom[1].Y()<<"; "<<rConditionGeom[1].Z()<<") "<<std::endl;
			  std::cout<<"   Distances: (d1:"<<distance1<<", d2:"<<distance2<<", radius:"<<tool_radius<<")"<<std::endl;
			      
			  if( ((1-alpha_radius)*tool_radius < distance1 &&  (1-alpha_radius)*tool_radius < distance2) && 
			      (distance1 < (1+alpha_radius)*tool_radius  &&  distance2 < (1+alpha_radius)*tool_radius) )
			    {
			      radius_insert = true;
				  
			      // std::cout<<" {side_length "<<side_length<<" > critical_side "<<rVariables.Refine.critical_side<<"} "<<std::endl;
			      // std::cout<<"  distances [1: "<<distance1<<", 2: "<<distance2<<"]"<<" tool_radius "<<tool_radius<<std::endl;
			      std::cout<<"   insert on radius "<<std::endl;
			    }
			  // else if( side_length > rVariables.Refine.critical_side * side_size_factor && 
			  // 	       ( distance1 < (1 + (side_size_factor+alpha_radius))*tool_radius && distance2 < (1 + (side_size_factor+alpha_radius))*tool_radius) ) {
				
			  // 	size_insert = true;
			  // 	std::cout<<" insert on radius-size "<<std::endl;
			  // }
			      
			}
			    
			  
			if(radius_insert){

			  if(!contact_active){
				
			    radius_insert = false;
			    std::cout<<" contact_not_active "<<std::endl;
			    // double& nodal_h1 = rConditionGeom[0].FastGetSolutionStepValue(NODAL_H);
			    // double& nodal_h2 = rConditionGeom[1].FastGetSolutionStepValue(NODAL_H);
			    // double& nodal_h0 = MasterNode.FastGetSolutionStepValue( NODAL_H );
			  
			    // double side = norm_2(rConditionGeom[0]-rConditionGeom[1]);
			    // // double d1 = mModelerUtilities.FindBoundaryH (rConditionGeom[0]);
			    // // double d2 = mModelerUtilities.FindBoundaryH (rConditionGeom[1]);
			    // // double d0 = mModelerUtilities.FindBoundaryH (MasterNode);
			    // // double size_master = nodal_h0;

			    // double size_factor = 3;
			    // bool candidate =false;
			    // if( ((nodal_h1+nodal_h2)*0.5 > size_factor * nodal_h0)){
			    //   candidate = true;
			    // }
			  
			    // double crit_factor = 2;
			    // if( (side > rVariables.Refine.critical_side * crit_factor) && candidate){
			    //   radius_insert = true;
			    // }
			      
			  }

			}


		      }
		    else{ //refine boundary with nodal_h sizes to large
			  
		      double& nodal_h1 = rConditionGeom[0].FastGetSolutionStepValue(NODAL_H);
		      double& nodal_h2 = rConditionGeom[1].FastGetSolutionStepValue(NODAL_H);
		      double& nodal_h0 = MasterNode.FastGetSolutionStepValue( NODAL_H );
			  
		      double side = norm_2(rConditionGeom[0]-rConditionGeom[1]);
		      // double d1 = mModelerUtilities.FindBoundaryH (rConditionGeom[0]);
		      // double d2 = mModelerUtilities.FindBoundaryH (rConditionGeom[1]);
		      // double d0 = mModelerUtilities.FindBoundaryH (MasterNode);
		      // double size_master = nodal_h0;

		      double size_factor = 3;
		      bool candidate =false;
		      if( ((nodal_h1+nodal_h2)*0.5 > size_factor * nodal_h0)){
			candidate = true;
		      }
			  
		      double crit_factor = 2;
		      if( (side > rVariables.Refine.critical_side * crit_factor) && candidate){
			size_insert = true;
		      }
		    }



		    if( radius_insert || size_insert ) //Boundary must be rebuild 
		      {
				
			std::cout<<"   CONTACT DOMAIN ELEMENT REFINED "<<ic->Id()<<std::endl;

			new_point.X() = 0.5*( rConditionGeom[1].X() + rConditionGeom[0].X() );
			new_point.Y() = 0.5*( rConditionGeom[1].Y() + rConditionGeom[0].Y() );
			new_point.Z() = 0.5*( rConditionGeom[1].Z() + rConditionGeom[0].Z() );
			  

			new_point.SetId(ic->Id()); //set condition Id

			Condition::Pointer ContactMasterCondition  = ic->GetValue(MASTER_CONDITION);
			

			if( (rConditionGeom[0].Is(TO_SPLIT) && rConditionGeom[1].Is(TO_SPLIT)) )
			  tool_project = true;
			    
			if( (rConditionGeom[0].Is(TO_SPLIT) || rConditionGeom[1].Is(TO_SPLIT)) && contact_active)
			  tool_project = true;
			    

			if(tool_project) //master node in tool -->  refine workpiece  // (tool_radius ==0 in workpiece nodes)
			  {
			    
			    if(new_point.Y()<(tip_center[1]) && new_point.Y()>(tip_center[1]-tool_radius)){

			      std::cout<<"   new_point  ("<<new_point.X()<<", "<<new_point.Y()<<") "<<std::endl;
			      std::cout<<"   tip_center ("<<tip_center[0]<<", "<<tip_center[1]<<") radius "<<tool_radius<<std::endl;

			      array_1d<double,3> tip_normal = tip_center-new_point;
				  				  	
			      if(norm_2(tip_normal)<tool_radius*0.95){ //if is in the tool tip
				tip_normal -= (tool_radius/norm_2(tip_normal)) * tip_normal;		
				if(norm_2(tip_normal)<tool_radius*0.05)
				  new_point  += tip_normal;
			    
				std::cout<<"   A: Tool Tip Correction COND ("<<ContactMasterCondition->Id()<<") "<<std::endl;
				std::cout<<"   new_point ("<<new_point.X()<<", "<<new_point.Y()<<") "<<std::endl;
			      }
			    }
			  }

			if(radius_insert)
			  contact_tip++;
			if(size_insert)
			  contact_size++;
			      
			std::cout<<"   MasterCondition RELEASED (Id: "<<ContactMasterCondition->Id()<<") "<<std::endl;
			ContactMasterCondition->Set(TO_ERASE);
			list_of_nodes.push_back(new_point);
			list_of_conditions.push_back(ContactMasterCondition);
		      }		    
		  }

		  number_contacts_domain ++;
		}
		// else{
		      
		//   std::cout<<"   Master Condition not found "<<std::endl;

		// }

		total_contact_conditions ++;

	      }
	  }

	std::cout<<"   [ Contact Conditions : "<<total_contact_conditions<<", (contacts in domain: "<<number_contacts_domain<<", of them active: "<<number_contacts_active<<") ] "<<std::endl;
	std::cout<<"   Contact Search End ["<<list_of_conditions.size()<<" : "<<list_of_nodes.size()<<"]"<<std::endl;
	std::cout<<"   Boundary Search Start "<<std::endl;
	    
	double non_contact_boundary_factor = 1.5;

	//LOOP TO CONSIDER ALL SUBDOMAIN CONDITIONS
	double cond_counter=0;
	for(ModelPart::ConditionsContainerType::iterator ic = rModelPart.ConditionsBegin(MeshId); ic!= rModelPart.ConditionsEnd(MeshId); ic++)
	  {
	    cond_counter ++;
	    bool refine_candidate = false;
	    if( rVariables.MeshingOptions.Is(Modeler::CONSTRAINED_MESH) ){
	      if( ic->Is(BOUNDARY) ) //ONLY SET TO THE BOUNDARY SKIN CONDITIONS (CompositeCondition)
		refine_candidate = true;
	      else
	       	refine_candidate = false;
	    }
	    else{
	      refine_candidate = true; 
	    }
		

	    if( refine_candidate ){
	      if (rVariables.BoundingBox.is_set == true ){
		refine_candidate = mModelerUtilities.CheckConditionInBox(*(ic.base()),RefiningBox,CurrentProcessInfo);
	      }
	    }


	    if( refine_candidate ){
			
	      radius_insert = false;
	      energy_insert = false;
	      mesh_size_insert = false;
	      tool_project = false;
	      contact_active = false;
	      contact_semi_active = false;
	      side_length = 0;
	      tool_radius = 0;
	      plastic_power = 0;
	      //double condition_radius = 0;
	      Geometry< Node<3> > rConditionGeom;
	      array_1d<double,3> tip_center;

	      if( ic->IsNot(TO_ERASE) ){

		// TOOL TIP INSERT;

		//std::cout<<" Condition "<<ic->Id()<<"("<<ic->GetGeometry()[0].Id()<<", "<<ic->GetGeometry()[1].Id()<<") NOT RELEASE  (number: "<<cond_counter<<") "<<std::endl;

		  
		rConditionGeom = ic->GetGeometry();
		array_1d<double, 3 > & ContactForceNormal1  = rConditionGeom[0].FastGetSolutionStepValue(CONTACT_FORCE);
		array_1d<double, 3 > & ContactForceNormal2  = rConditionGeom[1].FastGetSolutionStepValue(CONTACT_FORCE);

		//std::cout<<" Forces : [1] "<<norm_2(ContactForceNormal1)<<" [2] "<<norm_2(ContactForceNormal2)<<std::endl;
		if(norm_2(ContactForceNormal1)>0 && norm_2(ContactForceNormal2)>0){
		  contact_active = true;
		}
		else if(norm_2(ContactForceNormal1)>0 || norm_2(ContactForceNormal2)>0){
		  contact_semi_active = true;
		}

		      
		if( contact_active ){

		  side_length = mModelerUtilities.CalculateSideLength (rConditionGeom[0],rConditionGeom[1]);		    	     

		  double tip_correction = 0.6;

		  if( side_length > rVariables.Refine.critical_side*tip_correction){
		  

		    std::cout<<"   rigid {side_length "<<side_length<<" > critical_side "<<rVariables.Refine.critical_side*tip_correction<<"} "<<std::endl;


		    bool on_tip = false;
		    if(rConditionGeom[0].Is(TO_SPLIT) && rConditionGeom[1].Is(TO_SPLIT)){
		      on_tip = true;
		    }
		    else if (rConditionGeom[0].Is(TO_SPLIT) || rConditionGeom[1].Is(TO_SPLIT)){
		      if( side_length > 1.5*rVariables.Refine.critical_side*tip_correction ){
			on_tip = true;
		      }
		    }		  

		    bool on_radius = false;

		    if( on_tip && rVariables.rigid_wall_set ){

		      Vector Point(3);
		      if( rConditionGeom[0].Is(TO_SPLIT) ){
			
			Point[0] = rConditionGeom[0].X();
			Point[1] = rConditionGeom[0].Y();
			Point[2] = rConditionGeom[0].Z();
			on_radius = true;
			
		      }
		      else if( rConditionGeom[1].Is(TO_SPLIT) ){

			Point[0] = rConditionGeom[1].X();
			Point[1] = rConditionGeom[1].Y();
			Point[2] = rConditionGeom[1].Z();
			on_radius = true;

		      }
		      else{
			on_radius = false;
		      }
      

		      if( on_radius ){

			//std::cout<<" On radius "<<std::endl;
			ProcessInfo& CurrentProcessInfo = rModelPart.GetProcessInfo();
			double Time = CurrentProcessInfo[TIME];  
			for( unsigned int i = 0; i < rVariables.RigidWalls.size(); i++ )
			  {
			    if( rVariables.RigidWalls[i]->IsInside( Point, Time ) ){
			      tool_radius = rVariables.RigidWalls[i]->Radius(Point);
			      tip_center  = rVariables.RigidWalls[i]->Center(Point);
			    }
			  }
		      }
			
		    }
		    		   		  
						
		    if( on_radius && on_tip ) //master node in tool -->  refine workpiece  // (tool_radius ==0 in workpiece nodes)
		      {
			PointType center (0,tip_center[0],tip_center[1],tip_center[2]);
			array_1d<double, 3 > radius;
			radius[0]=rConditionGeom[0].X()-center.X();
			radius[1]=rConditionGeom[0].Y()-center.Y();
			radius[2]=rConditionGeom[0].Z()-center.Z();

			double distance1=norm_2(radius);

			radius[0]=rConditionGeom[1].X()-center.X();
			radius[1]=rConditionGeom[1].Y()-center.Y();
			radius[2]=rConditionGeom[1].Z()-center.Z();

			double distance2=norm_2(radius);
			    
			std::cout<<"   CENTER B: "<<center<<std::endl;
			std::cout<<"   Distances: (d1:"<<distance1<<", d2:"<<distance2<<", radius:"<<tool_radius<<")"<<std::endl;

			if( ((1-alpha_radius)*tool_radius < distance1 &&  (1-alpha_radius)*tool_radius < distance2) && 
			    (distance1 < (1+alpha_radius)*tool_radius  &&  distance2 < (1+alpha_radius)*tool_radius) )
			  {
			    radius_insert = true;
			    // std::cout<<" {side_length "<<side_length<<" > critical_side "<<rVariables.Refine.critical_side<<"} "<<std::endl;
			    // std::cout<<"  distances [1: "<<distance1<<", 2: "<<distance2<<"]"<<" tool_radius "<<tool_radius<<std::endl;
			    std::cout<<"   insert on radius "<<std::endl;
			  }

			std::cout<<"   RIGID TOOL insert : "<<radius_insert<<std::endl;
					      
		      }
		    // else{

		      //std::cout<<" Condition is not in wall Tip "<<std::endl;

		      // if(rConditionGeom[0].IsNot(TO_SPLIT))
		      // 	std::cout<<" Node ["<<rConditionGeom[0].Id()<<"] not tool tip "<<std::endl;
			    
		      // if(rConditionGeom[1].IsNot(TO_SPLIT))
		      // 	std::cout<<" Node ["<<rConditionGeom[1].Id()<<"] not tool tip "<<std::endl;
		      

		    //}
			  

		  }

		}


		// ENERGY INSERT

		unsigned int vsize=ic->GetValue(MASTER_ELEMENTS).size();

		//std::cout<<" MASTER_ELEMENTS_SIZE: "<<vsize<<std::endl;

		if (rVariables.RefiningOptions.Is(Modeler::CRITERION_ENERGY) && vsize>0){
		   
		  Element::ElementType& MasterElement = ic->GetValue(MASTER_ELEMENTS)[vsize-1];

		  //std::cout<<" MASTER_ELEMENT "<<MasterElement.Id()<<std::endl;

		  plastic_power=0;
		  std::vector<double> Value(1);
		  MasterElement.GetValueOnIntegrationPoints(PLASTIC_POWER,Value,CurrentProcessInfo);
			
		  //std::cout<<"   Plastic Power "<<Value[0]<<std::endl;
				  
		  Geometry<Node<3> >& pGeom = MasterElement.GetGeometry();
		  plastic_power = Value[0] * pGeom.Area();

		  //computation of the condition master element radius start: 
		  //PointsArrayType& vertices = pGeom.Points();
			 			    			
		  // double average_side_length= mModelerUtilities.CalculateAverageSideLength (vertices[0].X(), vertices[0].Y(),
		  // 							      vertices[1].X(), vertices[1].Y(),
		  // 							      vertices[2].X(), vertices[2].Y());
		  //condition_radius = pGeom.Area()/average_side_length;
		  //computation of the condition master element radius end;

		  //condition_radius is side_length
		  side_length = mModelerUtilities.CalculateSideLength (rConditionGeom[0],rConditionGeom[1]);

		  //condition_radius = mModelerUtilities.CalculateCircRadius (pGeom);

		  //if(plastic_power > rVariables.Refine.critical_dissipation && condition_radius > rVariables.Refine.critical_radius)
		  if(plastic_power > rVariables.Refine.critical_dissipation && side_length > rVariables.Refine.critical_side * non_contact_boundary_factor)
		    {
		      energy_insert = true;

		      // std::cout<<" PlasticPower "<<plastic_power<<" > Critical Dissipation "<<rVariables.Refine.critical_dissipation<<std::endl;
		      // std::cout<<" ConditionRadius "<<condition_radius<<" > Critical Radius "<<rVariables.Refine.critical_radius<<std::endl;
		      std::cout<<"   insert on energy "<<std::endl;
		      
		    }
		}


		// BOUNDARY SIZE INSERT

		if( (!radius_insert || !energy_insert) && vsize>0 ){
		   
		  Element::ElementType& MasterElement = ic->GetValue(MASTER_ELEMENTS)[vsize-1];

		  //std::cout<<" MASTER_ELEMENT "<<MasterElement.Id()<<std::endl;

				  
		  Geometry<Node<3> >& vertices = MasterElement.GetGeometry();
		  double Alpha =  rVariables.AlphaParameter;

		  bool accepted=mModelerUtilities.AlphaShape(Alpha,vertices);
		 
		  //condition_radius is side_length
		  side_length = mModelerUtilities.CalculateSideLength (rConditionGeom[0],rConditionGeom[1]);

		  //condition_radius = mModelerUtilities.CalculateCircRadius (pGeom);

		  //if(plastic_power > rVariables.Refine.critical_dissipation && condition_radius > rVariables.Refine.critical_radius)
		  if( !accepted && side_length > rVariables.Refine.critical_side * non_contact_boundary_factor)
		    {
		      mesh_size_insert = true;

		      std::cout<<"   insert on mesh size "<<std::endl;		      
		    }
		}




		if( radius_insert || energy_insert || mesh_size_insert ) //Boundary must be rebuild 
		  {

		    std::cout<<"   BOUNDARY DOMAIN ELEMENT REFINED "<<ic->Id()<<std::endl;

		    new_point.X() = 0.5*( rConditionGeom[1].X() + rConditionGeom[0].X() );
		    new_point.Y() = 0.5*( rConditionGeom[1].Y() + rConditionGeom[0].Y() );
		    new_point.Z() = 0.5*( rConditionGeom[1].Z() + rConditionGeom[0].Z() );
		      

		    new_point.SetId(ic->Id()); //set condition Id
		      
		    //it will be good if the node is detected in the tool tip using the rigid contact standards:
		    
		    if( (rConditionGeom[0].Is(TO_SPLIT) && rConditionGeom[1].Is(TO_SPLIT)) )
		      tool_project = true;

		    if( (rConditionGeom[0].Is(TO_SPLIT) || rConditionGeom[1].Is(TO_SPLIT)) && contact_active)
		      tool_project = true;

		    if( (rConditionGeom[0].Is(TO_SPLIT) || rConditionGeom[1].Is(TO_SPLIT)) && contact_semi_active)
		      tool_project = true;


		    if(tool_project){
			  
		      bool on_radius = false;
		      if(rConditionGeom[0].SolutionStepsDataHas( WALL_TIP_RADIUS )){
			tool_radius = rConditionGeom[0].FastGetSolutionStepValue( WALL_TIP_RADIUS );
			tip_center  = rConditionGeom[0].FastGetSolutionStepValue( WALL_REFERENCE_POINT );
			on_radius = true;
		      }
		      else if(rConditionGeom[1].SolutionStepsDataHas( WALL_TIP_RADIUS )){
			tool_radius = rConditionGeom[1].FastGetSolutionStepValue( WALL_TIP_RADIUS );
			tip_center  = rConditionGeom[1].FastGetSolutionStepValue( WALL_REFERENCE_POINT );
			on_radius = true;
		      }
		      else{
			on_radius = false;
		      }
		      

		      if(on_radius){

			if(new_point.Y()<(tip_center[1]) && new_point.Y()>(tip_center[1]-tool_radius)){
			    
			  std::cout<<"   new_point  ("<<new_point.X()<<", "<<new_point.Y()<<") "<<std::endl;
			  std::cout<<"   tip_center ("<<tip_center[0]<<", "<<tip_center[1]<<") radius "<<tool_radius<<std::endl;
			    
			  array_1d<double,3> tip_normal = tip_center-new_point;

			  if(norm_2(tip_normal)<tool_radius){ //if is in the tool tip
			    tip_normal -= (tool_radius/norm_2(tip_normal)) * tip_normal;		
			    if(norm_2(tip_normal)<tool_radius*0.08)
			      new_point  += tip_normal;
				
			    std::cout<<"   B: Tool Tip Correction COND ("<<ic->Id()<<") "<<std::endl;
			    std::cout<<"   new_point ("<<new_point.X()<<", "<<new_point.Y()<<") "<<std::endl;

			  }

			  
			}
			  
		      }
		    }

		    if(radius_insert)
		      tip_bound ++;
		    if(energy_insert || mesh_size_insert)
		      exterior_bound++;

		    ic->Set(TO_ERASE);
		    list_of_nodes.push_back(new_point);
		    list_of_conditions.push_back(*(ic.base()));

		      
		    
		    std::cout<<"   Refine Boundary  (Id:"<<ic->Id()<<"): ["<<rConditionGeom[0].Id()<<", "<<rConditionGeom[1].Id()<<"]"<<std::endl;
		    std::cout<<"   (x1:"<<rConditionGeom[0].X()<<", y1: "<<rConditionGeom[0].Y()<<") "<<" (x2:"<<rConditionGeom[1].X()<<", y2: "<<rConditionGeom[1].Y()<<") "<<std::endl;
		      
		    //std::cout<<" Added Node [Rcrit:"<<condition_radius<<",Scrit:"<<side_length<<",PlasticPower:"<<plastic_power<<"]"<<std::endl;
		    //std::cout<<" Conditions [Rcrit:"<<rVariables.Refine.critical_radius<<",Scrit:"<<rVariables.Refine.critical_side<<",PlasticPower:"<<rVariables.Refine.critical_dissipation<<"]"<<std::endl;
		    
		  }
		

	      }
	      // else{
	      //   std::cout<<" Condition "<<ic->Id()<<" Released "<<std::endl;
	      // }
	    
	    }
	  }	  
	    
	  
	std::cout<<"   Boundary Search End ["<<list_of_conditions.size()<<" : "<<list_of_nodes.size()<<"]"<<std::endl;

	std::cout<<"   [contact(TIP: "<<contact_tip<<", SIZE: "<<contact_size<<") -  bound(TIP: "<<tip_bound<<", SIZE: "<<exterior_bound<<")]"<<std::endl;

	std::cout<<"   Added nodes on boundary: "<<list_of_nodes.size()<<std::endl;
  

	//node to get the DOFs from
	Node<3>::DofsContainerType& reference_dofs = (rModelPart.NodesBegin(MeshId))->GetDofs();
	unsigned int step_data_size = rModelPart.GetNodalSolutionStepDataSize();
	double z = 0.0;

	unsigned int initial_node_size = rModelPart.Nodes().size()+1; //total model part node size
	unsigned int initial_cond_size = rModelPart.Conditions().size()+1; //total model part node size
	int id=0;
	//if points were added, new nodes must be added to ModelPart
	for(unsigned int i = 0; i<list_of_nodes.size(); i++)
	  {
	    id   = initial_node_size+i;
	    
	    double& x= list_of_nodes[i].X();
	    double& y= list_of_nodes[i].Y();

	    //std::cout<<" boundary node id "<<id<<std::endl;		
	    //std::cout<<" node creation position [CondID: "<<list_of_nodes[i]<<"] ("<<x<<", "<<y<<")"<<std::endl;
	    Node<3>::Pointer pnode = rModelPart.CreateNewNode(id,x,y,z);
		
	    //set to the main mesh (Mesh 0) to avoid problems in the PreIds (number of nodes: change) in other methods
	    if(MeshId!=0)
	      (rModelPart.Nodes(MeshId)).push_back(pnode);


	    pnode->SetBufferSize(rModelPart.NodesBegin(MeshId)->GetBufferSize() );


	    //assign data to dofs
	    unsigned int buffer_size = pnode->GetBufferSize();

	    //2D edges:
	    Geometry< Node<3> >& rConditionGeom  = list_of_conditions[i]->GetGeometry(); 

			    
	    //generating the dofs
	    for(Node<3>::DofsContainerType::iterator iii = reference_dofs.begin(); iii != reference_dofs.end(); iii++)
	      {
		Node<3>::DofType& rDof = *iii;
		Node<3>::DofType::Pointer p_new_dof = pnode->pAddDof( rDof );
			
		if( rConditionGeom[0].IsFixed(rDof.GetVariable()) && rConditionGeom[1].IsFixed(rDof.GetVariable()) )
		  (p_new_dof)->FixDof();
		else
		  (p_new_dof)->FreeDof();
	      }
		 
	

		
	    //int cond_id = list_of_nodes[i].Id();
	    //Geometry< Node<3> >& rConditionGeom = (*(rModelPart.Conditions(MeshId).find(cond_id).base()))->GetGeometry();

	    for(unsigned int step = 0; step<buffer_size; step++)
	      {
		//getting the data of the solution step
		double* step_data = (pnode)->SolutionStepData().Data(step);

		double* node0_data = rConditionGeom[0].SolutionStepData().Data(step);
		double* node1_data = rConditionGeom[1].SolutionStepData().Data(step);

		//copying this data in the position of the vector we are interested in
		for(unsigned int j= 0; j<step_data_size; j++)
		  {
		    step_data[j] = 0.5*node0_data[j] + 0.5*node1_data[j];
		  }
	      }

		
	    //set specific controls values and flags:
	    pnode->Set(BOUNDARY);
	    pnode->Set(NEW_ENTITY);  //if boundary is rebuild, the flag INSERTED must be set to new conditions too
	    std::cout<<" node "<<pnode->Id()<<" is new entity "<<std::endl;
	    
	    pnode->SetValue(DOMAIN_LABEL,MeshId);
	    double& nodal_h = pnode->FastGetSolutionStepValue(NODAL_H);
	    //nodal_h = 0.5*(nodal_h+rVariables.Refine.critical_side); //modify nodal_h for security
	    nodal_h = rVariables.Refine.critical_side; //modify nodal_h for security

	    const array_1d<double,3> ZeroNormal(3,0.0);
	    //correct normal interpolation
	    noalias(pnode->GetSolutionStepValue(NORMAL)) = list_of_conditions[i]->GetValue(NORMAL);
	    //std::cout<<" NORMAL "<<pnode->GetSolutionStepValue(NORMAL)<<std::endl;
	    //correct contact_normal interpolation (laplacian boundary projection uses it)
	    //noalias(pnode->GetSolutionStepValue(FORCE_CONTACT_NORMAL)) = ZeroNormal;

	    //recover the original position of the node
	    const array_1d<double,3>& disp = pnode->FastGetSolutionStepValue(DISPLACEMENT);
	    pnode->X0() = pnode->X() - disp[0];
	    pnode->Y0() = pnode->Y() - disp[1];
	    pnode->Z0() = pnode->Z() - disp[2];

	    //Conditions must be also created with the add of a new node:
	    Condition::NodesArrayType face1;
	    Condition::NodesArrayType face2;
	    face1.reserve(2);
	    face2.reserve(2);

	    face1.push_back(rConditionGeom(0));
	    face1.push_back(pnode);

	    face2.push_back(pnode);
	    face2.push_back(rConditionGeom(1));
		
	    id   = initial_cond_size+(i*2);
	    //properties to be used in the generation
	    Properties::Pointer properties = list_of_conditions[i]->pGetProperties();
	    Condition::Pointer pcond1      = list_of_conditions[i]->Create(id, face1, properties);
	    // std::cout<<" ID"<<id<<" 1s "<<pcond1->GetGeometry()[0].Id()<<" "<<pcond1->GetGeometry()[1].Id()<<std::endl;
	    id   = initial_cond_size+(i*2+1);
	    Condition::Pointer pcond2      = list_of_conditions[i]->Create(id, face2, properties);
	    // std::cout<<" ID"<<id<<" 2s "<<pcond2->GetGeometry()[0].Id()<<" "<<pcond2->GetGeometry()[1].Id()<<std::endl;

	    pcond1->Set(NEW_ENTITY);
	    pcond2->Set(NEW_ENTITY);

	    pcond1->SetValue(MASTER_NODES, list_of_conditions[i]->GetValue(MASTER_NODES) );
	    pcond1->SetValue(NORMAL, list_of_conditions[i]->GetValue(NORMAL) );
	    pcond1->SetValue(CAUCHY_STRESS_VECTOR,list_of_conditions[i]->GetValue(CAUCHY_STRESS_VECTOR));
	    pcond1->SetValue(DEFORMATION_GRADIENT,list_of_conditions[i]->GetValue(DEFORMATION_GRADIENT));

	    pcond2->SetValue(MASTER_NODES, list_of_conditions[i]->GetValue(MASTER_NODES) );
	    pcond2->SetValue(NORMAL, list_of_conditions[i]->GetValue(NORMAL) );
	    pcond2->SetValue(CAUCHY_STRESS_VECTOR,list_of_conditions[i]->GetValue(CAUCHY_STRESS_VECTOR));
	    pcond2->SetValue(DEFORMATION_GRADIENT,list_of_conditions[i]->GetValue(DEFORMATION_GRADIENT));

	    (rModelPart.Conditions(MeshId)).push_back(pcond1);
	    (rModelPart.Conditions(MeshId)).push_back(pcond2);

	    // (rModelPart.Conditions()).push_back(pcond1);
	    // (rModelPart.Conditions()).push_back(pcond2);
	  }

	
	//Clean Conditions
	ModelPart::ConditionsContainerType RemoveConditions;
	    
	//id = 0;
	for(ModelPart::ConditionsContainerType::iterator ic = rModelPart.ConditionsBegin(MeshId); ic!= rModelPart.ConditionsEnd(MeshId); ic++)
	  {

	    Geometry< Node<3> > rGeom =ic->GetGeometry();
	    for(unsigned int i=0; i<rGeom.size(); i++)
	      {
		rGeom[i].Reset(TO_SPLIT);
	      }
		
	    if(ic->IsNot(TO_ERASE)){
	      //id+=1;
	      RemoveConditions.push_back(*(ic.base()));
	      //RemoveConditions.back().SetId(id);
	    }
	    else{
	      //std::cout<<" is a release condition "<<std::endl;
	    }
	  }
	    
	rModelPart.Conditions(MeshId).swap(RemoveConditions);
	
      }


    std::cout<<"   Nodes and Conditions : "<<rModelPart.Nodes(MeshId).size()<<", "<<rModelPart.Conditions(MeshId).size()<<std::endl;
    std::cout<<"   REFINE BOUNDARY ]; "<<std::endl;
    KRATOS_CATCH(" ")
      }

  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::GenerateNewParticles (ModelPart& rModelPart,MeshingVariables &rVariables,struct triangulateio &in,struct triangulateio &out,ModelPart::IndexType MeshId)
  {
    std::cout<<" [ GENERATE NEW NODES: "<<std::endl;


    //Find out where the new nodes belong to:

    //defintions for spatial search
    typedef Node<3>                                  PointType;
    typedef Node<3>::Pointer                  PointPointerType;
    typedef std::vector<PointPointerType>          PointVector;
    typedef PointVector::iterator                PointIterator;
    typedef std::vector<double>                 DistanceVector;
    typedef std::vector<double>::iterator     DistanceIterator;

    typedef Bucket<3, PointType, PointVector, PointPointerType, PointIterator, DistanceIterator > BucketType;
    typedef Tree< KDTreePartition<BucketType> >     KdtreeType; //Kdtree

    //creating an auxiliary list for the new nodes
    PointVector list_of_new_nodes;
    //std::vector<int> local_ids;

    //node to get the DOFs from
    Node<3>::DofsContainerType& reference_dofs = (rModelPart.NodesBegin(MeshId))->GetDofs();

    double z = 0.0;

    unsigned int initial_node_size = rModelPart.Nodes().size()+1; //total model part node size
    //if points were added, new nodes must be added to ModelPart
    int j = 0;
    if (out.numberofpoints > in.numberofpoints)
      {
	for(int i = in.numberofpoints; i<out.numberofpoints; i++)
	  {
	    unsigned int id = initial_node_size + j ;
	    int base = i*2;
	    double& x= out.pointlist[base];
	    double& y= out.pointlist[base+1];

	    //std::cout<<" domain node id "<<id<<" local id "<<i+1<<std::endl;
	    //std::cout<<" node creation position ("<<x<<", "<<y<<")"<<std::endl;
	    Node<3>::Pointer pnode = rModelPart.CreateNewNode(id,x,y,z);
		
	    //set to the main mesh (Mesh 0) to avoid problems in the PreIds (number of nodes: change) in other methods
	    pnode->SetBufferSize(rModelPart.NodesBegin(MeshId)->GetBufferSize() );

	    list_of_new_nodes.push_back( pnode );

	    if(rVariables.idset){
	      rVariables.PreIds.push_back( pnode->Id() );
	      pnode->SetId(i+1);
	    }
	    //local_ids.push_back(i+1);

	    //set to the main mesh (Mesh 0) to avoid problems in the PreIds (number of nodes: change) in other methods
	    if(MeshId!=0)
	      (rModelPart.Nodes(MeshId)).push_back(pnode);

	    //generating the dofs
	    for(Node<3>::DofsContainerType::iterator iii = reference_dofs.begin(); iii != reference_dofs.end(); iii++)
	      {
		Node<3>::DofType& rDof = *iii;
		Node<3>::DofType::Pointer p_new_dof = pnode->pAddDof( rDof );

		(p_new_dof)->FreeDof();
	      }
		
	    j++;

	  }

      }

    std::cout <<"   Added nodes: " << out.numberofpoints-in.numberofpoints<<std::endl;
		
    //Set new PreIds in the rVariables.PreIds
    // j=0;
    // if(rVariables.idset){
    //   for( PointVector::iterator it =  list_of_new_nodes.begin(); it!=list_of_new_nodes.end(); it++)
    //     {
    //       //set PreIds
    //       rVariables.PreIds.push_back((*it)->Id());
    //       //recover local ids
    //       (*it)->SetId(local_ids[j]);
    //       //std::cout<<" Add rVariables.PreIds [ "<<(*it)->Id()<<" ]"<<std::endl;
    //       j++;
    //     }
    // }

    array_1d<double,3> N;
    array_1d<double,3> x1,x2,x3,xc;


    int point_base;
    unsigned int   MaximumNumberOfResults = list_of_new_nodes.size();
    PointVector    Results            (MaximumNumberOfResults);
    DistanceVector ResultsDistances   (MaximumNumberOfResults);

    int step_data_size = rModelPart.GetNodalSolutionStepDataSize();

    //if points were added
    if(out.numberofpoints-in.numberofpoints > 0)
      {

	unsigned int   bucket_size = 20;
	Node<3> work_point(0,0.0,0.0,0.0);

	ModelPart::NodesContainerType::iterator nodes_begin = rModelPart.NodesBegin(MeshId);
	KdtreeType  nodes_tree(list_of_new_nodes.begin(),list_of_new_nodes.end(),bucket_size);

	for(int el = 0; el< in.numberoftriangles; el++)
	  {
	    int base = el * 3;
	    //coordinates
	    point_base = (in.trianglelist[base] - 1)*2;
	    x1[0] = in.pointlist[point_base];
	    x1[1] = in.pointlist[point_base+1];

	    point_base = (in.trianglelist[base+1] - 1)*2;
	    x2[0] = in.pointlist[point_base];
	    x2[1] = in.pointlist[point_base+1];

	    point_base = (in.trianglelist[base+2] - 1)*2;
	    x3[0] = in.pointlist[point_base];
	    x3[1] = in.pointlist[point_base+1];

	    //find the center and "radius" of the element
	    double xc,  yc, radius;
	    mMeshDataTransferUtilities.CalculateCenterAndSearchRadius( x1[0], x1[1],
								       x2[0], x2[1],
								       x3[0], x3[1],
								       xc,yc,radius);

	    //find all of the new nodes within the radius
	    work_point.X() = xc;
	    work_point.Y() = yc;
	    work_point.Z() = 0.0;

	    int number_of_points_in_radius = nodes_tree.SearchInRadius (work_point, radius*1.01, Results.begin(), ResultsDistances.begin(),  MaximumNumberOfResults);

	    Triangle2D3<Node<3> > geom(*( (nodes_begin +  in.trianglelist[base]-1).base() 	),
				       *( (nodes_begin +  in.trianglelist[base+1]-1).base() ),
				       *( (nodes_begin +  in.trianglelist[base+2]-1).base() ) );

	    //check if inside and eventually interpolate
	    for( PointIterator it_found = Results.begin(); it_found != Results.begin() + number_of_points_in_radius; it_found++)
	      {
		//if((*it_found)->IsNot(STRUCTURE)){
		bool is_inside = false;
		is_inside = mMeshDataTransferUtilities.CalculatePosition(x1[0], x1[1],
									 x2[0], x2[1],
									 x3[0], x3[1],
									 (*it_found)->X(),(*it_found)->Y(),N);


		if(is_inside == true)
		  {
		    mMeshDataTransferUtilities.Interpolate(  geom,  N, step_data_size, *(it_found ) );
		  }
		//}
	      }
	  }
      }

    const array_1d<double,3> ZeroNormal(3,0.0);
    //set the coordinates to the original value
    for( PointVector::iterator it =  list_of_new_nodes.begin(); it!=list_of_new_nodes.end(); it++)
      {
	const array_1d<double,3>& disp = (*it)->FastGetSolutionStepValue(DISPLACEMENT);
	(*it)->X0() = (*it)->X() - disp[0];
	(*it)->Y0() = (*it)->Y() - disp[1];
	(*it)->Z0() = 0.0;

	//correct contact_normal interpolation
	noalias((*it)->GetSolutionStepValue(CONTACT_FORCE)) = ZeroNormal;
	noalias((*it)->GetSolutionStepValue(CONTACT_FORCE)) = ZeroNormal;
		    
	(*it)->SetValue(DOMAIN_LABEL,MeshId);

      }

    std::cout<<"   GENERATE NEW NODES ]; "<<std::endl;


  }

  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::SetElementNeighbours(ModelPart& rModelPart, MeshingVariables & rVariables,ModelPart::IndexType MeshId)
  {

    std::cout<<" [ SET ELEMENT NEIGHBOURS : "<<std::endl;
    std::cout<<"   Initial Faces : "<<rModelPart.Conditions(MeshId).size()<<std::endl;

    ModelPart::ElementsContainerType::const_iterator el_begin = rModelPart.ElementsBegin(MeshId);
	
    int facecounter=0;
    for(ModelPart::ElementsContainerType::const_iterator iii = rModelPart.ElementsBegin(MeshId);
	iii != rModelPart.ElementsEnd(MeshId); iii++)
      {

	int Id= iii->Id() - 1;
	//std::cout<<" Id ELNEIG "<<Id<<std::endl;

	(iii->GetValue(NEIGHBOUR_ELEMENTS)).resize(3);
	WeakPointerVector< Element >& neighb = iii->GetValue(NEIGHBOUR_ELEMENTS);

	for(int i = 0; i<3; i++)
	  {
	    int index = rVariables.NeighbourList[Id][i];
				
	    if(index > 0)
	      {
		//std::cout<<" Element "<<Id<<" size "<<rVariables.PreservedElements.size()<<std::endl;			    
		//std::cout<<" Index pre "<<index<<" size "<<rVariables.PreservedElements.size()<<std::endl;
		index = rVariables.PreservedElements[index-1];
		//std::cout<<" Index post "<<index<<std::endl;
	      }

	    if(index > 0)
	      {
		neighb(i) = *((el_begin + index -1 ).base());
	      }
	    else
	      {
		//neighb(i) = Element::WeakPointer();
		neighb(i) = *(iii.base());
		facecounter++;
	      }
	  }
      }
	
    std::cout<<"   Final Faces : "<<facecounter<<std::endl;
    std::cout<<"   SET ELEMENT NEIGHBOURS ]; "<<std::endl;

  }


  //*******************************************************************************************
  //*******************************************************************************************

  void TriangleMesh2DModeler::SetConditionsBoundary(ModelPart& rModelPart, MeshingVariables& rVariables,ModelPart::IndexType MeshId)
  {

    std::cout<<" [ SET BOUNDARY CONDITIONS : "<<std::endl;
    std::cout<<"   Initial Conditions : "<<rModelPart.Conditions(MeshId).size()<<std::endl;

    //properties to be used in the generation
    int number_properties = rModelPart.NumberOfProperties();
    Properties::Pointer properties = rModelPart.GetMesh().pGetProperties(number_properties-1);

    //reset the boundary flag
    for(ModelPart::NodesContainerType::const_iterator in = rModelPart.NodesBegin(MeshId); in!=rModelPart.NodesEnd(MeshId); in++)
      {
	in->Reset(BOUNDARY);
      }

    //filling the elemental neighbours list (from now on the elements list can not change)
    ModelPart::ElementsContainerType::const_iterator el_begin  = rModelPart.ElementsBegin(MeshId);
    ModelPart::ElementsContainerType::iterator elements_end = rModelPart.ElementsEnd(MeshId);


    //now the boundary faces
    int id=0;

    //set consecutive ids in the mesh conditions
    unsigned int condId=1;
    for(ModelPart::ConditionsContainerType::iterator ic = rModelPart.ConditionsBegin(MeshId); ic!= rModelPart.ConditionsEnd(MeshId); ic++)
      {
	Geometry< Node<3> >& rConditionGeom = ic->GetGeometry();
	if( rConditionGeom[0].Is(TO_ERASE) || rConditionGeom[1].Is(TO_ERASE) )
	  ic->Set(TO_ERASE);
	    
	ic->SetId(condId);
	condId++;
      }
	

    //control the previous mesh conditions
    std::vector<int> PreservedConditions( rModelPart.Conditions(MeshId).size() );
    std::fill( PreservedConditions.begin(), PreservedConditions.end(), 0 );

    //swap previous conditions
    ModelPart::ConditionsContainerType temporal_conditions;
    temporal_conditions.reserve(rModelPart.Conditions(MeshId).size());
	    
    temporal_conditions.swap(rModelPart.Conditions(MeshId));


    // std::cout<<"   Preserved Conditions ( ";
    // for (unsigned int i=0; i<PreservedConditions.size(); i++)
    //   {
    //     std::cout<<" "<<PreservedConditions[i]<<"  ";
    //   }
    // std::cout<<" ) "<<std::endl;

    for(ModelPart::ElementsContainerType::const_iterator ie = rModelPart.ElementsBegin(MeshId); ie != rModelPart.ElementsEnd(MeshId); ie++)
      {
	int Id=ie->Id() -1 ;

	ModelPart::ElementsContainerType::iterator el_neighb;
	/*each face is opposite to the corresponding node number so in 2D
	  0 ----- 1 2
	  1 ----- 2 0
	  2 ----- 0 1
	*/

	//finding boundaries and creating the "skin"
	//
	//********************************************************************

	Geometry< Node<3> >& rGeom = ie->GetGeometry();
	boost::numeric::ublas::matrix<unsigned int> lpofa; //points that define the faces

	//Get the standard ReferenceCondition
	const Condition & rReferenceCondition=rVariables.GetReferenceCondition();

	for(unsigned int i = 0; i<rGeom.size(); i++)
	  {

	    int index = rVariables.NeighbourList[Id][i];
		
	    if(index > 0)
	      {
		index = rVariables.PreservedElements[index-1];
	      }
		
	    if( index > 0)
	      {
		el_neighb = (rModelPart.Elements(MeshId)).find( el_begin->Id() + index-1 ); //if not found-> returns the last element
	      }
	    else
	      {
		el_neighb = elements_end;
	      }

	      
	    if( el_neighb == elements_end )
	      {
		rGeom.NodesInFaces(lpofa);   

		//if no neighnour is present => the face is free surface
		rGeom[lpofa(1,i)].Set(BOUNDARY);
		rGeom[lpofa(2,i)].Set(BOUNDARY);
	
		//Get the correct ReferenceCondition
		Condition::Pointer pBoundaryCondition;
		bool condition_found = false;
		bool point_condition = false; 

		    
		for(ModelPart::ConditionsContainerType::iterator ic = temporal_conditions.begin(); ic!= temporal_conditions.end(); ic++)
		  {
		    if( ic->IsNot(TO_ERASE) ){

		      if( ic->IsNot(CONTACT) ){
			  
			Geometry< Node<3> >& rConditionGeom = ic->GetGeometry();

			bool inserted = false;

			if( rConditionGeom[0].Is(NEW_ENTITY) || rConditionGeom[1].Is(NEW_ENTITY) ){
			  inserted = true;
			  if(rConditionGeom[0].Is(NEW_ENTITY))
			    std::cout<<" node 0: Id-> "<<rConditionGeom[0].Id()<<" is new entity "<<std::endl;
			  if(rConditionGeom[1].Is(NEW_ENTITY))
			    std::cout<<" node 1: Id-> "<<rConditionGeom[1].Id()<<" is new entity "<<std::endl;

			}

			if(ic->Is(NEW_ENTITY))
			  {
			    std::cout<<" Inserted Cond "<<ic->Id()<<" nodes "<<rConditionGeom[0].Id()<<" "<<rConditionGeom[1].Id()<<std::endl;
			    inserted = false;
			  }


			if( !inserted ){
			      
			  if( PreservedConditions[ic->Id()-1] == 0 ){
			      
			    if( (rConditionGeom[0].Id() == rGeom[lpofa(1,i)].Id() 
				 && rConditionGeom[1].Id() == rGeom[lpofa(2,i)].Id() ) || 
				(rConditionGeom[0].Id() == rGeom[lpofa(2,i)].Id() 
				 && rConditionGeom[1].Id() == rGeom[lpofa(1,i)].Id() ) ){
				
			      pBoundaryCondition = (*(ic.base())); //accessing boost::shared_ptr  get() to obtain the raw pointer
			      PreservedConditions[ic->Id()-1] += 1; //add each time is used
			      if( rConditionGeom.PointsNumber() == 1 )
 			          point_condition = true;	

			      condition_found=true;
			    }
			  }
			    
			}
			else{
			    
			  if( PreservedConditions[ic->Id()-1] < 2 ){
			    
			    if( rConditionGeom[0].Id() == rGeom[lpofa(1,i)].Id() ||
				rConditionGeom[1].Id() == rGeom[lpofa(2,i)].Id() || 
				rConditionGeom[0].Id() == rGeom[lpofa(2,i)].Id() ||
				rConditionGeom[1].Id() == rGeom[lpofa(1,i)].Id() ){
				
			      pBoundaryCondition = (*(ic.base())); //accessing boost::shared_ptr  get() to obtain the raw pointer
			      PreservedConditions[ic->Id()-1] += 1; //add each time is used
			      if( rConditionGeom.PointsNumber() == 1 )
 			          point_condition = true;
	
			      condition_found=true;
			    }	

			    std::cout<<" INSERTED COND "<<ic->Id()<<std::endl;
			  }			
			  
			}
			    			    			    			    
		      }
		      else{
			    
			PreservedConditions[ic->Id()-1] += 1;  //will not be restored
			//std::cout<<" Condition Contact "<<ic->Id()<<std::endl;

		      }
			
		    }
			  

		    if(condition_found==true){
		      // std::cout<<" Condition Found:  "<<ic->Id()<<" ("<<ic->GetGeometry()[0].Id()<<", "<<ic->GetGeometry()[1].Id()<<") == ("<<rGeom[lpofa(1,i)].Id()<<" "<<rGeom[lpofa(2,i)].Id()<<") ->  Used : "<<PreservedConditions[ic->Id()-1]<<" times "<<std::endl;
		      break;
		    }
		  }

		//Generate condition
		Condition::NodesArrayType face;
		face.reserve(2);
		face.push_back(rGeom(lpofa(1,i)));
		face.push_back(rGeom(lpofa(2,i)));
		id ++;

		//std::cout<<" id "<<id<<std::endl;

		Condition::Pointer p_cond;
		if(condition_found){
		  p_cond = pBoundaryCondition->Create(id, face, properties);
		      
		  p_cond->Data() =pBoundaryCondition->Data();

		  if( !point_condition ){
		      WeakPointerVector<Element > master_elems;
		      master_elems.push_back(Element::WeakPointer( *(ie.base()) ));
		      p_cond->SetValue(MASTER_ELEMENTS, master_elems );
		      
		      
		      WeakPointerVector<Node<3> > master_nodes;
		      master_nodes.push_back( Node<3>::WeakPointer( rGeom(lpofa(0,i)) ));
		      p_cond->SetValue(MASTER_NODES, master_nodes );
		  }    

		}
		else{
		  std::cout<<" Create Condition "<<id<<"("<<face[0].Id()<<","<<face[1].Id()<<")"<<std::endl;
		  p_cond = rReferenceCondition.Create(id, face, properties);
		      
		  //if a condition is created new nodes must be labeled TO_REFINE
		  face[0].Set(TO_REFINE);
		  face[1].Set(TO_REFINE);

		  Vector StressVector=ZeroVector(3);
		  Matrix DeformationGradient=identity_matrix<double>( 2 );

		  p_cond->SetValue(CAUCHY_STRESS_VECTOR,StressVector);
		  p_cond->SetValue(DEFORMATION_GRADIENT,DeformationGradient);
		  p_cond->GetValue(MASTER_ELEMENTS).push_back( Element::WeakPointer( *(ie.base()) ) );
		  p_cond->GetValue(MASTER_NODES).push_back( Node<3>::WeakPointer( rGeom(lpofa(0,i)) ) );
		}

		//usually one MasterElement and one MasterNode in 2D
		

		rModelPart.Conditions(MeshId).push_back(p_cond);

	      }

	  }

      }
    // std::cout<<"   Preserved Conditions ( ";
    // for (unsigned int i=0; i<PreservedConditions.size(); i++)
    //   {
    //     std::cout<<" "<<PreservedConditions[i]<<"  ";
    //   }
    // std::cout<<" ) "<<std::endl;

    std::cout<<"   Boundary Conditions LOCATED ["<<rModelPart.Conditions(MeshId).size()<<"]"<<std::endl;
    //all previous conditions have to be added
    for(ModelPart::ConditionsContainerType::iterator ic = temporal_conditions.begin(); ic!= temporal_conditions.end(); ic++)
      {
	bool node_not_preserved = false;
	bool condition_not_preserved = false;
	if( PreservedConditions[ic->Id()-1] == 0 ){

	  Geometry< Node<3> >& rGeom = ic->GetGeometry();
	  Condition::NodesArrayType face;

	  face.reserve(rGeom.size() );

	  for(unsigned int j=0; j<rGeom.size(); j++)
	    {
	      face.push_back(rGeom(j));
	    }

	  //if a condition is created new nodes must be labeled to REFINE
	  if( ic->Is(TO_ERASE) )
	    condition_not_preserved = true;
	  // if( face[0].IsNot(BOUNDARY) || face[1].IsNot(BOUNDARY) )
	  //   node_not_preserved = true;

	  if( face[0].Is(TO_ERASE) || face[1].Is(TO_ERASE) )
	    node_not_preserved = true;

	  if( face[0].Is(TO_REFINE) || face[1].Is(TO_REFINE) )
	    node_not_preserved = true;
	  
	  if(node_not_preserved == true || condition_not_preserved == true)
	    continue;

	  PreservedConditions[ic->Id()-1] += 1;

	  id +=1;

	  rModelPart.Conditions(MeshId).push_back(ic->Create(id,face,ic->pGetProperties()));

	  rModelPart.Conditions(MeshId).back().Data() = ic->Data();
	  std::cout<<" Temporal Condition Not Set "<<ic->Id()<<"("<<ic->GetGeometry()[0].Id()<<","<<ic->GetGeometry()[1].Id()<<")"<<std::endl;

	  std::cout<<" Push Back Not Set Conditions "<<id<<"("<<face[0].Id()<<","<<face[1].Id()<<")"<<std::endl;

	}
      }

    //control if previous conditions have been assigned
    int all_assigned = 0; 
    for(unsigned int i=0; i<PreservedConditions.size(); i++)
      {
	if( PreservedConditions[i] == 0 )
	  all_assigned ++;
      }

    if(all_assigned == 0)
      std::cout<<"   Boundary Conditions RELOCATED ["<<all_assigned<<"]"<<std::endl;
    else
      std::cout<<"   Boundary Conditions NOT relocated ["<<all_assigned<<"]"<<std::endl;
	
    std::cout<<"   Final Conditions: "<<rModelPart.Conditions(MeshId).size()<<std::endl;
    std::cout<<"   SET BOUNDARY CONDITIONS ]; "<<std::endl;
    //rModelPart.Conditions(MeshId).Sort();
    //rModelPart.Conditions(MeshId).Unique();
	
  }


  //*******************************************************************************************
  //*******************************************************************************************


} // Namespace Kratos

