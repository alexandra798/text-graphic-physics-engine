#include "Systeme.h"
#include "PointMateriel.h"
#include "ChampNewtonien.h"
#include "Libre.h"
#include "IntegrateurEulerCromer.h"
#include <iostream>
#include <memory>

int main() {
    // Créer le système
    Systeme systeme;
    
    // Créer la contrainte
    auto contrainte_libre = std::make_shared<Libre>();
    systeme.ajouter_contrainte(contrainte_libre);
    
    // Créer le premier objet (Terre)
    auto terre = std::make_unique<PointMateriel>(
        Vecteur(0, 0, 0),      // Position
        Vecteur(0, 0, 0),      // Vitesse
        5.972e24               // Masse (kg)
    );
    
    // Pour afficher le champ newtonien, il faut sauvegarder le pointeur partagé de la Terre
    auto terre_ptr = std::make_shared<PointMateriel>(
        Vecteur(0, 0, 0),
        Vecteur(0, 0, 0),
        5.972e24
    );
    
    // Créer le deuxième objet (satellite)
    auto satellite = std::make_unique<PointMateriel>(
        Vecteur(6.37101e6, 0, 0),  // Position (au rayon terrestre)
        Vecteur(0, 0, 0),           // Vitesse
        0.1                         // Masse (kg)
    );
    
    // Pour afficher le champ newtonien, il faut sauvegarder le pointeur partagé du satellite
    auto satellite_ptr = std::make_shared<PointMateriel>(
        Vecteur(6.37101e6, 0, 0),
        Vecteur(0, 0, 0),
        0.1
    );
    
    // Créer les champs de forces
    auto champ1 = std::make_shared<ChampNewtonien>(terre_ptr);
    auto champ2 = std::make_shared<ChampNewtonien>(satellite_ptr);
    
    // Ajouter les champs de forces au système
    systeme.ajouter_champ_forces(champ1);
    systeme.ajouter_champ_forces(champ2);
    
    // Ajouter les objets au système
    systeme.ajouter_objet(std::move(terre));
    systeme.ajouter_objet(std::move(satellite));
    
    // Définir les contraintes pour les objets
    systeme.ajouter_contrainte_a_objet(0, 0);  // La Terre utilise la contrainte libre
    systeme.ajouter_contrainte_a_objet(0, 1);  // Le satellite utilise la contrainte libre
    
    // Afficher le système
    std::cout << systeme << std::endl;
    
    return 0;
}