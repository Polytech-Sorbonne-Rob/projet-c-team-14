# Projet C 

## A propos

Ce programme possède plusieurs fonctionnalités. Il permet dans un premier temps le **tracking** d'une plage de couleur avec l'utilisation d'un **pan-tilt équipé de sa caméra** à l'aide d'une carte arduino. De plus, il utilise [tesseract](https://github.com/tesseract-ocr/tesseract), un logiciel de reconnaissance optique de caractères. Ce dernier a été entrainé afin de pouvoir reconnaître des calculs simples de la forme:

`a + b = c` ou plus généralement `expr1 = expr2`.

Les caractères lus sont : 
* les entiers de **0** à **9**
* les symboles mathématiques suivant: **+ - x**

Pour accéder à la documentation, il faut ouvrir le fichier `html\index.html`.

## Préparation

Dans un premier temps, assurez-vous d'avoir la bibliothèque [OpenCV](https://docs.opencv.org/master/) qui suit ce chemin:
```
/usr/include/opencv2
```

Afin d'utiliser le pan-tilt, il faut téléverser le [programme arduino](./code_arduino/) sur la carte qui se situe dans le dossier code_arduino.


Il est nécéssaire d'installer tesseract au préalable pour l'utilisation du projet libre. 

```
sudo apt-get install tesseract-ocr
```

Afin d'installer la bibliothèque de reconnaissance d'écriture manuscrite, Il faut placer le fichier foo.traineddata, qui se trouve dans le dossier extra, dans le chemin:
```
/usr/share/tesseract-ocr/4.00/tessdata/
```

Pour lancer le programme, il suffit de taper les commandes suivantes:
```
make

./main 
```

Aucun paramètre d'entrée n'est nécessaire.


## Projet imposé
Le projet imposé consiste à réaliser le tracking d'une couleur avec l'utilisation d'une caméra pan-tilt et d'une carte arduino.

Ce dernier autorise deux possibilités: 
- la première consiste à mouvoir la caméra en utilisant les touches `zqsd` tel des touches directionnelles.
- la seconde est le tracking du vert avec la caméra.

Cette seconde possibilité possède aussi une trackbar qui permet à l'utilisateur de régler la plage de couleurs souhaitée de manière très précise.

Afin d'accéder au projet imposé, il faut:
- lancer le programme
- appuyer sur la touche `v`
- puis appuyer sur la touche `m` pour intervertir entre le mode manuel et le mode tracking

Afin de quitter le programme, il est nécessaire d'appuyer sur la touche `echap` du clavier.

## Projet libre
Le projet libre consiste à déterminer si une équation présentée devant la caméra est juste ou fausse.

Afin d'accéder au projet libre, il faut:
- lancer le programme
- appuyer sur la touche `b`

Tout comme le projet imposé la caméra peut être déplacée avec les touches `zqsd`.

Une fois que le mode est choisi, une fenêtre apparait avec un rectangle au centre. Pour utiliser le programme, il faut:
- écrire l'équation voulue sur un fond blanc avec un gros marqueur (par exemple une ardoise) de la forme `expr1=expr2`
- placer l'équation entière dans le rectangle central 
- appuyer sur la touche "enter"
- vérifier sur la console si l'équation est celle attendue: si oui appuyer sur `a` si non appuyer sur `e` pour recommencer à partir de la deuxième étape

La caméra fera alors un hochement de tête si l'équation est juste et un signe "non" sinon.

Il est aussi possible de forcer ce mouvement de tête en appuyant sur les touches:
* `y` pour oui
* `n` pour non


### Remerciements
Nous tenons particulièrement à remercier **M. Saint-Bauzel** et **M. Maurice** pour leur accompagnement tout au long de ce projet.

Ainsi que les Gits suivant qui nous ont permis d'obtenir le css et le javascript de la documentation:
* [jothepro](https://github.com/jothepro/doxygen-awesome-css) 
* [Velron](https://github.com/Velron/doxygen-bootstrapped)

### Auteurs : Léo LAVAL & Lucas RIBEIRO
