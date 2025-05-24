#include "Systeme.h"
#include "IntegrateurEulerCromer.h"
#include "PointMateriel.h"
#include "ChargeElectrique.h"
#include "ChampNewtonien.h"
#include "GravitationConstante.h"
#include "Libre.h"
#include <stdexcept>
#include <iomanip>

// Constructeur par défaut
Systeme::Systeme() 
    : integrateur(std::make_unique<IntegrateurEulerCromer>()),temps_actuel(0.0) {}

// Constructeur avec intégrateur
Systeme::Systeme(std::unique_ptr<Integrateur> integ)
    : integrateur(std::move(integ)), temps_actuel(0.0) {
    if (!integrateur) {
        throw std::runtime_error("L'intégrateur ne peut pas être nul");
    }
}

// Ajouter un objet
void Systeme::ajouter_objet(std::unique_ptr<ObjetPhysique> objet) {
    if (!objet) {
        throw std::runtime_error("Impossible d'ajouter un objet nul");
    }
    objets.push_back(std::move(objet));
}

// Ajouter une contrainte
void Systeme::ajouter_contrainte(std::shared_ptr<Contrainte> contrainte) {
    if (!contrainte) {
        throw std::runtime_error("Impossible d'ajouter une contrainte nulle");
    }
    contraintes.push_back(contrainte);
}

// Ajouter un champ de forces
void Systeme::ajouter_champ_forces(std::shared_ptr<ChampForces> champ) {
    if (!champ) {
        throw std::runtime_error("Impossible d'ajouter un champ de forces nul");
    }
    champs.push_back(champ);
}

// Définir l'intégrateur
void Systeme::set_integrateur(std::unique_ptr<Integrateur> integ) {
    if (!integ) {
        throw std::runtime_error("L'intégrateur ne peut pas être nul");
    }
    integrateur = std::move(integ);
}

// Ajouter une contrainte à un objet
void Systeme::ajouter_contrainte_a_objet(size_t index_contrainte, size_t index_objet) {
    if (index_contrainte >= contraintes.size()) {
        throw std::out_of_range("Indice de contrainte hors limites");
    }
    if (index_objet >= objets.size()) {
        throw std::out_of_range("Indice d'objet hors limites");
    }
    objets[index_objet]->setContrainte(contraintes[index_contrainte]);
}

// Ajouter un champ de forces à un objet
void Systeme::ajouter_champ_a_objet(size_t index_champ, size_t index_objet) {
    if (index_champ >= champs.size()) {
        throw std::out_of_range("Indice de champ de forces hors limites");
    }
    if (index_objet >= objets.size()) {
        throw std::out_of_range("Indice d'objet hors limites");
    }
    objets[index_objet]->setChampForces(champs[index_champ]);
}

// Évolution du système
void Systeme::evolue(double dt) {
    if (!integrateur) {
        throw std::runtime_error("Aucun intégrateur n'est défini");
    }
    
    // Intégrer chaque objet
    for (auto& objet : objets) {
        integrateur->integre(*objet, temps_actuel, dt);
    }
    
    // Mettre à jour le temps
    temps_actuel += dt;
}

// Accesseur
const ObjetPhysique& Systeme::get_objet(size_t i) const {
    if (i >= objets.size()) {
        throw std::out_of_range("Indice d'objet hors limites");
    }
    return *objets[i];
}

const Contrainte& Systeme::get_contrainte(size_t i) const {
    if (i >= contraintes.size()) {
        throw std::out_of_range("Indice de contrainte hors limites");
    }
    return *contraintes[i];
}

const ChampForces& Systeme::get_champ(size_t i) const {
    if (i >= champs.size()) {
        throw std::out_of_range("Indice de champ de forces hors limites");
    }
    return *champs[i];
}

// Opérateur de sortie
std::ostream& operator<<(std::ostream& os, const Systeme& sys) {
    os << "Système : à t = " << sys.temps_actuel << " :" << std::endl;
    
    // Afficher tous les objets
    for (size_t i = 0; i < sys.objets.size(); ++i) {
        os << "Objet n° " << (i + 1) << " : ";
        
        // Afficher différentes étiquettes selon le type d'objet
        if (dynamic_cast<const PointMateriel*>(sys.objets[i].get())) {
            os << "Point Matériel :" << std::endl;
        } else if (dynamic_cast<const ChargeElectrique*>(sys.objets[i].get())) {
            os << "Charge Électrique :" << std::endl;
        } else {
            os << "Objet Physique :" << std::endl;
        }
        
        // Afficher les paramètres
        os << sys.objets[i]->getParametres() << " # paramètre" << std::endl;
        os << sys.objets[i]->getDeriveeParametres() << " # vitesse" << std::endl;
        os << sys.objets[i]->position() << " # position physique" << std::endl;
        os << sys.objets[i]->vitesse() << " # vitesse physique" << std::endl;
        os << sys.objets[i]->getMasse() << " # masse" << std::endl;
        
        // Afficher les informations de la contrainte
        os << "Contrainte : type "; // Modifié pour la clarté
        if (dynamic_cast<const Libre*>(&sys.objets[i]->getContrainte())) {
            os << "Libre";
        } else {
            os << "Inconnue";
        }
        os << std::endl;
        
        if (i < sys.objets.size() - 1) {
            os << std::endl;
        }
    }
    
    // Afficher tous les champs de forces
    if (!sys.champs.empty()) {
        os << std::endl;
        for (size_t i = 0; i < sys.champs.size(); ++i) {
            os << "Champ n° " << (i + 1) << " : ";
            
            // Afficher différentes informations selon le type de champ de forces
            if (auto cn = dynamic_cast<const ChampNewtonien*>(sys.champs[i].get())) {
                os << "champ newtonien, centre : " << cn->getCentre().position() 
                   << ", masse : " << cn->getCentre().getMasse();
            } else if (auto gc = dynamic_cast<const GravitationConstante*>(sys.champs[i].get())) {
                os << "gravitation constante : " << *gc;
            } else {
                os << "champ inconnu";
            }
            os << std::endl;
        }
    }
    
    // Afficher toutes les contraintes
    if (!sys.contraintes.empty()) {
        os << std::endl;
        for (size_t i = 0; i < sys.contraintes.size(); ++i) {
            os << "Contrainte n° " << (i + 1) << " : type "; // Modifié pour la clarté
            if (dynamic_cast<const Libre*>(sys.contraintes[i].get())) {
                os << "Libre";
            } else {
                os << "Inconnue";
            }
            if (i < sys.contraintes.size() - 1) {
                os << std::endl;
            }
        }
    }
    
    return os;
}