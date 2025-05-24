#pragma once
#include "ChampForces.h"
#include "Vecteur.h"
#include "ObjetPhysique.h"

// Déclaration anticipée pour éviter les inclusions circulaires
class PointMateriel;

class GravitationConstante : public ChampForces {
private:
    Vecteur gravitation;  // Vecteur de gravité

public:
    // Constructeur
    GravitationConstante();
    GravitationConstante(const Vecteur& g);
    
    // Méthode héritée de ChampForces
    Vecteur force(const ObjetPhysique& objet, double temps) const override;
    
    // Accesseur
    const Vecteur& getGravitation() const;
    
    // Surcharge de l'opérateur de sortie
    friend std::ostream& operator<<(std::ostream& os, const GravitationConstante& g);
};