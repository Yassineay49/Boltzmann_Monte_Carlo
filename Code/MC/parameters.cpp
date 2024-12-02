#include "toml/toml.hpp"
#include "parameters.hpp"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <valarray>
#include <cmath>


//Création et initialisation de la structure paramètres en se basant sur le fichier param.toml
void init_parameters(struct_parameters& parameters) {

    //Opening file
    auto param_file = toml::parse(parameters.fileName);

    //Simulation parameters
    const auto& simulation = toml::find(param_file, "simulation");
    parameters.test_case = toml::find<int>(simulation, "test_case"); //Test case
    parameters.nbDims = toml::find<int>(simulation, "nbDims");//Number of dimensions
    parameters.nbMC = toml::find<int>(simulation, "nbMC"); //Number of MC particles 
    parameters.finalTime = toml::find<double>(simulation, "finalTime"); //Final time of the simulation
    parameters.dt = toml::find<double>(simulation, "dt"); //Time step
    parameters.solutionType = toml::find<std::string>(simulation, "solutionType"); //Type of solution
    parameters.domainType = toml::find<std::string>(simulation, "domainType"); //Type of domain

    // Position pour laquelle on veut calculer la solution (ici au centre)
    parameters.array_x = { toml::find<double>(simulation, "xmin"), toml::find<double>(simulation, "xmax") };

    // Vitesse initiale pour laquelle on veut calculer la solution
    parameters.array_v = std::valarray<double>(toml::find<double>(simulation, "v1"), parameters.nbDims);

    // Nombre de points de calcul
    parameters.nbPtsX = toml::find<int>(simulation, "nbPtsX");

    if (parameters.nbDims >= 2) {
        parameters.array_y = { toml::find<double>(simulation, "ymin"), toml::find<double>(simulation, "ymax") };
        parameters.array_v[1] = toml::find<double>(simulation, "v2");
        parameters.nbPtsY = toml::find<int>(simulation, "nbPtsY");
        if (parameters.nbDims == 3) {
            parameters.array_z = { toml::find<double>(simulation, "zmin"), toml::find<double>(simulation, "zmax") };
            parameters.array_v[2] = toml::find<double>(simulation, "v3");
            parameters.nbPtsZ = toml::find<int>(simulation, "nbPtsZ");
        }
    }

    //Physical parameters
    const auto& physics = toml::find(param_file, "physics");
    parameters.sigmaS = toml::find<double>(physics, "sigmaS");
    parameters.sigmaT = toml::find<double>(physics, "sigmaT");

    parameters.modV = 0;
    for(int iter=1 ; iter <= parameters.nbDims ; iter++){
        parameters.modV += std::abs(parameters.array_v[iter]);
    }

}
