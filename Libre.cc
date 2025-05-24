#include "Libre.h"
#include "ObjetPhysique.h" 
#include "Vecteur.h"

Vecteur Libre::applique_force(const ObjetPhysique& objet, const Vecteur& force, double /*temps*/) const {
    double masse = objet.getMasse();
    if (masse > 0) {
        return force * (1.0 / masse);
    } else {
        return force;
    }
}

Vecteur Libre::position(const ObjetPhysique& objet) const {
    return objet.getParametres();
}

Vecteur Libre::vitesse(const ObjetPhysique& objet) const {
    return objet.getDeriveeParametres();
}