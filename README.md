# cMandel

![Example mandelbrot image](assets/images/example.png)

cMandel is a C program for generating and rendering mandelbrot sets.

## Dependencies

This project uses `libpng` and `libomp` using your system package manager.

MacOS versions of llvm don't support libomp, which is what this project uses for multithreading. To get around this, install `llvm` using brew. The Makefile will use this version of llvm, which supports libomp.

## Building

```bash
# Builds
make all

# Cleans up
make clean

# Debug executable
make debug

# Runs
./cmandel
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first to
discuss what you would like to change.

## License

[MIT](https://choosealicense.com/licenses/mit/)
