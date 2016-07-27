#Ping - Pong

##Qu'est - ce ?

Le jeu comme son nom l'indique est un jeu de Ping - Pong inspiré du célèbre jeu disponible sur les toutes premières consoles de salon avec pour seul objectif, déplacer sa raquette de haut en bas pour faire rebondir la balle.

##D'où vient l'idée ?

Étant étudiant en Génie Électrique et Informatique Industrielle nous avions un projet tuteuré, j'ai donc choisi celui - ci dont la consigne était de développer un jeu (au choix) en réseau (avec le protocole choisi). La seule interdiction était d'utiliser un moteur graphique qui simplifierait trop le développement.

##Comment est - il développé le jeu ?

Le jeu est développé en C++ à l'aide de la librairie SFML qui me permet de gérer :

* les éléments dessinables et les formes
* les sockets
* les touches
* les sons
* les vues

Le type de programmation utilisé est l'orienté objet car, pour ce type d'application, cela va nous permettre de mieux gérer les différents éléments comme les raquettes et la balle.

##Caractéristiques du jeu :

Pour ce jeu, deux joueurs sont attendu pour pouvoir jouer, dans le cas contraire, le jeu se lancera mais restera sur le menu (pour la version finale car ceci n'est pas, géré, pour le moment.
Nous pouvons choisir via le menu des paramètres plusieurs options tel que :
* la taille de la balle
* la vitesse de la balle
* la taille des raquettes
* la limite de points pour gagner
* les couleurs des éléments (dans une prochaine mise à jour, voir même utiliser des thèmes déjà créés)


