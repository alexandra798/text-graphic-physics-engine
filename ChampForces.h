#pragma once
#include "Vecteur.h"
#include <stdexcept>

// Déclaration anticipée pour éviter les références circulaires
class ObjetPhysique;

class ChampForces {
public:
    // Constructeur et destructeur virtuel
    ChampForces() = default;
    virtual ~ChampForces() = default;
    

    
    // Fonction virtuelle pure, calcule la force agissant sur l'objet physique
    virtual Vecteur force(const ObjetPhysique& objet, double temps) const = 0;

};