// ==========================================================
// Heat Equation
// Author: Lucas Berg
// ==========================================================
// Considering dx=dy
// Solving using Explicit Finite Difference Method (FDM)
// ==========================================================

#include "params/params.h"
#include "grid/grid.h"

int main (int argc, char *argv[]) {
	
	if (argc-1 != 6) {
		fprintf(stderr, "-----------------------------------------------------\n");
		fprintf(stderr, "Usage:> %s <L> <dx> <T> <dt> <alpha> <print_rate>\n", argv[0]);
		fprintf(stderr, "-----------------------------------------------------\n");
		fprintf(stderr, "<L> = Size of grid\n");
		fprintf(stderr, "<dx> = Space discretization of the grid\n");
		fprintf(stderr, "<T> = Maximum simulation time\n");
		fprintf(stderr, "<dt> = Time discretization of the simulation\n");
		fprintf(stderr, "<alpha> = Diffusivity constant\n");
		fprintf(stderr, "<print_rate> = Print rate of the solution to file\n");
		fprintf(stderr, "-----------------------------------------------------\n");
		exit(EXIT_FAILURE);
	}
	Parameters *params = new Parameters(argv);
	//params->print();
	
	Grid *grid = new Grid(params->L, params->dx, params->nx,\
						  params->L, params->dy, params->ny);
	grid->set_boundary_conditions(100.0, 0.0, 0.0, 0.0);
	
	// MAIN SOLUTION
	double gamma = params->calculate_gamma();
	bool is_stable = params->check_time_discretization();
	if (!is_stable) {
		params->adjust_time_discretization();
		gamma = params->calculate_gamma();
	}
		
	char filename[200];
	// Time loop
	for (int k = 0; k < params->nt; k++) {
		// Set boundary conditions
		grid->set_boundary_conditions(100.0, 0.0, 0.0, 0.0);
		
		// Write the current solution
		if (k % params->print_rate == 0) {
			sprintf(filename, "outputs/u_%d.vtk", k);
			grid->write(filename);
		}

		// Solve for the next timestep
		// Space loop
		for (int i = 1; i < params->nx-1; i++) {
			for (int j = 1; j < params->ny-1; j++) {
				int k = i*params->ny+j;
				int north = (i-1)*params->ny+j;
				int south = (i+1)*params->ny+j;
				int east = i*params->ny+(j+1);
				int west = i*params->ny+(j-1);

				// Explicit formula
				grid->u_new[k] = gamma * (grid->u_old[north] + grid->u_old[south] + grid->u_old[east] + grid->u_old[west] - 4*grid->u_old[k]) + grid->u_old[k];
			}
    	}

		// Swap the solution vectors
		std::swap(grid->u_old, grid->u_new);
	}

	delete grid;
	delete params;

	return 0;
}