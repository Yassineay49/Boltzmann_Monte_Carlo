set palette defined (-5 0 0 1, 0 1 1 1, 5 1 0 0)
set terminal gif enhanced font "Nunito Sans" 30 animate delay 20 loop 1 optimize size 3000,2000
set output "advection.gif"
set xr[-1:1]
set yr[-1:6]
dt=0.1
do for [i=0:10] {
t=i*dt
set title "t = ".sprintf("%f", t)." s"
plot "Resultats/solution_t_".i.".txt" u 1:5 with lines lw 10
}
set output