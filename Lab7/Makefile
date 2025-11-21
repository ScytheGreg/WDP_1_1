PRG_C = $(wildcard *.c)
EXE_C   = $(patsubst %.c,%.e,$(PRG_C))
CFLAGS = @opcje

all: $(EXE_C)

%.e: %.c 
	gcc $(CFLAGS) $^ -o $*.e

clean:
	rm -f *.e