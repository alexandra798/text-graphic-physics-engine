#pragma once
#include "ChampForces.h"
#include "Vecteur.h"

class ChampElectromagnetique : public ChampForces {
private:
    Vecteur champ_electrique;   // Vecteur champ électrique E
    Vecteur champ_magnetique;   // Vecteur champ magnétique B
    
public:
    // Constructeur
    ChampElectromagnetique(const Vecteur& E, const Vecteur& B);
    
    // Calculer la force de Lorentz : F = q(E + v × B)
    Vecteur force(const ObjetPhysique& objet, double temps) const override;
    
    // Accesseurs
    const Vecteur& getChampElectrique() const { return champ_electrique; }
    const Vecteur& getChampMagnetique() const { return champ_magnetique; }
};