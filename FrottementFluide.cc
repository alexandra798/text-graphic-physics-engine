#include "FrottementFluide.h"
#include "ObjetPhysique.h"
#include <stdexcept>

FrottementFluide::FrottementFluide(double coefficient_frottement)
    : lambda(coefficient_frottement) {
    if (lambda < 0) {
        throw std::runtime_error("Le coefficient de frottement doit être non négatif");
    }
}

Vecteur FrottementFluide::force(const ObjetPhysique& objet, double /* temps */) const {
    // Obtenir la vitesse de l'objet
    Vecteur vitesse = objet.vitesse();
    
    // Calculer la force de frottement
    return vitesse * (-lambda);
}