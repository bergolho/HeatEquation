#ifndef PARAMS_H
#define PARAMS_H

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>

class Parameters {
public:
	int nx;
	int ny;
	int nt;
	double L;
	double T;
	double dx;
	double dy;
	double dt;
	double alpha;
	int print_rate;
public:
	Parameters (char *argv[]);
	double calculate_gamma ();
	void adjust_time_discretization ();
	bool check_time_discretization ();
	void print ();
};

#endif