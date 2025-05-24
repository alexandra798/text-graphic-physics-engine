#pragma once
#include "ForceCentrale.h"
#include "ObjetPhysique.h"
#include "Vecteur.h"

class ChampNewtonien : public ForceCentrale {
private:
    static constexpr double G = 6.67430e-11;  // Constante gravitationnelle universelle, unité : m^3 kg^-1 s^-2
    
public:
    // Constructeur
    ChampNewtonien(std::shared_ptr<ObjetPhysique> centre);
    
    // Calculer la force gravitationnelle de Newton
    Vecteur force(const ObjetPhysique& objet, double temps) const override;
    
    // Obtenir l'objet central (pour l'affichage)
    const ObjetPhysique& getCentre() const { return *centre; }
};