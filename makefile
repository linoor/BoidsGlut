BOIDS = boid
UNITTESTS = unittests
SCENE = scene
SOURCES = $(UNITTESTS) $(SCENE) $(BOIDS)
COMPILER = g++
LIBS = -lglut -lGL -lGLU

test:
	$(COMPILER) -std=c++11 $(UNITTESTS).cpp -o unittests
	./unittests

scene: clean
	$(COMPILER) -std=c++11 $(SCENE).cpp $(LIBS) -o scene
	./scene

clean:
	rm -f $(SOURCES)

