// IntegrateurEulerCromer.h
#pragma once
#include "Integrateur.h"

class IntegrateurEulerCromer : public Integrateur {
public:
    // Constructeur et destructeur
    IntegrateurEulerCromer() = default;
    virtual ~IntegrateurEulerCromer() override = default;
    
    // Implémentation de la méthode d'intégration d'Euler-Cromer
    virtual void integre(ObjetMobile& objet, double t, double dt) const override;
};
