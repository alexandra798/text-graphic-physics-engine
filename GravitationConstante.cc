#include "GravitationConstante.h"
#include "ObjetPhysique.h"
#include "constantes.h"
#include <iostream>

// Le constructeur par défaut utilise la constante gravitationnelle terrestre
GravitationConstante::GravitationConstante()
    : gravitation(constantes::g) {}

// Constructeur utilisant un vecteur de gravité spécifié
GravitationConstante::GravitationConstante(const Vecteur& g)
    : gravitation(g) {}

// Calculer la force de gravité agissant sur l'objet physique
Vecteur GravitationConstante::force(const ObjetPhysique& objet, double /* temps */) const {
    // F = m * g
    return gravitation * objet.getMasse();
}

// Obtenir le vecteur de gravité
const Vecteur& GravitationConstante::getGravitation() const {
    return gravitation;
}

// Surcharge de l'opérateur de sortie
std::ostream& operator<<(std::ostream& os, const GravitationConstante& g) {
    os << g.getGravitation() << " # Intensité de la gravité";
    return os;
}