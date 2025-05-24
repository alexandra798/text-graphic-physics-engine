#include "ForceCentrale.h"
#include "ObjetPhysique.h"
#include <stdexcept>

// Constructeur
ForceCentrale::ForceCentrale(std::shared_ptr<ObjetPhysique> centre)
    : centre(centre) {
    if (!centre) {
        throw std::runtime_error("L'objet central ne peut pas être nul");
    }
}

// Calculer le vecteur de force en carré inverse
Vecteur ForceCentrale::quadratique_inverse(const ObjetPhysique& objet) const {
    // Obtenir la position de l'objet central et de l'objet cible
    Vecteur pos_centre = centre->position();
    Vecteur pos_objet = objet.position();
    
    // Calculer le vecteur de différence de position entre les deux objets
    Vecteur diff = pos_centre - pos_objet;
    
    // Calculer le carré de la distance
    double dist2 = diff.norme2();
    
    // Si la distance est trop petite, retourner un vecteur nul pour éviter les problèmes numériques
    if (dist2 < 1e-10) {
        return Vecteur(diff.memeDimension(pos_objet) ? pos_objet.memeDimension(Vecteur()) : 3);
    }
    
    // Calculer le vecteur unitaire (direction de l'objet cible vers l'objet central)
    Vecteur unit_vector = diff * (1.0 / sqrt(dist2)); // La direction est de l'objet vers le centre
    
    // Calculer la magnitude de la force en carré inverse
    double magnitude = 1.0 / dist2;
    
    // Retourner le vecteur de force en carré inverse
    return unit_vector * magnitude;
}