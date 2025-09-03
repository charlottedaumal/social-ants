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

   ```bash
   make <nom_de_la_cible>```

### Compilation avec QT Creator  
1. Ouvrez le fichier suivant pour configurer le projet : `src/CMakeLists.txt`

2. Sélectionnez la cible à exécuter directement dans l’interface de QtCreator.

---

## 🎯 Cibles Principales   

Le projet inclut plusieurs exécutables permettant de tester individuellement différents composants de la simulation :

* `application` → Application principale du projet. Il s'agit de la simulation complète dans son état final.  
* `enemyTest` → Teste les combats entre fourmis soldats et prédateurs (termites) dans l’environnement.  
* `termiteTest` → Permet de faire apparaître une termite dans l’environnement de simulation en appuyant sur la touche `T`.  
* `pheromoneTest` → Crée un chemin de phéromones dans le cercle olfactif d'une fourmi témoin.  Affiche ensuite les phéromones perçues lorsque l'on appuie sur la touche `Q`.  
* `anthillTest` → Fait apparaître les fourmilières et leurs fourmis associées. Les fourmis ouvrières sont capables de retrouver leur chemin vers la fourmilière en suivant les phéromones.
* `antTest` → Ajoute manuellement des fourmis dans l’environnement
   - Touche `W`: crée une **fourmi ouvrière**  
   - Touche `S`: crée une **fourmi soldat**
* `foodTest` → Fait apparaître spontanément des sources de nourriture dans l’environnement simulé.

---

## ⚙️ Commandes  

* touche `C` → affecte la température minimale (-10°C) à l'environnement
* touche `N` → affecte la température usuelle (20°C) à l'environnement
* touche `F` → affecte la température maximale (35°C) à l'environnement
* touche `Y` → permet de changer la température de l'environnement
* touche `Q` → permet d'observer l'affichage des phéromones perçues par la fourmi
* touche `W` → crée une fourmi ouvrière
* touche `S` → crée une fourmi soldat
* touche `T` → ajoute une termite  


* touche `M` → crée l'environnement tel qu'il est configuré dans le fichier `res/map1.map`
* touche `espace` → met la simulation en pause
* touche `D` → met la simulation en mode debug
* touche `R` → reset les stats et l'environnement
* touche `Z` → enregistre les données de la simulation en cours dans un fichier nommé `map_saved.map`
* touche `escape` → ferme la simulation 

 
* touches `PgUp` et `PgDown` → permettent de basculer sur les différents graph représentant l'évolution de la simulation

---

## 📝 Modification de Conception :

L’implémentation du projet a été conduite en accord avec les spécifications fournies dans l’énoncé.

---

## ✨ Fonctionalités étendues de la simulation

Nous avons implémenté plusieurs extensions afin d'enrichir le réalisme et la complexité de la simulation. Voici les principales améliorations:

* Réduction et déshydratation de la nourriture → lorsque la quantité de nourriture passe sous un seuil critique, sa **taille diminue automatiquement** et sa **texture change**: elle est alors considérée comme **déshydratée**.

 
* Mémorisation de points de reprise → Une fonctionnalité de **sauvegarde d'état** a été ajoutée.  
- Appuyer sur la touche `Z` permet d’enregistrer l’état courant de la simulation dans un fichier.
- Cela permet de **reprendre la simulation** à partir de ce point ultérieurement.


* Influence de la température → la **température ambiante** affecte directement l’environnement:
- Elle modifie les **forces de combat** et les **vitesses de déplacement** des animaux.
- En période de **gel**, **l’environnement entier se fige** (freeze).


* Introduction des insecticides → nous avons introduit des **zones d’insecticides** générées automatiquement, similaires aux sources de nourriture.
- Générées via la classe `InsecticideGenerator` (hérite de `Generator`)
- Elles **polluent** les sources de nourriture et les fourmilières à proximité.
- Elles **éliminent tous les animaux** se trouvant dans leur zone d'effet. 
⚠️ Conséquences :
- Les **fourmis ouvrières** ramassant de la nourriture contaminée **meurent**.
- Les **fourmilières exposées rétrécissent** progressivement jusqu’à **disparaître**.


* Cycle Jour / Nuit → un **cycle jour/nuit** a été implémenté à l’aide d’un **type énuméré**.
- Le cycle change **toutes les 5 secondes de simulation**
- Le **fond visuel** de l’environnement est modifié en fonction du moment du cycle

---

## License

This project is for educational purposes.  
Content © Charlotte Daumal & Clemence Kiehl. Academic use only.
