#pragma once

// Déclaration anticipée
class PointMateriel;
class ChargeElectrique;
class Systeme;


class SupportADessin {
public:
    // Destructeur virtuel
    virtual ~SupportADessin() = default;
    
    // Supprimer les opérations de copie et de déplacement (selon les exigences du devoir)
    SupportADessin(const SupportADessin&) = delete;
    SupportADessin& operator=(const SupportADessin&) = delete;
    SupportADessin(SupportADessin&&) = delete;
    SupportADessin& operator=(SupportADessin&&) = delete;
    
    // Constructeur par défaut
    SupportADessin() = default;
    
    // Fonctions virtuelles pures, fournissant une méthode de dessin pour chaque type d'objet dessinable
    virtual void dessine(const PointMateriel&) = 0;
    virtual void dessine(const ChargeElectrique&) = 0;
    virtual void dessine(const Systeme&) = 0;
    // D'autres méthodes de dessin pour d'autres types peuvent être ajoutées au besoin
};