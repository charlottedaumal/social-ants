# The Ants: A Simulation of an Auto-Organized System

**Authors:** Charlotte Daumal & Clemence Kiehl  
**Context:** This project was completed as part of the *Programmation Orienté Objet* course taught by Prof. Jamila Sam at EPFL  
**Language:** C++  
**Date:** June 2021

> [!WARNING]
> 📣 This project's documentation files (`.md` format) are written in french since the whole course was taught in french.

---

## 📘 Description
 
Ce programme simule le fonctionnement d’une colonie de fourmis dans un environnement peuplé de ressources et de prédateurs (termites). Le modèle met en scène deux types de fourmis aux rôles complémentaires : les ouvrières, chargées de collecter la nourriture générée automatiquement et de la rapporter à la fourmilière, et les soldats, mobilisés pour affronter les prédateurs.  
L’objectif de cette simulation est d’illustrer les mécanismes d’auto-organisation et la capacité d’adaptation d’une colonie face à un environnement changeant.

---

## ▶️ Compilation & Execution  

Ce projet utilise **CMake** pour la compilation. Vous pouvez compiler le code soit en ligne de commande, soit via l’environnement **QtCreator**.

### Compilation en ligne de commande  
1. Depuis le dossier `build`, configurez le projet avec la commande suivante :

   ```bash
   cmake ../src```
   
2. Compilez la cible souhaitée avec

   ```make <nom_de_la_cible>```

### Compilation avec QT Creator  
1. Ouvrez le fichier suivant pour configurer le projet :

```src/CMakeLists.txt```

2. Sélectionnez la cible à exécuter directement dans l’interface de QtCreator.

---

## 🎯 Cibles Principales   

* application -> correspond à l’application finale.

* enemyTest-> permet de tester les affrontements entre fourmis et prédateurs

* termiteTest -> permet de créer dans l’environnement de simulation une termite au moyen de la touche ’T'

* pheromoneTest -> permet de créer un chemin de phéromones dans le cercle olfactif de la fourmi témoin et d’observer l’affichage des phéromones perçues par celle-ci après que l’on ait appuyé sur la touche ‘Q’

* anthillTest -> fait apparaitre les fourmilières et leurs fourmis. On peut remarquer que les fourmis ouvrières parviennent à ramener de la nourriture à leur fourmilière en suivant les traces de phéromones. 

* antTest -> permet de créer dans l’environnement de simulation une fourmi ouvrière au moyen de la touche ‘W’, ainsi qu’une fourmi soldat grâce à la touche ’S’

* foodTest -> permet de voir apparaître spontanément des sources de nourriture dans l’environnement 

---

## ⚙️ Commandes  

* touche ‘C‘ -> permet d'affecter la température minimale(-10C) à l'environnement
* touche ‘D‘ -> permet de mettre la simulation en mode debug
* touche ‘F‘ -> permet d'affecter la température maximale(35°C) à l'environnement
* touche ‘M‘ -> permet la création de l'environnement tel qu'il est configuré dans le fichier *res/map1.map*
* touche ‘N‘ -> permet d'affecter la température usuelle à l'environnement (20°C)
* touche ‘Q‘ -> permet d'observer l'affichage des phéromones perçues par la fourmi
* touche ‘R‘ -> reset les stats et l'environnement
* touche ‘S‘ -> permet de créer une fourmi soldat
* touche ‘T‘ -> permet d'ajouter une termite
* touche ‘W‘ -> permet de créer une fourmi ouvrière
* touche ‘Y‘ -> permet de changer la température de l'environnement
* touche ‘Z‘ -> enregistre les données de la simulation en cours dans un fichier nommé map_saved.map

* touche ‘espace‘ -> permet de mettre la simulation en pause
* touche ‘escape‘ -> permet de fermer la simulation
 
* touches ‘PgUp‘ et ‘PgDown‘ -> permettent de basculer sur les différents graph représentant l'évolution de la simulation

---

## 📝 Modification de Conception :

Le codage du projet a été réalisé en adéquation avec l’énoncé du projet.

---

## 📚 Extensions :

Nous avons élaboré une extension permettant de **réduire la taille de la nourriture** et de la faire changer de texture en dessous d'une quantité seuil (on la considère comme déshydratée)

De plus, nous avons aussi codé une extension permettant la **mémorisation de points de reprises**. Ainsi, le fait d'appuyer sur la touche 'Z' permet de mémoriser dans un fichier un point de reprise correspondant à l'état courant de la simulation.

On a aussi fait en sorte que la **température ait une influence sur l'environnement** : Elle affecte les forces de combat et les vitesses des animaux. En période de gel, tout l'environnement se freeze. 
 
Nous avons aussi introduit la **notion d'insecticides**, générés automatiquement dans l’environnement à la manière des sources de nourriture (classe InsecticideGenerator héritée d’une classe générale Generator) et qui polluent les sources de nourriture et les fourmillières à proximité et tuent tous les animaux à proximité. 
 
Par conséquent, les fourmis ouvrières qui collectent de la nourriture contaminée meurent et les fourmilières exposées diminuent en taille puis disparaissent.
 
Enfin nous avons mis en place un **cycle Jour/Nuit** au moyen du type énuméré. Toutes les 5secondes de simulation, le cycle change et le fond de l'environnement se modifie en conséquence.

---

## License

This project is for educational purposes.  
Content © Charlotte Daumal & Clemence Kiehl. Academic use only.
