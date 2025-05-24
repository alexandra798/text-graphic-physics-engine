#pragma once
#include "ObjetPhysique.h"
#include "Dessinable.h"
#include "SupportADessin.h"
#include <memory>
#include "Vecteur.h"
#include "ChampForces.h"
#include "Contrainte.h"

class PointMateriel : public ObjetPhysique, public Dessinable {
public:
    // Constructeurs
    PointMateriel();
    PointMateriel(const Vecteur& position, const Vecteur& vitesse, double masse,
                  std::shared_ptr<ChampForces> champ = nullptr,
                  std::shared_ptr<Contrainte> contrainte = nullptr);

    // Destructeur
    virtual ~PointMateriel() = default;

    // Implémentation de la méthode de dessin de Dessinable
    virtual void dessine_sur(SupportADessin& support) override
    { support.dessine(*this); }

    // Ajouter des méthodes d'affichage
    void affiche() const;
    void affiche(double temps) const;

    // Opérateur de sortie
    friend std::ostream& operator<<(std::ostream& os, const PointMateriel& point);
};