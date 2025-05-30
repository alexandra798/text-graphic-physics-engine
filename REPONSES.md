

## [Question P1.1] Comment représentez-vous ces vecteurs ? Comment sont-ils organisés : quels attributs ? quelles méthodes ? quels droits d'accès ?

**Attributs (privés) :**

- `std::vector<double> coords` : Conteneur dynamique stockant les coordonnées du vecteur
- Cet attribut est **privé** pour assurer l'encapsulation et protéger l'intégrité des données

**Méthodes publiques :**

- **Constructeurs** : par défaut, avec dimension, avec coordonnées 3D, avec liste d'initialisation
- **Opérateurs arithmétiques** : `+`, `-`, `*` (scalaire et produit scalaire), `^` (produit vectoriel)
- **Opérateurs de comparaison** : `==`, `!=`
- **Accès aux éléments** : `operator[]`, `at()` avec vérification des bornes
- **Propriétés** : `norme()`, `norme2()`, `memeDimension()`
- **Utilitaires** : `augmente()`, `set_coord()`

Cette organisation respecte le principe d'encapsulation en cachant l'implémentation interne tout en offrant une interface riche et intuitive.

## [Question P1.2] Quel choix avez vous fait pour les opérations entre vecteurs de dimensions différentes ?

J'ai choisi l'approche **restrictive** : les opérations entre vecteurs de dimensions différentes lèvent une exception `std::runtime_error`.

**Justification :**

- **Sécurité mathématique** : Évite les opérations mal définies
- **Clarté du code** : Force l'utilisateur à être explicite sur ses intentions
- **Détection précoce d'erreurs** : Les erreurs de dimension sont détectées immédiatement
- **Cohérence** : Comportement uniforme pour toutes les opérations

## [Question P4.1] Avez-vous ajouté un constructeur de copie ? Pourquoi ?

**Non, je n'ai pas ajouté de constructeur de copie explicite** car j'utilise `= default`.

**Justification :**

- `std::vector<double>` gère déjà correctement la copie profonde
- Le constructeur de copie par défaut généré par le compilateur est suffisant
- Cela respecte la **règle de zéro** : si aucune gestion manuelle de ressources n'est nécessaire, utiliser les versions par défaut
- Plus maintenable et moins sujet aux erreurs

## [Question P4.2] Constructeur par coordonnées sphériques

**a) Implications au niveau des attributs :** Aucune modification des attributs ne serait nécessaire. Le constructeur convertirait simplement les coordonnées sphériques $(r, \theta, \phi)$ en coordonnées cartésiennes selon : $$x = r \sin\theta \cos\phi$$ $$y = r \sin\theta \sin\phi$$
 $$z = r \cos\theta$$

**b) Difficulté majeure en C++ :** **Ambiguïté de surcharge** : impossible de distinguer entre :

- `Vecteur(double r, double theta, double phi)` // sphériques
- `Vecteur(double x, double y, double z)` // cartésiennes

Les deux signatures sont identiques pour le compilateur (trois `double`), rendant la résolution impossible.

## [Question P4.3] Quels opérateurs avez vous introduits ?

**Opérateurs arithmétiques :**

- `operator+`, `operator+=` (addition)
- `operator-`, `operator-=` (soustraction)
- `operator-` unaire (opposé)
- `operator*`, `operator*=` (multiplication scalaire)
- `operator*` (produit scalaire)
- `operator^`, `operator^=` (produit vectoriel)
- `operator~` (vecteur unitaire)

**Opérateurs de comparaison :**

- `operator==`, `operator!=`

**Opérateurs d'accès :**

- `operator[]` (accès direct)

**Opérateur d'affichage :**

- `operator<<` (fonction amie)

## [Question P6.1] Comment avez vous conçu votre classe `Integrateur` ?

**Conception :**

- **Classe abstraite** avec méthode virtuelle pure `integre()`
- **Pas d'attributs** : un intégrateur est un algorithme stateless
- **Interface minimale** : une seule méthode `integre(ObjetMobile& objet, double t, double dt)`
- **Destructeur virtuel** pour assurer la destruction correcte via polymorphisme

**Justification :** Cette conception implémente le **patron Stratégie**, permettant de changer d'algorithme d'intégration à l'exécution tout en respectant le principe ouvert/fermé.

## [Question P6.2] Relation entre `Integrateur` et `IntegrateurEulerCromer`

**Relation d'héritage** : `IntegrateurEulerCromer` hérite de `Integrateur`

- `Integrateur` définit l'interface abstraite
- `IntegrateurEulerCromer` implémente l'algorithme spécifique
- Permet le **polymorphisme** : utilisation via pointeurs/références `Integrateur*`
- Facilite l'**extensibilité** : ajout de nouveaux intégrateurs sans modifier le code existant

## [Question P7.1] Comment avez vous traduit le fait que `GravitationConstante` est un champ de force ?

`GravitationConstante` **hérite de `ChampForces`** et implémente la méthode virtuelle pure `force()`.

**Implémentation :**

```cpp
Vecteur GravitationConstante::force(const ObjetPhysique& objet, double) const {
    return gravitation * objet.getMasse(); // F = m * g
}
```

Cette conception respecte le **principe de substitution de Liskov** : `GravitationConstante` peut être utilisée partout où `ChampForces` est attendu.

## [Question P7.2] Comment les points matériels deviennent-ils des objets physiques ?

**Hiérarchie d'héritage :** `PointMateriel` hérite de `ObjetPhysique` qui hérite de `ObjetMobile`

**Traduction :**

- `ObjetMobile` : paramètres génériques et équation d'évolution
- `ObjetPhysique` : ajout de masse, champs de forces, contraintes
- `PointMateriel` : spécialisation pour les particules ponctuelles

Cette architecture respecte le **principe de responsabilité unique** en séparant les préoccupations mathématiques, physiques et géométriques.

## [Question P8.1.1] En termes de POO, quelle est donc la nature de la méthode dessine_sur() ?

**Méthode virtuelle pure** dans la classe abstraite `Dessinable`.

C'est une implémentation du **patron Visiteur** permettant le double dispatch : la méthode appropriée est sélectionnée selon le type concret de l'objet dessinable ET du support de dessin.

## [Question P8.1.2] A quoi faut-il faire attention pour les classes contenant des pointeurs ? Quelle(s) solution(s) est/sont envisageable(s) ?

**Problèmes potentiels :**

- Fuites mémoire
- Double suppression
- Pointeurs pendants
- Copies superficielles

**Solutions adoptées :**

- **Pointeurs intelligents** : `std::shared_ptr`, `std::unique_ptr`
- **Respect de la règle de cinq** quand nécessaire
- **Principe RAII** : acquisition des ressources à l'initialisation
- **Sémantique de déplacement** pour l'efficacité

## [Question P8.2] Comment représentez vous la classe `Systeme` ? Expliquez votre conception (attributs, interface, ...).

**Attributs privés :**

- `std::vector<std::unique_ptr<ObjetPhysique>> objets`
- `std::vector<std::shared_ptr<ChampForces>> champs`
- `std::vector<std::shared_ptr<Contrainte>> contraintes`
- `std::unique_ptr<Integrateur> integrateur`
- `double temps_actuel`

**Interface publique :**

- **Ajout de composants** : `ajouter_objet()`, `ajouter_champ_forces()`, `ajouter_contrainte()`
- **Association** : `ajouter_champ_a_objet()`, `ajouter_contrainte_a_objet()`
- **Simulation** : `evolue(double dt)`
- **Accès** : getters en lecture seule
- **Affichage** : `dessine_sur()`, `operator<<`

**Justification de conception :**

- `unique_ptr` pour les objets : propriété exclusive
- `shared_ptr` pour champs/contraintes : partage entre objets
- Séparation claire entre simulation et affichage
- Interface cohérente et sûre

## [Question P12.1] Où cela s'intègre-t-il dans votre projet/conception ? Quels changements cela engendre-t-il (ou pas) ?(Intégration de Runge-Kutta 4)

**Intégration dans l'architecture :** L'`IntegrateurRungeKutta4` s'intègre parfaitement dans l'architecture existante :

- **Hérite de `Integrateur`** : même interface que Euler-Cromer
- **Polymorphisme** : changement transparent via `set_integrateur()`
- **Aucun changement architectural** requis

**Utilisation :**

```cpp
// Euler-Cromer (rapide, moins précis)
systeme.set_integrateur(std::make_unique<IntegrateurEulerCromer>());

// Runge-Kutta 4 (plus lent, plus précis)
systeme.set_integrateur(std::make_unique<IntegrateurRungeKutta4>());
```

**Avantages de cette conception :**

- **Modularité** : ajout sans modification du code existant
- **Flexibilité** : choix de l'intégrateur selon les besoins
- **Comparaison** : facilite l'évaluation des différentes méthodes
- **Extensibilité** : ajout facile d'autres intégrateurs (Newmark, Verlet, etc.)

Cette architecture démontre la puissance de la conception orientée objet : l'ajout de nouvelles fonctionnalités se fait sans perturbation du système existant, respectant parfaitement le principe ouvert/fermé.