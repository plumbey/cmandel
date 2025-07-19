ifeq ($(shell uname -s), Darwin)
BREW_PREFIX := /opt/homebrew/bin/brew --prefix
CFLAGS += -I$(shell $(BREW_PREFIX) libgd)/include
LDFLAGS += -L$(shell $(BREW_PREFIX) libgd)/lib
endif

all: 
	gcc $(CFLAGS) $(LDFLAGS) -o cmandel main.c mandelbrot.c color.c -lgd -lz -lm -O3

clean:
	rm cmandel output.png 2> /dev/null || true
