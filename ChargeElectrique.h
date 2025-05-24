#pragma once
#include "PointMateriel.h"
#include "SupportADessin.h"
#include <memory>
#include "ChampForces.h"
#include "Contrainte.h"

class ChargeElectrique : public PointMateriel {
private:
    double charge;
public:
    // Constructeur
    ChargeElectrique();
    ChargeElectrique(const Vecteur& position, const Vecteur& vitesse,
                 double masse,
                 double charge,  // Ajouter le paramètre de charge
                 std::shared_ptr<ChampForces> champ = nullptr,
                 std::shared_ptr<Contrainte> contrainte = nullptr);

    // Obtenir la charge électrique
    double getCharge() const;
    
    // Définir la charge électrique
    void setCharge(double q);
    
    // Calculer l'équation du mouvement (implémentation de la fonction virtuelle dans ObjetMobile)
    virtual Vecteur evolution(double temps) const override;
    
    // Implémenter la méthode de dessin de Dessinable
    virtual void dessine_sur(SupportADessin& support) override {
        support.dessine(*this); }
    
    // Surcharge de l'opérateur de sortie
    friend std::ostream& operator<<(std::ostream& os, const ChargeElectrique& pm);
};