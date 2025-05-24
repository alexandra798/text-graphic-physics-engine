#include "ObjetPhysique.h"
#include <stdexcept>

#include <iostream>

// Implémentation du constructeur
ObjetPhysique::ObjetPhysique()
    : ObjetMobile(), masse(1.0) {}

ObjetPhysique::ObjetPhysique(const Vecteur& param, const Vecteur& deriv, double m,
                           std::shared_ptr<ChampForces> ch,
                           std::shared_ptr<Contrainte> con)
    : ObjetMobile(param, deriv), champ(ch), contrainte(con), masse(m) {
    if (masse <= 0) {
        throw std::runtime_error("La masse doit être une valeur positive");
    }
}

// Accesseur
const ChampForces& ObjetPhysique::getChampForces() const {
    if (!champ) {
        throw std::runtime_error("Champ de forces non défini");
    }
    return *champ;
}

const Contrainte& ObjetPhysique::getContrainte() const {
    if (!contrainte) {
        throw std::runtime_error("Contrainte non définie");
    }
    return *contrainte;
}

// Modificateur
void ObjetPhysique::setChampForces(std::shared_ptr<ChampForces> ch) {
    champ = ch;
}

void ObjetPhysique::setContrainte(std::shared_ptr<Contrainte> con) {
    contrainte = con;
}

// Calcule la force agissant sur l'objet
Vecteur ObjetPhysique::force(double temps) const {
    if (!champ) {
        // Si aucun champ de forces n'est défini, retourne un vecteur nul
        return Vecteur(3);
    }
    return champ->force(*this, temps);
}

// Obtient la position réelle de l'objet
Vecteur ObjetPhysique::position() const {
    if (!contrainte) {
        // Si aucune contrainte n'est définie, retourne directement le vecteur des paramètres
        return getParametres();
    }
    return contrainte->position(*this);
}

// Obtient la vitesse réelle de l'objet
Vecteur ObjetPhysique::vitesse() const {
    if (!contrainte) {
        // Si aucune contrainte n'est définie, retourne directement le vecteur dérivé des paramètres
        return getDeriveeParametres();
    }
    return contrainte->vitesse(*this);
}

// Calcule l'équation du mouvement de l'objet
Vecteur ObjetPhysique::evolution(double temps) const {
    if (!contrainte) {
        // Si aucune contrainte n'est définie, retourne un vecteur nul
        return Vecteur(3);
    }
    
    // Calcule la force et applique la contrainte
    Vecteur f = force(temps);
    return contrainte->applique_force(*this, f, temps);
}

// Surcharge de l'opérateur de sortie
std::ostream& operator<<(std::ostream& os, const ObjetPhysique& obj) {
    os << obj.getMasse() << " # masse" << std::endl;
    os << obj.position() << " # position" << std::endl;
    os << obj.vitesse() << " # vitesse";
    return os;
}

// Implémentation de l'accesseur
double ObjetPhysique::getMasse() const {
    return masse;
}