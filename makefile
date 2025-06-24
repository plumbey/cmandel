ifeq ($(shell uname -s), Darwin)
BREW_PREFIX := /opt/homebrew/bin/brew --prefix
CFLAGS += -I$(shell $(BREW_PREFIX) libgd)/include
LDFLAGS += -L$(shell $(BREW_PREFIX) libgd)/lib
endif

all: mandelbrot color
	gcc $(CFLAGS) $(LDFLAGS) -o main main.c mandelbrot.o color.o raylib.h -lgd -lz -lm -lraylib

color:
	gcc $(CFLAGS) $(LDFLAGS) -o color.o -c color.c	-lgd -lz -lm

mandelbrot:
	gcc $(CFLAGS) $(LDFLAGS) -o mandelbrot.o -c mandelbrot.c -lgd -lz -lm 

clean:
	@rm mandelbrot.o color.o clay_raylib.o
