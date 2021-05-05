CC = gcc

# Debug
CFLAGS = -Iinclude -I../src -g -O2
LDFLAGS = -lSOIL -lglut32 -lopengl32 -lglu32 -lm
UNIXFLAGS = -lSOIL -lglut -lGL -lSOIL -lGLU -lm 
SOURCES = \
	camera.c \
    draw.c \
    model.c \
	callbacks.c \
    main.c

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = grafika

all: $(SOURCES) $(EXECUTABLE)


$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@



clean:
	rm $(OBJECTS)
