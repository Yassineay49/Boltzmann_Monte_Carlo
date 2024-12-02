OBJS	= parameters.o particles.o population.o domain.o main.o
SOURCE	= parameters.cpp particles.cpp population.cpp domain.cpp main.cpp
HEADER	= parameters.hpp particles.hpp population.hpp domain.hpp main.hpp
OUT	= main
CXX	 = g++
FLAGS	 = -c -O3 -std=c++11

all: $(OBJS)
	$(CXX) -g $(OBJS) -o $(OUT) $(LFLAGS)

parametres.o: parametres.cpp
	$(CXX) $(FLAGS) parametres.cpp 

particles.o: particles.cpp
	$(CXX) $(FLAGS) particles.cpp 

population.o: population.cpp
	$(CXX) $(FLAGS) population.cpp 

domain.o: domain.cpp
	$(CXX) $(FLAGS) domain.cpp 

main.o: main.cpp
	$(CXX) $(FLAGS) main.cpp 


clean:
	rm -f $(OBJS) $(OUT) Resultats/solution*.txt *.png
clean_res:
	rm -f Resultats/solution*.txt