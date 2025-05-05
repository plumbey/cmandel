all: mandelbrot
	clang -o main main.c mandelbrot.o -lgd -lpng -lz -ljpeg -lfreetype -lm -O3
mandelbrot:
	clang -c mandelbrot.c -o mandelbrot.o 
clean:
	@rm mandelbrot.o
