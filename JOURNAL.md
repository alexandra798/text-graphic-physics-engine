
Systeme需要多个属性，用指针指向多个或单个物体、约束、力、积分器
文本支持显示，和SupportADessin以及TextViewer
积分器&运动之物已经写出来了，包括各种成员函数的实现
testIntegrateur1写出来了并成功运行
它需要的东西不多，就是运动对象、物理对象和质点这三个类，还有积分器抽象类、欧拉积分器，还有立场类（重力场，很简单）
为了将测试结果画图表示出来，我还安装了gnuplot，并且学会了如何将输出结果写入一个txt文件
testIntegrateur2也可以写，同样的场景把积分器1换成积分器2就行
这个简单的测试没有用到Contrainte类，因此我对它怎么运作还是一头雾水

可能需要修改【物理对象】类和【立场】类和【质点】类，为了执行第二个测试。我相信我写的已经够了？
进行修改直到“抽象程度”符合要求，且tesIntegrateur1和testPointMateriel能成功执行
以及，我们需要增加全新的类：约束
新增测试：testPomme，需要用到牛顿力场。

## testPointMateriel
Tests
Produisez enfin un programme de test testPointMateriel.cc dans lequel sont créés un champ de gravité (vertical, d'intensité 9.81 m/s²) et différents points matériels. Afficher ensuite les caractéristiques de tous les objets.

Note : pour l'affichage des PointMateriel, nous vous conseillons d'avoir deux méthodes affiche(), une qui ne prend pas d'argument et affiche divers paramètres du PointMateriel, sauf sa force subie, et une seconde qui prend un temps en paramètre, appelle la première méthode, puis affiche la force subie au temps correspondant.
La surcharge de l'opérateur << n'appellera que la première de ces deux méthodes.

Modifiez le Makefile pour établir le lien entre les différents fichiers de votre projet.

NOTE IMPORTANTE : Je rappelle que les programmes de test font pleinement partie du projet et devront être rendus avec le projet.

Exemple de tests
Voici par exemple ce que pourrait produire votre programme de test:
(le format d'affichage ci-dessous facilitera plus tard la comparaison des sorties de vos programmes aux résultats attendus.)

Nous avons :
un champ de force :
0 0 -9.81 # intensite

un point matériel :
0.1 # masse
1 2 3 # position
0 0.1 0.2 # vitesse
0 0 -0.981 # force

et un autre point matériel :
2 # masse
-1.1 1.2 1.3 # position
0.2 0.1 0 # vitesse
0 0 -19.62 # force

### testPointMateriel(remake)
Les points matériels de la semaine passée sont (doivent être) des objets physiques...

[Question P7.2] Comment cela doit-il se traduire dans votre projet ?

Répondez à cette question dans votre fichier REPONSES

Ce faisant (modifications nécessaires), vous risquez de dupliquer certaines informations. Ce qu'il faut, bien sûr, absolument éviter ! Il faut donc réviser cette classe.

[ Remarque : ce genre de problèmes (modifier la conception d'un code existant) est typique de l'évolution d'un logiciel. On appelle cela le refactoring (et il y a des livres entiers à ce sujet).
Ce n'est donc pas par erreur de conception du projet que je vous fait modifier votre code, mais bien pour
(1) voir l'introduction des nouveaux concepts vus en cours et leur importance, leurs implications ; et
(2) pratiquer ce type de révisions/modifications de code (refactoring).
Nous le ferrons encore quelques fois au fur et à mesure des nouveaux concepts. Si votre conception du projet est claire et cohérente, cela ne devrait pas poser plus de problème que de déplacer/remplacer quelques lignes de code.
]

Note : tout ce qui suit dans cette partie (« Révision des points matériels ») est en fait assez simple (déplacement de code, et peut être remplacement de quelque noms) et ne devrait pas prendre plus de 10-20 min en tout.

Le plus simple dans notre cas consiste simplement à supprimer les attributs et les méthodes que nous avons déjà mis ailleurs. En fait, c'est aussi un bon moyen de voir si l'on a fait une bonne conception: pour chaque attribut et chaque méthode il faut se demander à quel niveau d'abstraction il/elle appartient: est-ce une propriété propre aux points matériels ou est-ce quelque chose de plus abstrait ?

Au final, je pense qu'il ne reste plus grand chose dans vos points matériels. Mais c'est bien sûr à vous de voir/décider: vous êtes responsables de votre conception.

Pour finir, modifiez le Makefile pour établir le lien entre ces différents nouveaux fichiers et procéder aux modifications nécessaires.
Au final, lorsque votre binôme aura terminé les champs de forces, les contraintes et la contrainte Libre, modifiez testPointMateriel.cc en conséquence puis vérifiez qu'il compile et s'exécute encore correctement.

## testPomme
应该不难吧？
Pour finir et bien illustrer les différentes classes introduites cette semaine, je vous propose de coder votre premier exercice de Physique : quelle est la trajectoire d'une pomme de 0.1 kg tombant sur la Terre (rayon = 6371e3 m, masse = 5.972e24 kg), depuis une altitude de 10 m?

La Terre et la pomme seront considérées comme des points matériels. Au niveau des contraintes, les deux sont libres. Par contre, on introduit ici un nouveau champ de forces: la gravité newtonienne entre masses.

Commencez pour cela par définir une classe ForceCentrale qui est un champ de forces central, c.-à-d. défini par un point.

Dans notre cas, le point central de ce champ de forces sera donné par un objet physique dont la classe ForceCentrale aura une référence (comme attribut, donc).

Nous vous proposons également d'ajouter une méthode quadratique_inverse() non publique (private ou protected suivant votre choix) qui prend un autre objet et retourne le vecteur nul si cet autre objet est trop proche (précision numérique) du point central du champ de force, et sinon, le vecteur de norme l'inverse du carré des distances et de direction de l'autre objet vers le point central du champ de force.

Définissez ensuite une classe ChampNewtonien, qui est un champ de forces central dont la méthode force() retourne la force de gravité suivant la formule de Newton.
On veillera à ce que la dimension de cette force soit celle de l'objet reçu en paramètre (c.-à-d. la même dimension que celle choisie pour la représentation physique de cet objet).

Rappel : G, la constante universelle de gravitation, a pour valeur 6,674 3015 × 10^(−11) m^(3) kg^(−1) s^(−2).

Pour tester, créer un fichier testPomme.cc qui effectue la simulation décrite plus haut (une pomme de 0.1 kg tombant sur la Terre (rayon = 6371e3 m, masse = 5.972e24 kg), depuis une altitude de 10 m).

Vous pouvez retrouver les résultats sur plusieurs pas de temps (avec dt=1e-3) dans les fichiers suivants :

tests/pomme-1.txt (link): les 100 premiers pas de calcul;
tests/pomme-2.txt (link): les 1.4 premières secondes affichées tous les 0.1 s (donc affiché tous les 100 pas de calcul; dt est toujours égal à 1e-3 s ici).

## exerciceP9
注意事项：Systeme类和TextViewer类
### testPomme(remake) 命名为exerciceP9-pomme.cc
Le retour de la pomme
On veut ici créer notre première simulation d'un système complet (et peut être quelques autres). Pour cela, on va commencer par reproduire le résultat de la chute d'une pomme, mais dans un Systeme.

Pour cela, implémentez dans une méthode evolue(double dt) de la classe Systeme, une boucle sur tous les objets (pouvant évoluer) qu'il contient. Cette boucle fait avancer (grâce au même intégrateur, composant interne du système) chacun de ces objets du pas de temps dt fourni.

Dans un fichier exerciceP9.cc, créez puis faîtes évoluer un système ayant les mêmes caractéristiques que celles de l'exemple de la chute d'une pomme de la semaine passée, et vérifiez que vous obtenez les mêmes résultats

Note : la méthode dessine_sur() d'un objet en mode texte (sur un TextViewer, donc) peut très bien être différente de son affichage (avec <<). On peut par exemple vouloir que l'affichage (avec <<) soit plus complet, avec plus d'informations, alors que la méthode dessine_sur() serait plus simple, n'affichant que le strict nécessaire (si cela vous aide pour dessiner avec gnuplot, Excel ou tout autre logiciel de dessin externe).
Vous êtes libres de faire ces affichages comme bon vous semble (même si cela (le résultat de dessine_sur()) n'est plus très lisible par un humain).
Après, vous pouvez aussi faire plusieurs SupportADessin textuels différents suivant vos besoin (p.ex. GnuplotViewer, DebugViewer, PositionOnlyViewer qui sont des TextViewer).

### exerciceP9-AUTRES
Si vous avez le temps, vous pouvez maintenant créer d'autres exercices de Physique, par exemple (références à vérifier SVP -- pas sûr de mes sources ;-)) :

Exercice 3.1 (cinématique) Le corbeau et le renard (chute combinée d'une pierre et d'un fromage) ;
Exercice Ex-Cathedra 7.3 (moment cinétique et énergie) satellite en orbite ;
Exercice 7.3 (moment cinétique et énergie) voyage vers Mars.
(Note: on a sélectionné ici que des exercices avec champ gravitationnel constant ou champ newtonien; nous aborderons des exercices plus compliqués dans le sujet P11, en semaine 10.)

## exerciceP11-magnetique
P11.6.b - Mouvement dans un champ magnétique avec frottement (exercice PA1 4.3 ?)
On s'intéresse ici au mouvement d'une particule massique chargée dans un champ magnétique constant et dans un fluide (ayant donc une force de frottement fluide).

Pour décrire une telle situation, vous aurez besoin :

d'un champ électromagnétique constant ;
d'un champ de frottement fluide ;
de pouvoir les composer ;
d'un point matériel avec charge électrique ;
de la contrainte libre.
Note : l'exercice en question néglige les effets de la gravité ; vous n'avez donc pas besoin ici du champ gravitationnel constant.

Dans un fichier exerciceP11-magnetique.cc, créez :

un champ électromagnétique constant de champ électrique nul, de champ magnétique 0.5 T suivant l'axe vertical (c.-à-d. B=(0, 0, 0.5));
un champ de forces de frottement fluide d'intensité 1.33e-5 S.I.;
une contrainte libre;
une particule de masse 1.5e-4 kg, de charge 2e-6, en position (0, 0, 0), de vitesse initiale 0.3 m/s suivant l'axe des ordonnées (c.-à-d. v0=(0.3, 0, 0)).
Avec un intégrateur d'Euler-Cromer et un pas de temps de 0.001 s, vous devriez obtenir les résultats ci-dessous.



la troisième coordonnée (z) est toujours nulle;
il pourrait aussi être intéressant de dessiner la trajectoire (p.ex. avec gnuplot ou autre) sur des temps plus longs;
sur des temps plus longs, il n'est aussi pas forcément nécessaire d'afficher les valeurs à chaque pas d'intégration; vous pourriez choisir aussi un « pas de temps d'affichage » (multiple du pas d'intégration); p.ex. avoir un pas d'intégration de 0.001 s, mais un affichage que toutes les 0.05 s (tous les 50 pas d'intégration).
t     x           y
0     0           0
0.001 0.00029997 -2e-09
0.002 0.00059992 -5.99965e-09
0.003 0.00089984 -1.19986e-08
0.004 0.00119973 -1.99965e-08
0.005 0.0014996  -2.99929e-08
0.006 0.00179944 -4.19876e-08
0.007 0.00209926 -5.59801e-08
0.008 0.00239904 -7.19702e-08
0.009 0.0026988  -8.99574e-08
0.01  0.00299854 -1.09941e-07
0.011 0.00329824 -1.31922e-07
0.012 0.00359793 -1.55899e-07
0.013 0.00389758 -1.81871e-07
0.014 0.00419721 -2.09839e-07
0.015 0.00449681 -2.39801e-07
0.016 0.00479638 -2.71759e-07
0.017 0.00509593 -3.05711e-07
0.018 0.00539545 -3.41657e-07
0.019 0.00569495 -3.79596e-07
0.02  0.00599442 -4.19529e-07
0.021 0.00629386 -4.61454e-07
0.022 0.00659327 -5.05372e-07
0.023 0.00689266 -5.51283e-07
0.024 0.00719203 -5.99185e-07
0.025 0.00749136 -6.49079e-07
0.026 0.00779067 -7.00963e-07
0.027 0.00808995 -7.54839e-07
0.028 0.00838921 -8.10705e-07
0.029 0.00868844 -8.68561e-07
0.03  0.00898764 -9.28407e-07

### 为实现这个模拟练习所需新增的classes/方法/功能/成员函数/属性

#### P11.2.b - Champ électromagnétique constant
Un champ électromagnétique constant est défini par deux vecteurs : un champ électrique et un champ magnétique.
La force qu'il retourne est le produit de la charge de l'objet (à voir lequel) par la somme du champ électrique et du produit vectoriel de la vitesse de l'objet par le champ magnétique (F = q ( E + v ^ B )).

#### P11.2.a - Frottement fluide
Un frottement fluide est un champ de forces qui nécessite un paramètre, le coefficient de frottement -- disons λ -- et qui pour un objet donné retourne -λ fois la vitesse de cet objet.

#### P11.3 - Composition (de ChampForces ou de Contraintes)
Un schéma classique de conception est celui de la composition: chaque fois qu'un « objet » (au sens large) peut se composer avec un autre « objet » pour en donner un troisième. Par exemple, l'union de deux ensembles est un ensemble, la composition de deux (demi-)scènes visuelles serait une scène visuelle, etc., et pour nous, p.ex., la composition (addition) de deux champs de forces est un champ de forces. Cela permet ensuite d'en composer autant que l'on veut.

Implémentez la notion de ChampCompose qui est un champ de forces et contient un ensemble (de tailles quelconque) de champs de forces. Sa méthode force() est simplement la somme de celles de ses composantes.

Vous pouvez aussi, si vous le souhaitez, faire de même avec la notion de contraintes. Par contre, s'il n'est pas difficile d'imaginer la composition des applique_force() des contraintes (somme), il est nettement moins clair comment les positions et vitesses de celles-ci doivent se composer. 你需要仔细思考后做出决定，并告诉我你为什么选择这种composer les positions et vitesses的方式
(Pour aller plus loin, on pourrait imaginer une méthode supplémentaire qui au lieu de passer du vecteur d'état à une position passerait d'une position physique à une autre position physique. On pourrait alors utiliser la méthode qui passe du vecteur d'état à une position physique pour le premier champ de forces, puis ensuite composer (appels successifs enchaînés) les secondes méthodes de tous les champs de forces suivants.)

#### P11.5 - Points matériels chargés
已实现，但是尚未决定要将其作为ObjetPhysique的子类还是PointMateriel的子类。你仔细思考后替我作出判断。

#### Contrainte libre
La plus simple des contraintes est celle qui ne contraint rien du tout. Créez pour cela une classe Libre dont :

la méthode applique_force(), retourne simplement la force divisée par la masse de l'objet (si elle n'est pas nulle et simplement cette force si la masse est nulle)
la méthode position(), retourne simplement le vecteur d'état E de l'objet;
la méthode vitesse(), retourne simplement le vecteur «dérivée temporelle des paramètres» E' de l'objet.
（我们已经有了Libre类，你检查一下是否符合要求，并进行修改，这样就行）
