#pragma once

// Déclaration anticipée
class SupportADessin;


class Dessinable {
public:
    // Destructeur virtuel
    virtual ~Dessinable() = default;
    
    // Fonction virtuelle pure, doit être implémentée dans chaque classe dérivée
    // Note : Selon les exigences du devoir, cette méthode doit être redéfinie dans chaque classe dérivée,
    // plutôt que d'être définie dans la classe de base et héritée
    virtual void dessine_sur(SupportADessin& support) = 0;
};