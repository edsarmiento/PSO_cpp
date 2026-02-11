/* 
 * File:   pso.h
 * Author: alejandro
 *
 * Created on January 25, 2012, 11:36 PM
 */

#include <stdlib.h>
#include <string>
#include <iostream>

#ifndef PSO_H
#define	PSO_H

const double elemenSize=3;
const double nuc44factor=0.277316;
const double min[3] = {0, 0, 15};

const double nuc44[][15]={
    {5 ,-4 ,-4 ,-4 ,-4 , 1 , 1 ,-4 ,-4 , 1 ,-4 ,-1 ,-1 ,-1 ,-2},
    {-4 , 5 ,-4 ,-4 ,-4 , 1 ,-4 , 1 , 1 ,-4 ,-1 ,-4 ,-1 ,-1 ,-2},
    {-4 ,-4 , 5 ,-4 , 1 ,-4 , 1 ,-4 , 1 ,-4 ,-1 ,-1 ,-4 ,-1 ,-2},
    {-4 ,-4 ,-4 , 5 , 1 ,-4 ,-4 , 1 ,-4 , 1 ,-1 ,-1 ,-1 ,-4 ,-2},
    {-4 ,-4 , 1 , 1 ,-1 ,-4 ,-2 ,-2 ,-2 ,-2 ,-1 ,-1 ,-3 ,-3 ,-1},
    {1 , 1 ,-4 ,-4 ,-4 ,-1 ,-2 ,-2 ,-2 ,-2 ,-3 ,-3 ,-1 ,-1 ,-1},
    {1 ,-4 , 1 ,-4 ,-2 ,-2 ,-1 ,-4 ,-2 ,-2 ,-3 ,-1 ,-3 ,-1 ,-1},
    {-4 , 1 ,-4 , 1 ,-2 ,-2 ,-4 ,-1 ,-2 ,-2 ,-1 ,-3 ,-1 ,-3 ,-1},
    {-4 , 1 , 1 ,-4 ,-2 ,-2 ,-2 ,-2 ,-1 ,-4 ,-1 ,-3 ,-3 ,-1 ,-1},
    {1 ,-4 ,-4 , 1 ,-2 ,-2 ,-2 ,-2 ,-4 ,-1 ,-3 ,-1 ,-1 ,-3 ,-1},
    {-4 ,-1 ,-1 ,-1 ,-1 ,-3 ,-3 ,-1 ,-1 ,-3 ,-1 ,-2 ,-2 ,-2 ,-1},
    {-1 ,-4 ,-1 ,-1 ,-1 ,-3 ,-1 ,-3 ,-3 ,-1 ,-2 ,-1 ,-2 ,-2 ,-1},
    {-1 ,-1 ,-4 ,-1 ,-3 ,-1 ,-3 ,-1 ,-3 ,-1 ,-2 ,-2 ,-1 ,-2 ,-1},
    {-1 ,-1 ,-1 ,-4 ,-3 ,-1 ,-1 ,-3 ,-1 ,-3 ,-2 ,-2 ,-2 ,-1 ,-1},
    {-2 ,-2 ,-2 ,-2 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1}
};

int nucleotideToInt(char);

inline double drandom() {
    return rand()*1.0 / RAND_MAX;
}

double **getInitialPopulation(int, int, double* , double* );

double *basicPSO(int np, int tp,
        double* min, double* max, 
        double(*f)(double*, std::string, std::string), 
        int iteraciones, double* vmin, double* vmax, 
        double w, double c1, double c2, 
        std::string cad1, std::string cad2,
        std::ostream &sout);

void alinear(std::string cad1, std::string cad2,
        int np,int tp,int iteraciones,double c1, double c2, double w,
        std::ostream &sout);


//NUC 44 Matrix

/*
     A   T   G   C   S   W   R   Y   K   M   B   V   H   D   N
A   5  -4  -4  -4  -4   1   1  -4  -4   1  -4  -1  -1  -1  -2
T  -4   5  -4  -4  -4   1  -4   1   1  -4  -1  -4  -1  -1  -2
G  -4  -4   5  -4   1  -4   1  -4   1  -4  -1  -1  -4  -1  -2
C  -4  -4  -4   5   1  -4  -4   1  -4   1  -1  -1  -1  -4  -2
S  -4  -4   1   1  -1  -4  -2  -2  -2  -2  -1  -1  -3  -3  -1
W   1   1  -4  -4  -4  -1  -2  -2  -2  -2  -3  -3  -1  -1  -1
R   1  -4   1  -4  -2  -2  -1  -4  -2  -2  -3  -1  -3  -1  -1
Y  -4   1  -4   1  -2  -2  -4  -1  -2  -2  -1  -3  -1  -3  -1
K  -4   1   1  -4  -2  -2  -2  -2  -1  -4  -1  -3  -3  -1  -1
M   1  -4  -4   1  -2  -2  -2  -2  -4  -1  -3  -1  -1  -3  -1
B  -4  -1  -1  -1  -1  -3  -3  -1  -1  -3  -1  -2  -2  -2  -1
V  -1  -4  -1  -1  -1  -3  -1  -3  -3  -1  -2  -1  -2  -2  -1
H  -1  -1  -4  -1  -3  -1  -3  -1  -3  -1  -2  -2  -1  -2  -1  
D  -1  -1  -1  -4  -3  -1  -1  -3  -1  -3  -2  -2  -2  -1  -1
N  -2  -2  -2  -2  -1  -1  -1  -1  -1  -1  -1  -1  -1  -1  -1
 */

#endif	/* PSO_H */

