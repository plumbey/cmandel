ifeq ($(shell uname -s), Darwin)
BREW_PREFIX := /opt/homebrew/bin/brew --prefix
CFLAGS += -I$(shell $(BREW_PREFIX) libgd)/include
LDFLAGS += -L$(shell $(BREW_PREFIX) libgd)/lib
endif

OUT = cmandel

all: 
	gcc $(CFLAGS) $(LDFLAGS) -o $(OUT) main.c mandelbrot.c color.c -lgd -lz -lm -O3

run: all
	./$(OUT)

clean:
	rm cmandel output.png 2> /dev/null || true
