#pragma once
#include "ChampForces.h"
#include <memory>
#include "Vecteur.h"
class ObjetPhysique;


class ForceCentrale : public ChampForces {
protected:
    std::shared_ptr<ObjetPhysique> centre;  // Objet central
    
    // Calculer le vecteur de force en carré inverse
    Vecteur quadratique_inverse(const ObjetPhysique& objet) const;
    
public:
    // Constructeur
    ForceCentrale(std::shared_ptr<ObjetPhysique> centre);
    
    // Destructeur
    virtual ~ForceCentrale() = default;
    
    // Fonction virtuelle pure, doit être implémentée par les classes dérivées
    virtual Vecteur force(const ObjetPhysique& objet, double temps) const override = 0;
};