# Ce dossier contient les fichiers visant à tester l'échantillonnage de la fonction SampleVprime

Le fichier sampling_test.cpp fait office de "main". Il s'appuie sur les fichiers du répertoire parent "MC" (domain.cpp, population.cpp, particles.cpp, parametres.cpp). IL génère un vecteur de vecteur de taille 3 * nMC (3 dimensions * le nombre de particules) contenant des coordonnées cartésiennes puis écrit ces données dans un fichier .json

Le fichier treatment.py lit les fichiers data.json et nMC.json pour connaître le nombre de particules et les coordonnées tirées aléatoirement. Il calcule ensuite la moyenne des coordonnées tirées en x, y et z et effectue un test de Kolmogorov-Smirnov pour s'assurer que le tirage aléatoire est bien effectué uniformément sur la sphère unité.

# Compilation
g++ -o run sampling_test.cpp ../../domain.cpp ../../particles.cpp ../../population.cpp ../../parameters.cpp -I..

# Exécution
./run

python3 treatment.py



NB :
Fichier sampling_test.cpp légèrement différent du main.cpp du répertoire parent
Raison : ce dernier est encore en évolution
Ce cas test sera mis à jour une fois le code de résolution achevé