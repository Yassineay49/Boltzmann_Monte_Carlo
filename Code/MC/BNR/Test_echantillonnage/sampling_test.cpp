#include "../../population.hpp"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <valarray>
#include <random>
#include <iostream>
#include <fstream>
// #include </home/gabriel/Téléchargements/visit3_3_3.linux-x86_64/3.3.3/linux-x86_64/include/vtk/vtk-8.1/vtkjsoncpp/json/json.h>
using Vecteur = std::valarray<double>;

int main(int argc, char const* argv[])
{
    int
        d = 3,     //Nb de dimensions
                   // /!\test implémenté uniquement pour la 3D
        nMC = 10000;  // Nb de particules

//Création du domaine
std::valarray<Vecteur> Omega(d);
Vecteur nbNodesInDimension(d);
for (int i = 0; i < d; i++)
{
    Vecteur dimDomain = {-1,1};
    Omega[i] = dimDomain;
}
GenericDomain* Domaine = NULL;
//Domaine = new PeriodicDomain(d, Omega);

//temps, vitesse et position init
double t=1.0;              // Tps pour lequel on calcule la solution
Vecteur x = Vecteur(d,0.0); //position initialisée au centre
Vecteur v = Vecteur(d,1.0); //Vitesse initiale

//Solution u(x,t,v)
double u(0.0);

double normV = 1.0;
double sum = 0.0;
std::vector<double> rand(d,0.0);
std::vector<double> sample(d,0.0);
std::vector<std::vector<double>> data;
std::default_random_engine generator;
std::normal_distribution<double> distribution(0, 1);

//Tirage aléatoire de n_samples vecteurs
for (int i =0; i < nMC; i++)
{
    rand[0] = distribution(generator);
    rand[1] = distribution(generator);
    rand[2] = distribution(generator);

    sum = sqrt(pow(rand[0],2) + pow(rand[1],2) + pow(rand[2],2));

    sample[0] = normV * rand[0] / sum;
    sample[1] = normV * rand[1] / sum; 
    sample[2] = normV * rand[2] / sum; 

    /* for (int i = 0; i < sample.size(); ++i) {
        std::cout << sample[i] << " ";
    }
    std::cout << std::endl; */

    data.push_back(sample);
}

/*for (const auto& point : data) {
    for (const auto& coord : point) {
            std::cout << coord << " ";
    }
        std::cout << std::endl;
}
*/

// Écriture des données dans un fichier JSON
std::ofstream outFile("data.json");

// Ouvrir le fichier en mode texte
outFile << "[";

for (size_t i = 0; i < data.size(); ++i)
{
    const auto& point = data[i];

    outFile << "[";
    for (size_t j = 0; j < point.size(); ++j)
    {
        outFile << point[j];
        if (j < point.size() - 1)
        {
                outFile << ",";
        }
    }
    outFile << "]";

    if (i < data.size() - 1)
    {
        outFile << ",";
    }
}

// Fermer le fichier
outFile << "]" << std::endl;
outFile.close();

std::ofstream outFile1("nMC.json");
outFile1 << nMC << std::endl;
outFile1.close();

}