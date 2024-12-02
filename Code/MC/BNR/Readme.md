# Base de non régression


## Execution

Pour éxecuter la base de test il surffit de taper la commande :
```bash
python3 BNR.py
```

## Structure du code


Le script __BNR.py__ fait une boucle sur tous les tests disponibles. Il existe deux sortes de test. En premier sont ceux qui test simplement des fonctions au sein des modules, et donc vont utiliser tout le code "parent" exepté le main. Les autres sont ceux qui calcul une solution avec le main du répertoire parent.
Un Readme relatif à chaque test est disponible dans les sous répertoire.

### première type
Lors de la boucle le système compile en utilisant le __Makefile__ disponible dans chaque répertoire. Ensuite le programme est executé puis les messages relatifs sont affichés dans la console. L'utilisateur est invité à les lire et décider de si le test est validé ou non. Enfin un "make clean" est effectué dans le répetoire puis le système passe au test suivant.

### deuxième type
Lors de la boucle le système compile en utilisant le __Makefile__ disponible dans le programme princiapal. Ensuite le programme est executé en utilisant le fichier de paramètre correspondant au test. L'utilisateur est invité à lire les messages de sorties et à décider de si le test est validé ou non. Enfin un "make clean" est effectué dans le répetoire principal ___MC___.