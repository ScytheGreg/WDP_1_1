PRG_C = $(wildcard *.cpp)
OBJ_C = $(patsubst %.cpp,%.o,$(PRG_C))
TARGET = main.e
CFLAGS = @opcjeCpp
SANITIZER_FLAGS = -fsanitize=undefined


all: $(TARGET)

# Kompilacja do plików obiektowych
%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

# Linkowanie WSZYSTKICH plików obiektowych
$(TARGET): $(OBJ_C)
	g++ -g -O0 $(OBJ_C) -o $(TARGET) $(SANITIZER_FLAGS)

clean:
	rm -f *.e *.o

.PHONY: all clean