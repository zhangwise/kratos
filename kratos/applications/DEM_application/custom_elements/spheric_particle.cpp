//
//   Project Name:        Kratos
//   Last Modified by:    $Author: Nelspon $
//   Date:                $Date: 2006-11-27 16:07:33 $
//   Revision:            $Revision: 1.1.1.1 $
//
//


// System includes
#include <string>
#include <iostream>


// External includes


// Project includes
#include "includes/define.h"
#include "spheric_particle.h"
#include "custom_utilities/GeometryFunctions.h"
#include "DEM_application.h"


namespace Kratos
{
     // using namespace GeometryFunctions;

      SphericParticle::SphericParticle() : DiscreteElement(){}

      SphericParticle::SphericParticle( IndexType NewId, GeometryType::Pointer pGeometry) : DiscreteElement(NewId, pGeometry){}

      SphericParticle::SphericParticle( IndexType NewId, GeometryType::Pointer pGeometry,  PropertiesType::Pointer pProperties)
      : DiscreteElement(NewId, pGeometry, pProperties){}

      SphericParticle::SphericParticle(IndexType NewId, NodesArrayType const& ThisNodes)
      : DiscreteElement(NewId, ThisNodes){}

      Element::Pointer SphericParticle::Create(IndexType NewId, NodesArrayType const& ThisNodes, PropertiesType::Pointer pProperties) const
      {
         return DiscreteElement::Pointer(new SphericParticle(NewId, GetGeometry().Create( ThisNodes ), pProperties) );
      }

      /// Destructor.
      SphericParticle::~SphericParticle(){}


      void SphericParticle::Initialize(){

        KRATOS_TRY

        mpFailureId = &(this->GetValue(PARTICLE_FAILURE_ID));

        //mDimension = this->GetGeometry().WorkingSpaceDimension();
        mDimension = 3; ///WARNING: I: to be revised.
        
        double density      = GetGeometry()(0)->FastGetSolutionStepValue(PARTICLE_DENSITY);
        double radius       = GetGeometry()(0)->FastGetSolutionStepValue(RADIUS);
        double& mass        = GetGeometry()(0)->FastGetSolutionStepValue(NODAL_MASS);

        double & Inertia         = GetGeometry()(0)->FastGetSolutionStepValue(PARTICLE_INERTIA);
        double & MomentOfInertia = GetGeometry()(0)->FastGetSolutionStepValue(PARTICLE_MOMENT_OF_INERTIA);


        mContinuumGroup     = this->GetGeometry()[0].GetSolutionStepValue(PARTICLE_CONTINUUM);

        //TO BE IMPROVED: i would like to work with *mpFailureId as integer. the problem is that it has to be exported to GID to be plotted.

        //provisional way is:
        if(mContinuumGroup==0)  {*mpFailureId=1;}
        else                    {*mpFailureId=0;}

        //easiest way is:   
        //*mpFailureId          = !(mContinuumGroup);
           
        if(mDimension ==2)
        {
            mass     = M_PI * radius * radius * density;

            mRealMass = mass;

            Inertia = 0.25 * M_PI * radius * radius * radius  * radius ;

            MomentOfInertia = 0.5 * radius * radius;

        }
        else
        {
            mass     = 4.0 / 3.0 * M_PI * radius * radius * radius * density;

            mRealMass = mass;

            Inertia = 0.25 * M_PI * radius * radius * radius  * radius ;

            MomentOfInertia = 0.4 * radius * radius;

        }
        
        //KRATOS_WATCH(*mpFailureId)



        KRATOS_CATCH( "" )

      }

    //**************************************************************************************************************************************************
    //**************************************************************************************************************************************************


      void SphericParticle::CalculateRightHandSide(VectorType& rRightHandSideVector,ProcessInfo& rCurrentProcessInfo){

        ComputeParticleContactForce(rCurrentProcessInfo);

        if( (rCurrentProcessInfo[ROTATION_OPTION] != 0) && (rCurrentProcessInfo[ROTATION_SPRING_OPTION] != 0) )
        {
            ComputeParticleRotationSpring(rCurrentProcessInfo);
        }

       CharacteristicParticleFailureId(rCurrentProcessInfo);

    //**************************************************************************************************************************************************
    //**************************************************************************************************************************************************

      }
      void SphericParticle::EquationIdVector(EquationIdVectorType& rResult, ProcessInfo& rCurrentProcessInfo){}
      void SphericParticle::MassMatrix(MatrixType& rMassMatrix, ProcessInfo& rCurrentProcessInfo)

      {

          double radius = GetGeometry()(0)->GetSolutionStepValue(RADIUS);
          double volume =   1.333333333333333*M_PI*radius*radius*radius;
          double density = GetGeometry()(0)->GetSolutionStepValue(PARTICLE_DENSITY);
          rMassMatrix.resize(1,1);
          rMassMatrix(0,0) = volume*density;

      }

        void SphericParticle::SetInitialContacts(int case_opt) //vull ficar que sigui zero si no son veins cohesius.

        {
            bool delta_OPTION;
            bool continuum_simulation_OPTION;

            switch (case_opt)
            {
                case 0:
                    delta_OPTION = false;
                    continuum_simulation_OPTION = false;
                    break;
                case 1:
                    delta_OPTION = true;
                    continuum_simulation_OPTION = false;
                    break;
                case 2:
                    delta_OPTION = true;
                    continuum_simulation_OPTION = true;
                    break;
                case 3:
                    delta_OPTION = false;
                    continuum_simulation_OPTION = true;
                    break;
                default:
                    delta_OPTION = false;
                    continuum_simulation_OPTION = false;
            }

            // DEFINING THE REFERENCES TO THE MAIN PARAMETERS

            ParticleWeakVectorType& r_neighbours             = this->GetValue(NEIGHBOUR_ELEMENTS);

            //this->GetValue(INITIAL_NEIGHBOUR_ELEMENTS).resize(r_neighbours.size());
            this->GetValue(PARTICLE_INITIAL_DELTA).resize(r_neighbours.size());
            this->GetValue(PARTICLE_CONTACT_DELTA).resize(r_neighbours.size());
            this->GetValue(PARTICLE_CONTACT_FAILURE_ID).resize(r_neighbours.size());

            ParticleWeakVectorType& r_initial_neighbours     = this->GetValue(INITIAL_NEIGHBOUR_ELEMENTS);

            unsigned int i=0;

            //default
            *mpFailureId=1;

            //SAVING THE INICIAL NEIGHBOURS, THE DELTAS AND THE FAILURE ID

            for(ParticleWeakIteratorType_ptr ineighbour = r_neighbours.ptr_begin();  //loop over the neighbours and store into a initial_neighbours vector.
            ineighbour != r_neighbours.ptr_end(); ineighbour++){

                if (this->Id() != ((*ineighbour).lock())->Id() )

                {

                    array_1d<double,3> other_to_me_vect = this->GetGeometry()(0)->Coordinates() - ((*ineighbour).lock())->GetGeometry()(0)->Coordinates();
                    double distance                     = sqrt(other_to_me_vect[0] * other_to_me_vect[0] +
                                                         other_to_me_vect[1] * other_to_me_vect[1] +
                                                         other_to_me_vect[2] * other_to_me_vect[2]);

                    double radius_sum                   = this->GetGeometry()(0)->GetSolutionStepValue(RADIUS) + ((*ineighbour).lock())->GetGeometry()(0)->GetSolutionStepValue(RADIUS);
                    double initial_delta                = radius_sum - distance;

                    int r_other_continuum_group = ((*ineighbour).lock())->GetGeometry()(0)->GetSolutionStepValue(PARTICLE_CONTINUUM);

                    //default:
                    this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[i]=1;
                    this->GetValue(PARTICLE_INITIAL_DELTA)[i]=0.0;
                    this->GetValue(PARTICLE_CONTACT_DELTA)[i]=0.0;

                        /* this loop will set only the 0 (contunuum simulating case) to the initial neighbours. The force calculator will change this
                         * values depending of the type of failure as it is describre here:
                         *
                         *   mContactFailureId values:
                         *      0 := Still a continuum simulating contact
                         *      1 := General detachment (no initial continuum case: non continuum simulating particles or particles from diferent continuum group.)
                         *      2 := Partially detached
                         *      3 := tensile case
                         *      4 := shear case
                         *      5 :=von Misses.....M: define new cases...
                         */

                    if( ( (r_other_continuum_group == mContinuumGroup) && (mContinuumGroup != 0) ) || ( fabs(initial_delta)>1.0e-6 ) ) // R: TOLERANCIA PER DIR QUE TENEN UN IDENTACIÓ O SEPARACIÓ; HAURIA DANAR LLIGADA AMB LU DE LA BUSQUEDA. la busqueda es fa per intersecció, es a dir identació es detecta pero si estan separades un pel ja no es troba com a veí.
                    //THESE ARE THE CASES THAT NEED TO STORE THE INITIAL NEIGHBOURS
                    {

                        r_initial_neighbours.push_back(*ineighbour);

                        if (delta_OPTION == true)
                        {
                            this->GetValue(PARTICLE_INITIAL_DELTA)[i]  =   initial_delta;
                            this->GetValue(PARTICLE_CONTACT_DELTA)[i]  =   initial_delta; //these variables are different and need to be kept.
                        }

                        if (continuum_simulation_OPTION == true)
                        {
                            if ( (r_other_continuum_group == mContinuumGroup) && (mContinuumGroup != 0) )
                            {

                                this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[i]=0;
                                *mpFailureId=0; // if a cohesive contact exist, the FailureId becomes 0.

                            }
                         
                        }//for continuum_simulation_OPTION                                                                                                 //hi havia: r_VectorContactFailureId[i]=1; //generally detached    //diferent group

                    } // FOR THE CASES THAT NEED STORING INITIAL NEIGHBOURS
//KRATOS_WATCH( this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[i])
                    i++;

                }//if I found myself.
            } //end for: ParticleWeakIteratorType ineighbour

            //KRATOS_WATCH(*mpFailureId)

        }//SetInitialContacts


       void SphericParticle::ComputeParticleContactForce(const ProcessInfo& rCurrentProcessInfo )

       {

            KRATOS_TRY

            ParticleWeakVectorType& r_neighbours             = this->GetValue(NEIGHBOUR_ELEMENTS);

          // vector<double>& r_VectorContactFailureId            = this->GetValue(PARTICLE_CONTACT_FAILURE_ID); //M:temporarily a vector of doubles... it should be vector of ints..
            vector<double>& r_VectorContactInitialDelta         = this->GetValue(PARTICLE_CONTACT_DELTA);

            // PROCESS INFO

            const array_1d<double,3>& gravity   = rCurrentProcessInfo[GRAVITY];

            double dt                           = rCurrentProcessInfo[DELTA_TIME];
            int damp_id                         = rCurrentProcessInfo[DAMP_TYPE];
            int force_calculation_type_id       = rCurrentProcessInfo[FORCE_CALCULATION_TYPE];
            int rotation_OPTION                 = rCurrentProcessInfo[ROTATION_OPTION]; //M:  it's 1/0, should be a boolean
            int global_variables_OPTION         = rCurrentProcessInfo[GLOBAL_VARIABLES_OPTION]; //M:  it's 1/0, should be a boolean

            int case_OPTION                     = rCurrentProcessInfo[CASE_OPTION];
            bool delta_OPTION;
            bool continuum_simulation_OPTION;

                switch (case_OPTION) {
                    case 0:
                        delta_OPTION = false;
                        continuum_simulation_OPTION = false;
                        break;
                    case 1:
                        delta_OPTION = true;
                        continuum_simulation_OPTION = false;
                        break;
                    case 2:
                        delta_OPTION = true;
                        continuum_simulation_OPTION = true;
                        break;
                    case 3:
                        delta_OPTION = false;
                        continuum_simulation_OPTION = true;
                        break;
                    default:
                        delta_OPTION = false;
                        continuum_simulation_OPTION = false;
                }

            // GETTING PARTICLE PROPERTIES

        //    int FailureId = *mpFailureId;
          //  int continuum_group     = mContinuumGroup;

            double Tension          = this->GetGeometry()[0].GetSolutionStepValue(PARTICLE_TENSION);
            double Cohesion         = this->GetGeometry()[0].GetSolutionStepValue(PARTICLE_COHESION);
            double FriAngle         = this->GetGeometry()[0].GetSolutionStepValue(PARTICLE_FRICTION); //M: CFENG: es aixo el angle de friccio?
            double Friction         = tan( FriAngle / 180.0 * M_PI);

            double radius               = this->GetGeometry()[0].GetSolutionStepValue(RADIUS);
            //double visco_damp_coeff = this->GetGeometry()[0].GetSolutionStepValue(VISCO_DAMP_COEFF);
            double restitution_coeff = this->GetGeometry()[0].GetSolutionStepValue(RESTITUTION_COEFF);
            double mass                 = mRealMass;

            double young                = this->GetGeometry()[0].GetSolutionStepValue(YOUNG_MODULUS);
            double poisson              = this->GetGeometry()[0].GetSolutionStepValue(POISSON_RATIO);

            array_1d<double,3>& force           = this->GetGeometry()[0].GetSolutionStepValue(RHS);//total forces, we reset to 0. and we calculate again.
            //COMPROBAR QUE ES ZERO DEL INITIALIZE SOLUTION STEP

            array_1d<double,3> applied_force    = this->GetGeometry()[0].GetSolutionStepValue(APPLIED_FORCE); //Nelson: se llama force la que hauria d0haver aqui

            force  = mass*gravity + applied_force;
            
            array_1d<double, 3 > & mRota_Moment = this->GetGeometry()[0].GetSolutionStepValue(PARTICLE_MOMENT);

            size_t iContactForce = 0;

            for(ParticleWeakIteratorType neighbour_iterator = r_neighbours.begin();
            neighbour_iterator != r_neighbours.end(); neighbour_iterator++)

            {
                // GETTING NEIGHBOUR PROPERTIES

                double other_radius                 = neighbour_iterator->GetGeometry()(0)->GetSolutionStepValue(RADIUS);
                double other_density                = neighbour_iterator->GetGeometry()(0)->GetSolutionStepValue(PARTICLE_DENSITY);
                double other_mass                   = 4.0 / 3.0 * M_PI * other_radius * other_radius * other_radius * other_density;
                double equiv_mass                   = sqrt(mass*other_mass);//(mass*other_mass*(mass+other_mass)) / ((mass+other_mass)*(mass+other_mass)); //I: calculated by Roberto Flores
                //double other_visco_damp_coeff       = neighbour_iterator->GetGeometry()(0)->GetSolutionStepValue(VISCO_DAMP_COEFF);
                double other_restitution_coeff      = neighbour_iterator->GetGeometry()(0)->GetSolutionStepValue(RESTITUTION_COEFF);
                double equiv_visco_damp_coeff;       //= (visco_damp_coeff + other_visco_damp_coeff) / 2.0;   //M: is it correct to be a simple mean.
                double equiv_restitution_coeff      = sqrt(restitution_coeff * other_restitution_coeff); //I: we assume this.
                // double other_mass                   = neighbour_iterator.mRealMass;
                double other_young                  = neighbour_iterator->GetGeometry()[0].GetSolutionStepValue(YOUNG_MODULUS);
                double other_poisson                = neighbour_iterator->GetGeometry()[0].GetSolutionStepValue(POISSON_RATIO);
                double other_tension                = neighbour_iterator->GetGeometry()[0].GetSolutionStepValue(PARTICLE_TENSION);
                double other_cohesion               = neighbour_iterator->GetGeometry()[0].GetSolutionStepValue(PARTICLE_COHESION);
                double other_FriAngle               = neighbour_iterator->GetGeometry()[0].GetSolutionStepValue(PARTICLE_FRICTION);

                // CONTINUUM SIMULATING PARAMETERS:

                double initial_delta = 0.0;
                double CTension = 0.0;
                double CCohesion = 0.0;

                ///WARNING: XAPUZAAAAA
                //double& mContactFailureId_double    = int(r_VectorContactFailureId[iContactForce]);
                //int mContactFailureId               = int(mContactFailureId_double);

                //array_1d<double,3>& mContactForces  = this->GetValue(PARTICLE_CONTACT_FORCES)[iContactForce];


/*
                KRATOS_WATCH( continuum_simulation_OPTION)
                        KRATOS_WATCH(*mpFailureId)
                        KRATOS_WATCH(this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[iContactForce])
*/
                if ( continuum_simulation_OPTION && (*mpFailureId==0) && (this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[iContactForce]==0) )
                {
                    // Test for Average, 120531, should be discussed
                    CTension  = (Tension + other_tension)   * 0.5;
                    CCohesion = (Cohesion + other_cohesion) * 0.5;

                    //KRATOS_WATCH(CTension)
                    //KRATOS_WATCH(CCohesion)


                    /*
                    CTensionUP    = 2* Tension * other_tension;
                    if(CTensionUP==0){

                        CTension=0;
                    }
                    else {

                    CTension    = 2* Tension * other_tension / (Tension + other_tension);

                    }
                    CCohesion   = 2* Cohesion * other_cohesion / (Cohesion + other_cohesion);
                     *
                    */
                }


                if( delta_OPTION && (iContactForce < r_VectorContactInitialDelta.size()) )
                {

                    initial_delta = r_VectorContactInitialDelta[iContactForce];
                }

                // BASIC CALCULATIONS

                array_1d<double,3> other_to_me_vect = this->GetGeometry()(0)->Coordinates() - neighbour_iterator->GetGeometry()(0)->Coordinates();
                double distance                     = sqrt(other_to_me_vect[0] * other_to_me_vect[0] +
                                                      other_to_me_vect[1] * other_to_me_vect[1] +
                                                      other_to_me_vect[2] * other_to_me_vect[2]);

                double radius_sum                   = radius + other_radius;

                double indentation                  = radius_sum - distance - initial_delta; //M: Here, Initial_delta is expected to be positive if it is embeding and negative if it's separation.

                double equiv_radius     = 2* radius * other_radius / (radius + other_radius);
                double equiv_area       = M_PI * equiv_radius * equiv_radius;
                double equiv_poisson    = 2* poisson * other_poisson / (poisson + other_poisson);
                double equiv_young      = 2 * young * other_young / (young + other_young);

                Friction                = tan( (FriAngle + other_FriAngle) * 0.5  / 180.0 * M_PI);

                //MACRO PARAMETERS

                double kn               = M_PI * 0.5 * equiv_young * equiv_radius; //M: CANET FORMULA
                double ks               = kn / (2.0 * (1.0 + equiv_poisson));
                double RN               = CTension * equiv_area; //tensile strenght
                double RT_base          = CCohesion * equiv_area; //cohesion

                if (global_variables_OPTION == 1) //globally defined parameters
                {

                  // KRATOS_WATCH("-------GLOBAL VARIABLES----------")

                   kn       = rCurrentProcessInfo[GLOBAL_KN];
                   ks       = rCurrentProcessInfo[GLOBAL_KT];
                   RN       = rCurrentProcessInfo[GLOBAL_RN];
                   RT_base  = rCurrentProcessInfo[GLOBAL_RT];
                   Friction = tan( (rCurrentProcessInfo[GLOBAL_FRI_ANG])*(M_PI/180) );

                }

                if(equiv_restitution_coeff>0){

                    equiv_visco_damp_coeff  = -( (2*log(equiv_restitution_coeff)*sqrt(equiv_mass*kn)) / (sqrt( (log(equiv_restitution_coeff)*log(equiv_restitution_coeff)) + (M_PI*M_PI) )) );
                }

                else {

                    equiv_visco_damp_coeff  = ( 2*sqrt(equiv_mass*kn) );
                }


                // FORMING LOCAL CORDINATES

                double NormalDir[3]           = {0.0};
                double LocalCoordSystem[3][3] = {{0.0}, {0.0}, {0.0}};
                NormalDir[0] = other_to_me_vect[0];   // M. this way the compresion is positive.
                NormalDir[1] = other_to_me_vect[1];
                NormalDir[2] = other_to_me_vect[2];
                GeometryFunctions::ComputeContactLocalCoordSystem(NormalDir, LocalCoordSystem);

                // VELOCITIES AND DISPLACEMENTS

                array_1d<double, 3 > vel            = this->GetGeometry()(0)->GetSolutionStepValue(VELOCITY);
                array_1d<double, 3 > other_vel      = neighbour_iterator->GetGeometry()(0)->GetSolutionStepValue(VELOCITY);

                array_1d<double, 3 > delta_displ            = this->GetGeometry()(0)->GetSolutionStepValue(DELTA_DISPLACEMENT);
                array_1d<double, 3 > other_delta_displ      = neighbour_iterator->GetGeometry()(0)->GetSolutionStepValue(DELTA_DISPLACEMENT);

                array_1d<double, 3 > delta_vel            = this->GetGeometry()(0)->GetSolutionStepValue(DELTA_VELOCITY);
                array_1d<double, 3 > other_delta_vel      = neighbour_iterator->GetGeometry()(0)->GetSolutionStepValue(DELTA_VELOCITY);

                double DeltDisp[3] = {0.0};
                double RelVel [3] = {0.0};
                double DeltRelVel[3] = {0.0};//Ignasi

                RelVel[0] = (vel[0] - other_vel[0]);
                RelVel[1] = (vel[1] - other_vel[1]);
                RelVel[2] = (vel[2] - other_vel[2]);

                //DeltDisp in global cordinates

                DeltDisp[0] = (delta_displ[0] - other_delta_displ[0]);
                DeltDisp[1] = (delta_displ[1] - other_delta_displ[1]);
                DeltDisp[2] = (delta_displ[2] - other_delta_displ[2]);

                //DeltRelVel in global cordinates

                DeltRelVel[0] = delta_vel[0] - other_delta_vel[0];
                DeltRelVel[1] = delta_vel[1] - other_delta_vel[1];
                DeltRelVel[2] = delta_vel[2] - other_delta_vel[2];
 
                if ( rotation_OPTION == 1 )
                {

                    double velA[3]   = {0.0};
                    double velB[3]   = {0.0};
                    double dRotaDisp[3] = {0.0};

                    array_1d<double, 3 > AngularVel       = this->GetGeometry()(0)->FastGetSolutionStepValue(ANGULAR_VELOCITY);
                    array_1d<double, 3 > Other_AngularVel = neighbour_iterator->GetGeometry()(0)->FastGetSolutionStepValue(ANGULAR_VELOCITY);

                    double Vel_Temp[3]       = {      AngularVel[0],       AngularVel[1],       AngularVel[2]};
                    double Other_Vel_Temp[3] = {Other_AngularVel[0], Other_AngularVel[1], Other_AngularVel[2]};
                    GeometryFunctions::CrossProduct(Vel_Temp,             LocalCoordSystem[2], velA);
                    GeometryFunctions::CrossProduct(Other_Vel_Temp, LocalCoordSystem[2], velB);

                    dRotaDisp[0] = -velA[0] * radius - velB[0] * other_radius;
                    dRotaDisp[1] = -velA[1] * radius - velB[1] * other_radius;
                    dRotaDisp[2] = -velA[2] * radius - velB[2] * other_radius;
                    //////contribution of the rotation vel
                    DeltDisp[0] += dRotaDisp[0] * dt;
                    DeltDisp[1] += dRotaDisp[1] * dt;
                    DeltDisp[2] += dRotaDisp[2] * dt;

                }//if rotation_OPTION

                double LocalDeltDisp[3] = {0.0};
                double LocalDeltRelVel[3] = {0.0};//Ignasi
                double LocalContactForce[3]  = {0.0};
                double GlobalContactForce[3] = {0.0};
                double LocalRelVel[3] = {0.0};
                //double GlobalContactForceOld[3] = {0.0};


                GlobalContactForce[0] = this->GetValue(PARTICLE_CONTACT_FORCES)[iContactForce][0];   //M:aqui tenim guardades les del neighbour calculator.
                GlobalContactForce[1] = this->GetValue(PARTICLE_CONTACT_FORCES)[iContactForce][1];
                GlobalContactForce[2] = this->GetValue(PARTICLE_CONTACT_FORCES)[iContactForce][2];

                GeometryFunctions::VectorGlobal2Local(LocalCoordSystem, DeltDisp, LocalDeltDisp);
                GeometryFunctions::VectorGlobal2Local(LocalCoordSystem, DeltRelVel, LocalDeltRelVel);//Ignasi
                GeometryFunctions::VectorGlobal2Local(LocalCoordSystem, GlobalContactForce, LocalContactForce);
                GeometryFunctions::VectorGlobal2Local(LocalCoordSystem, RelVel, LocalRelVel);


                // FORCES


                if ( (indentation > 0.0) || (this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[iContactForce] == 0) )  // for detached particles we enter only if the indentation is > 0.
                                                                                                              // for attached particles we enter only if the particle is still attached.
                {
               

                // TANGENTIAL FORCE: incremental calculation. YADE develops a complicated "absolute method"

                    LocalContactForce[0] += - ks * LocalDeltDisp[0];  // 0: first tangential
                    LocalContactForce[1] += - ks * LocalDeltDisp[1];  // 1: second tangential
                 
                // NORMAL FORCE

                    switch (force_calculation_type_id) //  0---linear comp & tension ; 1 --- Hertzian (no linear comp, linear tension)

                    {
                        case 0:

                            if(indentation >= 0.0) {LocalContactForce[2]= kn * indentation;}
                            else {LocalContactForce[2]= kn * indentation; }
                            break;

                        case 1:

                            if(indentation >= 0.0) {LocalContactForce[2]= kn * pow(indentation, 1.5); }
                            else { LocalContactForce[2] = kn * indentation; }
                            break;

                        default:
                            if(indentation >= 0.0) {LocalContactForce[2]= kn * indentation; }
                            else {LocalContactForce[2]= kn * indentation; }
                            break;

                    }

                }

                if ( (indentation <= 0.0) && (this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[iContactForce] != 0) )

                {
                    LocalContactForce[0] = 0.0;  // 0: first tangential
                    LocalContactForce[1] = 0.0;  // 1: second tangential
                    LocalContactForce[2] = 0.0;  // 2: normal force
                }

                // TENSION FAILURE

                if ( (this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[iContactForce] == 0) && (-LocalContactForce[2] > RN) )   //M:si la tensio supera el limit es seteja tot a zero.

                {
                    LocalContactForce[0]  = 0.0;
                    LocalContactForce[1]  = 0.0;
                    LocalContactForce[2]  = 0.0;

                    this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[iContactForce] = 3;  //tensile failure case.

                //M: podria ficar que ara la cohesion = dinamic cohesion, not static... ??
                }

                // SHEAR FAILURE

                if (this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[iContactForce] == 0)
                {
                    double ShearForceMax = RT_base + LocalContactForce[2] * Friction ;  // MOHR COULOMB MODEL.

                    if(LocalContactForce[2] < 0.0)
                    {

                        ShearForceMax = RT_base;

                    }

                    double ShearForceNow = sqrt(LocalContactForce[0] * LocalContactForce[0]
                                         +      LocalContactForce[1] * LocalContactForce[1]);  //M: combinació de les dues direccions tangencials.

                    //No cohesion or friction, no shear resistance

                    if(ShearForceMax == 0.0)
                    {
                        LocalContactForce[0] = 0.0;
                        LocalContactForce[1] = 0.0;
                    }

                    else if(ShearForceNow > ShearForceMax)     // the actual shear force is actualized to the maximum one, never over; also decomposed in the same directions.
                    {
                        LocalContactForce[0] = ShearForceMax / ShearForceNow * LocalContactForce[0];
                        LocalContactForce[1] = ShearForceMax / ShearForceNow * LocalContactForce[1];

                        //mContactFailureId = 4; // Shear failure case.
                       this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[iContactForce] = 4;
                       
                        //M: podria ficar que ara la cohesion = dinamic cohesion, not static... ??
                    }
                }

          // VISCODAMPING (applyied locally)

                    //*** the compbrobation is component-wise since localContactForce and RelVel have in principle no relationship.
                    // the visco force can be higher than the contact force only if they go to the same direction. (in my opinion)
                    // but in oposite direction the visco damping can't overpass the force...

		
	     if ( (damp_id == 2 || damp_id == 3 ) && ( (indentation > 0.0) || (this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[iContactForce] == 0) ) )

             {

      
                    double OldLocalContactForce[3]  = {0.0}; //M.
                        
                        OldLocalContactForce[2] = LocalContactForce[2];
                    
                        LocalContactForce[2] += - equiv_visco_damp_coeff * LocalRelVel[2];
                        
                        if(LocalContactForce[2]*OldLocalContactForce[2]<0){LocalContactForce[2]=0.0;} //the contact force can not change the direction due to the visco damp.
                        
                        if ( fabs(LocalContactForce[0] + ks * LocalDeltDisp[0]) < 1e-12 ) {
                        
                            for (unsigned int index = 0; index < 2; index++)
                            {
                               OldLocalContactForce[index] = LocalContactForce[index];

                               LocalContactForce[index] += - equiv_visco_damp_coeff * LocalRelVel[index];

                               if(LocalContactForce[index]*OldLocalContactForce[index]<0){LocalContactForce[index]=0.0;}
                            }
                        }
                        else {
                        
                            for (unsigned int index = 0; index < 2; index++)
                            {
                               OldLocalContactForce[index] = LocalContactForce[index];

                               LocalContactForce[index] += - equiv_visco_damp_coeff * LocalDeltRelVel[index];

                               if(LocalContactForce[index]*OldLocalContactForce[index]<0){LocalContactForce[index]=0.0;}
                            }
                        }
                }

             


                // TRANSFORMING TO GLOBAL FORCES AND ADDING UP

                    GeometryFunctions::VectorLocal2Global(LocalCoordSystem, LocalContactForce, GlobalContactForce);

                    force[0] += GlobalContactForce[0];
                     if(this->Id()==2){             KRATOS_WATCH(force[1])}
                    force[1] += GlobalContactForce[1];
                     if(this->Id()==2){             KRATOS_WATCH(force[1])}
                    force[2] += GlobalContactForce[2];

                    

                // SAVING FOR NEXT STEPS

                    this->GetValue(PARTICLE_CONTACT_FORCES)[iContactForce][0] = GlobalContactForce[0];
                    this->GetValue(PARTICLE_CONTACT_FORCES)[iContactForce][1] = GlobalContactForce[1];
                    this->GetValue(PARTICLE_CONTACT_FORCES)[iContactForce][2] = GlobalContactForce[2];

                    if ( rotation_OPTION == 1 )
                    {

                 ////global moment return back,for the ball self

                    double MA[3] = {0.0};
                    GeometryFunctions::CrossProduct(LocalCoordSystem[2], GlobalContactForce, MA);
                    mRota_Moment[0] -= MA[0] * radius;
                    mRota_Moment[1] -= MA[1] * radius;
                    mRota_Moment[2] -= MA[2] * radius;

                    }

                    iContactForce++;

            }//for each neaighbour

            KRATOS_CATCH("")

        }//ComputeParticleContactForce


       void SphericParticle::ApplyLocalForcesDamping(const ProcessInfo& rCurrentProcessInfo )

       {

          KRATOS_TRY
          array_1d<double,3>& force = this->GetGeometry()[0].GetSolutionStepValue(RHS);
          double LocalDampRatio     = this->GetGeometry()[0].GetSolutionStepValue(PARTICLE_LOCAL_DAMP_RATIO);

              // LOCAL DAMPING OPTION FOR THE UNBALANCED FORCES (IN GLOBAL CORDINATES).
             
                for (int iDof = 0; iDof < 3; iDof++)
                {
                   
                    force[iDof] = (1 - LocalDampRatio) * force[iDof];
                    
                }
           
            KRATOS_CATCH("")

      } //ApplyLocalForcesDamping

       void SphericParticle::ApplyLocalMomentsDamping(const ProcessInfo& rCurrentProcessInfo )

       {

       KRATOS_TRY
       // int damp_id                         = rCurrentProcessInfo[DAMP_TYPE];  //M: revisable....en principi akest era per visco o local de forces no per moment.

        array_1d<double, 3 > & RotaMoment       = this->GetGeometry()[0].GetSolutionStepValue(PARTICLE_MOMENT);
        double LocalDampRatio                   = this->GetGeometry()[0].GetSolutionStepValue(PARTICLE_LOCAL_DAMP_RATIO);

        // LOCAL DAMPING OPTION FOR THE UNBALANCED FORCES (IN GLOBAL CORDINATES).


        for (int iDof = 0; iDof < 3; iDof++)
        {
            if (this->GetGeometry()(0)->GetSolutionStepValue(ANGULAR_VELOCITY)[iDof] > 0.0)
            {
                 RotaMoment[iDof] = RotaMoment[iDof] - LocalDampRatio * fabs(RotaMoment[iDof]);

            }
            else
            {
                 RotaMoment[iDof] = RotaMoment[iDof] + LocalDampRatio * fabs(RotaMoment[iDof]);
            }
        }

    KRATOS_CATCH("")

    } //ApplyLocalMomentsDamping


       void SphericParticle::CharacteristicParticleFailureId(const ProcessInfo& rCurrentProcessInfo )

       {  

       KRATOS_TRY

       // SETTING THE CARACHTERISTIC FAILURE TYPE OF THE PARTICLE (THE DOMINANT ONE) FOR VISUALITZATION.

            /* ContactFailureId = 2 (partially detached) it's never considerer in a contact, but it can be a desired output on the visualitzation.
             *
             * If the particle has no neighbour, but it is not from ContinuumGroup = 0 its becouse it has lost all the neighbours,
             * we are not interested in its global failure type but in its neighbours failure type. See: //// DETECTING A COHESIVE PARTICLE THAT HAS BEEN COMPLETELY DETACHED. in AfterForceCalculation.
             *
             * If one of the failure types completely dominates over the others this is the FailureId choosen for the particle
             *
             * If its partially detached by some type(s) of failure but the dominant contact state is "still atached", so failureId =0, we chose FailureId = 2.
             *
             * If the particle is not simulating the continuum, the failure type is 1 (default set from the particle whose ContinuumGroup is 0); It won't be printed as output.
             *
             */

            /*
             *   *mpFailureId values:
             *      0 := all neighbours attached
             *      1 := General detachment (all neighbours lost or no initial continuum case)
             *      2 := Partially detached and no dominance
             *      3 := tensile dominating on the contact detachment
             *      4 := shear dominating on the contact detachment
             */






            int tempType[5] = {0,0,0,0,0};




            if (*mpFailureId != 1)  // for *mpFailureId == 1 there's no failure to represent, the particle is not a continuum-simulating one or has been completelly detached already.
            {
                
                ParticleWeakVectorType& r_neighbours             = this->GetValue(NEIGHBOUR_ELEMENTS);

                

                unsigned int itype = 0;

                for(ParticleWeakIteratorType neighbour_iterator = r_neighbours.begin();  //loop over neighbours, just to run the index.
                    neighbour_iterator != r_neighbours.end(); neighbour_iterator++)
                {

                    //if( int(this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[itype]) == 0)
                    if( this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[itype] == 0)
                    {
                        tempType[0]++;
                    }
                    else if( this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[itype] == 1)
                    {
                        tempType[1]++;
                    }

                    // mContactFailureId == 2 intentionally skipped!

                    else if( this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[itype] == 3)
                    {
                        tempType[3]++;
                    }
                    else if( this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[itype] == 4)
                    {
                        tempType[4]++;
                    }

                    itype++;

                }

                if ( tempType[0] == 0)  //no neighbour is attached
                {

                     *mpFailureId = 1;

                }   // no one neighbour is attached (but maybe still contacting).

                else if( (tempType[3] > tempType[4]) ) //some neighbour attached but failure 3 dominates over 4.
                {
                    *mpFailureId = 3;
                }

                else if( (tempType[4] > tempType[3]) ) // the same but 4 dominates over 3.
                {
                    *mpFailureId = 4;
                }
                else if ( (tempType[4] > 0) || (tempType[3] > 0) ) // no 3 neither 4 dominates but one of them may exist.
                {

                   *mpFailureId = 2;  // Partially detached / mix case.
                }
                else
                {

                   *mpFailureId = 0;  // last option: no one detached.
                }

            }// if (*mpFailureId != 1)

      /*
            if(this->GetGeometry()(0)->Id()==1890)

            {

                if(rCurrentProcessInfo[TIME_STEPS]>4950)
                {

                   ParticleWeakVectorType& r_neighbours             = this->GetValue(NEIGHBOUR_ELEMENTS);

                   unsigned int itype = 0;

                   KRATOS_WATCH("VEINS AL PAS DE TEMPS ")
                   KRATOS_WATCH(rCurrentProcessInfo[TIME_STEPS])

                    for(ParticleWeakIteratorType neighbour_iterator = r_neighbours.begin();  //loop over neighbours, just to run the index.
                        neighbour_iterator != r_neighbours.end(); neighbour_iterator++)
                    {

                        KRATOS_WATCH(this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[itype])
                        //KRATOS_WATCH(this->GetValue(PARTICLE_CONTACT_FAILURE_ID)[itype])
                        itype++;

                    }

                    KRATOS_WATCH("tipus acumulats ")

                   for(int aa = 0; aa != 5; aa++)
                   {

                    KRATOS_WATCH(tempType[aa])
                   }

                    KRATOS_WATCH(*mpFailureId)

                    KRATOS_WATCH(rCurrentProcessInfo[TIME_STEPS])

                    


                }


            }
       
      //this->GetValue(PARTICLE_FAILURE_ID)=*mpFailureId ;

       
       //testing
       if (*mpFailureId != 0.0)
            {
            KRATOS_WATCH(*mpFailureId)
            KRATOS_WATCH(this->GetValue(PARTICLE_FAILURE_ID))
            }
        */
      

            KRATOS_CATCH("")

    } //CharacteristicParticleFailureId


       void SphericParticle::ComputeParticleRotationSpring(const ProcessInfo& rCurrentProcessInfo)
       {
        //double dt                           = rCurrentProcessInfo[DELTA_TIME]; //C.F.: neew
        /*
                    c=objecte_contacte(particula,vei)

            força=(c.RADI)*3;  //M: idea: to create a class contact, create objects of contacts with all the paramaters. easier...

          */

        double Tension        = this->GetGeometry()[0].GetSolutionStepValue(PARTICLE_TENSION);
        double Cohesion       = this->GetGeometry()[0].GetSolutionStepValue(PARTICLE_COHESION);
        double young          = this->GetGeometry()[0].GetSolutionStepValue(YOUNG_MODULUS);
        double poisson        = this->GetGeometry()[0].GetSolutionStepValue(POISSON_RATIO);
        double radius         = this->GetGeometry()[0].GetSolutionStepValue(RADIUS);
        double inertia        = this->GetGeometry()[0].GetSolutionStepValue(PARTICLE_INERTIA);

        array_1d<double, 3 > & mRota_Moment = GetGeometry()(0)->FastGetSolutionStepValue(PARTICLE_MOMENT);

        ParticleWeakVectorType& rE             = this->GetValue(NEIGHBOUR_ELEMENTS);

        Vector & mRotaSpringFailureType  = this->GetValue(PARTICLE_ROTATE_SPRING_FAILURE_TYPE);

        size_t iContactForce = 0;

        for(ParticleWeakIteratorType ineighbour = rE.begin(); ineighbour != rE.end(); ineighbour++)
        {

            //if(mIfInitalContact[iContactForce] == 1 && mRotaSpringFailureType[iContactForce] == 0) ///M.S:NEWWWW, IF THE SPRING BRAKES... NO MORE CONTRIBUION.
            //if( mRotaSpringFailureType[iContactForce] == 0) //M.S: CAL FICAR A INITIALIZE QUE SIGUI 1 I DESPRES INITIAL CONTACTS POSAR 0 SI NECESITEN, IGUAL QUE FAILURE NORMAL.
            //mmm.. what about the other failure types? if a contact is broken due to shear or tensile, it cant be a bending
            {

                array_1d<double, 3 > & mRotaSpringMoment  = this->GetValue(PARTICLE_ROTATE_SPRING_MOMENT)[ iContactForce ];

                double other_radius    = ineighbour->GetGeometry()(0)->FastGetSolutionStepValue(RADIUS);
                double other_young     = ineighbour->GetGeometry()[0].GetSolutionStepValue(YOUNG_MODULUS);
                double other_poisson   = ineighbour->GetGeometry()[0].GetSolutionStepValue(POISSON_RATIO);
                double other_tension   = ineighbour->GetGeometry()[0].GetSolutionStepValue(PARTICLE_TENSION);
                double other_cohesion  = ineighbour->GetGeometry()[0].GetSolutionStepValue(PARTICLE_COHESION);
                double other_inertia   = ineighbour->GetGeometry()(0)->FastGetSolutionStepValue(PARTICLE_INERTIA);

                Tension  = (Tension  + other_tension ) * 0.5;
                Cohesion = (Cohesion + other_cohesion) * 0.5;

                double equiv_radius     = (radius + other_radius) * 0.5 ;
                double equiv_area       = M_PI * equiv_radius * equiv_radius;
                double equiv_poisson    = (poisson + other_poisson) * 0.5 ;
                double equiv_young      = (young  + other_young)  * 0.5;

                double kn               = equiv_young * equiv_area / (2.0 * equiv_radius);
                double ks               = kn / (2.0 * (1.0 + equiv_poisson));

                array_1d<double,3> other_to_me_vect = GetGeometry()(0)->Coordinates() - ineighbour->GetGeometry()(0)->Coordinates();

               /////Cfeng: Forming the Local Contact Coordinate system
                double NormalDir[3]           = {0.0};
                double LocalCoordSystem[3][3] = {{0.0}, {0.0}, {0.0}};
                NormalDir[0] = other_to_me_vect[0];
                NormalDir[1] = other_to_me_vect[1];
                NormalDir[2] = other_to_me_vect[2];
                GeometryFunctions::ComputeContactLocalCoordSystem(NormalDir, LocalCoordSystem);

                double LocalRotaSpringMoment[3]     = {0.0};
                double GlobalRotaSpringMoment[3]    = {0.0};
                double GlobalRotaSpringMomentOld[3] = {0.0};

                double DeltRotaDisp[3] = {0.0};
                //double DeltRotaDisp2[3] = {0.0};

                double LocalDeltRotaDisp[3] = {0.0};

                double TargetDeltRotaDist[3] = {0.0};
                double NeighbourDeltRotaDist[3] = {0.0};
                
                for (int i=0;i<3;i++)
                {
                
                    TargetDeltRotaDist[i] = this->GetGeometry()(0)->FastGetSolutionStepValue(DELTA_ROTA_DISPLACEMENT)[i];
                    NeighbourDeltRotaDist[i] = ineighbour->GetGeometry()(0)->FastGetSolutionStepValue(DELTA_ROTA_DISPLACEMENT)[i];
                    DeltRotaDisp[i] =  - ( TargetDeltRotaDist[i] - NeighbourDeltRotaDist[i] );
                
                }
              
                GeometryFunctions::VectorGlobal2Local(LocalCoordSystem, DeltRotaDisp, LocalDeltRotaDisp);

                GlobalRotaSpringMomentOld[0] = mRotaSpringMoment[ 0 ];

                GlobalRotaSpringMomentOld[1] = mRotaSpringMoment[ 1 ];

                GlobalRotaSpringMomentOld[2] = mRotaSpringMoment[ 2 ];

                GeometryFunctions::VectorGlobal2Local(LocalCoordSystem, GlobalRotaSpringMomentOld, LocalRotaSpringMoment);


                double Inertia_I = (inertia + other_inertia) * 0.5;

                double Inertia_J = Inertia_I * 2.0;


                LocalRotaSpringMoment[0] +=  - Inertia_I * LocalDeltRotaDisp[0] * kn / equiv_area;

                LocalRotaSpringMoment[1] +=  - Inertia_I * LocalDeltRotaDisp[1] * kn / equiv_area;

                LocalRotaSpringMoment[2] +=  - Inertia_J * LocalDeltRotaDisp[2] * ks / equiv_area;


                ////Judge if the rotate spring is broken or not
                double GlobalContactForce[3]  = {0.0};
                double LocalContactForce [3]  = {0.0};

                GlobalContactForce[0] = this->GetValue(PARTICLE_CONTACT_FORCES)[ iContactForce ][ 0 ];
                GlobalContactForce[1] = this->GetValue(PARTICLE_CONTACT_FORCES)[ iContactForce ][ 1 ];
                GlobalContactForce[2] = this->GetValue(PARTICLE_CONTACT_FORCES)[ iContactForce ][ 2 ]; //GlobalContactForce[2] = mContactForces[3 * iContactForce  + 2 ];
                GeometryFunctions::VectorGlobal2Local(LocalCoordSystem, GlobalContactForce, LocalContactForce);

                double ForceN  = LocalContactForce[2];
                double ForceS  = sqrt( LocalContactForce[0] * LocalContactForce[0] + LocalContactForce[1] * LocalContactForce[1]);
                double MomentS = sqrt(LocalRotaSpringMoment[0] * LocalRotaSpringMoment[0] + LocalRotaSpringMoment[1] * LocalRotaSpringMoment[1]);
                double MomentN = LocalRotaSpringMoment[2];

                //////bending stress and axial stress add together, use edge of the bar will failure first
                double TensiMax = -ForceN / equiv_area + MomentS        / Inertia_I * equiv_radius;
                double ShearMax = ForceS  / equiv_area + fabs(MomentN)  / Inertia_J * equiv_radius;

                if(TensiMax > Tension || ShearMax > Cohesion)
                {
                    mRotaSpringFailureType[iContactForce] = 1;


                    LocalRotaSpringMoment[0] = 0.0;
                    LocalRotaSpringMoment[1] = 0.0;
                    LocalRotaSpringMoment[2] = 0.0;
                }

                GeometryFunctions::VectorLocal2Global(LocalCoordSystem, LocalRotaSpringMoment, GlobalRotaSpringMoment);



                mRotaSpringMoment[ 0 ] = GlobalRotaSpringMoment[0];
                mRotaSpringMoment[ 1 ] = GlobalRotaSpringMoment[1];
                mRotaSpringMoment[ 2 ] = GlobalRotaSpringMoment[2];

                ////feedback, contact moment----induce by rotation spring
                mRota_Moment[0] -= GlobalRotaSpringMoment[0];
                mRota_Moment[1] -= GlobalRotaSpringMoment[1];
                mRota_Moment[2] -= GlobalRotaSpringMoment[2];
            }

            iContactForce++;
            }


        }//ComputeParticleRotationSpring

void SphericParticle::CalculateInitialLocalAxes(const ProcessInfo& rCurrentProcessInfo )

        {
            KRATOS_WATCH("INITIALIZE_AXES")

            //1. Create the local axes (points)

            array_1d<double,3> CentrePoint = this->GetGeometry()(0)->Coordinates();
           
            this->GetValue(ARROW_POINT) = vector< array_1d<double,3> >();
            this->GetValue(ARROW_POINT).resize(3);
            vector< array_1d<double,3> >& TargetPointVector = this->GetValue(ARROW_POINT);
   
            TargetPointVector[0]=CentrePoint;
            TargetPointVector[1]=CentrePoint;
            TargetPointVector[2]=CentrePoint;
         
            TargetPointVector[0][0] += 1.0;
            TargetPointVector[1][1] += 1.0;
            TargetPointVector[2][2] += 1.0;

            KRATOS_WATCH(TargetPointVector)

         }

        void SphericParticle::CalculateLocalAxes(const ProcessInfo& rCurrentProcessInfo )
        {

            //1. rotate the local axes

            array_1d<double,3>  CentrePoint = this->GetGeometry()(0)->Coordinates();

            array_1d<double,3> LineVector = this->GetGeometry()(0)->FastGetSolutionStepValue(DELTA_ROTA_DISPLACEMENT);

            
            //KRATOS_WATCH(LineVector)
 
            double RotationAngle;
            
            GeometryFunctions::norm(LineVector,RotationAngle);

           
            //KRATOS_WATCH(LineVector)
            // KRATOS_WATCH(RotationAngle)

            // KRATOS_WATCH(rCurrentProcessInfo[TIME_STEPS])
            
            //vector<array_1d<double,3> >& TargetPointVector = this->GetValue(ARROW_POINT);
  
             
            for (int e = 0; e<3; e++)
            {

                array_1d<double,3>& TargetPoint = this->GetValue(ARROW_POINT)[e];

               GeometryFunctions::RotatePointAboutArbitraryLine( TargetPoint, CentrePoint, LineVector, RotationAngle);

            }
        
            //2. calculate the Euler angles from the rotation

            array_1d<double,3>  OriginalVector_X  = ZeroVector(3);
            OriginalVector_X[0] = 1.0;
            OriginalVector_X[1] = 0.0;
            OriginalVector_X[2] = 0.0;

            array_1d<double,3>  OriginalVector_Z  = ZeroVector(3);
            OriginalVector_Z[0] = 0.0;
            OriginalVector_Z[1] = 0.0;
            OriginalVector_Z[2] = 1.0;

            array_1d<double,3>  RotatedVector_X   = this->GetValue(ARROW_POINT)[0] - CentrePoint;
            array_1d<double,3>  RotatedVector_Z   = this->GetValue(ARROW_POINT)[2] - CentrePoint;
            array_1d<double,3>& EulerAngles       = this->GetGeometry()(0)->GetSolutionStepValue(EULER_ANGLES);
            
            array_1d<double,3> Eu = ZeroVector(3);
            Eu[0]=EulerAngles[0]-1.57080e+00;
            Eu[1]=EulerAngles[1]-0.0;
            Eu[2]=EulerAngles[2]-1.57080e+00;
            
           // KRATOS_WATCH(Eu)
/*
            KRATOS_WATCH(OriginalVector_X)
             KRATOS_WATCH(RotatedVector_X)
             KRATOS_WATCH(OriginalVector_Z)
             KRATOS_WATCH(RotatedVector_Z)
*/
            GeometryFunctions::CalculateEulerAngles(OriginalVector_X, OriginalVector_Z, RotatedVector_X, RotatedVector_Z, EulerAngles );        

       }

       void SphericParticle::DampMatrix(MatrixType& rDampMatrix, ProcessInfo& rCurrentProcessInfo){}

       void SphericParticle::GetDofList(DofsVectorType& ElementalDofList, ProcessInfo& CurrentProcessInfo)

       {

            ElementalDofList.resize( 0 );

            for ( unsigned int i = 0; i < GetGeometry().size(); i++ )
            {
                ElementalDofList.push_back( GetGeometry()[i].pGetDof( DISPLACEMENT_X ) );
                ElementalDofList.push_back( GetGeometry()[i].pGetDof( DISPLACEMENT_Y ) );

                if ( GetGeometry().WorkingSpaceDimension() == 3 )
                {
                    ElementalDofList.push_back( GetGeometry()[i].pGetDof( DISPLACEMENT_Z ) );
                }
            }
        }

       void SphericParticle::InitializeSolutionStep(ProcessInfo& rCurrentProcessInfo)

       {

          int case_opt         = rCurrentProcessInfo[CASE_OPTION];
          int mSwitch          = rCurrentProcessInfo[DUMMY_SWITCH];

          if( (mSwitch==0) && (case_opt!=0) )
          {
                SetInitialContacts(case_opt);  //si finalment nomes has de fer aixo el switch el pots ficar a la strategia i testalvies que i entrem cada cop a comprobar.
          }

          array_1d<double,3>& force           = this->GetGeometry()[0].GetSolutionStepValue(RHS);//total forces, we reset to 0. and we calculate again.
          noalias(force)                      = ZeroVector(3);



        }
       void SphericParticle::FinalizeSolutionStep(ProcessInfo& rCurrentProcessInfo)
       
       {

           this->GetGeometry()[0].FastGetSolutionStepValue(EXPORT_PARTICLE_FAILURE_ID) = double(this->GetValue(PARTICLE_FAILURE_ID));
           // the elemental variable is copied to a nodal variable in order to export the results onto GiD Post.
       }

       void SphericParticle::Calculate(const Variable<double>& rVariable, double& Output, const ProcessInfo& rCurrentProcessInfo)

       {

           //KRATOS_WATCH(rVariable)

            if (rVariable == DELTA_TIME)
            {
                double E = this->GetGeometry()(0)->FastGetSolutionStepValue(YOUNG_MODULUS);
                double K = E * M_PI * this->GetGeometry()(0)->FastGetSolutionStepValue(RADIUS);
                Output = 0.34 * sqrt( mRealMass / K);

                if(rCurrentProcessInfo[ROTATION_OPTION] == 1)
                {
                    Output = Output * 0.5; //factor for critical time step when rotation is allowed.
                }
            } //CRITICAL DELTA CALCULATION

            if (rVariable == PARTICLE_LOCAL_DAMP_RATIO)
            {
                int damp_id             = rCurrentProcessInfo[DAMP_TYPE];
                int rotation_OPTION     = rCurrentProcessInfo[ROTATION_OPTION];

                if (damp_id == 1 || damp_id == 3 )
                {
                   ApplyLocalForcesDamping( rCurrentProcessInfo );

                   if ( rotation_OPTION != 0 && (damp_id !=4) ) //M: maybe a new damping option should be implemented to choose independently damping on rotation
                   {
                       ApplyLocalMomentsDamping( rCurrentProcessInfo );
                   }
                }
            } //DAMPING

             if (rVariable == DUMMY_LOCAL_AXES) //M.S: CANVIAR!!

            {
                CalculateInitialLocalAxes( rCurrentProcessInfo );

            } //EULER_ANGLES

            if (rVariable == PRESSURE) //M.S: CANVIAR!!

            {               
                CalculateLocalAxes( rCurrentProcessInfo );

            } //EULER_ANGLES



        }//calculate


       void SphericParticle::Calculate(const Variable<array_1d<double, 3 > >& rVariable, array_1d<double, 3 > & Output, const ProcessInfo& rCurrentProcessInfo){}
       void SphericParticle::Calculate(const Variable<Vector >& rVariable, Vector& Output, const ProcessInfo& rCurrentProcessInfo){}
       void SphericParticle::Calculate(const Variable<Matrix >& rVariable, Matrix& Output, const ProcessInfo& rCurrentProcessInfo){}

}  // namespace Kratos.
