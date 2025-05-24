#include "ChampElectromagnetique.h"
#include "ObjetPhysique.h"
#include "ChargeElectrique.h"
#include <stdexcept>

ChampElectromagnetique::ChampElectromagnetique(const Vecteur& E, const Vecteur& B)
    : champ_electrique(E), champ_magnetique(B) {
    // S'assurer que les champs électrique et magnétique ont la même dimension
    if (!E.memeDimension(B)) {
        throw std::runtime_error("Le champ électrique et le champ magnétique doivent avoir la même dimension");
    }
}

Vecteur ChampElectromagnetique::force(const ObjetPhysique& objet, double /* temps */) const {
    // Essayer de convertir l'objet en particule chargée
    const ChargeElectrique* charge_ptr = dynamic_cast<const ChargeElectrique*>(&objet);
    
    if (!charge_ptr) {
        // Si ce n'est pas une particule chargée, retourner une force nulle
        return Vecteur(objet.position().memeDimension(champ_electrique) ? 
                       champ_electrique.memeDimension(Vecteur()) : 3);
    }
    
    // Obtenir la charge électrique
    double q = charge_ptr->getCharge();
    
    // Obtenir la vitesse
    Vecteur v = objet.vitesse();
    
    // Calculer la force de Lorentz : F = q(E + v × B)
    Vecteur force_electrique = champ_electrique * q;
    Vecteur force_magnetique = (v ^ champ_magnetique) * q;
    
    return force_electrique + force_magnetique;
}