BOIDS = boid
UNITTESTS = unittests
SCENE = scene
SOURCES = $(UNITTESTS) $(SCENE) $(BOIDS)
CC = g++
LIBS = -lglut -lGL -lGLU

test:
	$(CC) -std=c++11 $(UNITTESTS).cpp $(LIBS) -o unittests
	./unittests

scene: clean
	$(CC) -std=c++11 $(SCENE).cpp $(LIBS) -o scene
	./scene

clean:
	rm -f $(SOURCES)

