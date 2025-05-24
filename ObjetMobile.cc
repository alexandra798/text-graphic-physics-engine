
// ObjetMobile.cc
#include "ObjetMobile.h"
#include "Vecteur.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

// Constructeur par défaut
ObjetMobile::ObjetMobile() 
    : parametres(3), derivee_parametres(3) {}

// Constructeur avec paramètres
ObjetMobile::ObjetMobile(const Vecteur& param, const Vecteur& deriv)
    : parametres(param), derivee_parametres(deriv) {
    
    if (param.norme2() > 0 && deriv.norme2() > 0 && !param.memeDimension(deriv)) {
        throw std::runtime_error("Les dimensions des vecteurs paramètres et dérivée doivent être identiques");
    }
}

// Accesseurs
Vecteur ObjetMobile::getParametres() const {
    return parametres;
}

Vecteur ObjetMobile::getDeriveeParametres() const {
    return derivee_parametres;
}

// Modificateurs
void ObjetMobile::setParametres(const Vecteur& param) {
    parametres = param;
}

void ObjetMobile::setDeriveeParametres(const Vecteur& deriv) {
    derivee_parametres = deriv;
}

// Surcharge de l'opérateur << pour l'affichage
std::ostream& operator<<(std::ostream& os, const ObjetMobile& obj) {
    os << obj.getParametres() << " # parametre" << std::endl;
    os << obj.getDeriveeParametres() << " # vitesse";
    return os;
}