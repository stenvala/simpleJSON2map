CC=g++
CFLAGS=-c -Wall -I/opt/local/include
INC = $(shell pkg-config)
LIB = $(shell pkg-config)
LDFLAGS=
SOURCES=main.cpp json2map.cpp
OBJECTS=$(SOURCES:.cpp=.o)

main: $(SOURCES) $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIB)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(INC)

clean:
	rm *.o


