#include <iostream>
#include <memory>
#include "PointMateriel.h"
#include "GravitationConstante.h"
#include "Libre.h"
#include "Vecteur.h"

using namespace std;

int main() {
    try {
        // Créer un champ de gravité vertical vers le bas (0, 0, -9.81)
        auto gravite = make_shared<GravitationConstante>(Vecteur(0.0, 0.0, -9.81));
        
        // Créer une contrainte libre (aucune contrainte)
        auto libre = make_shared<Libre>();
        
        // Afficher les informations du champ de gravité
        cout << "Nous avons :" << endl;
        cout << "un champ de force :" << endl;
        cout << *gravite << endl;
        cout << endl;
        
        // Créer le premier point matériel
        // Masse : 0.1 kg
        // Position : (1, 2, 3)
        // Vitesse : (0, 0.1, 0.2)
        PointMateriel point1(
            Vecteur(1.0, 2.0, 3.0),      // position
            Vecteur(0.0, 0.1, 0.2),       // vitesse
            0.1,                          // masse
            gravite,                      // champ de force
            libre                         // contrainte
        );
        
        // Créer le deuxième point matériel
        // Masse : 2 kg
        // Position : (-1.1, 1.2, 1.3)
        // Vitesse : (0.2, 0.1, 0)
        PointMateriel point2(
            Vecteur(-1.1, 1.2, 1.3),      // position
            Vecteur(0.2, 0.1, 0.0),       // vitesse
            2.0,                          // masse
            gravite,                      // champ de force
            libre                         // contrainte
        );
        
        // Afficher les informations du premier point matériel
        cout << "un point matériel :" << endl;
        point1.affiche(0.0);  // Afficher l'état au temps t=0
        cout << endl << endl;
        
        // Afficher les informations du deuxième point matériel
        cout << "et un autre point matériel :" << endl;
        point2.affiche(0.0);  // Afficher l'état au temps t=0
        cout << endl;
        
        // Optionnel : tester plus de fonctionnalités
        cout << "\n--- Tests supplémentaires ---" << endl;
        
        // Tester le calcul de l'énergie
        cout << "\nÉnergie cinétique du premier point : " 
             << point1.energieCinetique() << " J" << endl;
        cout << "Énergie cinétique du second point : " 
             << point2.energieCinetique() << " J" << endl;
        
        // Tester la méthode evolution (accélération)
        cout << "\nAccélération du premier point : " 
             << point1.evolution(0.0) << " m/s²" << endl;
        cout << "Accélération du second point : " 
             << point2.evolution(0.0) << " m/s²" << endl;
        
        // Tester un point matériel sans champ de gravité
        cout << "\n--- Point sans champ de force ---" << endl;
        PointMateriel point3(
            Vecteur(0.0, 0.0, 0.0),       // position
            Vecteur(1.0, 0.0, 0.0),       // vitesse
            1.0                           // masse
        );
        cout << "Point matériel sans champ :" << endl;
        cout << point3 << endl;
        cout << "Force : " << point3.force(0.0) << " # (devrait être nulle)" << endl;
        
    } catch (const exception& e) {
        cerr << "Erreur : " << e.what() << endl;
        return 1;
    }
    
    return 0;
}