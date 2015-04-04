UNITTESTS = unittests
SCENE = scene
SOURCES = $(UNITTESTS) $(SCENE)
COMPILER = g++
LIBS = -lglut -lGL -lGLU

test:
	$(COMPILER) -std=c++11 $(UNITTESTS).cpp -o unittests
	./unittests

scene:
	$(COMPILER) $(SCENE).cpp $(LIBS) -o scene
	./scene

clean:
	rm $(SOURCES)

