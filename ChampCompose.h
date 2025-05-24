#pragma once
#include "ChampForces.h"
#include <vector>
#include <memory>

class ChampCompose : public ChampForces {
private:
    std::vector<std::shared_ptr<ChampForces>> champs_composants;
    
public:
    // Constructeur
    ChampCompose() = default;
    
    // Ajouter un champ de force à la composition
    void ajouter_champ(std::shared_ptr<ChampForces> champ);
    
    // Calculer la force résultante de tous les champs
    Vecteur force(const ObjetPhysique& objet, double temps) const override;
    
    // Obtenir le nombre de champs dans la composition
    size_t nombre_champs() const { return champs_composants.size(); }
};