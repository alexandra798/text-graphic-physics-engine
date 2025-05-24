#include "PointMateriel.h"
#include "Vecteur.h"
#include <iostream>
#include <stdexcept>
#include <memory>

// Constructeur par défaut
PointMateriel::PointMateriel()
    : ObjetPhysique() {}

// Constructeur paramétré
PointMateriel::PointMateriel(const Vecteur& position, const Vecteur& vitesse, double masse,
                           std::shared_ptr<ChampForces> champ,
                           std::shared_ptr<Contrainte> contrainte)
    : ObjetPhysique(position, vitesse, masse, champ, contrainte) {
    // Le constructeur de la classe mère a déjà validé les paramètres
}

// Méthode affiche sans afficher la force
void PointMateriel::affiche() const {
    std::cout << getMasse() << " # masse" << std::endl;
    std::cout << position() << " # position" << std::endl;
    std::cout << vitesse() << " # vitesse";
}

// Méthode affiche affichant la force
void PointMateriel::affiche(double temps) const {
    affiche();
    std::cout << std::endl;
    std::cout << force(temps) << " # force";
}

// Opérateur de sortie - appelle seulement affiche sans paramètre
std::ostream& operator<<(std::ostream& os, const PointMateriel& point) {
    point.affiche();
    return os;
}