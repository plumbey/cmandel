#include "argsparse.h"

void print_help() {
    printf("cMandel v0.2\n");
    printf("Commands\n");
    printf("--------\n");
    printf("INFO: all examples are the default values\n");

    printf("-w: image width specifier in pixels\n");
    printf("Example: ./cmandel -w 3000\n\n");

    printf("-h: image height specifier in pixels\n");
    printf("Example: ./cmandel -h 3000\n\n");

    printf("-d: coordinate delta specifier\n");
    printf("specifies the distance between coordinate center points and their "
           "bounds\n");
    printf("Example: ./cmandel -d 1.0\n\n");

    printf("-x: coordinate x specifier\n");
    printf("specifies the x center point\n");
    printf("Example: ./cmandel -x -0.5\n\n");

    printf("-y: coordinate y specifier\n");
    printf("specifies the y center point\n");
    printf("Example: ./cmandel -y 0.0\n\n");

    printf("-m: maximum iteration specifier\n");
    printf(
        "specifies the maximum amount of iterations to generate the mandelbrot "
        "set\n");
    printf("Example: ./cmandel -m 1024\n\n");

    printf("-p: hue power specifier\n");
    printf("specifies how rainbow you want the mandelbrot set\n");
    printf("this is evaluated as an exponent so be careful with it (or don't I "
           "guess)\n");
    printf("Example: ./cmandel -p 1.2\n\n");

    printf("-D: darkness specifier\n");
    printf("specifies how dark you want the mandelbrot set\n");
    printf("this is evaluated as an exponent so be careful with it (or don't I "
           "guess)\n");
    printf("Example: ./cmandel -D 0.1\n\n");

    printf("-c: color-in specifier\n");
    printf("true or false specifier setting whether the set should be colored "
           "black\n");
    printf("Example: ./cmandel -c true\n\n");

    printf("-o: relative output filepath\n");
    printf("string specify where to write the output to, as a png\n");
    printf("Example: ./cmandel -o \"output.png\"\n");
    printf("Example: ./cmandel -o \".\"\n\n");

    printf("-t: maximum number of threads to use\n");
    printf("specifies as an integer how many threads will be allocated to "
           "cMandel. "
           "Set to 0 for all threads\n");
    printf("Example: ./cmandel -t 0\n");

    printf("--help: help menu\n");
    printf("prints this menu\n\n");
}
void parse_args(int argc, char *argv[], MandelData *data) {
    data->width = 3000;
    data->height = 3000;
    data->delta = 1.0;
    data->xCenter = -0.5;
    data->yCenter = 0;
    data->iterMax = 1024;
    data->huePower = 1.2;
    data->darkness = 0.1;
    data->colorIn = true;
    data->output = "./output.png";
    data->numThreads = 0;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-w") == 0 && i + 1 < argc) {
            int w = atoi(argv[++i]);
            if (w == 0 || w > 45000) {
                printf("Error! Invalid width specified\n");
                exit(1);
            }
            data->width = w;
        } else if (strcmp(argv[i], "-h") == 0 && i + 1 < argc) {
            int h = atoi(argv[++i]);
            if (h == 0 || h > 45000) {
                printf("Error! Invalid height specified\n");
                exit(1);
            }
            data->height = h;
        } else if (strcmp(argv[i], "-d") == 0 && i + 1 < argc) {
            double d = atof(argv[++i]);
            if (d == 0) {
                printf("Error! Invalid delta specified\n");
                exit(1);
            }
            data->delta = d;

        } else if (strcmp(argv[i], "-x") == 0 && i + 1 < argc) {
            double x = atof(argv[++i]);
            if (x == 0) {
                printf("Error! Invalid x center specified\n");
                exit(1);
            }
            data->xCenter = x;

        } else if (strcmp(argv[i], "-y") == 0 && i + 1 < argc) {
            double y = atof(argv[++i]);
            if (y == 0) {
                printf("Error! Invalid y center specified\n");
                exit(1);
            }
            data->yCenter = y;

        } else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            int m = atoi(argv[++i]);
            if (m == 0) {
                printf("Error! Invalid max iteration specified\n");
                exit(1);
            }
            data->iterMax = m;

        } else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            double p = atof(argv[++i]);
            if (p == 0) {
                printf("Error! Invalid hue power specified\n");
                exit(1);
            }
            data->huePower = p;

        } else if (strcmp(argv[i], "-D") == 0 && i + 1 < argc) {
            double D = atof(argv[++i]);
            if (D == 0) {
                printf("Error! Invalid darkness specified\n");
                exit(1);
            }
            data->darkness = D;

        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            i++;
            if (strcmp(argv[i], "false") == 0)
                data->colorIn = false;
            else if (strcmp(argv[i], "true") == 0)
                data->colorIn = true;
            else {
                printf("Error! Invalid color-in setting!\n");
                exit(1);
            }
        } else if (strcmp(argv[i], "--help") == 0) {
            print_help();
            exit(0);
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            char *name = argv[++i];
            int len = strlen(name);
            int has_slash = strchr(name, '/') != NULL;
            int has_png = len >= 4 && strcmp(name + len - 4, ".png") == 0;

            // Add ./ if no slash
            char temp[1024] = {0};
            if (!has_slash)
                strcat(temp, "./");

            strcat(temp, name);

            // Add .png if missing
            if (!has_png)
                strcat(temp, ".png");

            // Copy to data->outputName
            data->output = strdup(temp);
            if (data->output == NULL) {
                printf("Error! Could not allocate memory for output name\n");
                exit(1);
            }
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            int t = atoi(argv[++i]);
            if ((t == 0) || (t > omp_get_max_threads())) {
                printf(
                    "Error! Invalid thread count specified. Max threads: %i\n",
                    omp_get_max_threads());
                exit(1);
            }
            data->numThreads = t;
        }
    }
}
