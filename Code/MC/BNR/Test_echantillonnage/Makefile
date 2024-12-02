# Définir le compilateur
CXX = g++ 

# Définir les options de compilation
CXXFLAGS = -Wall -Wextra -std=c++11

# Nom du fichier exécutable
TARGET = run

# Définir les fichiers source
SOURCES = sampling_test.cpp ../../domain.cpp ../../particles.cpp ../../population.cpp ../../parameters.cpp

# Définir les fichiers objets
OBJECTS = $(SOURCES:.cpp=.o)

# Règle par défaut
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Règle pour créer les fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers compilés
clean:
	rm -f $(OBJECTS) $(TARGET)

# Règle pour empêcher les conflits avec des fichiers de même nom
.PHONY: all clean
