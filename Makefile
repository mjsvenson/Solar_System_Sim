CC = g++
LSFML = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CFLAGS = -Wall -Werror -pedantic
DEPS = Universe.h CelestialBody.h

all:NBody

NBody: NBody.o CelestialBody.o
	$(CC) $(CFLAGS) -o $@ $^ Universe.h $(LSFML)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $^

clean:
	rm NBody *.o *.gch
