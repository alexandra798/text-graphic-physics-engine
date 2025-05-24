#pragma once
#include "Dessinable.h"
#include "ObjetPhysique.h"
#include "ChampForces.h"
#include "Contrainte.h"
#include "Integrateur.h"
#include "SupportADessin.h"
#include <vector>
#include <memory>
#include <iostream>


class SupportADessin;

/**
 * @class Systeme
 * @brief Représente l'ensemble du système physique
 * * Contient un ensemble d'objets physiques, un ensemble de contraintes, 
 * un ensemble de champs de forces et un intégrateur
 */
class Systeme : public Dessinable {
private:
    // Utilisation de pointeurs intelligents pour gérer les objets
    std::vector<std::unique_ptr<ObjetPhysique>> objets;
    std::vector<std::shared_ptr<Contrainte>> contraintes;
    std::vector<std::shared_ptr<ChampForces>> champs;
    std::unique_ptr<Integrateur> integrateur;
    double temps_actuel;

public:
    // Constructeur par défaut
    Systeme();
    
    // Constructeur paramétré
    Systeme(std::unique_ptr<Integrateur> integ);
    
    // Destructeur
    virtual ~Systeme() = default;
    
    // Supprimer la construction par copie et l'affectation (car contient unique_ptr)
    Systeme(const Systeme&) = delete;
    Systeme& operator=(const Systeme&) = delete;
    
    // Construction par déplacement et affectation par déplacement
    Systeme(Systeme&&) = default;
    Systeme& operator=(Systeme&&) = default;
    
    // Ajouter un objet au système
    void ajouter_objet(std::unique_ptr<ObjetPhysique> objet);
    
    // Ajouter une contrainte au système
    void ajouter_contrainte(std::shared_ptr<Contrainte> contrainte);
    
    // Ajouter un champ de forces au système
    void ajouter_champ_forces(std::shared_ptr<ChampForces> champ);
    
    // Définir l'intégrateur
    void set_integrateur(std::unique_ptr<Integrateur> integ);
    
    // Ajouter la i-ème contrainte au j-ième objet
    void ajouter_contrainte_a_objet(size_t index_contrainte, size_t index_objet);
    
    // Ajouter le i-ème champ de forces au j-ième objet
    void ajouter_champ_a_objet(size_t index_champ, size_t index_objet);
    
    // Obtenir le temps actuel
    double get_temps() const { return temps_actuel; }
    
    // Définir le temps actuel
    void set_temps(double t) { temps_actuel = t; }
    
    // Faire évoluer le système d'un pas
    void evolue(double dt);
    
    // Implémenter l'interface Dessinable
    virtual void dessine_sur(SupportADessin& support) override
    { support.dessine(*this); }
    
    // Surcharge de l'opérateur de sortie
    friend std::ostream& operator<<(std::ostream& os, const Systeme& sys);
    
    // Obtenir le nombre d'objets (pour l'affichage)
    size_t nombre_objets() const { return objets.size(); }
    size_t nombre_contraintes() const { return contraintes.size(); }
    size_t nombre_champs() const { return champs.size(); }
    
    // Accesseurs (lecture seule)
    const ObjetPhysique& get_objet(size_t i) const;
    const Contrainte& get_contrainte(size_t i) const;
    const ChampForces& get_champ(size_t i) const;
};