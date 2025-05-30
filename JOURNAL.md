# JOURNAL DE PROJET - Simulateur Physique POO

*Note importante : En raison de circonstances particulières, ce projet a été réalisé individuellement plutôt qu'en binôme comme prévu initialement. Cette situation a nécessité une adaptation de l'organisation du travail et une gestion plus autonome de l'ensemble des tâches.*

## Semaine 1 (20 février 2025)

### Objectifs selon planning

- Prise de connaissance du projet
- Mise en place de l'environnement de travail (répertoire, fichier JOURNAL)

### Réalisations

- **Lecture approfondie de l'énoncé** : Compréhension des objectifs généraux et des contraintes techniques

- **Analyse des exigences** : Identification des trois composants principaux (objets mobiles, champs de forces, contraintes)

- Mise en place environnement

   :

  - Création du répertoire de projet sur les VMs IC-CO-IN-SC
  - Initialisation du fichier JOURNAL.md
  - Configuration de l'environnement de développement (éditeur, compilation)

- **Planification personnelle** : Adaptation du planning pour un travail individuel

### Réflexions

Travailler seul sur ce projet représente un défi considérable mais aussi une opportunité d'approfondir tous les aspects de la programmation orientée objet. Je dois être particulièrement rigoureux dans l'organisation du temps.

### Temps investi : ~4 heures

------

## Semaine 2 (27 février 2025)

### Objectifs selon planning

- Première classe : vecteurs (de dimension quelconque)
- [Option] Introduction à l'environnement graphique (Qt et OpenGL)
- Mise à jour du journal

### Réalisations

- Classe Vecteur complète

   : Implémentation avec :

  - Constructeurs multiples (dimension, coordonnées 3D, liste d'initialisation)
  - Opérations algébriques (addition, soustraction, produit scalaire/vectoriel)
  - Surcharge d'opérateurs (==, !=, +, -, *, ^, <<, ~)
  - Gestion des dimensions différentes (choix de la plus petite dimension)
  - Méthodes de normalisation et calcul de norme

- testVecteur.cc

   : Programme de test exhaustif

  - Validation de toutes les opérations
  - Tests de commutativité et associativité
  - Gestion des cas limites

### Difficultés rencontrées

- **Ambiguïté constructeurs** : Problème théorique avec constructeur sphérique vs cartésien
- **Gestion dimensions** : Choix de stratégie pour opérations entre vecteurs de dimensions différentes
- **Précision numérique** : Gestion de la comparaison de flottants

### Décision prise

- Report de l'interface graphique pour me concentrer sur la logique physique fondamentale
- Priorisation d'une architecture solide avant l'affichage

### Temps investi : ~8 heures

------

## Semaine 3 (6 mars 2025)

### Objectifs selon planning

- Mise en place de la modularisation (Makefile)
- Mise à jour du journal

### Réalisations

- Makefile initial

   : Première version pour compiler testVecteur

  - Variables compiler (CXX, CXXFLAGS)
  - Règles de compilation de base
  - Règle de nettoyage

- **Organisation du code** : Séparation headers/sources

- **Tests de compilation** : Validation sur les VMs de l'École

### Apprentissages

- **Makefile syntax** : Comprendre les dépendances et règles
- **Compilation séparée** : Bénéfices pour les projets moyens/grands
- **Flags de compilation** : Importance des warnings et du standard C++17

### Temps investi : ~5 heures

------

## Semaine 4 (13 mars 2025)

### Objectifs selon planning

- Inscriptions définitives au projet
- Révision/Extension des vecteurs
- Point matériel et gravité
- Mise à jour du journal, des réponses et de la conception

### Réalisations

- **Inscription individuelle** : Formalités administratives pour projet solo

- Architecture ObjetMobile

   : Classe abstraite de base

  - Paramètres d'état (vecteur E et sa dérivée E')
  - Méthode virtuelle pure `evolution(double temps)`

- ObjetPhysique

   : Classe héritant d'ObjetMobile

  - Gestion de la masse, champs de forces et contraintes
  - Méthodes pour position() et vitesse() physiques
  - Calcul de force() et evolution()

- **PointMateriel** : Spécialisation d'ObjetPhysique

- Interfaces abstraites

   :

  - `ChampForces` avec méthode `force()`
  - `Contrainte` avec méthodes `applique_force()`, `position()`, `vitesse()`

- **GravitationConstante** : Premier champ de forces (g uniforme)

- **Libre** : Première contrainte (mouvement libre)

- **testPointMateriel.cc** : Tests des objets physiques de base

### Difficultés rencontrées

- **Pointeurs intelligents** : Choix entre shared_ptr et unique_ptr
- **Références circulaires** : Problèmes d'inclusion entre classes
- **Conception abstraite** : Équilibrage entre généralité et simplicité

### Temps investi : ~10 heures

------

## Semaine 5 (20 mars 2025)

### Objectifs selon planning

- Pause pour respirer / rattrapage éventuel

### Réalisations

- **Révision architecture** : Validation de la conception avec les assistants

- Makefile avancé

   : Apprentissage des dépendances automatiques

  - Règles pour chaque fichier objet
  - Gestion des dépendances entre headers
  - Phony targets et optimisations

- Résolution problèmes compilation

   :

  - Déclarations anticipées pour éviter inclusions circulaires
  - Organisation propre des headers et sources

- **Documentation code** : Amélioration des commentaires

### Apprentissages

- **Déclarations anticipées** : Technique essentielle pour éviter les inclusions circulaires
- **RAII** : Gestion automatique des ressources avec pointeurs intelligents

### Temps investi : ~6 heures

------

## Semaine 6 (27 mars 2025)

### Objectifs selon planning

- Intégrateurs
- Objets, champs de forces et contraintes
- Mise à jour du journal, des réponses et de la conception

### Réalisations

- Interface Integrateur

   : Classe abstraite avec méthode 

  ```
  integre()
  ```

  - Pattern Strategy pour interchanger les algorithmes

- IntegrateurEulerCromer

   : Implémentation méthode semi-implicite

  - Mise à jour d'abord de la vitesse, puis de la position
  - Stabilité améliorée par rapport à Euler simple

- testIntegrateur1.cc

   : Tests avec différentes conditions initiales

  - Chute libre avec vitesse nulle
  - Mouvement parabolique
  - Validation des résultats physiques

- Extension champs de forces

   :

  - **ForceCentrale** : Classe abstraite pour forces en r^-2
  - **ChampNewtonien** : Force gravitationnelle F = G*m1*m2/r²

### Difficultés rencontrées

- **Compréhension Euler-Cromer** : Différence subtile avec Euler simple
- **Stabilité numérique** : Choix du pas de temps approprié
- **Gestion des singularités** : Distance nulle entre objets

### Apprentissages

- **Intégration numérique** : Compromis précision/stabilité
- **Physique numérique** : Validation des résultats par l'analyse

### Temps investi : ~9 heures

------

## Semaine 7 (3 avril 2025)

### Objectifs selon planning

- Développement du système complet
- Simulation (première version, en mode texte)
- Mise à jour du journal, des réponses et de la conception

### Réalisations

- Classe Systeme

   : Gestionnaire principal du simulateur

  - Collections d'objets, champs et contraintes avec pointeurs intelligents
  - Méthodes d'ajout et d'association entre composants
  - Évolution temporelle globale avec `evolue(dt)`
  - Gestion du temps interne du système

- Pattern Visitor pour affichage

   :

  - Interface `SupportADessin` avec méthodes `dessine()` surchargées
  - Interface `Dessinable` avec méthode `dessine_sur()`
  - **TextViewer** : Implémentation concrète pour affichage texte

- **Première simulation complète** : Intégration de tous les composants

### Difficultés rencontrées

- **Conception Systeme** : Équilibrage des responsabilités
- **Double dispatch** : Compréhension du mécanisme en C++
- **Gestion mémoire** : Cycles de vie des objets partagés

### Apprentissages

- **Pattern Visitor** : Séparation élégante logique métier/affichage
- **Polymorphisme avancé** : Techniques de dispatch multiple

### Temps investi : ~10 heures

------

## Semaine 8 (10 avril 2025)

### Objectifs selon planning

- Version graphique de la simulation
- Mise à jour du journal, des réponses et de la conception

### Réalisations

- **Report de l'interface graphique** : Décision de me concentrer sur la physique

- **Amélioration TextViewer** : Formatage avancé et gestion flexible des flux

- exerciceP9-pomme.cc

   : Première simulation physique complète

  - Terre et pomme avec force gravitationnelle newtonienne
  - Affichage de l'évolution de l'altitude dans le temps
  - Validation avec résultats théoriques attendus

- **Tests de robustesse** : Validation dans différentes conditions

### Justification choix

Priorité donnée à une simulation physique correcte et stable plutôt qu'à l'interface graphique. L'objectif est d'avoir une base solide avant d'ajouter la complexité visuelle.

### Résultats exercice P9

- Simulation fonctionnelle de la chute de la pomme sous attraction terrestre
- Comparaison satisfaisante avec les prédictions théoriques
- Stabilité numérique excellente avec Euler-Cromer

### Temps investi : ~8 heures

------

## Semaine 9 (17 avril 2025)

### Objectifs selon planning

- Rien (midterm) / rattrapage éventuel

### Réalisations

- **Période de midterm** : Concentration sur les autres cours
- **Maintenance du code** : Corrections mineures et optimisations
- **Préparation simulations complexes** : Planification des prochaines étapes
- **Documentation** : Mise à jour des commentaires et du fichier REPONSES

### Réflexions

Cette pause est bienvenue pour prendre du recul sur l'architecture développée et planifier les extensions futures. Le projet avance bien malgré le travail individuel.

### Temps investi : ~3 heures

------

## Semaine 10 (1 mai 2025)

### Objectifs selon planning

- Simulations plus complexes
- Mise à jour du journal, des réponses et de la conception

### Réalisations

- ChargeElectrique

   : Classe héritant de PointMateriel

  - Ajout de l'attribut charge électrique
  - Interaction avec les champs électromagnétiques

- ChampElectromagnetique

   : Force de Lorentz F = q(E + v×B)

  - Gestion des champs électrique et magnétique
  - Calcul du produit vectoriel pour la force magnétique

- **FrottementFluide** : Force proportionnelle à la vitesse

- **ChampCompose** : Pattern Composite pour combiner multiple forces

- exerciceP11-magnetique.cc

   : Simulation électromagnétique

  - Particule chargée dans un champ magnétique
  - Mouvement cyclotronique avec frottement
  - Démonstration de la trajectoire spiralée

### Difficultés rencontrées

- **Calculs vectoriels complexes** : Produit vectoriel 3D
- **Validation physique** : Vérification des résultats électromagnétiques
- **Débogage numérique** : Problèmes de précision avec petites valeurs

### Temps investi : ~11 heures

------

## Semaine 11 (8 mai 2025)

### Objectifs selon planning

- Autres intégrateurs
- Mise à jour du journal, des réponses et de la conception

### Réalisations

- IntegrateurRungeKutta4

   : Implémentation de l'algorithme RK4

  - Quatre évaluations par pas de temps (k1, k2, k3, k4)
  - Méthode d'ordre 4 pour meilleure précision
  - Tests comparatifs avec Euler-Cromer

- Validation des intégrateurs

   : Comparaison systématique

  - Précision vs coût de calcul
  - Stabilité pour différents pas de temps
  - Cas d'usage appropriés pour chaque méthode

- **Optimisation du Makefile** : Gestion automatique des dépendances

- **Tests de performance** : Mesure des temps d'exécution

### Résultats comparaison intégrateurs

- **Euler-Cromer** : Rapide, stable pour oscillateurs, précision limitée
- **Runge-Kutta 4** : Plus lent, précision excellente, adapté aux systèmes complexes

### Temps investi : ~9 heures

------

## Semaine 12 (15 mai 2025)

### Objectifs selon planning

- Extensions (optionnelles)
- Finalisation
- Mise à jour du journal, des réponses et de la conception

### Réalisations

- Débogage intensif

   : Résolution des problèmes subtils

  - Gestion mémoire avec Valgrind
  - Optimisation des performances
  - Correction des fuites potentielles

- Tests exhaustifs

   : Validation de tous les composants

  - Tests unitaires pour chaque classe
  - Tests d'intégration pour le système complet
  - Validation physique des résultats

- Finalisation documentation

   :

  - Mise à jour du fichier CONCEPTION.md
  - Amélioration des commentaires de code
  - Finalisation du fichier REPONSES.md

### Outils utilisés

- **Valgrind** : Détection de fuites mémoire
- **GDB** : Débogage interactif des problèmes complexes
- **Profiling** : Identification des goulots d'étranglement

### Temps investi : ~10 heures

------

## Semaine 13 (22 mai 2025)

### Objectifs selon planning

- Finalisation (et rendu ?)

### Réalisations

- **Finalisation du code** : Dernières corrections et optimisations

- Rédaction README

   : Guide complet d'utilisation

  - Instructions de compilation détaillées
  - Exemples d'utilisation de chaque programme
  - Description des paramètres physiques

- **Tests finaux** : Validation sur les VMs de l'École

- **Préparation du rendu** : Organisation des fichiers

- **Script de validation** : Automatisation des tests de régression

### Réflexions finales

Ce projet, bien que réalisé individuellement, a été extrêmement enrichissant. J'ai pu approfondir tous les aspects de la programmation orientée objet et développer une compréhension solide de la simulation physique numérique.

### Défis du travail individuel

- **Charge de travail importante** : Nécessité de maîtriser tous les aspects
- **Pas de répartition des tâches** : Gestion autonome de la complexité
- **Moins d'échanges** : Mais discussion avec les assistants compensée

### Satisfaction personnelle

Malgré les défis, le projet est fonctionnel et respecte toutes les exigences minimales avec plusieurs extensions intéressantes.

### Temps investi : ~8 heures

------

## Semaine 14 (29 mai 2025)

### Objectifs

- Rendu final le 1er juin à 23:59

### Réalisations finales

- **Validation finale** : Tests sur machines officielles
- **Soumission du projet** : Respect de la deadline
- **Archive de sauvegarde** : Copie de sécurité complète

------

## Bilan global du projet

### Temps total investi : ~116 heures

*Note : Le travail individuel a nécessité environ 40% de temps supplémentaire par rapport à un binôme*

### Objectifs atteints

- ✅ Simulation d'un point matériel en chute libre
- ✅ Exercice simple (pomme/Terre avec gravitation newtonienne)
- ✅ Exercice complexe (particule chargée électromagnétique)
- ✅ Deux intégrateurs différents (Euler-Cromer et Runge-Kutta 4)
- ✅ Architecture orientée objet complète et extensible

### Extensions réalisées

- Classe ChampCompose pour combiner multiple forces
- FrottementFluide pour effets dissipatifs
- Tests exhaustifs et validation physique
- Documentation complète et exemples d'utilisation

### Apprentissages principaux

1. **Architecture logicielle** : Conception d'un système complexe modulaire
2. **Programmation orientée objet** : Héritage, polymorphisme, patterns de conception
3. **Physique numérique** : Intégration numérique, stabilité, précision
4. **Gestion de projet** : Organisation du temps, documentation, tests

### Difficultés surmontées

- Gestion de la complexité croissante du système
- Débogage de problèmes subtils de précision numérique
- Équilibrage entre généralité et simplicité de l'architecture
- Validation physique des résultats de simulation

Ce projet représente une expérience formatrice complète en programmation orientée objet appliquée à la simulation physique, malgré les défis particuliers du travail individuel.