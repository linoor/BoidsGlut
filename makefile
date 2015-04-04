UNITTESTS = unittests
SCENE = scene
SOURCES = $(UNITTESTS) $(SCENE)
COMPILER = g++

test:
	$(COMPILER) -std=c++11 $(UNITTESTS).cpp -o unittests
	./unittests

scene:
	$(COMPILER) $(SCENE).cpp -lGL -lglut -o scene
	./scene

clean:
	rm $(SOURCES)

