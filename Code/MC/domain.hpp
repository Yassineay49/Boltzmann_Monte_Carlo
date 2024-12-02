#include "main.hpp"
#include "parameters.hpp"



/* CLASSE DÉFINISSANT LE DOMAINE DANS LEQUEL LE PAQUET DE PARTICULE ÉVOLUE */
class GenericDomain
{
protected:
   const struct_parameters _parameters;
   std::valarray<Vecteur> _Omega;

public:
   /* Constructeurs et destructeurs par défaut */
   GenericDomain(const struct_parameters& parameters, const std::valarray<Vecteur>& Om);
   virtual ~GenericDomain();

   /* Fonctions membres */
   double initialCondition(const Vecteur&, const Vecteur&) const;
   virtual void applyBoundaryConditions(Vecteur&, double&, Vecteur&) const = 0;
   void applyInitialCondition() const;
   double sigmaS(const Vecteur&, const double&, const Vecteur&) const;
   double sigmaT(const Vecteur&, const double&, const Vecteur&) const;
   double sampleTau(const Vecteur&, const double&, const Vecteur&) const;
   Vecteur sampleVprime(const Vecteur&, const double&, const double&, const Vecteur&) const;

   /* Accesseurs */
   const std::valarray<Vecteur>& get_Omega() const { return _Omega; }
};

/* Domaine avec conditions de bords périodiques */
class PeriodicDomain : public GenericDomain
{
public:
   /* Constructeurs et destructeurs par défaut */
   PeriodicDomain(const struct_parameters& parameters, const std::valarray<Vecteur>& Om) : GenericDomain(parameters, Om) {};
   virtual ~PeriodicDomain();

   virtual void applyBoundaryConditions(Vecteur&, double&, Vecteur&) const;
};

/* Domaine avec choc élastique aux parois */
class ElasticDomain : public GenericDomain
{
public:
   /* Constructeurs et destructeurs par défaut */
   ElasticDomain(const struct_parameters& parameters, const std::valarray<Vecteur>& Om) : GenericDomain(parameters, Om) {};
   virtual ~ElasticDomain();

   virtual void applyBoundaryConditions(Vecteur&, double&, Vecteur&) const;
};