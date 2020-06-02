# Allows using spaces
.RECIPEPREFIX += 
CPP=g++

CFLAGS=-I.

DEPS = block.h gameboard.h
OBJ = block.o gameboard.o

#  Rule to create .o files from wildcard.cpp.
# Gets called whenever ie. block.o gets requested.
# $@ is the target before the : and $< is the first prerequisite
# I believe this means it runs recursively until $< is met?
%.o: %.cpp $(DEPS)
    $(CPP) -c -o $@ $< $(CFLAGS)

# Create tetris executable from main.cpp and everything listed
# in $OBJ. $^ is the list after the :
tetris: $(OBJ) main.cpp
    $(CPP) -o $@ $^ $(CFLAGS)


# Create tests executable from tests.cpp and everything listed
# in $OBJ
tests: $(OBJ) tests.cpp
    $(CPP) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
    rm -f *.o tetris tests
