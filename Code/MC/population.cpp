#include "population.hpp"


/* Constructeur par défaut de la classe Population */
Population::Population(const GenericDomain* Domain, const struct_parameters& parameters, double& vect_u, const Vecteur& vect_x) :
   _Domain(Domain),
   _parameters(parameters),
   _nbParticles(parameters.nbMC),
   _vect_u(vect_u),
   _vect_x(vect_x)
{
};

/* Destructeur par défaut */
Population::~Population()
{
};

/* Fonction qui fait évoluer plein de particules */
void Population::move()
{
   for (int iter_i = 0; iter_i < this->_parameters.nbMC; iter_i++)
   {
      /* On crée une particule */
      Particle particle(this->_Domain, this->_parameters, this->_vect_x);
      /* La particule est "envoyée" évoluer */
      particle.move(_vect_u);
   }
};
