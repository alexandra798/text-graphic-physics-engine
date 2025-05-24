// IntegrateurRungeKutta4.cc
#include "IntegrateurRungeKutta4.h"

void IntegrateurRungeKutta4::integre(ObjetMobile& objet, double t, double dt) const {
    // 1. Récupérer les paramètres actuels
    Vecteur parametres_initiaux = objet.getParametres();
    Vecteur derivee_initiale = objet.getDeriveeParametres();
    
    // 2. Calcul des coefficients k1, k2, k3, k4 pour la méthode RK4
    
    // k1 : évaluation au point initial
    Vecteur k1 = objet.evolution(t);
    
    // Calcul d'un état intermédiaire pour k2 (t + dt/2, y + dt/2 * k1)
    objet.setDeriveeParametres(derivee_initiale + k1 * (dt/2));
    objet.setParametres(parametres_initiaux + derivee_initiale * (dt/2));
    
    // k2 : évaluation au point intermédiaire
    Vecteur k2 = objet.evolution(t + dt/2);
    
    // Calcul d'un état intermédiaire pour k3 (t + dt/2, y + dt/2 * k2)
    objet.setDeriveeParametres(derivee_initiale + k2 * (dt/2));
    objet.setParametres(parametres_initiaux + derivee_initiale * (dt/2) + k1 * (dt*dt/4));
    
    // k3 : évaluation au second point intermédiaire
    Vecteur k3 = objet.evolution(t + dt/2);
    
    // Calcul d'un état intermédiaire pour k4 (t + dt, y + dt * k3)
    objet.setDeriveeParametres(derivee_initiale + k3 * dt);
    objet.setParametres(parametres_initiaux + derivee_initiale * dt + k2 * (dt*dt/2));
    
    // k4 : évaluation au point final
    Vecteur k4 = objet.evolution(t + dt);
    
    // 3. Combinaison des coefficients pour obtenir la nouvelle dérivée
    Vecteur nouvelle_derivee = derivee_initiale + (k1 + k2*2 + k3*2 + k4) * (dt/6);
    
    // 4. Calcul des nouveaux paramètres
    Vecteur nouveaux_parametres = parametres_initiaux + 
                                 (derivee_initiale + nouvelle_derivee) * (dt/2);
    
    // 5. Mise à jour de l'objet
    objet.setParametres(nouveaux_parametres);
    objet.setDeriveeParametres(nouvelle_derivee);
}