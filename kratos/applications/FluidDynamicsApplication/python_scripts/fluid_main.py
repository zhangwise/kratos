from __future__ import print_function, absolute_import, division #makes KratosMultiphysics backward compatible with python 2.6 and 2.7

from KratosMultiphysics import *
from KratosMultiphysics.IncompressibleFluidApplication import *
from KratosMultiphysics.FluidDynamicsApplication import *
from KratosMultiphysics.ExternalSolversApplication import *
from KratosMultiphysics.MeshingApplication import *

######################################################################################
######################################################################################
######################################################################################
##PARSING THE PARAMETERS
import define_output

parameter_file = open("ProjectParameters.json",'r')
ProjectParameters = Parameters( parameter_file.read())

DomainSize = ProjectParameters["problem_data"]["DomainSize"].GetInt()

## defining a model part for the fluid
main_model_part = ModelPart(ProjectParameters["problem_data"]["ModelPartName"].GetString())

###TODO replace this "model" for real one once available
Model = {ProjectParameters["problem_data"]["ModelPartName"].GetString() : main_model_part}

#construct the solver
solver_module = __import__(ProjectParameters["solver_settings"]["solver_type"].GetString())
solver = solver_module.CreateSolver(main_model_part, ProjectParameters["solver_settings"])

solver.AddVariables()

#obtain the list of the processes to be applied
process_definition = Parameters(ProjectParameters["boundary_conditions_process_list"])

###read the model - note that SetBufferSize is done here
solver.ImportModelPart()

###add AddDofs
solver.AddDofs()


##here all of the allocation of the strategies etc is done
solver.Initialize()



##HUGE CHAPUZA! let our auxiliary model know of all the model_parts and submodel_parts
Model.update({"Inlet3D_Inlet_velocity_Auto1": main_model_part, #"Inlet3D_Inlet_velocity_Auto1"),
             "Outlet3D_Outlet_pressure_Auto1":main_model_part, #.GetSubModelPart("Outlet3D_Outlet_pressure_Auto1"),
             "Slip3D_No_Slip_Auto1":main_model_part.GetSubModelPart("Slip3D_No_Slip_Auto1"),
             "NoSlip3D_No_Slip_Auto1":main_model_part.GetSubModelPart("NoSlip3D_No_Slip_Auto1")})
print("PLEASE CORRECT THIS HUGE CHAPUZA")




#TODO: decide which is the correct place to initialize the processes 
list_of_processes = []
process_definition = ProjectParameters["boundary_conditions_process_list"]
for i in range(process_definition.size()):
    item = process_definition[i]
    module = __import__(item["implemented_in_module"].GetString())
    interface_file = __import__(item["implemented_in_file"].GetString())
    p = interface_file.Factory(item, Model)
    list_of_processes.append( p )
    print("done ",i)
            

for process in list_of_processes:
    process.ExecuteInitialize()


#TODO: think if there is a better way to do this
fluid_model_part = solver.GetComputeModelPart()


# initialize GiD  I/O
from gid_output import GiDOutput
output_settings = ProjectParameters["output_configuration"]
gid_io = GiDOutput(output_settings["output_filename"].GetString(),
                   output_settings["VolumeOutput"].GetBool(),
                   output_settings["GiDPostMode"].GetString(),
                   output_settings["GiDMultiFileFlag"].GetString(),
                   output_settings["GiDWriteMeshFlag"].GetBool(),
                   output_settings["GiDWriteConditionsFlag"].GetBool())
output_time = output_settings["output_time"].GetDouble()

gid_io.initialize_results(fluid_model_part)



for process in list_of_processes:
    process.ExecuteBeforeSolutionLoop()

## Stepping and time settings
Dt = ProjectParameters["problem_data"]["time_step"].GetDouble()
end_time = ProjectParameters["problem_data"]["end_time"].GetDouble()


time = 0.0
step = 0
out = 0.0
while(time <= end_time):

    time = time + Dt
    step = step + 1
    main_model_part.CloneTimeStep(time)

    print("STEP = ", step)
    print("TIME = ", time)

    if(step >= 3):
        for process in list_of_processes:
            process.ExecuteInitializeSolutionStep()
        
        solver.Solve()
        
        for process in list_of_processes:
            process.ExecuteFinalizeSolutionStep()

        #TODO: decide if it shall be done only when output is processed or not
        for process in list_of_processes:
            process.ExecuteBeforeOutputStep()
    
        if(output_time <= out):
            gid_io.write_results(
                time,
                fluid_model_part,
                output_settings["nodal_results"],
                output_settings["gauss_points_results"])
            out = 0
        
        
        for process in list_of_processes:
            process.ExecuteAfterOutputStep()

        out = out + Dt

gid_io.finalize_results()

for process in list_of_processes:
    process.ExecuteFinalize()












