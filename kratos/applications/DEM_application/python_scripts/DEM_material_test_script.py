from __future__ import print_function, absolute_import, division #makes KratosMultiphysics backward compatible with python 2.6 and 2.7
from KratosMultiphysics import *
from KratosMultiphysics.DEMApplication import *
# from KratosMultiphysics.MetisApplication import *
# from KratosMultiphysics.mpi import *

import math
import datetime
import shutil


class MaterialTest:

  def __init__(self, DEM_parameters, procedures, solver, graphs_path, balls_model_part):
    
      self.graphs_path = graphs_path
      self.balls_model_part = balls_model_part
      self.Procedures = procedures
      self.solver = solver
      
      self.sup_layer_fm = list()
      self.inf_layer_fm = list()
      self.others = list()
      
      self.bond_00_05 = list();
      self.bond_05_10 = list()
      self.bond_10_15 = list()
      self.bond_15_20 = list()
      self.bond_20_25 = list()
      self.bond_25_30 = list()
      self.bond_30_35 = list()
      self.bond_35_40 = list()
      self.bond_40_45 = list()
      self.bond_45_50 = list()
      self.bond_50_55 = list()
      self.bond_55_60 = list()
      self.bond_60_65 = list()
      self.bond_65_70 = list()
      self.bond_70_75 = list()
      self.bond_75_80 = list()
      self.bond_80_85 = list()
      self.bond_85_90 = list()
      self.sizes = [];
      self.sigma_mean_table = [];
      self.tau_mean_table = [];
      self.sigma_rel_std_dev_table = [];
      self.tau_rel_std_dev_table = [];
      self.sigma_ratio_table = [];
      self.graph_counter = 0;
      self.renew_pressure = 0;
      self.Pressure = 0.0;

      for i in xrange(0,18):
          self.sizes.append(0.0)
          self.sigma_mean_table.append(0.0)
          self.tau_mean_table.append(0.0)
          self.sigma_rel_std_dev_table.append(0.0)
          self.tau_rel_std_dev_table.append(0.0)
          self.sigma_ratio_table.append(0.0)
 
      self.strain = 0.0; self.total_stress = 0.0; self.volumetric_strain = 0.0; self.radial_strain = 0.0; self.first_time_entry = 1; self.first_time_entry_2 = 1
      self.strain_fem = 0.0; self.total_stress_bot = 0.0; self.total_stress_mean = 0.0; self.total_stress_fem = 0.0
      
      # for the graph plotting    
      self.loading_velocity = 0.0
      self.height = DEM_parameters.SpecimenLength
      self.diameter = DEM_parameters.SpecimenDiameter

      self.initial_time = datetime.datetime.now()

      os.chdir(self.graphs_path)

      self.chart = open(DEM_parameters.problem_name + "_Parameter_chart.grf", 'w')

      if(DEM_parameters.TestType == "BTS"):

          self.bts_export = open(DEM_parameters.problem_name + "_bts" + ".grf", 'w');
          self.Procedures.BtsSkinDetermination(self.balls_model_part, self.solver)

      else:
        
        for node in self.balls_model_part.Nodes:
          if (node.GetSolutionStepValue(GROUP_ID) == 1):  # reserved for specimen particles with imposed displacement and strain-stress measurement (superior). Doesn't recive pressure
              self.sup_layer_fm.append(node)
          elif (node.GetSolutionStepValue(GROUP_ID) == 2):  # reserved for specimen particles with imposed displacement and strain-stress measurement (superior). Doesn't recive pressure
              self.inf_layer_fm.append(node)
          else:
              self.others.append(node)

        self.graph_export_top = open(DEM_parameters.problem_name + "_graph_TOP.grf", 'w')
        self.graph_export_bot = open(DEM_parameters.problem_name +"_graph_BOT.grf", 'w')
        self.graph_export_mean = open(DEM_parameters.problem_name +"_graph_MEAN.grf", 'w')
        self.graph_export_volumetric = open(DEM_parameters.problem_name+"_graph_VOL.grf",'w')
        
        if(DEM_parameters.FemPlates == "ON"):
          self.graph_export_fem = open(DEM_parameters.problem_name +"_graph_PLATE.grf", 'w')

        #measuring height:
        #pre_utilities = PreUtilities(self.balls_model_part)
      
        #(subtotal_top,weight_top) = pre_utilities.MeasureTopHeigh(self.balls_model_part)
        #(subtotal_bot,weight_bot) = pre_utilities.MeasureBotHeigh(self.balls_model_part)
    
        #if(DEM_parameters.FemPlates == "ON"):
          #mean_top = 0.30
          #mean_bot = 0.00
          
        #else:
          #(subtotal_top,weight_top) = pre_utilities.MeasureTopHeigh(self.balls_model_part)
          #(subtotal_bot,weight_bot) = pre_utilities.MeasureBotHeigh(self.balls_model_part)

          #mean_top = subtotal_top/weight_top;
          #mean_bot = subtotal_bot/weight_bot;
      
        #ini_height = mean_top - mean_bot

        height = DEM_parameters.SpecimenLength #ini_height    
      
      
        print ('Initial Height of the Model: ' + str(height)+'\n')
        
        if(DEM_parameters.PredefinedSkinOption == "ON" ):
          print ("ERROR: in Concrete Test Option the Skin is automatically predefined. Switch the Predefined Skin Option OFF")

        (xtop_area,xbot_area,xlat_area,xtopcorner_area,xbotcorner_area) = self.Procedures.CylinderSkinDetermination(self.balls_model_part,self.solver,DEM_parameters) # defines the skin and areas
      
      
      if ( ( DEM_parameters.TestType == "Triaxial") or ( DEM_parameters.TestType == "Hydrostatic") ):

        #Correction Coefs
        self.alpha_top = 3.141592*self.diameter*self.diameter*0.25/(xtop_area + 0.70710678*xtopcorner_area)
        self.alpha_bot = 3.141592*self.diameter*self.diameter*0.25/(xbot_area + 0.70710678*xbotcorner_area)
        self.alpha_lat = 3.141592*self.diameter*self.height/(xlat_area + 0.70710678*xtopcorner_area + 0.70710678*xbotcorner_area) 
    
 
  
  def Main(self,DEM_parameters):
    
    graph_frequency        = int(DEM_parameters.GraphExportFreq/self.balls_model_part.ProcessInfo.GetValue(DELTA_TIME))
   
    if( (DEM_parameters.TestType == "Triaxial" ) and (DEM_parameters.ConfinementPressure != 0.0) ):
          
      if( self.renew_pressure == 10):
        
        ApplyLateralPressure(self.Pressure, self.Procedures.XLAT, self.Procedures.XBOT, self.Procedures.XTOP, self.Procedures.XBOTCORNER, self.Procedures.XTOPCORNER,self.alpha_top,self.alpha_bot,self.alpha_lat)
                
        self.renew_pressure = 0

      self.renew_pressure += 1
      
    total_force_top = 0.0
    total_force_bot = 0.0
    total_force_bts = 0.0
    total_fem_force = 0.0

    if( DEM_parameters.TestType != "None" ):
      
      dt = self.balls_model_part.ProcessInfo.GetValue(DELTA_TIME)
      self.strain += -1.0*DEM_parameters.LoadingVelocityTop*dt/DEM_parameters.SpecimenLength

      if( self.graph_counter == graph_frequency):
        
        self.graph_counter = 0
        
        if( DEM_parameters.TestType =="BTS"):

          for node in self.sup_layer_fm:

            force_node_y = node.GetSolutionStepValue(ELASTIC_FORCES)[1]

            total_force_bts += force_node_y
            
          bts_export.write(str(step)+"  "+str(total_force_bts)+'\n')
          bts_export.flush()
          
        else:

          radial_strain = MeasureRadialStrain(self.Procedures.XLAT)
          
          for node in self.sup_layer_fm:

            force_node_y = node.GetSolutionStepValue(ELASTIC_FORCES)[1]

            total_force_top += force_node_y

          self.total_stress_top = total_force_top/(DEM_parameters.MeasuringSurface*1000000)
          
          for node in self.inf_layer_fm:

            force_node_y = -node.GetSolutionStepValue(ELASTIC_FORCES)[1]

            total_force_bot += force_node_y

          self.total_stress_bot = total_force_bot/(DEM_parameters.MeasuringSurface*1000000)
          
          self.graph_export_top.write(str(self.strain)+"    "+str(self.total_stress_top)+'\n')
          self.graph_export_bot.write(str(self.strain)+"    "+str(self.total_stress_bot)+'\n')
          self.total_stress_mean = 0.5*(self.total_stress_bot + self.total_stress_top)

          self.graph_export_mean.write(str(self.strain)+"    "+str(self.total_stress_mean)+'\n')
          
          self.graph_export_top.flush()
          self.graph_export_bot.flush()
          self.graph_export_mean.flush()
          
          volumetric_strain = self.strain - 2*radial_strain
          
          self.graph_export_volumetric.write(str(volumetric_strain)+"    "+str(self.total_stress_mean)+'\n')
          self.graph_export_volumetric.flush()
          
          self.Pressure = self.total_stress_mean*1e6

          if(self.Pressure > DEM_parameters.ConfinementPressure * 1e6 ):
            
            self.Pressure = DEM_parameters.ConfinementPressure * 1e6 
            
            if( (DEM_parameters.HorizontalFixVel == "ON") and (self.first_time_entry_2) ):
              
                self.balls_model_part.ProcessInfo.SetValue(FIX_VELOCITIES_FLAG, 1)
                self.first_time_entry_2 = 0
                  
          
          ##################################PLATE##################################

          if(DEM_parameters.FemPlates == "ON"):

            for node in RigidFace_model_part.Nodes:
              if (node.GetSolutionStepValue(EXPORT_GROUP_ID)==1):
                current_heigh = node.Y
                break;
            
            strain_fem = -(current_heigh-mean_top)/height
            for node in RigidFace_model_part.Nodes:
              if (node.GetSolutionStepValue(EXPORT_GROUP_ID)==1):

                force_node_fem_y = node.GetSolutionStepValue(TOTAL_FORCES)[1]
                total_fem_force += force_node_fem_y
                
            total_stress_fem = total_fem_force/(DEM_parameters.MeasuringSurface*1000000)
            
            if((DEM_parameters.FemPlates == "ON") and (current_heigh <= 0.30)):
              
                graph_export_fem.write(str(strain_fem)+"  "+str(total_stress_fem)+'\n')    
            graph_export_fem.flush()
          
          ##################################POISSON##################################
          
          #if(DEM_parameters.PoissonMeasure == "ON"):
                      
            #xleft_weight  = 0.0         
            #xright_weight  = 0.0

            #left_counter = 0.0
            #right_counter = 0.0

            #for node in left_nodes:
              
              #xleft_weight = +(node.X - node.GetSolutionStepValue(RADIUS))*node.GetSolutionStepValue(RADIUS)
              #left_counter = +node.GetSolutionStepValue(RADIUS)
              
            #for node in right_nodes:
              
              #xright_weight = +(node.X + node.GetSolutionStepValue(RADIUS))*node.GetSolutionStepValue(RADIUS)
              #right_counter = +node.GetSolutionStepValue(RADIUS)
            
            #width_now = xright_weight/right_counter - xleft_weight/left_counter

            #measured_poisson =  ((width_now-width_ini)/width_ini)/strain
            
            #graph_export_poisson.write(str(strain)+"  "+str(measured_poisson)+'\n')

    self.graph_counter += 1
  
  def PrintChart(self,DEM_parameters):
    
    loading_velocity = DEM_parameters.LoadingVelocityTop
  
    print ('************DEM VIRTUAL LAB******************'+'\n')
    print ('Loading velocity: ' + str(loading_velocity) + '\n')
    print ('Expected maximum deformation: ' + str(-loading_velocity*DEM_parameters.FinalTime/self.height*100) +'%'+'\n'+'\n'  )

    self.chart.write(("***********PARAMETERS*****************")+'\n')
    self.chart.write( "                                    " +'\n')
    self.chart.write( "    DENSI  = " + (str(DEM_parameters.w_densi))+" Kg/m3     "+'\n')
    self.chart.write( "    STAFRC = " + (str(DEM_parameters.InternalFriction))+"           "+'\n')
    self.chart.write( "    DYNFRC = " + (str(DEM_parameters.w_dynfrc))+"          " +'\n')
    self.chart.write( "    YOUNG  = " + (str(DEM_parameters.w_young/1e9))+" GPa"+"     " +'\n')
    self.chart.write( "    POISS  = " + (str(DEM_parameters.w_poiss))+"           " +'\n')
    self.chart.write( "    FTS    = " + (str(DEM_parameters.NormalTensileStrength))+" Mpa        " +'\n')
    self.chart.write( "    LCS1   = " + (str(DEM_parameters.LCS1))+" Mpa       " +'\n')
    self.chart.write( "    LCS2   = " + (str(DEM_parameters.LCS2))+" Mpa       " +'\n')
    self.chart.write( "    LCS3   = " + (str(DEM_parameters.LCS3))+" Mpa       " +'\n')
    self.chart.write( "    YRC1   = " + (str(DEM_parameters.YRC1))+"           " +'\n')
    self.chart.write( "    YRC2   = " + (str(DEM_parameters.YRC2))+"           " +'\n')
    self.chart.write( "    YRC3   = " + (str(DEM_parameters.YRC3))+"           " +'\n')
    self.chart.write( "    NG     = " + (str(7.0/6.0*2.0*(1.0+DEM_parameters.w_poiss)))+"           " +'\n')
    self.chart.write( "    FSS    = " + (str(DEM_parameters.TangentialStrength))+" Mpa       " +'\n')
    self.chart.write( "    YEP    = " + (str(DEM_parameters.PlasticYoungModulus/1e9))+" GPa"+"     " +'\n')
    self.chart.write( "    YIELD  = " + (str(DEM_parameters.PlasticYieldStress))+" Mpa       " +'\n')
    self.chart.write( "    EDR    = " + (str(DEM_parameters.DamageDeformationFactor))+"           " +'\n')
    self.chart.write( "    GDAMP  = " + (str(DEM_parameters.GlobalForceReduction))+"           " +'\n')
    self.chart.write( "    LDAMP  = " + (str(DEM_parameters.LocalDampingFactor))+"           " +'\n')
    self.chart.write( "    ALPHA  = " + str(1.00) +"           " +'\n')
    self.chart.write( "                                    " +'\n')
    self.chart.write( "**************************************" +'\n')

    self.chart.close()
    
    a_chart = open(DEM_parameters.problem_name + "_Parameter_chart.grf","r")

    for line in a_chart.readlines():
      print(line)
    a_chart.close()

  
  def FinalizeGraphs(self,DEM_parameters):
  
    os.chdir(self.graphs_path)

    #fer una copia i cambiar de nom.  
      
    for filename in os.listdir("."):
      
      if filename.startswith(DEM_parameters.problem_name + "_graph_TOP.grf"):
        shutil.copy(filename, filename+"COPY")
        os.rename(filename+"COPY", DEM_parameters.problem_name + "_graph_" + str(self.initial_time) + "_TOP.csv")
      if filename.startswith(DEM_parameters.problem_name + "_graph_BOT.grf"):
        shutil.copy(filename, filename+"COPY")
        os.rename(filename+"COPY", DEM_parameters.problem_name + "_graph_" + str(self.initial_time) + "_BOT.csv")
      if filename.startswith(DEM_parameters.problem_name + "_graph_MEAN.grf"):
        shutil.copy(filename, filename+"COPY")
        os.rename(filename+"COPY", DEM_parameters.problem_name + "_graph_" + str(self.initial_time) + "_MEAN.csv")
      if filename.startswith(DEM_parameters.problem_name + "_graph_PLATE.grf"):
        shutil.copy(filename, filename+"COPY")
        os.rename(filename+"COPY", DEM_parameters.problem_name + "_graph_" + str(self.initial_time) + "_PLATE.csv")

      self.graph_export_top.close()
      self.graph_export_bot.close()
      self.graph_export_mean.close()
      self.graph_export_volumetric.close()
      
      if(DEM_parameters.FemPlates == "ON"):
        self.graph_export_fem.close()

    if(DEM_parameters.TestType == "BTS"):
      self.bts_export.close()
  
  def OrientationStudy(self,contact_model_part):
    
    #OrientationChart = open("OrientationChart", 'w')
      
    #OrientationChart.write(str(j)+"    "+str(alpha_deg)+'\n')
      
    for element in contact_model_part.Elements:

      u1 = element.GetNode(1).X - element.GetNode(0).X
      u2 = element.GetNode(1).Y - element.GetNode(0).Y
      u3 = element.GetNode(1).Z - element.GetNode(0).Z
      
      alpha = abs(math.asin(abs(u2)/math.sqrt((u1*u1)+(u2*u2)+(u3*u3))))
      
      alpha_deg = alpha/math.pi*180

      if(alpha_deg >= 0.0 and alpha_deg < 5.0):
        self.bond_00_05.append(element)

      if(alpha_deg >= 5.0 and alpha_deg < 10.0):
        self.bond_05_10.append(element)
        
      if(alpha_deg >= 10.0 and alpha_deg < 15.0):
        self.bond_10_15.append(element)
        
      if(alpha_deg >= 15.0 and alpha_deg < 20.0):
        self.bond_15_20.append(element)
        
      if(alpha_deg >= 20.0 and alpha_deg < 25.0):
        self.bond_20_25.append(element)
        
      if(alpha_deg >= 25.0 and alpha_deg < 30.0):
        self.bond_25_30.append(element)
        
      if(alpha_deg >= 30.0 and alpha_deg < 35.0):
        self.bond_30_35.append(element)
      
      if(alpha_deg >= 35.0 and alpha_deg < 40.0):
        self.bond_35_40.append(element)
      
      if(alpha_deg >= 40.0 and alpha_deg < 45.0):
        self.bond_40_45.append(element)
        
      if(alpha_deg >= 45.0 and alpha_deg < 50.0):
        self.bond_45_50.append(element)
        
      if(alpha_deg >= 50.0 and alpha_deg < 55.0):
        self.bond_50_55.append(element)
        
      if(alpha_deg >= 55.0 and alpha_deg < 60.0):
        self.bond_55_60.append(element)
      
      if(alpha_deg >= 60.0 and alpha_deg < 65.0):
        self.bond_60_65.append(element)
        
      if(alpha_deg >= 65.0 and alpha_deg < 70.0):
        self.bond_65_70.append(element)
        
      if(alpha_deg >= 70.0 and alpha_deg < 75.0):
        self.bond_70_75.append(element)
            
      if(alpha_deg >= 75.0 and alpha_deg < 80.0):
        self.bond_75_80.append(element)
        
      if(alpha_deg >= 80.0 and alpha_deg < 85.0):
        self.bond_80_85.append(element)
        
      if(alpha_deg >= 85.0 and alpha_deg < 90.0):
        self.bond_85_90.append(element)
    
    ii=0 
    for item in [self.bond_00_05, self.bond_05_10, self.bond_10_15, self.bond_15_20, self.bond_20_25, self.bond_25_30, self.bond_30_35, self.bond_35_40, self.bond_40_45,  self.bond_45_50, self.bond_50_55, self.bond_55_60, self.bond_60_65, self.bond_65_70, self.bond_70_75, self.bond_75_80, self.bond_80_85, self.bond_85_90]:
      
      self.sizes[ii] = len(item)  
      
      i = 0.0
      sigma_sum =0.0
      tau_sum = 0.0
      
      sigma_total_sum_squared = 0
      tau_total_sum_squared = 0.0
      
      volume = 0.0
      area = 0.0

      for element in item:
        
        sigma_normal = element.GetValue(CONTACT_SIGMA)
        sigma_tau = element.GetValue(CONTACT_TAU)
        
        sigma_sum += sigma_normal
        tau_sum += sigma_tau
        
        sigma_partial_sum_squared = sigma_normal ** 2.0
        sigma_total_sum_squared += sigma_partial_sum_squared
        
        tau_partial_sum_squared = sigma_tau ** 2.0
        tau_total_sum_squared += tau_partial_sum_squared
        
        i += 1.0

      sigma_mean = sigma_sum / len(item)
      sigma_var = sigma_total_sum_squared / len(item) - sigma_mean ** 2.0
      
      sigma_std_dev = 0.0

      if(abs(sigma_var) > 1e-9):
          std_dev = sigma_var ** 0.5

      sigma_rel_std_dev = sigma_std_dev / sigma_mean
      
      tau_mean = tau_sum/ len(item)
      tau_var = tau_total_sum_squared / len(item) - tau_mean ** 2.0
      
      tau_std_dev = 0.0

      if(abs(tau_var) > 1e-9):
          tau_std_dev = tau_var ** 0.5

      tau_rel_std_dev = tau_std_dev / tau_mean
      
      self.sigma_mean_table[ii] = sigma_mean
      self.sigma_rel_std_dev_table[ii] = sigma_rel_std_dev
      self.tau_mean_table[ii] = tau_mean   
      self.tau_rel_std_dev_table[ii] = tau_rel_std_dev
      self.sigma_ratio_table[ii]=sigma_mean/(self.total_stress_mean*1e6)
      ii+=1
      
    print(self.sigma_ratio_table)
  
      
def ApplyPressure(Pressure, XLAT, XBOT, XTOP, XBOTCORNER, XTOPCORNER, alpha_top, alpha_bot, alpha_lat):

    for node in XLAT:

        r = node.GetSolutionStepValue(RADIUS)
        x = node.X
        y = node.Y
        z = node.Z

        values = [0.0,0.0,0.0]
        
        cross_section = 3.141592 * r * r

        vect = [0.0,0.0,0.0]

        # vector normal al centre:
        vect_moduli = math.sqrt(x * x + z * z)

        if(vect_moduli > 0.0):
            vect[0] = -x / vect_moduli
            vect[1] = 0
            vect[2] = -z / vect_moduli

        values[0] = cross_section * alpha_lat * Pressure * vect[0]
        values[1] = 0.0
        values[2] = cross_section * alpha_lat * Pressure * vect[2]

        node.SetSolutionStepValue(EXTERNAL_APPLIED_FORCE, values)

    for node in XTOP:

        r = node.GetSolutionStepValue(RADIUS)
        x = node.X
        y = node.Y
        z = node.Z

        values = [0.0,0.0,0.0]

        cross_section = 3.141592 * r * r

        values[0] = 0.0
        values[1] = -cross_section * alpha_top * Pressure
        values[2] = 0.0

        node.SetSolutionStepValue(EXTERNAL_APPLIED_FORCE, values)

    for node in XBOT:

        r = node.GetSolutionStepValue(RADIUS)
        x = node.X
        y = node.Y
        z = node.Z

        values = [0.0,0.0,0.0]

        cross_section = 3.141592 * r * r

        values[0] = 0.0
        values[1] = cross_section * alpha_bot * Pressure
        values[2] = 0.0

        node.SetSolutionStepValue(EXTERNAL_APPLIED_FORCE, values)

    for node in XTOPCORNER:

        r = node.GetSolutionStepValue(RADIUS)
        x = node.X
        y = node.Y
        z = node.Z

        values = [0.0,0.0,0.0]

        cross_section = 3.141592 * r * r

        vect = [0.0,0.0,0.0]

        # vector normal al centre:
        vect_moduli = math.sqrt(x * x + z * z)

        if(vect_moduli > 0.0):
            vect[0] = -x / vect_moduli
            vect[1] = 0
            vect[2] = -z / vect_moduli

        values[0] = cross_section * alpha_lat * Pressure * vect[0] * 0.70710678
        values[1] = -cross_section * alpha_top * Pressure * 0.70710678
        values[2] = cross_section * alpha_lat * Pressure * vect[2] * 0.70710678

        node.SetSolutionStepValue(EXTERNAL_APPLIED_FORCE, values)

    for node in XBOTCORNER:

        r = node.GetSolutionStepValue(RADIUS)
        x = node.X
        y = node.Y
        z = node.Z

        values = [0.0,0.0,0.0]

        cross_section = 3.141592 * r * r

        vect = [0.0,0.0,0.0]

        # vector normal al centre:
        vect_moduli = math.sqrt(x * x + z * z)

        if(vect_moduli > 0.0):
            vect[0] = -x / vect_moduli
            vect[1] = 0
            vect[2] = -z / vect_moduli

        values[0] = cross_section * alpha_lat * Pressure * vect[0] * 0.70710678
        values[1] = cross_section * alpha_bot * Pressure * 0.70710678
        values[2] = cross_section * alpha_lat * Pressure * vect[2] * 0.70710678

        node.SetSolutionStepValue(EXTERNAL_APPLIED_FORCE, values)


def ApplyLateralPressure(Pressure, XLAT, XBOT, XTOP, XBOTCORNER, XTOPCORNER, alpha_top, alpha_bot, alpha_lat):

    for node in XLAT:

        r = node.GetSolutionStepValue(RADIUS)
        x = node.X
        y = node.Y
        z = node.Z

        values = [0.0,0.0,0.0]

        cross_section = 3.141592 * r * r

        vect = [0.0,0.0,0.0]

        # vector normal al centre:
        vect_moduli = math.sqrt(x * x + z * z)

        if(vect_moduli > 0.0):
            vect[0] = -x / vect_moduli
            vect[1] = 0
            vect[2] = -z / vect_moduli

        values[0] = cross_section * alpha_lat * Pressure * vect[0]
        values[1] = 0.0
        values[2] = cross_section * alpha_lat * Pressure * vect[2]

        node.SetSolutionStepValue(EXTERNAL_APPLIED_FORCE, values)

    for node in XTOPCORNER:

        r = node.GetSolutionStepValue(RADIUS)
        x = node.X
        y = node.Y
        z = node.Z

        values = [0.0,0.0,0.0]

        cross_section = 3.141592 * r * r

        vect = [0.0,0.0,0.0]

        # vector normal al centre:
        vect_moduli = math.sqrt(x * x + z * z)

        if(vect_moduli > 0.0):
            vect[0] = -x / vect_moduli
            vect[1] = 0
            vect[2] = -z / vect_moduli

        values[0] = cross_section * alpha_lat * Pressure * vect[0] * 0.70710678
        values[1] = 0.0
        values[2] = cross_section * alpha_lat * Pressure * vect[2] * 0.70710678

        node.SetSolutionStepValue(EXTERNAL_APPLIED_FORCE, values)

    for node in XBOTCORNER:

        r = node.GetSolutionStepValue(RADIUS)
        x = node.X
        y = node.Y
        z = node.Z

        values = [0.0,0.0,0.0]

        cross_section = 3.141592 * r * r

        vect = [0.0,0.0,0.0]

        # vector normal al centre:
        vect_moduli = math.sqrt(x * x + z * z)

        if(vect_moduli > 0.0):
            vect[0] = -x / vect_moduli
            vect[1] = 0
            vect[2] = -z / vect_moduli

        values[0] = cross_section * alpha_lat * Pressure * vect[0] * 0.70710678
        values[1] = 0.0
        values[2] = cross_section * alpha_lat * Pressure * vect[2] * 0.70710678

        node.SetSolutionStepValue(EXTERNAL_APPLIED_FORCE, values)

def MeasureRadialStrain(LAT):
    
   mean_radial_strain = 0.0
   weight = 0.0
   
   for node in LAT:
     
     r = node.GetSolutionStepValue(RADIUS)
     x = node.X
     z = node.Z
     
     x0 = node.X0
     z0 = node.Z0
     
     dist_initial = math.sqrt(x0 * x0 + z0 * z0)
     dist_now = math.sqrt(x * x + z * z)
     
     node_radial_strain = (dist_now - dist_initial) / dist_initial
     
     mean_radial_strain += node_radial_strain*r*r
     weight += r*r
   
   if(weight == 0.0):
     print ("Error in MeasureRadialStrain. Lateral skin particles not well defined")
   else:
     
    radial_strain = mean_radial_strain/weight
   
   return radial_strain