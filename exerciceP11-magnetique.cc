#include <iostream>
#include <iomanip>
#include <memory>
#include "Systeme.h"
#include "ChargeElectrique.h"
#include "ChampElectromagnetique.h"
#include "FrottementFluide.h"
#include "ChampCompose.h"
#include "Libre.h"
#include "IntegrateurEulerCromer.h"
#include "TextViewer.h"

int main() {
    try {
        // Créer le système et l'intégrateur
        Systeme systeme;
        systeme.set_integrateur(std::make_unique<IntegrateurEulerCromer>());
        
        // Créer un champ électromagnétique : champ électrique nul, champ magnétique (0, 0, 0.5) T
        auto champ_em = std::make_shared<ChampElectromagnetique>(
            Vecteur(3),              // Champ électrique nul
            Vecteur(0.0, 0.0, 0.5)  // Champ magnétique 0.5 T le long de l'axe z
        );
        
        // Créer un champ de force de frottement fluide, intensité 1.33e-5 S.I.
        auto frottement = std::make_shared<FrottementFluide>(1.33e-5);
        
        // Créer un champ de force composé
        auto champ_compose = std::make_shared<ChampCompose>();
        champ_compose->ajouter_champ(champ_em);
        champ_compose->ajouter_champ(frottement);
        
        // Créer une contrainte libre
        auto contrainte_libre = std::make_shared<Libre>();
        
        // Créer une particule chargée
        auto particule = std::make_unique<ChargeElectrique>(
            Vecteur(0.0, 0.0, 0.0),      // Position (0, 0, 0)
            Vecteur(0.3, 0.0, 0.0),      // Vitesse initiale 0.3 m/s le long de l'axe x
            1.5e-4,                       // Masse 1.5e-4 kg
            2e-6,                         // Charge 2e-6 C
            champ_compose,                // Champ de force composé
            contrainte_libre              // Contrainte libre
        );
        
        // Ajouter la particule au système
        systeme.ajouter_objet(std::move(particule));
        
        // Paramètres de simulation
        double dt = 0.001;  // Pas de temps 0.001 s
        double t_max = 0.03;  // Simuler jusqu'à 0.03 s
        
        // Afficher l'en-tête du tableau
        std::cout << "t     x           y" << std::endl;
        
        // Définir la précision de sortie
        std::cout << std::fixed << std::setprecision(9);
        
        // Afficher l'état initial
        const ChargeElectrique& charge = dynamic_cast<const ChargeElectrique&>(systeme.get_objet(0));
        Vecteur pos = charge.position();
        std::cout << std::setprecision(0) << systeme.get_temps() 
                  << "     " << std::setprecision(9) << pos[0] 
                  << "           " << pos[1] << std::endl;
        
        // Lancer la simulation
        while (systeme.get_temps() < t_max) {
            // Évoluer d'un pas
            systeme.evolue(dt);
            
            // Obtenir la position
            const ChargeElectrique& charge_actuelle = dynamic_cast<const ChargeElectrique&>(systeme.get_objet(0)); // Renommé pour éviter l'occultation
            Vecteur pos_actuelle = charge_actuelle.position(); // Renommé pour éviter l'occultation
            
            // Afficher les résultats
            // Ajuster le format de sortie pour correspondre aux résultats attendus
            std::cout << std::setprecision(3) << systeme.get_temps() << " ";
            
            // Coordonnée x
            if (std::abs(pos_actuelle[0]) < 1e-9) {
                std::cout << "0";
            } else {
                std::cout << std::setprecision(9) << pos_actuelle[0];
            }
            std::cout << " ";
            
            // Coordonnée y - utiliser la notation scientifique
            if (std::abs(pos_actuelle[1]) < 1e-9) { // Comparaison à zéro
                 std::cout << std::scientific << std::setprecision(5) << pos_actuelle[1]; // Toujours utiliser la notation scientifique pour la cohérence
            } else {
                std::cout << std::scientific << std::setprecision(5) << pos_actuelle[1];
            }
            
            std::cout << std::fixed << std::endl; // Revenir à la notation fixe pour la prochaine ligne si nécessaire
        }
        
        // Vérifier : la coordonnée z est toujours nulle
        const ChargeElectrique& charge_finale = dynamic_cast<const ChargeElectrique&>(systeme.get_objet(0)); // Pour obtenir la dernière position
        std::cout << "\nVérification : coordonnée z = " << charge_finale.position()[2]
                  << " (devrait toujours être zéro)" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}