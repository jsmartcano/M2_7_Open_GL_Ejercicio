CC = gcc
LDLIBS = -lGL -lGLU -lglut  
TARGETS=  planetariosol robotsol

all: $(TARGETS)

clean:
	rm -f *.o *.~ *~ $(TARGETS)