#pragma once
#include "ObjetMobile.h"
#include "ChampForces.h"
#include "Contrainte.h"
#include <memory>
#include <iostream>
#include <stdexcept>

class ObjetPhysique : public ObjetMobile {
private:

    std::shared_ptr<ChampForces> champ;    // Champ de forces
    std::shared_ptr<Contrainte> contrainte; // Contrainte
    double masse;

public:
    // Constructeur
    ObjetPhysique();
    // Modifié dans ObjetPhysique.h en :
    ObjetPhysique(const Vecteur& param, const Vecteur& deriv, double m = 1.0,
              std::shared_ptr<ChampForces> ch = nullptr,
              std::shared_ptr<Contrainte> con = nullptr);  // Supprimer la partie implémentation, ne conserver que la déclaration
    

    // Destructeur
    virtual ~ObjetPhysique() = default;


    // Accesseur
    
    const ChampForces& getChampForces() const;
    const Contrainte& getContrainte() const;
    
    // Modificateur

    void setChampForces(std::shared_ptr<ChampForces> ch);
    void setContrainte(std::shared_ptr<Contrainte> con);

    
    // Calcule la force agissant sur l'objet
    Vecteur force(double temps = 0) const;
    
    
    // Obtient la position et la vitesse réelles de l'objet
    Vecteur position() const;  
    Vecteur vitesse() const;

    double getMasse() const;  
    
    // Fonction virtuelle héritée d'ObjetMobile, calcule l'équation du mouvement
    virtual Vecteur evolution(double temps) const override;

    
    double energieCinetique() const {
        // Calcule E = 1/2 * m * v^2
        return 0.5 * getMasse() * vitesse().norme2();
    }
    
    
    // Surcharge de l'opérateur de sortie
    friend std::ostream& operator<<(std::ostream& os, const ObjetPhysique& obj);


};