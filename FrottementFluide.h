#pragma once
#include "ChampForces.h"
#include "Vecteur.h"

class FrottementFluide : public ChampForces {
private:
    double lambda;  // Coefficient de frottement
    
public:
    // Constructeur
    explicit FrottementFluide(double coefficient_frottement);
    
    // Calculer la force de frottement
    Vecteur force(const ObjetPhysique& objet, double temps) const override;
    
    // Accesseur
    double getCoefficient() const { return lambda; }
};