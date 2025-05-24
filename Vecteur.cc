#include "Vecteur.h"
#include <cmath>
#include <stdexcept>

// Constructeurs
Vecteur::Vecteur(size_t dimension) {
    if (dimension == 0) {
        throw std::invalid_argument("La dimension du vecteur ne peut pas être nulle");
    }
    coords.resize(dimension, 0.0);
}

Vecteur::Vecteur(double x, double y, double z) {
    coords = {x, y, z};
}

Vecteur::Vecteur(std::initializer_list<double> values) {
    if (values.size() == 0) {
        throw std::invalid_argument("Le vecteur ne peut pas être vide");
    }
    coords.assign(values.begin(), values.end());
}

// Accès aux éléments
double& Vecteur::operator[](size_t index) {
    return coords[index];
}

const double& Vecteur::operator[](size_t index) const {
    return coords[index];
}

double& Vecteur::at(size_t index) {
    if (index >= coords.size()) {
        throw std::out_of_range("Indice du vecteur hors limites");
    }
    return coords[index];
}

const double& Vecteur::at(size_t index) const {
    if (index >= coords.size()) {
        throw std::out_of_range("Indice du vecteur hors limites");
    }
    return coords[index];
}

// Opérations sur les vecteurs
bool Vecteur::memeDimension(const Vecteur& autre) const {
    return coords.size() == autre.coords.size();
}

void Vecteur::augmente(double valeur) {
    coords.push_back(valeur);
}

void Vecteur::set_coord(size_t index, double valeur) {
    at(index) = valeur;  // at() lèvera une exception si l'indice est invalide
}

// Opérateurs arithmétiques
Vecteur Vecteur::operator-() const {
    Vecteur resultat(coords.size());
    for (size_t i = 0; i < coords.size(); ++i) {
        resultat.coords[i] = -coords[i];
    }
    return resultat;
}

Vecteur Vecteur::operator~() const {
    const double n = norme();
    if (n < 1e-10) {
        throw std::runtime_error("Impossible de normaliser un vecteur nul");
    }
    return *this * (1.0 / n);
}

Vecteur Vecteur::operator+(const Vecteur& autre) const {
    if (!memeDimension(autre)) {
        throw std::runtime_error("Les dimensions des vecteurs ne correspondent pas pour l'addition");
    }
    
    Vecteur resultat(coords.size());
    for (size_t i = 0; i < coords.size(); ++i) {
        resultat.coords[i] = coords[i] + autre.coords[i];
    }
    return resultat;
}

Vecteur& Vecteur::operator+=(const Vecteur& autre) {
    if (!memeDimension(autre)) {
        throw std::runtime_error("Les dimensions des vecteurs ne correspondent pas pour l'addition");
    }
    
    for (size_t i = 0; i < coords.size(); ++i) {
        coords[i] += autre.coords[i];
    }
    return *this;
}

Vecteur Vecteur::operator-(const Vecteur& autre) const {
    if (!memeDimension(autre)) {
        throw std::runtime_error("Les dimensions des vecteurs ne correspondent pas pour la soustraction");
    }
    
    Vecteur resultat(coords.size());
    for (size_t i = 0; i < coords.size(); ++i) {
        resultat.coords[i] = coords[i] - autre.coords[i];
    }
    return resultat;
}

Vecteur& Vecteur::operator-=(const Vecteur& autre) {
    if (!memeDimension(autre)) {
        throw std::runtime_error("Les dimensions des vecteurs ne correspondent pas pour la soustraction");
    }
    
    for (size_t i = 0; i < coords.size(); ++i) {
        coords[i] -= autre.coords[i];
    }
    return *this;
}

Vecteur Vecteur::operator*(double scalaire) const {
    Vecteur resultat(coords.size());
    for (size_t i = 0; i < coords.size(); ++i) {
        resultat.coords[i] = coords[i] * scalaire;
    }
    return resultat;
}

Vecteur& Vecteur::operator*=(double scalaire) {
    for (size_t i = 0; i < coords.size(); ++i) {
        coords[i] *= scalaire;
    }
    return *this;
}

double Vecteur::operator*(const Vecteur& autre) const {
    if (!memeDimension(autre)) {
        throw std::runtime_error("Les dimensions des vecteurs ne correspondent pas pour le produit scalaire");
    }
    
    double somme = 0.0;
    for (size_t i = 0; i < coords.size(); ++i) {
        somme += coords[i] * autre.coords[i];
    }
    return somme;
}

Vecteur Vecteur::operator^(const Vecteur& autre) const {
    if (coords.size() != 3 || autre.coords.size() != 3) {
        throw std::runtime_error("Le produit vectoriel n'est défini que pour les vecteurs 3D");
    }
    
    Vecteur resultat(3);
    resultat.coords[0] = coords[1] * autre.coords[2] - coords[2] * autre.coords[1];
    resultat.coords[1] = coords[2] * autre.coords[0] - coords[0] * autre.coords[2];
    resultat.coords[2] = coords[0] * autre.coords[1] - coords[1] * autre.coords[0];
    return resultat;
}

Vecteur& Vecteur::operator^=(const Vecteur& autre) {
    *this = *this ^ autre;
    return *this;
}

// Opérateurs de comparaison
bool Vecteur::operator==(const Vecteur& autre) const {
    if (!memeDimension(autre)) {
        return false;
    }
    
    for (size_t i = 0; i < coords.size(); ++i) {
        if (std::abs(coords[i] - autre.coords[i]) > 1e-10) {
            return false;
        }
    }
    return true;
}

bool Vecteur::operator!=(const Vecteur& autre) const {
    return !(*this == autre);
}

// Propriétés du vecteur
double Vecteur::norme2() const {
    double somme = 0.0;
    for (size_t i = 0; i < coords.size(); ++i) {
        somme += coords[i] * coords[i];
    }
    return somme;
}

double Vecteur::norme() const {
    return std::sqrt(norme2());
}

// Fonctions amies
Vecteur operator*(double scalaire, const Vecteur& v) {
    return v * scalaire;
}

std::ostream& operator<<(std::ostream& os, const Vecteur& v) {
    for (size_t i = 0; i < v.coords.size(); ++i) {
        os << v.coords[i];
        if (i < v.coords.size() - 1) {
            os << " ";
        }
    }
    return os;
}

// Méthodes héritées (implémentées à l'aide d'opérateurs)
Vecteur Vecteur::addition(const Vecteur& autre) const {
    return *this + autre;
}

Vecteur Vecteur::soustraction(const Vecteur& autre) const {
    return *this - autre;
}

Vecteur Vecteur::oppose() const {
    return -(*this);
}

Vecteur Vecteur::mult(double scalaire) const {
    return *this * scalaire;
}

double Vecteur::prod_scal(const Vecteur& autre) const {
    return *this * autre;
}

Vecteur Vecteur::prod_vect(const Vecteur& autre) const {
    return *this ^ autre;
}

Vecteur Vecteur::unitaire() const {
    return ~(*this);
}

void Vecteur::affiche() const {
    std::cout << *this;
}

bool Vecteur::compare(const Vecteur& autre) const {
    return *this == autre;
}