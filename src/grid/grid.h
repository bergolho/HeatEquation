#ifndef GRID_H
#define GRID_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>

class Grid {
public:
    int nx;
    int ny;
    double Lx;
    double Ly;
    double dx;
    double dy;
    double *u_old;
    double *u_new;
public:
    Grid (double Lx, double dx, int nx,\
          double Ly, double dy, int ny);
    ~Grid ();
    void set_boundary_conditions (double u_upper, double u_left,\
                                  double u_right, double u_bottom);
    void write (const char filename[]);
};

#endif