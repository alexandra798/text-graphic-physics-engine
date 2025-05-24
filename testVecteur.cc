#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include "Vecteur.h"

using namespace std;

int main() {
    try {
        // un vecteur en 3D :
        Vecteur vect1(1.0, 2.0, -0.1);

        // un autre vecteur en 3D
        Vecteur vect2(2.6, 3.5, 4.1);

        Vecteur vect3(vect1);  // copie de V1
        Vecteur vect4(4);      // le vecteur nul en 4D

        // Test des opérateurs d'affichage (<<) et de comparaison (== et !=)
        cout << "Vecteur 1 : " << vect1 << endl;
        cout << "Vecteur 2 : " << vect2 << endl;
        cout << "Vecteur 3 : " << vect3 << endl;
        cout << "Vecteur 4 : " << vect4 << endl;

        cout << "Le vecteur 1 est ";
        if (vect1 == vect2) {
            cout << "égal au";
        } else {
            cout << "différent du";
        }
        cout << " vecteur 2," << endl << "et est ";
        if (vect1 != vect3) {
            cout << "différent du";
        } else {
            cout << "égal au";
        }
        cout << " vecteur 3." << endl;

        // Tests des opérations algébriques
        cout << "\n=== Tests des opérateurs algébriques ===" << endl;

        // Addition (+, +=)
        cout << "\nAddition:" << endl;
        cout << "vect1 + vect2 = " << (vect1 + vect2) << endl;
        cout << "vect2 + vect1 = " << (vect2 + vect1) << " (commutativité)" << endl;
        
        Vecteur temp = vect1;
        temp += vect2;
        cout << "vect1 += vect2 donne " << temp << endl;

        // Soustraction (-, -=)
        cout << "\nSoustraction:" << endl;
        cout << "vect1 - vect2 = " << (vect1 - vect2) << endl;
        cout << "vect2 - vect1 = " << (vect2 - vect1) << endl;
        
        temp = vect1;
        temp -= vect2;
        cout << "vect1 -= vect2 donne " << temp << endl;

        // Opposé (-)
        cout << "\nOpposé:" << endl;
        cout << "-vect1 = " << -vect1 << endl;

        // Multiplication par un scalaire (*, *=)
        cout << "\nMultiplication par un scalaire:" << endl;
        double scalaire = 2.5;
        cout << "vect1 * " << scalaire << " = " << (vect1 * scalaire) << endl;
        cout << scalaire << " * vect1 = " << (scalaire * vect1) << " (commutativité)" << endl;
        
        temp = vect1;
        temp *= scalaire;
        cout << "vect1 *= " << scalaire << " donne " << temp << endl;

        // Produit scalaire (*)
        cout << "\nProduit scalaire:" << endl;
        cout << "vect1 * vect2 = " << (vect1 * vect2) << endl;
        cout << "vect2 * vect1 = " << (vect2 * vect1) << " (commutativité)" << endl;

        // Produit vectoriel (^, ^=)
        cout << "\nProduit vectoriel:" << endl;
        cout << "(vect1 ^ vect2) = " << (vect1 ^ vect2) << endl;
        cout << "(vect2 ^ vect1) = " << (vect2 ^ vect1) << endl;
        
        temp = vect1;
        temp ^= vect2;
        cout << "vect1 ^= vect2 donne " << temp << endl;

        // Vecteur unitaire (~)
        cout << "\nVecteur unitaire:" << endl;
        cout << "~vect1 = " << ~vect1 << endl;
        cout << "norme(~vect1) = " << (~vect1).norme() << " (doit être proche de 1)" << endl;

        // Norme et norme au carré
        cout << "\nNorme:" << endl;
        cout << "norme2(vect1) = " << vect1.norme2() << endl;
        cout << "norme(vect1) = " << vect1.norme() << endl;

    } catch (const exception &e) {
        cerr << "Erreur : " << e.what() << endl;
    }
    return 0;
}