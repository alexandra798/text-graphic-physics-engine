// IntegrateurEulerCromer.cc
#include "IntegrateurEulerCromer.h"
#include "ObjetMobile.h"
#include "Vecteur.h"

void IntegrateurEulerCromer::integre(ObjetMobile& objet, double t, double dt) const {
    // 1. Récupérer les paramètres actuels (position, etc.)
    Vecteur parametres = objet.getParametres();
    Vecteur derivee = objet.getDeriveeParametres();
    
    // 2. Calcul de la nouvelle dérivée des paramètres (accélération)
    Vecteur nouvelle_derivee = objet.evolution(t);
    
    // 3. Mise à jour de la dérivée des paramètres (vitesse)
    // Méthode d'Euler-Cromer: on met d'abord à jour la vitesse
    derivee = derivee + nouvelle_derivee * dt;
    objet.setDeriveeParametres(derivee);
    
    // 4. Mise à jour des paramètres (position)
    // Puis on utilise cette nouvelle vitesse pour mettre à jour la position
    parametres = parametres + derivee * dt;
    objet.setParametres(parametres);
}
