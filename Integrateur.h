// Integrateur.h
#pragma once
#include "ObjetMobile.h"
#include <stdexcept>

class Integrateur {
protected:
    double pas_temps; // Pas d'intégration dt
    
public:
    // Constructeurs
    Integrateur() = default;
    virtual ~Integrateur() = default;
    
    // Méthode virtuelle pure pour intégrer l'objet mobile
    virtual void integre(ObjetMobile& objet, double t, double dt) const = 0;


};