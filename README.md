# cMandel

![Example mandelbrot image](assets/images/example.png)

cMandel is a C program for generating and rendering mandelbrot sets.

## Dependencies

Install dependencies using your system package manager.

[gd](https://github.com/libgd/libgd)

[zlib](https://zlib.net/)

Or using Nix

`nix develop`

Or if you have Zig installed check out [Using Zig](#using-zig)

## Building

### Using Make

```bash
# Builds
make all

# Cleans up
make clean

# Runs
./cmandel
```

### Using Zig

```bash
# Builds external dependencies and cmandel
zig build

# Runs
./zig-out/bin/cmandel
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first to
discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[MIT](https://choosealicense.com/licenses/mit/)
