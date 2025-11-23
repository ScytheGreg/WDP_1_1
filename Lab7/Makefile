PRG_C = $(wildcard *.c)
OBJ_C = $(patsubst %.c,%.o,$(PRG_C))
TARGET = main.e
CFLAGS = @opcje
SANITIZER_FLAGS = -fsanitize=undefined


all: $(TARGET)

# Kompilacja do plików obiektowych
%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

# Linkowanie WSZYSTKICH plików obiektowych
$(TARGET): $(OBJ_C)
	gcc $(OBJ_C) -o $(TARGET) $(SANITIZER_FLAGS)

clean:
	rm -f *.e *.o

.PHONY: all clean