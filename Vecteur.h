#pragma once
#include <initializer_list>
#include <vector>
#include <iostream>
#include <stdexcept>


class Vecteur {
private:
    std::vector<double> coords;  ///< Coordonnées du vecteur

public:
    // Constructeurs
    // Constructeur par défaut (crée un vecteur vide)
    Vecteur() = default;
    
    // Crée un vecteur nul de la dimension spécifiée
    explicit Vecteur(size_t dimension);
    
    // Crée un vecteur 3D à partir de coordonnées
    Vecteur(double x, double y, double z);
    
    // Crée un vecteur à partir d'une liste d'initialisation
    Vecteur(std::initializer_list<double> values);
    
    // Constructeur de copie
    Vecteur(const Vecteur& autre) = default;
    
    // Constructeur de déplacement
    Vecteur(Vecteur&& autre) = default;

    // Opérateurs d'affectation
    // Opérateur d'affectation par copie
    Vecteur& operator=(const Vecteur& autre) = default;
    
    // Opérateur d'affectation par déplacement
    Vecteur& operator=(Vecteur&& autre) = default;

    // Accès aux éléments
    // Accéder à l'élément par indice (sans vérification des limites)
    double& operator[](size_t index);
    
    // Accéder à l'élément par indice (sans vérification des limites, version const)
    const double& operator[](size_t index) const;
    
    // Accès sécurisé aux éléments avec vérification des limites
    double& at(size_t index);
    
    // Accès sécurisé aux éléments avec vérification des limites (version const)
    const double& at(size_t index) const;

    // Opérations sur les vecteurs
    // Vérifier si deux vecteurs ont la même dimension
    bool memeDimension(const Vecteur& autre) const;
    
    // Ajouter une nouvelle coordonnée au vecteur
    void augmente(double valeur);
    
    // Définir la valeur de la coordonnée
    void set_coord(size_t index, double valeur);

    // Opérateurs arithmétiques
    // Opérateur unaire moins
    Vecteur operator-() const;
    
    // Opérateur vecteur unitaire
    Vecteur operator~() const;
    
    // Addition de vecteurs
    Vecteur operator+(const Vecteur& autre) const;
    
    // Addition de vecteurs avec affectation
    Vecteur& operator+=(const Vecteur& autre);
    
    // Soustraction de vecteurs
    Vecteur operator-(const Vecteur& autre) const;
    
    // Soustraction de vecteurs avec affectation
    Vecteur& operator-=(const Vecteur& autre);
    
    // Multiplication par un scalaire
    Vecteur operator*(double scalaire) const;
    
    // Multiplication par un scalaire avec affectation
    Vecteur& operator*=(double scalaire);
    
    // Produit scalaire
    double operator*(const Vecteur& autre) const;
    
    // Produit vectoriel (3D uniquement)
    Vecteur operator^(const Vecteur& autre) const;
    
    // Produit vectoriel avec affectation (3D uniquement)
    Vecteur& operator^=(const Vecteur& autre);

    // Opérateurs de comparaison
    // Comparaison d'égalité
    bool operator==(const Vecteur& autre) const;
    
    // Comparaison d'inégalité
    bool operator!=(const Vecteur& autre) const;

    // Propriétés du vecteur
    // Calculer la norme au carré
    double norme2() const;
    
    // Calculer la norme
    double norme() const;

    // Fonctions amies
    // Multiplication par un scalaire (commutative)
    friend Vecteur operator*(double scalaire, const Vecteur& v);
    
    // Opérateur de flux de sortie
    friend std::ostream& operator<<(std::ostream& os, const Vecteur& v);

    // Méthodes héritées (conservées pour compatibilité)
    Vecteur addition(const Vecteur& autre) const;
    Vecteur soustraction(const Vecteur& autre) const;
    Vecteur oppose() const;
    Vecteur mult(double scalaire) const;
    double prod_scal(const Vecteur& autre) const;
    Vecteur prod_vect(const Vecteur& autre) const;
    Vecteur unitaire() const;
    void affiche() const;
    bool compare(const Vecteur& autre) const;
};