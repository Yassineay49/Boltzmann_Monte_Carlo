import os
import subprocess
import time

RED = "\033[31m"
GREEN = "\033[32m"
BLUE = "\033[34m"
YELLOW = "\033[33m"
BOLD = "\033[1m"
RESET = "\033[0m"


def u_init(x):
    y=0
    if 0.4<x<0.6:
        y=1

    return(y)

def u_exact(x,t):
    return(u_init(x-t*1.0))#en considérent que la vitesse est 1 



# Répertoire où se trouvent les fichiers résultat
result_directory = "../../Resultats/"

result_file_name = f"solution_t.txt"

# Chemin complet du fichier résultat
result_file_path = os.path.join(result_directory, result_file_name)
# Vérifier si le fichier résultat existe
if os.path.exists(result_file_path):
    with open(result_file_path, 'r') as file:
        lines = file.readlines()
        components = []
        for line in lines:

            parts = line.strip().split('\t')
            if len(parts) >= 4:
                x = float(parts[0])
                t = float(parts[2])
                u = float(parts[3])
                components.append((x, t, u))

    erreur=0.0
    for k in range(len(components)):
        erreur+=abs(u_exact(components[k][0],components[k][1])-components[k][2])
    erreur_moy=erreur/len(components)

    else:
        print(f"Le fichier {result_file_name} n'existe pas encore.")
    



print(f"L'erreur moyennée sur les itérations est de {erreur_moy}\n")

epsilon = 1.0
if erreur_temps<epsilon:
    print(f"{GREEN} OK\n")
else:
    print(f"{RED} BOF\n")