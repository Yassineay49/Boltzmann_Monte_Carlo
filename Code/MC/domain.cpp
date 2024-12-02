#include "domain.hpp"
#include "parameters.hpp"

GenericDomain::GenericDomain(const struct_parameters& parameters, const std::valarray<Vecteur>& Om) :
   _parameters(parameters),
   _Omega(Om)
{
};

GenericDomain::~GenericDomain()
{
};

ElasticDomain::~ElasticDomain()
{
};

PeriodicDomain::~PeriodicDomain()
{
};

// Here a general function for the application of arbitrary boundary conditions
void ElasticDomain::applyBoundaryConditions(Vecteur& xp, double& sp, Vecteur& vp) const
{
   // Choc élastique sur les parois
   double distance_avec_bord = 0.0;
   for (int iter_i = 0; iter_i < this->_parameters.nbDims; iter_i++)
   {
      if (xp[iter_i] <= this->_Omega[iter_i][0])
      {
         distance_avec_bord = abs(xp[iter_i] - this->_Omega[iter_i][0]);
         xp[iter_i] = this->_Omega[iter_i][0] + distance_avec_bord;
         vp[iter_i] *= -1;
      }
      else if (this->_Omega[iter_i][1] <= xp[iter_i])
      {
         distance_avec_bord = abs(xp[iter_i] - this->_Omega[iter_i][1]);
         xp[iter_i] = this->_Omega[iter_i][1] - distance_avec_bord;
         vp[iter_i] *= -1;
      }
   }
};

void PeriodicDomain::applyBoundaryConditions(Vecteur& xp, double& sp, Vecteur& vp) const
{
   for (int iter_i = 0; iter_i < this->_parameters.nbDims; iter_i++)
   {
      if (xp[iter_i] <= this->_Omega[iter_i][0])
      {
         xp[iter_i] += (this->_Omega[iter_i][1] - this->_Omega[iter_i][0]);
      }
      else if (this->_Omega[iter_i][1] <= xp[iter_i])
      {
         xp[iter_i] -= (this->_Omega[iter_i][1] - this->_Omega[iter_i][0]);
      }
   }
};

double GenericDomain::initialCondition(const Vecteur& x, const Vecteur& v) const
{
   double u_0;

 if (this->_parameters.test_case == 1) u_0 = 5.0;
   else if (this->_parameters.test_case == 2)
   {
      if (this->_parameters.nbDims == 3)
      {
         std::cout << "Test case 2 is only available for 2D and1D problems." << std::endl;
      }
      if (this->_parameters.nbDims == 1)
      {
         u_0 = (0.4 < x[0] and x[0] < 0.6) ? 1.0 : 0.0;
      }
      if (this->_parameters.nbDims == 2)
      {
         double x1,y1;
         double beta=5;
         x1=x[0];
         y1=x[1];
         double r = sqrt((x1)*(x1) + (y1)*(y1));
         if(r<0.25){
            u_0=1.0;
         }
         else{
            u_0=0.0;
         }

      }
   }

   else if (this->_parameters.test_case == 3) {

      Vecteur taille(3);

      taille[0] = (this->_parameters.array_x[1] - this->_parameters.array_x[0]);
      taille[1] = (this->_parameters.array_y[1] - this->_parameters.array_y[0]);
      taille[2] = (this->_parameters.array_z[1] - this->_parameters.array_z[0]);

      for (int iter_i = 0;iter_i < this->_parameters.nbDims;iter_i++) {
         u_0 = 10 * cos(x[iter_i] * taille[iter_i] / (2.1415 * 2));
      }
   }
   else { std::cout << "Test case not recognized : choose 1 or 2." << std::endl; }


   return u_0;
};

double GenericDomain::sigmaS(const Vecteur& xp, const double& t, const Vecteur& vp) const
{
   double sigmas = this->_parameters.sigmaS;
   return sigmas;
};

double GenericDomain::sigmaT(const Vecteur& xp, const double& t, const Vecteur& vp) const
{
   double sigmat = this->_parameters.sigmaT;
   return sigmat;
};


// Sample the velocity V′ of particle p from P_V'^s(xp, sp, τ, vp, v′)dv′
Vecteur GenericDomain::sampleVprime(const Vecteur& xp, const double& sp, const double& tau, const Vecteur& vp) const
{
   double normV = 1.0;
   Vecteur vprime(0.0, 3);

   // Initialisation du générateur de nombres aléatoires
   std::random_device rd;
   std::default_random_engine generator(rd());

   if (this->_parameters.nbDims == 1)
   {
      // tirage uniforme sur [-1, 1]
      std::uniform_real_distribution<double> distribution(-1, 1);
      auto tirage = distribution(generator);
      vprime[0] = normV * tirage / abs(tirage);
   }
   else if (this->_parameters.nbDims == 2)
   {
      // tirage uniforme sur le cercle unité
      std::uniform_real_distribution<double> distribution(0, 2 * M_PI);
      double theta = distribution(generator);
      vprime[0] = normV * cos(theta);
      vprime[1] = normV * sin(theta);
   }
   else if (this->_parameters.nbDims == 3)
   {
      // tirage uniforme sur la sphère unité (composition de loi normales)
      // voir Daniel Saada - lois uniformes sur la sphère
      std::normal_distribution<double> distribution(0, 1);

      vprime[0] = distribution(generator);
      vprime[1] = distribution(generator);
      vprime[2] = distribution(generator);
      vprime = vprime / sqrt((pow(vprime, 2)).sum());
      vprime = normV * vprime;
   }

   return vprime;
};

// Sample τ from the distribution having probability measure fτ(xp, sp, s, vp)ds
double GenericDomain::sampleTau(const Vecteur& xp, const double& sp, const Vecteur& vp) const
{
   // Initialisation du générateur de nombres aléatoires
   std::random_device rd;
   std::default_random_engine generator(rd());
   std::uniform_real_distribution<double> distribution(0, 1);

   double sigma_t = this->sigmaT(xp, sp, vp);
   return sigma_t > 0 ? -log(distribution(generator)) / (sigma_t * sqrt(((vp * vp).sum()))) : sp + 1;
};
