#JOURNAL PROJET SV 2021

##groupe 31 Charlotte Daumal et Clémence Kiehl
##coach: Aline Brunner 


###**Étape 1 : Vecteurs toriques**

**[Q1.1]** Pour éviter de dupliquer du code, on peut utiliser appeler certains constructeurs dans la définition d’autres constructeurs.
Cela rend le code plus lisible et plus concis et permet à certains constructeurs d’être écrits en seulement une ligne.

**[Q1.2]** Pour l’opérateur +, nous avons choisi une surcharge externe car nous pouvons écrire la définition de cet opérateur sans faire de copies inutiles et uniquement en utilisant l’interface de la classe ToricPosition. De plus, nous avons choisi de définir l’opérateur + à l’aide de l’opérateur +=, que nous avons défini précédemment, pour rendre notre code plus concis et établir un lien sémantique entre ces deux opérateurs.

**[Q1.3]** Pour l’opérateur <<, nous avons choisi une surcharge externe car on souhaite surcharger la classe ToricPosition. Or, celle-ci ne peut pas être l’opérande de gauche de l’opérateur << (qui sera en fait toujours précédé d’un flot de sortie).

**[Q1.5]** Pour réaliser l’algorithme demandé, nous avons décidé d’écrire deux boucles for, nous permettant de calculer les huit positions candidates grâce à uniquement deux Vec2d, et de rédiger seulement deux itérations conditionnelles if, pour toujours déterminer la plus petite distance à this et le vecteur position candidate correspondante. Ainsi, on rend le code plus concis, plus modularisé et moins répétitif.

**[Q1.6]** Pour éviter la duplication de code dans les fonctionnalités d’affichages, nous avons choisi de définir l’opérateur << en appelant dans sa définition la méthode ostream& display(ostream& out). 


###**Étape 2 : Promenades au hasard**

**[Q2.1]** On déclare en tant que const les méthodes qui sont des prédicats, c’est à dire les méthodes qui n’ont pas le droit de modifier les variables de la classe.
-> Dans notre cas, uniquement la méthode drawOn ne semble être un prédicat. Il semble donc judicieux de la déclarer comme const.

**[Q2.2]** Si on veut interdire la copie et l’affectation d’un Environment, il faut supprimer le constructeur de copie par défaut et supprimer l’opérateur d’affectation au moyen de la commande delete.

**[Q2.3]** Un Environment peut donc être considéré comme responsable de la durée de vie des animaux et des sources de nourritures amenés à être créés dans la simulation. Ainsi, si l’on détruit un Environment, on détruit aussi les animaux et la nourriture qui y sont associés.
La destruction d’un Environment peut se faire au moyen de la méthode reset().

**[Q2.4]** Une source de nourriture étant avant tout une entité dotée d’une position torique dans notre environnement torique, la classe Food est reliée à la classe Positionable par une relation de type « EST-UN ». Ainsi, il semble astucieux de faire hériter la classe Food de la classe Positionable pour modéliser cet aspect.

**[Q2.5]** Utiliser le type Quantity plutôt que d’un double rend le code plus lisible. En effet, en lisant les attributs de la classe Food, on aura un type Quantity qui décrit une quantité et nous ne sommes pas obligé de connaitre le sens du type double pour comprendre cette partie du code.

**[Q2.6]** Pour que la génération de nourriture se lance automatiquement, il faut appeler dans la définition de la méthode Environment:: update(sf::Time dt), la méthode FoodGenerator :: update(sf::Time dt).

**[Q2.7**] À ce stade, la classe Animal est une sous-classe de la classe Positionable, dont elle hérite. Elle est caractérisée par plusieurs attributs :
Une direction : _direction (Angle)
Un nombre de points de vie : _life_points (int)
Une espérance de vie : _ life _expectancy (int). 
Elle est également caractérisée par sa vitesse de déplacement, qui est accessible via la méthode getSpeed().
Sa position sera représentée à travers son lien d’héritage avec la super-classe Positionable (qui possède elle un paramètre représentant sa position torique) et sera donc un ToricPosition.

**[Q2.8**] La contrainte imposée sur le codage de setDirection se traduit en mettant cette méthode en protected. Ainsi, comme cela est requis, la méthode pourra être utilisée uniquement par les potentielles sous-classes d’Animal, ce qui évite toute modification incongrue du paramètre en question.

**[Q2.9**] On peut appeler la méthode de dessin drawOn dans le constructeur de la classe Animal. Ainsi, à chaque fois qu’un Animal sera créé, il sera automatiquement affiché. 

**[Q2.10**] Pour que les animaux de notre simulation se déplacent, nous devons modifier la méthode update de la classe Environment. Nous devons appeler dans cette méthode la méthode update de la classe Animal qui appelle au sein de sa définition la méthode move de la classe Animal, qui s’occupe de modéliser le déplacement des animaux dans l’environnement.

**[Q2.11]** Pour que On appelle la méthode isDead dans la méthode update de la classe Environment et si l’animal en question est considéré comme mort, on « delete » l’animal et on affecte au pointeur concerné la valeur nullptr avant d’effacer à la fin de la méthode les pointeurs nullptr du tableau paramètre contenant les animaux de l’environnement. 


###**Étape 3 : Les fourmis entrent en scène**

**[Q3.1**] Il semble bon de faire hériter toutes les classes possédant une méthode drawOn de Drawable et celles possédant une méthode update de Updatable. 
Ainsi, il nous semble judicieux de faire hériter de Drawable les classes Animal, Environment et Food et de faire hériter d’Updatable les classes Animal, Environment et FoodGenerator.
Cela amène un avantage à la conception : ces sous-classes devront obligatoirement redéfinir leurs méthodes drawOn et update si elles doivent rester instanciables (car ces méthodes sont virtuelles pures dans les classes Drawable et Updatable), ce qui est essentiel pour la bonne excévution du projet.

**[Q3.2]** Ici, il nous semble correct de déclarer la méthode getSpeed() comme virtuelle pure dans Animal.hpp car tous les animaux pouvant peupler notre environnement hériteront de la classe Animal et seront donc obligés d’avoir une vitesse de déplacement pour exister.
De plus, dans la classe Animal, il ne devrait pas être possible de définir explicitement cette méthode. Cependant, elle doit rester présente car elle représente un attribut de la classe Animal (vitesse de l’animal).
Par ailleurs, avec cette méthode virtuelle pure, la classe Animal devient une classe abstraite, et donc non instanciable.

**[Q3.3]** Pour éviter de dupliquer du code, nous avons décidé de déplacer la méthode drawOn(sf::RenderTarget& target) qui était présente dans la classe Animal dans la classe Ant, de la déclarer en tant que méthode virtuelle et de rajouter un paramètre de type string qui détermine la texture de l’affichage. 
Ainsi, dans les classes AntSoldier et AntWorker, nous appelons cette méthode en passant en paramètre la texture spécifique associée à la fourmi en question, à l’aide de l’opérateur de résolution de portée.

**[Q3.4**] Il n’est alors plus nécessaire pour la classe Animal de contenir une définition de la méthode drawOn(). En effet, on ne sait pas dessiner un animal quelconque.

**[Q3.5**] Il était important de modéliser l’ensemble des animaux de l’environnement comme un ensemble de pointeurs pour permettre le comportement polymorphique de ceux-ci, par exemple via l’affichage.

**[Q3.6]** À ce stade, on aboutit à la conception suivante : une classe Anthill qui hérite de Positionable, Drawable, Updatable. 
Elle est caractérisée par les attributs suivants : 
Un stock de nourriture : _food_stock (Quantity)
Un identifiant : _id (Uid)

**[Q3.7]** Afin de tenir compte des fourmilières, nous avons rajouté un attribut _anthills à la classe Environment. Nous avons donc dû modifier les méthodes reset, drawOn et update ainsi que le constructeur de Environment.

**[Q3.8]** On implémente la génération automatique des fourmis dans la méthode update de la classe Anthill.
Dans le programme, la méthode update de la classe Anthill sera appelée par la méthode update de la classe Environment.
(Raisonnement similaire à celui effectué pour la méthode update de FoodGenerator à l’étape 2)

**[Q3.9]** Pour éviter de dupliquer du code dans la sous-classe AntWorker, nous avons redéfini la méthode update dans la sous-classe AntWorker pour inclure leur comportement spécifique. Et, pour qu’elles gardent le comportement de base de tous les animaux, nous avons appelé la méthode update de la classe Ant qui appelle elle-même la méthode update de la classe Animal.

**[Q3.10]** La méthode update de la classe AntWorker va utiliser ces méthodes pour savoir si la fourmi a rencontré une source de nourriture ou non ou si elle rencontre une fourmilière et ainsi, la faire évoluer dans notre environnement.

**[Q3.11]** À ce stade, nous aboutissons à la conception suivante : une classe Pheromone qui hérite de la classe Positionable. 
Elle est caractérisée par les attributs suivants :
Une quantité de nourriture :  _quantity (double)
Un chronomètre : _timer (sf ::Time)

**[Q3.12]** Pour mémoriser la position de la fourmi, nous créons un attribut (_p0) qui contiendra la dernière position où la fourmi a déposé une trace de phéromone. Ceci va modifier la construction de la fourmi car nous allons devoir initialiser cet attribut dans le constructeur de la classe Ant.

**[Q3.13]** Une fois que nous avons ajouté les phéromones, nous devons modifier les méthodes reset, drawOn et update de la classe Environment.


###**Étape 4 : Prédateurs et combats**

**[Q4.1]** C’est la méthode move qui utilise la vitesse de déplacement du termite. Nous allons redéfinir cette méthode dans notre classe Termite.

**[Q4.2]** Nous aboutissons à la conception suivante : une classe Termite qui hérite de la classe Animal. A ce stade de la conception, la classe se caractérise par un attribut compteur de temps  _timer.

**[Q4.3]** Tester le type des objets à l'exécution peut être potentiellement nocif : en effet, il se peut que le type d’un objet soit inconnu à cause de l’héritage. Par exemple, si un objet est considéré comme un objet d’une classe de base de sa véritable classe, on ne peut pas déterminer a priori sa véritable nature. 
(Dans notre cas par exemple, une AntWorker est aussi une Ant et un Animal -> confusion lors des tests de type)
C’est pourquoi nous privilégions donc dans notre cas la technique du Double Dispatch, qui permet de dispatcher un appel à une méthode vers une méthode concrète suivant le type des objets appelés en paramètre.

**[Q4.4]** Afin de modéliser/initialiser l'état de l'animal, nous allons utiliser les types énumérés. Ils consistent en une liste de valeurs entières qui peuvent être attribuées à une variable appartenant à ce type énuméré. Dans notre cas, nous définissons dans la classe Animal un type énuméré Enum Status qui comprend trois états possibles : Attack, Idle et Escaping.

**[Q4.5]** Pour utiliser la force d’attaque, nous avons créé une méthode virtuelle pure fight dans Animal, que nous redéfinissons dans toutes ses sous-classes instanciables. Cette méthode se charge de décrémenter les points de vie de l’adversaire (un Animal passé en paramètre) de la valeur de la force d’attaque de l’animal qui attaque, passée en paramètres.

**[Q4.6]** La méthode fight de la classe Animal décrite dans la question [Q4.5] permet d’utiliser le polymorphisme concernant le temps durant lequel l’animal reste en mode Attack, qui dépend de son type. En effet, ce délai imparti est passé en paramètre lors des appels à la méthode fight dans les sous-classes de la classe Animal instanciables. Cela permet d’éviter de dupliquer le code de la méthode fight dans les sous-classes Ant et Termite d’Animal.

**[Q4.7]** Pour le repérage des ennemis par les prédateurs, nous pouvons créer la méthode getClosestEnemy dans la classe Environment. Celle-ci retourne, s’il existe, un ennemi proche et perceptible par l’animal. 
Ainsi, pour déterminer si un animal est l’ennemi d’un autre, nous appelons la méthode virtuelle pure IsEnemy de la classe Animal, redéfinie dans ses sous-classes instanciables. 

**[Q4.8]** Pour parer à un rebasculement "perpétuel" en mode Attack si les béligérants ne s'éloignent pas suffisament de leurs rayons de perception après avoir rebasculé en mode Idle, nous avons instauré un timer (_timer_peace) décomptant un temps minimum durant lequel l’animal n’a pas le droit de se mettre en mode Attack après un combat. 


###**Étape 5 : Statistiques et points de reprises**

**[Q5.1]** Les structures de données que nous avons choisies pour l’ensemble des graphes et l’ensemble des titres de la classe Stats sont des std::map. Elles stockent des std::unique_ptr<Graph> et des std::string pour respectivement pour l’ensemble de graphes et l’ensemble de titres, et ont toutes deux des clés de type int.

**[Q5.2]** Pour compter le nombre d’instances d’une certaine classe, nous itérons sur les ensembles d’animaux et de nourriture dans la classe Environment. Nous réalisons ces décomptes dans la méthode countEntities() de la classe Environment et les constructions des ensembles new_data dans la méthode fetchdata dans la classe Environment.
Pour compter le nombre de sources de nourritures présentes dans l’environnement, il suffit de prendre la taille du std::vector _food les répertoriant et la décrémenter de un.
Pour différencier et compter les différents animaux, nous avons mis en place des identifiants de type (attributs de tous les animaux) qui sont d’un si l’animal est une AntWorker, deux si l’animal est un AntSoldier et trois s’il s’agit d’une Termite. Cela nous permet de les compter de façon distincte grâce au polymorphisme qui est offert par les pointeurs du std::vector _animals les répertoriant.


