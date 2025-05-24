#include "ChargeElectrique.h"
#include "Vecteur.h"
#include "SupportADessin.h"
#include "PointMateriel.h"
#include <iostream>
#include <stdexcept>
#include <memory>

// Constructeur par défaut
ChargeElectrique::ChargeElectrique()
    : PointMateriel(), charge(0.0) {}  // Initialiser la charge à 0

// Constructeur avec paramètres
ChargeElectrique::ChargeElectrique(const Vecteur& position, const Vecteur& vitesse,
                                 double masse,
                                 double charge_val,  // Ajouter le paramètre de charge
                                 std::shared_ptr<ChampForces> champ,
                                 std::shared_ptr<Contrainte> contrainte)
    : PointMateriel(position, vitesse, masse, champ, contrainte),
      charge(charge_val) {  // Initialiser la charge
    
    // S'assurer que la position et la vitesse ont la même dimension
    if (!(position.memeDimension(vitesse))) {
        throw std::runtime_error("La position et la vitesse doivent avoir la même dimension");
    }
    
    // S'assurer que la masse est positive
    if (masse <= 0) {
        throw std::runtime_error("La masse doit être une valeur positive");
    }
}

// Calculer l'équation d'évolution de la charge (F = ma)
Vecteur ChargeElectrique::evolution(double temps) const {
    // Utiliser la force de l'objet physique divisée par la masse pour obtenir l'accélération
    return force(temps) * (1.0 / getMasse());
}

double ChargeElectrique::getCharge() const {
    return charge;
}

void ChargeElectrique::setCharge(double q) {
    charge = q;
}

// Surcharge de l'opérateur de sortie
std::ostream& operator<<(std::ostream& os, const ChargeElectrique& charge_obj) {
    os << static_cast<const PointMateriel&>(charge_obj) << std::endl;
    os << "Charge : " << charge_obj.getCharge() << " C" << std::endl;
    
    // Calculer et afficher la force à t=0
    os << charge_obj.force(0) << " # Force (charge)";
    
    return os;
}