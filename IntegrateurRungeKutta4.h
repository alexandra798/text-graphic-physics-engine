// IntegrateurRungeKutta4.h
#pragma once
#include "Integrateur.h"
#include "ObjetMobile.h"

class IntegrateurRungeKutta4 : public Integrateur {
public:
    // Constructeur et destructeur
    IntegrateurRungeKutta4() = default;
    virtual ~IntegrateurRungeKutta4() override = default;
    
    // Implémentation de la méthode d'intégration de Runge-Kutta d'ordre 4
    virtual void integre(ObjetMobile& objet, double t, double dt) const override;
};