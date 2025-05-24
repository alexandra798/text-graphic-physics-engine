#include "ChampNewtonien.h"
#include "ObjetPhysique.h"

// Constructeur
ChampNewtonien::ChampNewtonien(std::shared_ptr<ObjetPhysique> centre)
    : ForceCentrale(centre) {}

// Calculer la force gravitationnelle de Newton
Vecteur ChampNewtonien::force(const ObjetPhysique& objet, double /* temps */) const {
    // Obtenir la masse
    double masse_objet = objet.getMasse();
    double masse_centre = centre->getMasse();
    
    // Calculer le vecteur de force en carré inverse
    Vecteur force_direction = quadratique_inverse(objet);
    
    // Calculer la force de Newton : F = G * m1 * m2 / r^2
    return force_direction * (G * masse_objet * masse_centre);
}