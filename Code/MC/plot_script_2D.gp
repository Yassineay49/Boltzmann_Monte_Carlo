# Utilisez le terminal PNG et définissez la sortie
set terminal png
set output "solution_2d.png"

# Définissez le titre du graphique
set title "Visualisation 2D de la Solution à t=1.000000"

# Définissez les étiquettes des axes
set xlabel "Axe X"
set ylabel "Axe Y"

# Tracez la solution en 2D à partir du fichier de données
plot "solution_t_1.000000.txt" using 1:4 with lines title "Solution t=1.000000"

# Quittez Gnuplot
quit
