#ifndef PARAMETRES_HPP
#define PARAMETRES_HPP

#include <valarray>

struct struct_parameters {
    //Simulation parameters
    int nbDims = 0; //Number of dimensions
    int nbMC = 0; //Number of MC particles 
    int test_case = 0; //Test case
    double time = 0; //Current time of the simulation
    double finalTime = 0; //Final time of the simulation
    double dt = 0; //Time step

    std::valarray<double> array_x = { 0, 0 };
    std::valarray<double> array_y = { 0, 0 };
    std::valarray<double> array_z = { 0, 0 };
    std::valarray<double> array_v;

    int nbPtsX = 1,
        nbPtsY = 1,
        nbPtsZ = 1;

    std::string domainType = "";
    std::string fileName = "";
    std::string solutionType = "";

    //Phisical parameters
    double sigmaS = 0;
    double sigmaT = 0;
    double modV = 0;
};

void init_parameters(struct_parameters& parameters_1);

#endif
