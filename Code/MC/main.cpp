#include "main.hpp"
#include "population.hpp"

/*
   Ce code résout l'équation intégro-différentielle de
   Boltzmann par un schéma semi-analogue de Monte-Carlo.
*/

int main(int argc, char const* argv[])
{
   /* Déclaration - initialisation des variables */
   struct struct_parameters parameters;
   parameters.fileName = argc > 1 ? argv[1] : "param.toml";
   init_parameters(parameters);
   double nbIterations = int(parameters.finalTime / parameters.dt) + 1;

   /* Création du domaine où les particules se meuvent */
   //Limites du domaine
   std::valarray<Vecteur> Omega(parameters.nbDims);
   Omega[0] = parameters.array_x;
   if (parameters.nbDims >= 2) {
      Omega[1] = parameters.array_y;
      if (parameters.nbDims == 3) {
         Omega[2] = parameters.array_z;
      }
   }
   //Création du domaine
   GenericDomain* Domaine = NULL;
   if (parameters.domainType == "elastic") //Condition limites élastiques
   {
      Domaine = new ElasticDomain(parameters, Omega);
   }
   else if (parameters.domainType == "periodic")//Condition limites périodiques
   {
      Domaine = new PeriodicDomain(parameters, Omega);
   }
   else
   {
      delete Domaine;
      std::cout << "Domain type not recognized : choose \"elastic\" or \"periodic\"." << std::endl;
      exit(1);
   }


   /* Ouverture d'un fichier pour stocker la solution */
   std::ofstream file;

   if (parameters.solutionType != "time" and parameters.solutionType != "space")
   {
      std::cout << "Solution type not recognized : choose \"time\" or \"space\"." << std::endl;
      throw std::exception();
   }
   else if (parameters.solutionType == "time")
   {
      file.open("Resultats/solution_t.txt");
   }

   /* Création de la solution u(x, t, v) */
   std::valarray<std::valarray<std::valarray<double>>> u(std::valarray<std::valarray<double>>(std::valarray<double>(0.0, parameters.nbPtsZ), parameters.nbPtsY), parameters.nbPtsX);
   for (int iter_n = 0; iter_n < nbIterations; iter_n++)//Boucle sur les pas de temps
   {
      if (parameters.solutionType == "space")
      {
         file.open("Resultats/solution_t_" + std::to_string(iter_n) + ".txt");
      }

      for (int iter_i = 0; iter_i < parameters.nbPtsX; iter_i++)
      {
         for (int iter_j = 0; iter_j < parameters.nbPtsY; iter_j++)
         {
            for (int iter_k = 0; iter_k < parameters.nbPtsZ; iter_k++)
            {
               u[iter_i][iter_j][iter_k] = 0.0;
               double coord_x = parameters.array_x[0] + (iter_i + 0.5) * (parameters.array_x[1] - parameters.array_x[0]) / (parameters.nbPtsX);
               double coord_y = parameters.array_y[0] + (iter_j + 0.5) * (parameters.array_y[1] - parameters.array_y[0]) / (parameters.nbPtsY);
               double coord_z = parameters.array_z[0] + (iter_k + 0.5) * (parameters.array_z[1] - parameters.array_z[0]) / (parameters.nbPtsZ);

               u[iter_i][iter_j][iter_k] = iter_n > 0 ? 0.0 : Domaine->initialCondition({ coord_x, coord_y, coord_z }, parameters.array_v);
               /* Création de la population de particules (fictives) */
               Population packOfParticles(Domaine, parameters, u[iter_i][iter_j][iter_k], { coord_x, coord_y, coord_z });

               /* Les particules (fictives) évoluent */
               packOfParticles.move();

               /* On en déduit la solution u(coord_x, t, v) */
               u[iter_i][iter_j][iter_k] = packOfParticles.get_u();
               file << coord_x << "\t" << coord_y << "\t" << coord_z << "\t" << parameters.time << "\t" << u[iter_i][iter_j][iter_k] << std::endl;
            }
         }
      }
      parameters.time += parameters.dt;
      if (parameters.solutionType == "space")
      {
         file.close();
      }
   }
   file.close();

   delete Domaine;

   return 0;
}