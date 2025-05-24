#pragma once
#include "Contrainte.h"
#include "Vecteur.h"

// Déclaration anticipée
class ObjetPhysique;

class Libre : public Contrainte {
public:
    // Constructeur
    Libre() = default;
    
    // Implémentation des méthodes abstraites de la classe de base
    Vecteur applique_force(const ObjetPhysique& objet, const Vecteur& force, double temps) const override;
    
    Vecteur position(const ObjetPhysique& objet) const override;
    
    Vecteur vitesse(const ObjetPhysique& objet) const override;
};