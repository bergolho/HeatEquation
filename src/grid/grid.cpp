#include "grid.h"

Grid::Grid (double Lx, double dx, int nx,\
          double Ly, double dy, int ny) {
    this->Lx = Lx;
    this->Ly = Ly;
    this->dx = dx;
    this->dy = dy;
    this->nx = nx;
    this->ny = ny;
    this->u_old = new double[nx*ny]();
    this->u_new = new double[nx*ny]();
}

Grid::~Grid () {
    if (this->u_old) {
        delete [] this->u_old;
    }
    if (this->u_new) {
        delete [] this->u_new;
    }
}

void Grid::set_boundary_conditions (double u_upper, double u_left,\
                                  double u_right, double u_bottom) {
    // Upper
    for (int j = 0; j < this->ny; j++) {
        this->u_old[(this->nx-1)*this->ny+j] = u_upper;
    }
    // Bottom
    for (int j = 0; j < this->ny; j++) {
        this->u_old[j] = u_bottom;
    }
    // Left
    for (int j = 0; j < this->nx; j++) {
        this->u_old[j*this->ny] = u_left;
    }
    // Right
    for (int j = 0; j < this->nx; j++) {
        this->u_old[j*this->ny+(this->ny-1)] = u_right;
    }
}

void Grid::write (const char filename[]) {
    int np = this->nx*this->ny;
    FILE *file = fopen(filename,"w+");
    fprintf(file, "# vtk DataFile Version 4.2\n");
    fprintf(file, "vtk output\n");
    fprintf(file, "ASCII\n");
    fprintf(file, "DATASET POLYDATA\n");
    fprintf(file, "POINTS %d float\n", np);
    for (int i = 0; i < this->nx; i++) {
        double x = i*this->dx;
        for (int j = 0; j < this->ny; j++) {
            double y = j*this->dy;
            fprintf(file, "%lf %lf 0.0\n", x, y);
        }
    }
    fprintf(file, "VERTICES %d %d\n", np, np*2);
    for (int i = 0; i < this->nx; i++) {
        for (int j = 0; j < this->ny; j++) {
            int k = i*this->ny+j;
            fprintf(file, "1 %d\n", k);
        }
    }
    fprintf(file, "POINT_DATA %d\n", np);
    fprintf(file, "FIELD FieldData 1\n");
    fprintf(file, "u 1 %d float\n", np);
    for (int i = 0; i < this->nx; i++) {
        for (int j = 0; j < this->ny; j++) {
            int k = i*this->ny+j;
            fprintf(file, "%g\n", this->u_old[k]);
        }
    }
    fprintf(file, "METADATA\n");
    fprintf(file, "INFORMATION 0\n");
    fclose(file);
}