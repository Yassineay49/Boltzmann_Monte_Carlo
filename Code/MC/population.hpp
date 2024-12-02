#include "main.hpp"
#include "particles.hpp"
#include "parameters.hpp"



/* CLASSE DÉFINISSANT LES PAQUETS DE PARTICULES */
class Population
{
private:
   const GenericDomain* _Domain;
   const struct_parameters _parameters;
   const int _nbParticles;
   double _vect_u;
   Vecteur _vect_x;

public:
   Population(const GenericDomain*, const struct_parameters& parameters, double& u, const Vecteur& x);
   ~Population();

   void move(); //Fait se déplacer le groupe de particules
   const double& get_u() const { return this->_vect_u; };
};