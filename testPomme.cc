#include <iostream>
#include <iomanip>
#include <memory>
#include "PointMateriel.h"
#include "ChampNewtonien.h"
#include "Libre.h"
#include "IntegrateurEulerCromer.h"

int main() {
    // Constantes physiques
    const double RAYON_TERRE = 6.371e6;        // Rayon de la Terre (mètres)
    const double MASSE_TERRE = 5.972e24;       // Masse de la Terre (kilogrammes)
    const double MASSE_POMME = 0.1;            // Masse de la pomme (kilogrammes)
    const double ALTITUDE_INITIALE = 10.0;     // Altitude initiale (mètres)
    const double DT = 1e-3;                    // Pas de temps (secondes)
    
    // Créer la Terre (comme corps central, à l'origine)
    auto terre = std::make_shared<PointMateriel>(
        Vecteur(0.0, 0.0, 0.0),                // Position de la Terre (origine)
        Vecteur(0.0, 0.0, 0.0),                // Vitesse de la Terre (immobile)
        MASSE_TERRE                             // Masse de la Terre
    );
    
    // Créer un champ de gravité newtonien (la Terre comme centre de gravité)
    auto champ_gravite = std::make_shared<ChampNewtonien>(terre);
    
    // Créer une contrainte libre
    auto contrainte_libre = std::make_shared<Libre>();
    
    // Créer la pomme (située à 10 mètres au-dessus de la surface de la Terre)
    auto pomme = std::make_shared<PointMateriel>(
        Vecteur(0.0, RAYON_TERRE + ALTITUDE_INITIALE, 0.0),  // Position initiale
        Vecteur(0.0, 0.0, 0.0),                               // Vitesse initiale (immobile)
        MASSE_POMME,                                          // Masse de la pomme
        champ_gravite,                                        // Champ de gravité
        contrainte_libre                                      // Contrainte
    );
    
    // Créer un intégrateur d'Euler-Cromer
    IntegrateurEulerCromer integrateur;
    
    // Configuration du format de sortie
    std::cout << std::fixed << std::setprecision(4);
    
    // Paramètres de simulation
    double temps = 0.0;
    
    // Première partie : afficher l'altitude des 100 premiers pas
    for (int i = 0; i <= 100; ++i) {
        // Calculer l'altitude actuelle
        Vecteur pos = pomme->position();
        double altitude = pos.norme() - RAYON_TERRE;
        
        // Afficher le temps et l'altitude
        std::cout << temps << "  " << std::setprecision(6) << altitude << std::endl;
        
        // Effectuer un pas d'intégration (sauf pour le dernier)
        if (i < 100) {
            integrateur.integre(*pomme, temps, DT);
            temps += DT;
        }
    }
    
    std::cout << std::endl;
    std::cout << std::endl;
    
    // Réinitialiser la simulation
    temps = 0.0;
    std::cout << std::setprecision(4);
    
    // Recréer la pomme
    pomme = std::make_shared<PointMateriel>(
        Vecteur(0.0, RAYON_TERRE + ALTITUDE_INITIALE, 0.0),
        Vecteur(0.0, 0.0, 0.0),
        MASSE_POMME,
        champ_gravite,
        contrainte_libre
    );
    
    // Deuxième partie : afficher toutes les 0.1 secondes pendant les 1.4 premières secondes
    const int STEPS_PER_OUTPUT = 100;  // Afficher tous les 100 pas (0.1 seconde)
    const int TOTAL_OUTPUTS = 15;      // Afficher 15 fois au total (de 0 à 1.4 secondes)
    
    for (int output = 0; output < TOTAL_OUTPUTS; ++output) {
        // Calculer l'altitude actuelle
        Vecteur pos = pomme->position();
        double altitude = pos.norme() - RAYON_TERRE;
        
        // Afficher le temps et l'altitude
        std::cout << temps << "  " << std::setprecision(6) << altitude << std::endl;
        
        // Effectuer 100 pas d'intégration (sauf pour la dernière sortie)
        if (output < TOTAL_OUTPUTS - 1) {
            for (int step = 0; step < STEPS_PER_OUTPUT; ++step) {
                integrateur.integre(*pomme, temps, DT);
                temps += DT;
            }
        }
    }
    
    return 0;
}