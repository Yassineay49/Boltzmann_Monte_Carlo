#include "main.hpp"
#include "domain.hpp"

/* CLASSE DÉFINISSANT UNE PARTICULE UNIQUE */
class Particle
{
private:
   const GenericDomain* _Domain;
   const struct_parameters _parameters;
   double _sp, _wp, _t;
   Vecteur _xp;
   Vecteur _vp;

public:
   bool notInDomain();

public:
   Particle(const GenericDomain*, const struct_parameters& parameters, const Vecteur& x);
   ~Particle();
   virtual void move(double&);
};