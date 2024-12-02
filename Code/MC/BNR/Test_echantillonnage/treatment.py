import json
import numpy as np
import scipy

# Chemin vers le fichier output.json
output_json = 'data.json'

# Charger le fichier JSON
with open(output_json, 'r') as f:
    data_samples = json.load(f)

# Chemin vers le fichier output.json
output_json1 = 'nMC.json'

# Charger le fichier JSON
with open(output_json1, 'r') as f1:
    n_samples = json.load(f1)

# Traitement - Tests d'hypothèses statistiques
#Commençons par séparer les coordonnées x, y et z en 3 listes

data_transpose = list(map(list, zip(*data_samples)))

data_x = data_transpose[0]
data_y = data_transpose[1]
data_z = data_transpose[2]

#Calcul des moyennes (qui doivent tendre vers 0)
moyenne_x = np.mean(data_x)
moyenne_y = np.mean(data_y)
moyenne_z = np.mean(data_z)

# Afficher les moyennes
print("Moyenne des coordonnées en X:", moyenne_x)
print("Moyenne des coordonnées en Y:", moyenne_y)
print("Moyenne des coordonnées en Z:", moyenne_z)

#TEST DE KOLMOGOROV SMIRNOV
#Tirage aléatoire uniforme dans [-1,1] de taille n_samples
sample_test = np.random.uniform(-1,1,n_samples)

#print(scipy.stats.kstest(data_x,sample_test))
#print(scipy.stats.kstest(data_y,sample_test))
#print(scipy.stats.kstest(data_z,sample_test))

statistic, p_value_1 = scipy.stats.kstest(data_x,sample_test)
statistic, p_value_2 = scipy.stats.kstest(data_y,sample_test)
statistic, p_value_3 = scipy.stats.kstest(data_z,sample_test)


if n_samples < 1000 :
    print("Attention : l'échantillon fourni est trop petit pour être représentatif, il se peut que la moyenne ou le test de Kolmogorov-Smirnov bloquent")

if moyenne_x > 0.1 or moyenne_y > 0.1 or moyenne_z > 0.1 :
    print("Attention : l'échantillon tiré ne semble pas uniforme sur la sphère unité, la moyenne des coordonnées est trop éloignée de 0")
else :
    print("La moyenne des coordonnées du tirage aléatoire tend vers 0")
    
if p_value_1 < 0.05 or p_value_2 < 0.05 or p_value_3 < 0.05 :
    print("Attention : le test de Kolmogorov-Smirnov donne une p-value inférieure à 5%, le tirage aléatoire n'est donc très certainement pas uniforme sur la sphère unité")
else :
    print("Le test de Kolmogorov-Smirnov donne une p-value supérieure à 5%, il n'y a donc pas de raison de rejeter l'hypothèse que le tirage est uniforme sur la sphère unité")




