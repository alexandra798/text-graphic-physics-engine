#pragma once
#include "Vecteur.h"
#include <stdexcept>

// Déclaration anticipée pour éviter les références circulaires
class ObjetPhysique;

class Contrainte {
public:
    // Constructeur et destructeur virtuel
    Contrainte() = default;
    virtual ~Contrainte() = default;
    



    virtual Vecteur applique_force(const ObjetPhysique& objet, const Vecteur& force, double temps) const = 0;

    virtual Vecteur position(const ObjetPhysique& objet) const = 0;

    virtual Vecteur vitesse(const ObjetPhysique& objet) const = 0;
    

};