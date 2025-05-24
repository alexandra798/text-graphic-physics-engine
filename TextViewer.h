#pragma once
#include "SupportADessin.h"
#include <iostream>
#include "PointMateriel.h"
#include "ChargeElectrique.h"
#include "Systeme.h"


class TextViewer : public SupportADessin {
private:
    std::ostream& flot;  // Référence au flux de sortie

public:
    // Constructeur, accepte une référence à un flux de sortie
    explicit TextViewer(std::ostream& os = std::cout) : flot(os) {}
    
    // Implémentation des méthodes de dessin pour divers objets
    void dessine(const PointMateriel& pm) override;
    void dessine(const ChargeElectrique& ce) override;
    void dessine(const Systeme& sys) override;
};