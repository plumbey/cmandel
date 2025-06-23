ifeq ($(shell uname -s), Darwin)
BREW_PREFIX := /opt/homebrew/bin/brew --prefix
CFLAGS += -I$(shell $(BREW_PREFIX) libgd)/include
LDFLAGS += -L$(shell $(BREW_PREFIX) libgd)/lib
endif

all: 
	gcc $(CFLAGS) $(LDFLAGS) -o main main.c mandelbrot.c color.c renderers/raylib/clay_renderer_raylib.c -lgd -lz -lm -lraylib -O3
