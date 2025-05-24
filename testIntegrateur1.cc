#include <iostream>
#include <memory>
#include <iomanip>
#include "PointMateriel.h"
#include "GravitationConstante.h"
#include "Libre.h"
#include "IntegrateurEulerCromer.h"

int main() {
    try {
        // Créer un champ gravitationnel (gravité constante)
        auto gravite = std::make_shared<GravitationConstante>();
        
        // Créer une contrainte de mouvement libre
        auto libre = std::make_shared<Libre>();
        
        // Créer un point matériel avec une masse de 0.127 kg
        // Position initiale (0,0,1) et vitesse (0,1,2)
        auto point = std::make_shared<PointMateriel>(
            Vecteur(0, 0, 1),    // position
            Vecteur(0, 1, 2),    // vitesse
            0.127,               // masse
            gravite,             // champ de force
            libre                // contrainte
        );
        
        // Créer un intégrateur d'Euler-Cromer avec un pas de temps de 0.01s
        IntegrateurEulerCromer integrateur;
        
        // Afficher l'état initial
        std::cout << std::fixed << std::setprecision(5);
        std::cout << "État initial :" << std::endl;
        std::cout << point->getParametres() << " # paramètre" << std::endl;
        std::cout << point->getDeriveeParametres() << " # vitesse" << std::endl;
        std::cout << std::endl;
        
        // Intégrer sur plusieurs pas de temps
        double dt = 0.01;  // Pas de temps
        double t = 0.0;    // Temps actuel
        
        // Premier pas (t = 0.01)
        t += dt;
        integrateur.integre(*point, t, dt);
        std::cout << "t = " << t << std::endl;
        std::cout << point->getParametres() << " # paramètre" << std::endl;
        std::cout << point->getDeriveeParametres() << " # vitesse" << std::endl;
        std::cout << std::endl;
        
        // Deuxième pas (t = 0.02)
        t += dt;
        integrateur.integre(*point, t, dt);
        std::cout << "t = " << t << std::endl;
        std::cout << point->getParametres() << " # paramètre" << std::endl;
        std::cout << point->getDeriveeParametres() << " # vitesse" << std::endl;
        std::cout << std::endl;
        
        // Test avec vitesse initiale nulle
        std::cout << "\nTest avec vitesse initiale nulle :" << std::endl;
        point = std::make_shared<PointMateriel>(
            Vecteur(0, 0, 1),    // position
            Vecteur(0, 0, 0),    // vitesse nulle
            0.127,               // masse
            gravite,             // champ de force
            libre                // contrainte
        );
        
        t = 0.0;
        std::cout << "État initial :" << std::endl;
        std::cout << point->getParametres() << " # paramètre" << std::endl;
        std::cout << point->getDeriveeParametres() << " # vitesse" << std::endl;
        std::cout << std::endl;
        
        // Intégrer sur quelques pas
        for (int i = 0; i < 3; ++i) {
            t += dt;
            integrateur.integre(*point, t, dt);
            std::cout << "t = " << t << std::endl;
            std::cout << point->getParametres() << " # paramètre" << std::endl;
            std::cout << point->getDeriveeParametres() << " # vitesse" << std::endl;
            std::cout << std::endl;
        }
        
        // Test avec vitesse initiale ascendante
        std::cout << "\nTest avec vitesse initiale ascendante :" << std::endl;
        point = std::make_shared<PointMateriel>(
            Vecteur(0, 0, 1),    // position
            Vecteur(0, 0, 5),    // vitesse ascendante
            0.127,               // masse
            gravite,             // champ de force
            libre                // contrainte
        );
        
        t = 0.0;
        std::cout << "État initial :" << std::endl;
        std::cout << point->getParametres() << " # paramètre" << std::endl;
        std::cout << point->getDeriveeParametres() << " # vitesse" << std::endl;
        std::cout << std::endl;
        
        // Intégrer sur quelques pas
        for (int i = 0; i < 3; ++i) {
            t += dt;
            integrateur.integre(*point, t, dt);
            std::cout << "t = " << t << std::endl;
            std::cout << point->getParametres() << " # paramètre" << std::endl;
            std::cout << point->getDeriveeParametres() << " # vitesse" << std::endl;
            std::cout << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}