# CONCEPTION - Simulateur Physique Orienté Objet

## Vue d'ensemble de l'architecture

Ce projet implémente un simulateur physique orienté objet en C++ permettant de simuler le comportement de systèmes composés de plusieurs objets physiques soumis à diverses forces et contraintes.

## Hiérarchie des classes principales

### 1. Classes de base abstraites

#### `ObjetMobile`

- **Rôle** : Classe abstraite de base représentant tout objet ayant des paramètres d'état évoluant dans le temps

- Attributs

   :

  - `Vecteur parametres` : Vecteur d'état E (degrés de liberté)
  - `Vecteur derivee_parametres` : Dérivée temporelle E'

- Méthodes virtuelles pures

   :

  - `virtual Vecteur evolution(double temps) const = 0` : Équation d'évolution f(t,E,E')

#### `ChampForces`

- **Rôle** : Interface abstraite pour tous les champs de forces

- Méthode virtuelle pure

   :

  - `virtual Vecteur force(const ObjetPhysique& objet, double temps) const = 0`

#### `Contrainte`

- **Rôle** : Interface abstraite pour toutes les contraintes géométriques ou physiques

- Méthodes virtuelles pures

   :

  - `virtual Vecteur applique_force(...)` : Application de la contrainte aux forces
  - `virtual Vecteur position(...)` : Position dans l'espace physique
  - `virtual Vecteur vitesse(...)` : Vitesse dans l'espace physique

#### `Integrateur`

- **Rôle** : Interface pour les algorithmes d'intégration numérique

- Méthode virtuelle pure

   :

  - `virtual void integre(ObjetMobile& objet, double t, double dt) const = 0`

### 2. Classes concrètes principales

#### `ObjetPhysique` (hérite de `ObjetMobile`)

- **Rôle** : Représente un objet physique général avec masse, forces et contraintes

- Relations

   :

  - Composition avec `ChampForces` (via shared_ptr)
  - Composition avec `Contrainte` (via shared_ptr)

- Responsabilités

   :

  - Calcul des forces agissant sur l'objet
  - Gestion de la position et vitesse physiques via les contraintes
  - Implémentation de l'équation d'évolution générale

#### `PointMateriel` (hérite de `ObjetPhysique` et `Dessinable`)

- **Rôle** : Objet physique ponctuel dans l'espace 3D
- **Spécialisation** : Représentation simplifiée d'un objet sans extension spatiale

#### `ChargeElectrique` (hérite de `PointMateriel`)

- **Rôle** : Point matériel possédant une charge électrique
- **Attribut supplémentaire** : `double charge`
- **Interaction** : Réagit aux champs électromagnétiques

### 3. Hiérarchie des champs de forces

#### `GravitationConstante` (hérite de `ChampForces`)

- **Rôle** : Champ gravitationnel uniforme (g constant)

#### `ForceCentrale` (classe abstraite, hérite de `ChampForces`)

- **Rôle** : Base pour toutes les forces centrales (loi en r^-2)
- **Méthode protégée** : `quadratique_inverse()` pour le calcul de base

#### `ChampNewtonien` (hérite de `ForceCentrale`)

- **Rôle** : Force gravitationnelle newtonienne F = G*m1*m2/r²

#### `ChampElectromagnetique` (hérite de `ChampForces`)

- **Rôle** : Force de Lorentz F = q(E + v×B)

#### `FrottementFluide` (hérite de `ChampForces`)

- **Rôle** : Force de frottement proportionnelle à la vitesse

#### `ChampCompose` (hérite de `ChampForces`)

- **Rôle** : Composition de plusieurs champs de forces
- **Pattern** : Composite pour combiner multiple forces

### 4. Contraintes

#### `Libre` (hérite de `Contrainte`)

- **Rôle** : Mouvement libre sans contrainte géométrique
- **Comportement** : Position = paramètres, vitesse = dérivée des paramètres

### 5. Intégrateurs numériques

#### `IntegrateurEulerCromer` (hérite de `Integrateur`)

- **Algorithme** : Méthode d'Euler-Cromer (semi-implicite)
- **Avantages** : Simple, stable pour les oscillateurs

#### `IntegrateurRungeKutta4` (hérite de `Integrateur`)

- **Algorithme** : Runge-Kutta d'ordre 4
- **Avantages** : Précision élevée, adapté aux systèmes complexes

### 6. Système et affichage

#### `Systeme` (hérite de `Dessinable`)

- **Rôle** : Conteneur principal gérant tous les objets, forces et contraintes

- Responsabilités

   :

  - Gestion des collections d'objets, champs et contraintes
  - Évolution temporelle du système complet
  - Coordination entre tous les composants

#### Classes d'affichage (Pattern Visitor)

- `SupportADessin` : Interface visitor abstraite
- `TextViewer` : Implémentation pour affichage texte
- `Dessinable` : Interface pour objets dessinables

### 7. Classes utilitaires

#### `Vecteur`

- **Rôle** : Vecteur mathématique de dimension quelconque
- **Fonctionnalités** : Opérations vectorielles complètes (addition, produit scalaire/vectoriel, normalisation)

## Patterns de conception utilisés

### 1. **Strategy Pattern**

- **Contexte** : Classe `Integrateur`
- **Bénéfice** : Changement d'algorithme d'intégration à l'exécution

### 2. **Visitor Pattern**

- **Contexte** : `SupportADessin` et `Dessinable`
- **Bénéfice** : Séparation de la logique d'affichage des objets métier

### 3. **Composite Pattern**

- **Contexte** : `ChampCompose`
- **Bénéfice** : Combinaison de multiple champs de forces

### 4. **Template Method Pattern**

- **Contexte** : `ForceCentrale`
- **Bénéfice** : Factorisation du calcul des forces centrales

## Justifications des choix de conception

### Gestion mémoire

- **`std::shared_ptr`** pour les champs et contraintes : Permet le partage entre multiple objets
- **`std::unique_ptr`** pour les objets dans le système : Propriété exclusive claire

### Séparation des responsabilités

- **Contraintes séparées des objets** : Flexibilité pour appliquer différentes contraintes
- **Champs de forces externes** : Réutilisabilité et composition facile
- **Intégrateurs interchangeables** : Permet de tester différents algorithmes

### Extensibilité

- **Classes abstraites** : Facilite l'ajout de nouveaux types d'objets/forces
- **Interface uniforme** : Tous les objets peuvent être traités de manière polymorphe

### Performance vs Flexibilité

- **Trade-off assumé** : Privilégier la flexibilité et la maintenabilité
- **Utilisation de pointeurs intelligents** : Sécurité mémoire au détriment de performances marginales

## Limitations et améliorations possibles

### Limitations actuelles

1. **Pas de détection de collisions** entre objets
2. **Contraintes limitées** (seulement mouvement libre implémenté)
3. **Pas de gestion d'énergie** automatique
4. **Interface graphique** limitée au mode texte

### Extensions envisageables

1. **Contraintes géométriques** : Pendules, surfaces de contrainte
2. **Corps rigides** avec rotation
3. **Détection et résolution de collisions**
4. **Interface graphique OpenGL**
5. **Sauvegarde/reprise** de simulation
6. **Analyse d'énergie** et conservation

Cette architecture respecte les principes SOLID et offre une base solide pour l'extension future du simulateur.