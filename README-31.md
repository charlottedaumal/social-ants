#PROJET SV 2021 : «Fourmis : simulation d'un système auto-organisé»

##groupe 31 Charlotte Daumal et Clémence Kiehl
##coach: Aline Brunner


 
 Notre programme est une simulation informatique sur la base d’un modèle constitué d’un monde, de fourmilières et de prédateurs (termites)
Dans le cadre notre modélisation nous étudions le comportement de 2 types de fourmis: les fourmis ouvrières dont le rôle est de ramener de la nourriture (générée automatiquement) à la fourmilière, et les fourmis soldats qui pourront être engagées dans des combats avec des prédateurs (termites).

La simulation a donc pour but final d’illustrer l’auto-organisation d’une colonie de fourmis et son adaptation à l’environnement.

##COMPILATION ET EXECUTION :

Ce projet utilise CMake pour compiler 

en ligne de commande :
dans le dossier build : cmake../src
make nom_cible pour la génération de la cible

dans QTCreator:
    - mise en place du projet : ouvrir le fichier src/CmakeLists.txt
    - choisir la cible à exécuter

##CIBLES PRINCIPALES : 

* application -> correspond à l’application finale.

* enemyTest-> permet de tester les affrontements entre fourmis et prédateurs

* termiteTest -> permet de créer dans l’environnement de simulation une termite au moyen de la touche ’T'

* pheromoneTest -> permet de créer un chemin de phéromones dans le cercle olfactif de la fourmi témoin et d’observer l’affichage des phéromones perçues par celle-ci après que l’on ait appuyé sur la touche ‘Q’

* anthillTest -> fait apparaitre les fourmilières et leurs fourmis. On peut remarquer que les fourmis ouvrières parviennent à ramener de la nourriture à leur fourmilière en suivant les traces de phéromones. 

* antTest -> permet de créer dans l’environnement de simulation une fourmi ouvrière au moyen de la touche ‘W’, ainsi qu’une fourmi soldat grâce à la touche ’S’

* foodTest -> permet de voir apparaître spontanément des sources de nourriture dans l’environnement 


##COMMANDES :

* touche **'C'** -> permet d'affecter la température minimale(-10C) à l'environnement
* touche **'D'** -> permet de mettre la simulation en mode debug
* touche **'F'** -> permet d'affecter la température maximale(35°C) à l'environnement
* touche **'M'** -> permet la création de l'environnement tel qu'il est configuré dans le fichier *res/map1.map*
* touche **'N'** -> permet d'affecter la température usuelle à l'environnement (20°C)
* touche **'Q'** -> permet d'observer l'affichage des phéromones perçues par la fourmi
* touche **'R'** -> reset les stats et l'environnement
* touche **'S'** -> permet de créer une fourmi soldat
* touche **'T'** -> permet d'ajouter une termite
* touche **'W'** -> permet de créer une fourmi ouvrière
* touche **'Y'** -> permet de changer la température de l'environnement
* touche **'Z'** -> enregistre les données de la simulation en cours dans un fichier nommé map_saved.map

* touche **espace** -> permet de mettre la simulation en pause
* touche **escape** -> permet de fermer la simulation
 
* touches **PgUp** et **PgDown** -> permettent de basculer sur les différents graph représentant l'évolution de la simulation

##MODIFICATION DE CONCEPTION :

Le codage du projet a été réalisé en adéquation avec l’énoncé du projet.
**

##EXTENSIONS :

Nous avons élaboré une extension permettant de **réduire la taille de la nourriture** et de la faire changer de texture en dessous d'une quantité seuil (on la considère comme déshydratée)

De plus, nous avons aussi codé une extension permettant la **mémorisation de points de reprises**. Ainsi, le fait d'appuyer sur la touche 'Z' permet de mémoriser dans un fichier un point de reprise correspondant à l'état courant de la simulation.

On a aussi fait en sorte que la **température ait une influence sur l'environnement** : Elle affecte les forces de combat et les vitesses des animaux. En periode de gel, tout l'environnement se freeze. 
 
 Nous avons aussi introduit la **notion d'insecticides**, générés automatiquement dans l’environnement à la manière des sources de nourriture (classe InsecticideGenerator héritée d’une classe générale Generator) et qui polluent les sources de nourriture et les fourmillières à proximité et tuent tous les animaux à proximité. 
 
 Par conséquent, les fourmis ouvrières qui collectent de la nourriture contaminée meurent et les fourmilières exposées diminuent en taille puis disparaissent.
 
 Enfin nous avons mis en place un **cycle Jour/Nuit** au moyen du type énuméré. Toutes les 5secondes de simulation, le cycle change et le fond de l'environnement se modifie en conséquence.
 

