/*
==============================================================================
KratosOpenCLApplication
A library based on:
Kratos
A General Purpose Software for Multi-Physics Finite Element Analysis
Version 1.0 (Released on march 05, 2007).

Copyright 2007
Pooyan Dadvand, Riccardo Rossi, Farshid Mossaiby
pooyan@cimne.upc.edu
rrossi@cimne.upc.edu
mossaiby@yahoo.com
- CIMNE (International Center for Numerical Methods in Engineering),
Gran Capita' s/n, 08034 Barcelona, Spain


Permission is hereby granted, free  of charge, to any person obtaining
a  copy  of this  software  and  associated  documentation files  (the
"Software"), to  deal in  the Software without  restriction, including
without limitation  the rights to  use, copy, modify,  merge, publish,
distribute,  sublicense and/or  sell copies  of the  Software,  and to
permit persons to whom the Software  is furnished to do so, subject to
the following condition:

Distribution of this code for  any  commercial purpose  is permissible
ONLY BY DIRECT ARRANGEMENT WITH THE COPYRIGHT OWNERS.

The  above  copyright  notice  and  this permission  notice  shall  be
included in all copies or substantial portions of the Software.

THE  SOFTWARE IS  PROVIDED  "AS  IS", WITHOUT  WARRANTY  OF ANY  KIND,
EXPRESS OR  IMPLIED, INCLUDING  BUT NOT LIMITED  TO THE  WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT  SHALL THE AUTHORS OR COPYRIGHT HOLDERS  BE LIABLE FOR ANY
CLAIM, DAMAGES OR  OTHER LIABILITY, WHETHER IN AN  ACTION OF CONTRACT,
TORT  OR OTHERWISE, ARISING  FROM, OUT  OF OR  IN CONNECTION  WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

==============================================================================
*/

//
//   Project Name:        Kratos
//   Last Modified by:    $Author: mossaiby $
//   Date:                $Date: 2011-02-27 13:42:51 $
//   Revision:            $Revision: 1.00 $
//
//

//
// opencl_fluid_solver.cl
//
// OpenCL kernels and functions used in opencl_fluid_solver.h


#include "opencl_edge_data_common.cl"


//
// AddVectorInplace
//
// Adds Vec2 to Vec1, putting the result in Vec1

__kernel void AddVectorInplace(__global ValueType *Vec1, __global ValueType *Vec2, const IndexType n)
{
	// Get work item index
	const size_t i = get_global_id(0);

	// Check if we are in the range
	if (i < n)
	{
		Vec1[i] += Vec2[i];
	}
}

//
// SubVectorInplace
//
// Subtracts Vec2 from Vec1, putting the result in Vec1

__kernel void SubVectorInplace(__global ValueType *Vec1, __global ValueType *Vec2, const IndexType n)
{
	// Get work item index
	const size_t i = get_global_id(0);

	// Check if we are in the range
	if (i < n)
	{
		Vec1[i] -= Vec2[i];
	}
}

//
// SolveStep1_1
//
// Part of SolveStep1

__kernel void SolveStep1_1(__global ValueType *mHavg, __global VectorType *mvel_n1, __global VectorType *mTauPressure, __global VectorType *mTauConvection, __global VectorType *mTau2, double mViscosity, double time_inv_avg, double mstabdt_pressure_factor, double mstabdt_convection_factor, double mtau2_factor, const IndexType n_nodes)
{
	// Get work item index
	const size_t i_node = get_global_id(0);

	// Check if we are in the range
	if (i_node < n_nodes)
	{
		double h_avg_i = mHavg[i_node];
		double vel_norm = KRATOS_OCL_LENGTH3(mvel_n1[i_node]);

		mTauPressure[i_node] = 1.00 / (2.00 * vel_norm / h_avg_i + mstabdt_pressure_factor * time_inv_avg + (4.00 * mViscosity) / (h_avg_i * h_avg_i));
		mTauConvection[i_node] = 1.00 / (2.00 * vel_norm / h_avg_i + mstabdt_convection_factor * time_inv_avg + (4.00 * mViscosity) / (h_avg_i * h_avg_i));
		mTau2[i_node] = (mViscosity + h_avg_i * vel_norm * 0.5) * mtau2_factor;
	}
}

//
// SolveStep1_2
//
// Part of SolveStep1

__kernel void SolveStep1_2(__global VectorType *mPi, __global VectorType *mvel_n1, __global IndexType *RowStartIndex, __global IndexType *ColumnIndex, __read_only image2d_t EdgeValues, __global ValueType *InvertedMass, const IndexType n_nodes, __local IndexType *Bounds)
{
	// Get work item index
	const size_t i_node = get_global_id(0);
	const size_t i_thread = get_local_id(0);

	// Reading for loop bounds

	if (i_thread == 0)
	{
		Bounds[0] = RowStartIndex[i_node];
	}

	if (i_node < n_nodes)
	{
		Bounds[i_thread + 1] = RowStartIndex[i_node + 1];
	}

	barrier(CLK_LOCAL_MEM_FENCE);

	// Check if we are in the range
	if (i_node < n_nodes)
	{
		VectorType Temp_Pi_i_node = 0.00;

		VectorType a_i = mvel_n1[i_node];

		for (IndexType csr_index = Bounds[i_thread]; csr_index != Bounds[i_thread + 1]; csr_index++)
		{
			IndexType j_neighbour = ColumnIndex[csr_index];
		    VectorType a_j = mvel_n1[j_neighbour];

			EdgeType CurrentEdge = ReadDouble16FromDouble16Image(EdgeValues, csr_index);
			VectorType Ni_DNj = KRATOS_OCL_VECTOR3(KRATOS_OCL_NI_DNJ_0(CurrentEdge), KRATOS_OCL_NI_DNJ_1(CurrentEdge), KRATOS_OCL_NI_DNJ_2(CurrentEdge));

		    Add_ConvectiveContribution(Ni_DNj, &Temp_Pi_i_node, a_i, a_i, a_j);  // U_i = a_i, U_j = a_j
		}

		mPi[i_node] = InvertedMass[i_node] * Temp_Pi_i_node;
	}
}

//
// CalculateRHS
//
// Part of CalculateRHS
// Note: Will replace double3 with 3 doubles if problem occures

__kernel void CalculateRHS(__global VectorType *mPi, __global VectorType *vel_buffer, __global IndexType *RowStartIndex, __global IndexType *ColumnIndex, __read_only image2d_t EdgeValues, __global ValueType *LumpedMass, __global VectorType *convective_velocity, __global ValueType *pressure, __global VectorType *rhs_buffer, __global ValueType *mTauConvection, double3 mBodyForce, double inverse_rho, double mViscosity, const IndexType n_nodes, __local IndexType *Bounds)
{
	// Get work item index
	const size_t i_node = get_global_id(0);
	const size_t i_thread = get_local_id(0);

	// Reading for loop bounds

	if (i_thread == 0)
	{
		Bounds[0] = RowStartIndex[i_node];
	}

	if (i_node < n_nodes)
	{
		Bounds[i_thread + 1] = RowStartIndex[i_node + 1];
	}

	barrier(CLK_LOCAL_MEM_FENCE);

	// Check if we are in the range
	if (i_node < n_nodes)
	{
		VectorType Temp_rhs_i_node = LumpedMass[i_node] * mBodyForce;

		VectorType a_i = convective_velocity[i_node];
		VectorType U_i = vel_buffer[i_node];
		VectorType pi_i = mPi[i_node];
		ValueType p_i = pressure[i_node];
		ValueType edge_tau = mTauConvection[i_node];

		// Convective term
		for (IndexType csr_index = Bounds[i_thread]; csr_index != Bounds[i_thread + 1]; csr_index++)
		{
			IndexType j_neighbour = ColumnIndex[csr_index];

			VectorType U_j = vel_buffer[j_neighbour];
			VectorType pi_j = mPi[j_neighbour];
			ValueType p_j = pressure[j_neighbour];

			EdgeType CurrentEdge = ReadDouble16FromDouble16Image(EdgeValues, csr_index);
			VectorType Ni_DNj = KRATOS_OCL_VECTOR3(KRATOS_OCL_NI_DNJ_0(CurrentEdge), KRATOS_OCL_NI_DNJ_1(CurrentEdge), KRATOS_OCL_NI_DNJ_2(CurrentEdge));

			Sub_ConvectiveContribution(Ni_DNj, &Temp_rhs_i_node, a_i, U_i, U_j);
			Sub_grad_p(Ni_DNj, &Temp_rhs_i_node, p_i * inverse_rho, p_j * inverse_rho);

			VectorType Lij0 = KRATOS_OCL_VECTOR3(KRATOS_OCL_LAPLACIANIJ_0_0(CurrentEdge), KRATOS_OCL_LAPLACIANIJ_0_1(CurrentEdge), KRATOS_OCL_LAPLACIANIJ_0_2(CurrentEdge));
			VectorType Lij1 = KRATOS_OCL_VECTOR3(KRATOS_OCL_LAPLACIANIJ_1_0(CurrentEdge), KRATOS_OCL_LAPLACIANIJ_1_1(CurrentEdge), KRATOS_OCL_LAPLACIANIJ_1_2(CurrentEdge));
			VectorType Lij2 = KRATOS_OCL_VECTOR3(KRATOS_OCL_LAPLACIANIJ_2_0(CurrentEdge), KRATOS_OCL_LAPLACIANIJ_2_1(CurrentEdge), KRATOS_OCL_LAPLACIANIJ_2_2(CurrentEdge));

			Sub_ViscousContribution(Lij0.x, Lij1.y, Lij2.z, &Temp_rhs_i_node, U_i, mViscosity, U_j, mViscosity);

			// Add stabilization
			VectorType stab_low;
			VectorType stab_high;

			CalculateConvectionStabilization_LOW(Lij0, Lij1, Lij2, &stab_low, a_i, U_i, U_j);
			CalculateConvectionStabilization_HIGH(Ni_DNj, &stab_high, a_i, pi_i, pi_j);  // TODO: Move this upward to use less registers!

			Sub_StabContribution(&Temp_rhs_i_node, edge_tau, 1.00, stab_low, stab_high);
		}

		rhs_buffer[i_node] = Temp_rhs_i_node;
	}
}

//
// SolveStep2_1
//
// Part of SolveStep2

__kernel void SolveStep2_1(__global VectorType *mvel_n1, __global VectorType *mXi, __global ValueType *mTauPressure, __global ValueType *mPn, __global ValueType *mPn1, __global IndexType *RowStartIndex, __global IndexType *ColumnIndex, __read_only image2d_t EdgeValues, __global ValueType *rhs_buffer, __global ValueType *mL_Values, ValueType mRho, ValueType delta_t, const IndexType n_nodes, __local IndexType *Bounds)
{
	// Get work item index
	const size_t i_node = get_global_id(0);
	const size_t i_thread = get_local_id(0);

	// Reading for loop bounds

	if (i_thread == 0)
	{
		Bounds[0] = RowStartIndex[i_node];
	}

	if (i_node < n_nodes)
	{
		Bounds[i_thread + 1] = RowStartIndex[i_node + 1];
	}

	barrier(CLK_LOCAL_MEM_FENCE);

	// Check if we are in the range
	if (i_node < n_nodes)
	{
		ValueType Temp_rhs_i_node = 0.00;

		ValueType p_i = mPn1[i_node];
		ValueType p_old_i = mPn[i_node];

		VectorType U_i_curr = mvel_n1[i_node];
		VectorType xi_i = mXi[i_node];

		ValueType l_ii = 0.00;

		// TODO: Get this flag dynamically from host if needed

#ifndef SYMM_PRESS

			ValueType edge_tau = mTauPressure[i_node];

#endif

		IndexType DiagonalIndex;

		// Loop over all neighbours
		for (IndexType csr_index = Bounds[i_thread]; csr_index != Bounds[i_thread + 1]; csr_index++)
		{
			IndexType j_neighbour = ColumnIndex[csr_index];

			// Remember the index of diagonal element to avoid a search
			if (j_neighbour == i_node)
			{
				DiagonalIndex = csr_index;
			}

			ValueType p_j = mPn1[j_neighbour];
			ValueType p_old_j = mPn[j_neighbour];

			VectorType U_j_curr = mvel_n1[j_neighbour];
			VectorType xi_j = mXi[j_neighbour];

			EdgeType CurrentEdge = ReadDouble16FromDouble16Image(EdgeValues, csr_index);
			VectorType Ni_DNj = KRATOS_OCL_VECTOR3(KRATOS_OCL_NI_DNJ_0(CurrentEdge), KRATOS_OCL_NI_DNJ_1(CurrentEdge), KRATOS_OCL_NI_DNJ_2(CurrentEdge));
			VectorType DNi_Nj = KRATOS_OCL_VECTOR3(KRATOS_OCL_DNI_NJ_0(CurrentEdge), KRATOS_OCL_DNI_NJ_1(CurrentEdge), KRATOS_OCL_DNI_NJ_2(CurrentEdge));

			VectorType Lij0 = KRATOS_OCL_VECTOR3(KRATOS_OCL_LAPLACIANIJ_0_0(CurrentEdge), KRATOS_OCL_LAPLACIANIJ_0_1(CurrentEdge), KRATOS_OCL_LAPLACIANIJ_0_2(CurrentEdge));
			VectorType Lij1 = KRATOS_OCL_VECTOR3(KRATOS_OCL_LAPLACIANIJ_1_0(CurrentEdge), KRATOS_OCL_LAPLACIANIJ_1_1(CurrentEdge), KRATOS_OCL_LAPLACIANIJ_1_2(CurrentEdge));
			VectorType Lij2 = KRATOS_OCL_VECTOR3(KRATOS_OCL_LAPLACIANIJ_2_0(CurrentEdge), KRATOS_OCL_LAPLACIANIJ_2_1(CurrentEdge), KRATOS_OCL_LAPLACIANIJ_2_2(CurrentEdge));

			// TODO: Get this flag dynamically from host if needed

#ifdef SYMM_PRESS

			ValueType edge_tau = 0.5 * (mTauPressure[i_node] + mTauPressure[j_neighbour]);

#endif

			// Compute laplacian operator
			ValueType sum_l_ikjk;
			CalculateScalarLaplacian(Lij0.x, Lij1.y, Lij2.z, &sum_l_ikjk);

			ValueType sum_l_ikjk_onlydt = sum_l_ikjk * (delta_t);
			sum_l_ikjk *= (delta_t + edge_tau);

			// Assemble right-hand side

			// Pressure contribution
			Temp_rhs_i_node -= sum_l_ikjk * (p_j - p_i);
			Temp_rhs_i_node += sum_l_ikjk_onlydt * (p_old_j - p_old_i);  // TODO: Optimize this a bit!

			// Calculating the divergence of the fract vel
			Sub_D_v(Ni_DNj, &Temp_rhs_i_node, U_i_curr * mRho, U_j_curr * mRho);

			// High order stabilizing term
			ValueType Temp = 0.00;

			Add_div_v(Ni_DNj, DNi_Nj, &Temp, xi_i, xi_j);

			Temp_rhs_i_node += edge_tau * Temp;

			// Assemble laplacian matrix
			mL_Values[csr_index] = sum_l_ikjk;  // TODO: Check this! I assume that the graph of mL is EXACTLY as mr_matrix_container!

			l_ii -= sum_l_ikjk;
		}

		mL_Values[DiagonalIndex] = l_ii;  // TODO: Check this! I assume that the graph of mL is EXACTLY as mr_matrix_container!

		rhs_buffer[i_node] = Temp_rhs_i_node;
	}
}

//
// SolveStep2_2
//
// Part of SolveStep2

__kernel void SolveStep2_2(__global VectorType *mXi, __global ValueType *mPn1, __global IndexType *RowStartIndex, __global IndexType *ColumnIndex, __read_only image2d_t EdgeValues, __global ValueType *InvertedMass, const IndexType n_nodes, __local IndexType *Bounds)
{
	// Get work item index
	const size_t i_node = get_global_id(0);
	const size_t i_thread = get_local_id(0);

	// Reading for loop bounds

	if (i_thread == 0)
	{
		Bounds[0] = RowStartIndex[i_node];
	}

	if (i_node < n_nodes)
	{
		Bounds[i_thread + 1] = RowStartIndex[i_node + 1];
	}

	barrier(CLK_LOCAL_MEM_FENCE);

	// Check if we are in the range
	if (i_node < n_nodes)
	{
		VectorType Temp_Xi_i_node = 0.00;
		ValueType p_i = mPn1[i_node];

		// Loop over all neighbours
		for (IndexType csr_index = Bounds[i_thread]; csr_index != Bounds[i_thread + 1]; csr_index++)
		{
			// Get global index of neighbouring node j
			IndexType j_neighbour = ColumnIndex[csr_index];
			ValueType p_j = mPn1[j_neighbour];

			// Projection of pressure gradients
			EdgeType CurrentEdge = ReadDouble16FromDouble16Image(EdgeValues, csr_index);
			VectorType Ni_DNj = KRATOS_OCL_VECTOR3(KRATOS_OCL_NI_DNJ_0(CurrentEdge), KRATOS_OCL_NI_DNJ_1(CurrentEdge), KRATOS_OCL_NI_DNJ_2(CurrentEdge));

			Add_grad_p(Ni_DNj, &Temp_Xi_i_node, p_i, p_j);
		}

		mXi[i_node] = Temp_Xi_i_node * InvertedMass[i_node];
	}
}

//
// SolveStep3_1
//
// Part of SolveStep3

__kernel void SolveStep3_1(__global VectorType *mvel_n1, __global ValueType *mPn, __global ValueType *mPn1, __global IndexType *RowStartIndex, __global IndexType *ColumnIndex, __read_only image2d_t EdgeValues, __global ValueType *InvertedMass, ValueType rho_inv, ValueType factor, ValueType delta_t, const IndexType n_nodes, __local IndexType *Bounds)
{
	// Get work item index
	const size_t i_node = get_global_id(0);
	const size_t i_thread = get_local_id(0);

	// Reading for loop bounds

	if (i_thread == 0)
	{
		Bounds[0] = RowStartIndex[i_node];
	}

	if (i_node < n_nodes)
	{
		Bounds[i_thread + 1] = RowStartIndex[i_node + 1];
	}

	barrier(CLK_LOCAL_MEM_FENCE);

	// Check if we are in the range
	if (i_node < n_nodes)
	{
		VectorType correction = 0.00;
		ValueType delta_p_i = (mPn1[i_node] - mPn[i_node]) * rho_inv * factor;

		// Compute edge contributions dt * M ^ (-1) Gp
		for (IndexType csr_index = Bounds[i_thread]; csr_index != Bounds[i_thread + 1]; csr_index++)
		{
			// Get global index of neighbouring node j
			IndexType j_neighbour = ColumnIndex[csr_index];
			ValueType delta_p_j = (mPn1[j_neighbour] - mPn[j_neighbour]) * rho_inv * factor;

			EdgeType CurrentEdge = ReadDouble16FromDouble16Image(EdgeValues, csr_index);
			VectorType Ni_DNj = KRATOS_OCL_VECTOR3(KRATOS_OCL_NI_DNJ_0(CurrentEdge), KRATOS_OCL_NI_DNJ_1(CurrentEdge), KRATOS_OCL_NI_DNJ_2(CurrentEdge));

			Sub_grad_p(Ni_DNj, &correction, delta_p_i,  delta_p_j);
		}

		// Correct fractional momentum
		mvel_n1[i_node] += delta_t * InvertedMass[i_node] * correction;
	}
}

//
// SolveStep3_2
//
// Part of SolveStep3

__kernel void SolveStep3_2(__global VectorType *mvel_n1, __global ValueType *mdiv_error, __global IndexType *RowStartIndex, __global IndexType *ColumnIndex, __read_only image2d_t EdgeValues, ValueType mRho, const IndexType n_nodes, __local IndexType *Bounds)
{
	// Get work item index
	const size_t i_node = get_global_id(0);
	const size_t i_thread = get_local_id(0);

	// Reading for loop bounds

	if (i_thread == 0)
	{
		Bounds[0] = RowStartIndex[i_node];
	}

	if (i_node < n_nodes)
	{
		Bounds[i_thread + 1] = RowStartIndex[i_node + 1];
	}

	barrier(CLK_LOCAL_MEM_FENCE);

	// Check if we are in the range
	if (i_node < n_nodes)
	{
		ValueType Temp_div_i_err = 0.00;
		VectorType U_i_curr = mvel_n1[i_node];

		// Compute edge contributions dt * M ^ (-1) Gp
		for (IndexType csr_index = Bounds[i_thread]; csr_index != Bounds[i_thread + 1]; csr_index++)
		{
			IndexType j_neighbour = ColumnIndex[csr_index];
			VectorType U_j_curr = mvel_n1[j_neighbour];

			EdgeType CurrentEdge = ReadDouble16FromDouble16Image(EdgeValues, csr_index);
			VectorType Ni_DNj = KRATOS_OCL_VECTOR3(KRATOS_OCL_NI_DNJ_0(CurrentEdge), KRATOS_OCL_NI_DNJ_1(CurrentEdge), KRATOS_OCL_NI_DNJ_2(CurrentEdge));

			Add_D_v(Ni_DNj, &Temp_div_i_err, U_i_curr * mRho, U_j_curr * mRho);
		}

		mdiv_error[i_node] = Temp_div_i_err;
	}
}

/*
	void ApplyVelocityBC(CalcVectorType& VelArray) {
	    KRATOS_TRY


	    if(mWallLawIsActive == false)
	    {
		//apply conditions on corner edges
		int edge_size = medge_nodes_direction.size();
		#pragma omp parallel for firstprivate(edge_size)
		for (int i = 0; i < edge_size; i++)
		{
		    int i_node = medge_nodes[i];
		    const array_1d<double, TDim>& direction = medge_nodes_direction[i];
			array_1d<double, TDim>& U_i = VelArray[i_node];
			double temp=0.0;
			for (unsigned int comp = 0; comp < TDim; comp++)
			    temp += U_i[comp] * direction[comp];

			for (unsigned int comp = 0; comp < TDim; comp++)
			    U_i[comp] = direction[comp]*temp;

		}

		//apply conditions on corners
		int corner_size = mcorner_nodes.size();
		for (int i = 0; i < corner_size; i++)
		{
		    int i_node = mcorner_nodes[i];

		    array_1d<double, TDim>& U_i = VelArray[i_node];
			for (unsigned int comp = 0; comp < TDim; comp++)
			    U_i[comp] = 0.0;
		}
	    }


	    //slip condition
	    int slip_size = mSlipBoundaryList.size();
	    #pragma omp parallel for firstprivate(slip_size)
	    for (int i_slip = 0; i_slip < slip_size; i_slip++)
	    {
		unsigned int i_node = mSlipBoundaryList[i_slip];
		    array_1d<double, TDim>& U_i = VelArray[i_node];
		    array_1d<double, TDim>& an_i = mSlipNormal[i_node];
		    double projection_length = 0.0;
		    double normalization = 0.0;
		    for (unsigned int comp = 0; comp < TDim; comp++) {
			projection_length += U_i[comp] * an_i[comp];
			normalization += an_i[comp] * an_i[comp];
		    }
		    projection_length /= normalization;
		    //tangential momentum as difference between original and normal momentum
		    for (unsigned int comp = 0; comp < TDim; comp++)
			U_i[comp] -= projection_length * an_i[comp];

	    }

	    //fixed condition
	    int fixed_size = mFixedVelocities.size();
	    #pragma omp parallel for firstprivate(fixed_size)
	    for (int i_velocity = 0; i_velocity < fixed_size; i_velocity++)
	    {
		unsigned int i_node = mFixedVelocities[i_velocity];

		    const array_1d<double, TDim>& u_i_fix = mFixedVelocitiesValues[i_velocity];
		    array_1d<double, TDim>& u_i = VelArray[i_node];

		    for (unsigned int comp = 0; comp < TDim; comp++)
			u_i[comp] = u_i_fix[comp];

	    }



	    KRATOS_CATCH("")
	}

*/

//
// ComputeWallResistance
//
// Part of ComputeWallResistance

__kernel void ComputeWallResistance(const IndexType slip_size)
{
	// Get work item index
	const size_t i_slip = get_global_id(0);

	// Check if we are in the range
	if (i_slip < slip_size)
	{
		ValueType k = 0.41;
		ValueType B = 5.1;
		//double density = mRho;
		//double mu = mViscosity;
		ValueType toll = 1e-6;
		//double ym = mY_wall;
		ValueType y_plus_incercept = 10.9931899;
		IndexType itmax = 100;

		IndexType i_node = mSlipBoundaryList[i_slip];
		//unsigned int i_node = mSlipBoundaryList[i_slip];

		//array_1d<double, TDim>& rhs_i = rhs[i_node];
		//const array_1d<double, TDim>& U_i = vel[i_node];
		//const array_1d<double, TDim>& an_i = mSlipNormal[i_node];

		VectorType U_i = vel[i_node];
		//VectorType an_i = mSlipNormal[i_node];

		// Compute the modulus of the velocity
		ValueType mod_vel = KRATOS_OCL_LENGTH3(U_i);
		ValueType area = KRATOS_OCL_LENGTH3(mSlipNormal[i_node]);

		//for (unsigned int comp = 0; comp < TDim; comp++)
		//{
			//mod_vel += U_i[comp] * U_i[comp];
			//area += an_i[comp] * an_i[comp];
		//}
		//mod_vel = sqrt(mod_vel);
		//area = sqrt(area);

		// Now compute the skin friction
		ValueType mod_uthaw = sqrt(mod_vel * mu / ym);
		ValueType y_plus = ym * mod_uthaw / mu;

		if (y_plus > y_plus_incercept)
		{
			// Begin cycle to calculate the real u_thaw's module
			IndexType it = 0;
			ValueType dx = 1e10;

			while (fabs(dx) > toll * mod_uthaw && it < itmax)
			{
				ValueType a = 1.00 / k;
				ValueType temp = a * log(ym * mod_uthaw / mu) + B;
				ValueType y = mod_uthaw * (temp) - mod_vel;
				ValueType y1 = temp + a;
				dx = y / y1;
				mod_uthaw -= dx;
				it++;
			}

			//if (it == itmax)
			//{
				//std::cout << "attention max number of iterations exceeded in wall law computation" << std::endl;
			//}
		}

		if (mod_vel > 1e-12)
		{
			rhs[i_node] -= U_i * area * mod_uthaw * mod_uthaw * density / mod_vel;
			//for (unsigned int comp = 0; comp < TDim; comp++)
			//{
				//rhs_i[comp] -= U_i[comp] * area * mod_uthaw * mod_uthaw * density / (mod_vel);
			//}
		}
}
