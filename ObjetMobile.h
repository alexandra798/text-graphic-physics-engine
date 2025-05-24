
// ObjetMobile.h
#pragma once
#include "Vecteur.h"
#include <stdexcept>




class ObjetMobile {
private:
    Vecteur parametres;         // Vecteur E (degrés de liberté)
    Vecteur derivee_parametres; // Vecteur E' (dérivée temporelle)

public:
    // Constructeurs
    ObjetMobile();
    ObjetMobile(const Vecteur& param, const Vecteur& deriv);
    virtual ~ObjetMobile() = default; // Destructeur virtuel
    

    // Accesseurs
    Vecteur getParametres() const;
    Vecteur getDeriveeParametres() const;
    
    // Modificateurs
    void setParametres(const Vecteur& param);
    void setDeriveeParametres(const Vecteur& deriv);
    
    // Méthode virtuelle pure représentant l'équation d'évolution f(t, E, E')
    virtual Vecteur evolution(double temps) const = 0;
    
    // Surcharge de l'opérateur << pour l'affichage
    friend std::ostream& operator<<(std::ostream& os, const ObjetMobile& obj);

protected:

    void checkParametres() const {
        if (parametres.norme() < 0) {
            throw std::runtime_error("Invalid parametres vector");
        }
    }
    
    void checkDeriveeParametres() const {
        if (derivee_parametres.norme() < 0) {
            throw std::runtime_error("Invalid derivee_parametres vector");
        }
    }
};