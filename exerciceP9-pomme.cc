#include <iostream>
#include <iomanip>
#include <memory>
#include "Systeme.h"
#include "PointMateriel.h"
#include "ChampNewtonien.h"
#include "Libre.h"
#include "IntegrateurEulerCromer.h"
#include "TextViewer.h"

int main() {
    // Constantes physiques
    const double RAYON_TERRE = 6.371e6;        // Rayon de la Terre (mètres)
    const double MASSE_TERRE = 5.972e24;       // Masse de la Terre (kilogrammes)
    const double MASSE_POMME = 0.1;            // Masse de la pomme (kilogrammes)
    const double ALTITUDE_INITIALE = 10.0;     // Altitude initiale (mètres)
    const double DT = 1e-3;                    // Pas de temps (secondes)
    
    // Créer le système et configurer l'intégrateur Euler-Cromer
    Systeme systeme(std::make_unique<IntegrateurEulerCromer>());
    
    // Créer la Terre (comme corps central, à l'origine)
    auto terre = std::make_unique<PointMateriel>(
        Vecteur(0.0, 0.0, 0.0),                // Position de la Terre (origine)
        Vecteur(0.0, 0.0, 0.0),                // Vitesse de la Terre (immobile)
        MASSE_TERRE                             // Masse de la Terre
    );
    
    // Ajouter la Terre au système (nécessite de sauvegarder la référence pour créer le champ de force)
    // Note : Nous devons créer un shared_ptr avant de l'ajouter au système
    auto terre_shared = std::make_shared<PointMateriel>(
        Vecteur(0.0, 0.0, 0.0),
        Vecteur(0.0, 0.0, 0.0),
        MASSE_TERRE
    );
    
    // Créer un champ gravitationnel newtonien (la Terre comme centre de gravité)
    auto champ_gravite = std::make_shared<ChampNewtonien>(terre_shared);
    
    // Créer une contrainte libre
    auto contrainte_libre = std::make_shared<Libre>();
    
    // Ajouter le champ de force et la contrainte au système
    systeme.ajouter_champ_forces(champ_gravite);
    systeme.ajouter_contrainte(contrainte_libre);
    
    // Créer la pomme (située à 10 mètres au-dessus de la surface de la Terre)
    auto pomme = std::make_unique<PointMateriel>(
        Vecteur(0.0, RAYON_TERRE + ALTITUDE_INITIALE, 0.0),  // Position initiale
        Vecteur(0.0, 0.0, 0.0),                               // Vitesse initiale (immobile)
        MASSE_POMME                                           // Masse de la pomme
    );
    
    // Ajouter la Terre et la pomme au système
    systeme.ajouter_objet(std::make_unique<PointMateriel>(*terre_shared));
    systeme.ajouter_objet(std::move(pomme));
    
    // Définir le champ de force et la contrainte pour la pomme (Terre index 0, pomme index 1)
    systeme.ajouter_champ_a_objet(0, 1);    // Appliquer le champ de force 0 à l'objet 1 (pomme)
    systeme.ajouter_contrainte_a_objet(0, 1); // Appliquer la contrainte 0 à l'objet 1 (pomme)
    systeme.ajouter_contrainte_a_objet(0, 0); // Appliquer la contrainte 0 à l'objet 0 (Terre, bien qu'elle ne bouge pas)
    
    // Créer l'afficheur texte
    TextViewer viewer(std::cout);
    
    // Configuration du format de sortie
    std::cout << std::fixed << std::setprecision(4);
    
    // Première partie : Afficher l'altitude des 100 premiers pas
    std::cout << "=== Simulation détaillée des 100 premiers pas ===" << std::endl;
    for (int i = 0; i <= 100; ++i) {
        // Obtenir l'état actuel de la pomme
        const ObjetPhysique& pomme_ref = systeme.get_objet(1);
        Vecteur pos = pomme_ref.position();
        double altitude = pos.norme() - RAYON_TERRE;
        
        // Afficher le temps et l'altitude
        std::cout << systeme.get_temps() << "  " << std::setprecision(6) << altitude << std::endl;
        
        // Effectuer un pas d'intégration (sauf pour la dernière fois)
        if (i < 100) {
            systeme.evolue(DT);
        }
    }
    
    std::cout << std::endl;
    std::cout << std::endl;
    
    // Réinitialiser le système pour le test de la deuxième partie
    std::cout << "=== Réinitialisation du système pour le test de la deuxième partie ===" << std::endl;
    
    // Créer un nouveau système
    Systeme systeme2(std::make_unique<IntegrateurEulerCromer>());
    
    // Recréer tous les composants
    auto terre_shared2 = std::make_shared<PointMateriel>(
        Vecteur(0.0, 0.0, 0.0),
        Vecteur(0.0, 0.0, 0.0),
        MASSE_TERRE
    );
    
    auto champ_gravite2 = std::make_shared<ChampNewtonien>(terre_shared2);
    auto contrainte_libre2 = std::make_shared<Libre>();
    
    systeme2.ajouter_champ_forces(champ_gravite2);
    systeme2.ajouter_contrainte(contrainte_libre2);
    
    auto pomme2 = std::make_unique<PointMateriel>(
        Vecteur(0.0, RAYON_TERRE + ALTITUDE_INITIALE, 0.0),
        Vecteur(0.0, 0.0, 0.0),
        MASSE_POMME
    );
    
    systeme2.ajouter_objet(std::make_unique<PointMateriel>(*terre_shared2));
    systeme2.ajouter_objet(std::move(pomme2));
    
    systeme2.ajouter_champ_a_objet(0, 1);
    systeme2.ajouter_contrainte_a_objet(0, 1);
    systeme2.ajouter_contrainte_a_objet(0, 0);
    
    // Deuxième partie : Afficher pendant les 1.4 premières secondes, une sortie toutes les 0.1 secondes
    std::cout << std::setprecision(4);
    const int STEPS_PER_OUTPUT = 100;  // Sortie tous les 100 pas (0.1 seconde)
    const int TOTAL_OUTPUTS = 15;      // Total de 15 sorties (de 0 à 1.4 secondes)
    
    for (int output = 0; output < TOTAL_OUTPUTS; ++output) {
        // Obtenir l'état actuel de la pomme
        const ObjetPhysique& pomme_ref2 = systeme2.get_objet(1);
        Vecteur pos = pomme_ref2.position();
        double altitude = pos.norme() - RAYON_TERRE;
        
        // Afficher le temps et l'altitude
        std::cout << systeme2.get_temps() << "  " << std::setprecision(6) << altitude << std::endl;
        
        // Effectuer 100 pas d'intégration (sauf pour la dernière fois)
        if (output < TOTAL_OUTPUTS - 1) {
            for (int step = 0; step < STEPS_PER_OUTPUT; ++step) {
                systeme2.evolue(DT);
            }
        }
    }
    
    std::cout << std::endl;
    std::cout << "=== Utilisation de TextViewer pour afficher l'état final du système ===" << std::endl;
    
    // Utiliser TextViewer pour afficher l'état du système
    systeme2.dessine_sur(viewer);
    
    std::cout << std::endl;
    std::cout << "=== Utilisation de la sortie standard pour afficher l'état final du système ===" << std::endl;
    
    // Utiliser l'opérateur de sortie standard pour afficher l'état du système
    std::cout << systeme2 << std::endl;
    
    return 0;
}