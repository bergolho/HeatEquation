#include "params.h"

Parameters::Parameters (char *argv[]) {
    this->L = atof(argv[1]);
    this->dx = atof(argv[2]);
    this->dy = this->dx;
    this->T = atof(argv[3]);
    this->dt = atof(argv[4]);
    this->alpha = atof(argv[5]);
    this->nx = nearbyint(this->L / this->dx);
    this->ny = nearbyint(this->L / this->dy);
    this->nt = nearbyint(this->T / this->dt);
    this->print_rate = atoi(argv[6]);
}

double Parameters::calculate_gamma () {
    return this->alpha * this->dt / pow(this->dx, 2);
}

void Parameters::adjust_time_discretization () {
    int prev_nt = this->nt;
    double prev_dt = this->dt;

    this->dt = pow(this->dx, 2)/(4.0*this->alpha);
    this->nt = nearbyint(this->T / this->dt);

    printf("[!] Adjusting time discretization from '%lf' to '%lf'\n",\
            prev_dt, this->dt);
}

bool Parameters::check_time_discretization () {
    return (this->dt <= (pow(this->dx, 2)/(4.0*this->alpha)));
}

void Parameters::print () {
    printf("nx = %d\n", this->nx);
    printf("ny = %d\n", this->ny);
    printf("dx = %g\n", this->dx);
    printf("dy = %g\n", this->dy);
    printf("L = %g\n", this->L);
    printf("nt = %d\n", this->nt);
    printf("dt = %g\n", this->dt);
    printf("T = %g\n", this->T);
    printf("alpha = %g\n", this->alpha);
    printf("print_rate = %d\n", this->print_rate);
}