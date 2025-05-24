#include "ChampCompose.h"
#include "ObjetPhysique.h"
#include <stdexcept>

void ChampCompose::ajouter_champ(std::shared_ptr<ChampForces> champ) {
    if (!champ) {
        throw std::runtime_error("Impossible d'ajouter un champ de force vide");
    }
    champs_composants.push_back(champ);
}

Vecteur ChampCompose::force(const ObjetPhysique& objet, double temps) const {
    if (champs_composants.empty()) {
        // S'il n'y a pas de champs de force, retourner un vecteur nul
        return Vecteur(objet.position().memeDimension(Vecteur()) ?
                       objet.position().memeDimension(Vecteur()) : 3);
    }
    
    // Calculer la force du premier champ, comme valeur initiale
    Vecteur force_totale = champs_composants[0]->force(objet, temps);
    
    // Accumuler les forces des champs restants
    for (size_t i = 1; i < champs_composants.size(); ++i) {
        force_totale += champs_composants[i]->force(objet, temps);
    }
    
    return force_totale;
}