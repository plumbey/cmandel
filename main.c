#include "raylib.h"
#include <gd.h>
#define CLAY_IMPLEMENTATION
#include "mandelbrot.h"
#include "clay.h"
#include "clay_renderer_raylib.c"

void handleClayErrors(Clay_ErrorData errorData)
{
    printf("%s", errorData.errorText.chars);
}

int main(void)
{

    MandelbrotData mandelbrotData =
    {
        // This makes the image dimensions square, eliminating distortions
        .pixelWidth = 2000,
        .pixelHeight = 2000,
        .realCenter = -0.8,
        .imagCenter = 0.0,
        .coordinateDelta = 1.5,
        .maxIterations = 512,
        .hueIntensity = 0.8,
        .darkness = 0.125
    };

    gdImagePtr mandelbrotImagePtr; 
    mandelbrotImagePtr = gdImageCreateTrueColor(mandelbrotData.pixelWidth, mandelbrotData.pixelHeight);

    generateMandelbrot(mandelbrotImagePtr, mandelbrotData);
    FILE* output = fopen("mandelbrot.png", "wb");
    gdImagePng(mandelbrotImagePtr, output);
    fclose(output);

    Clay_Raylib_Initialize(GetScreenWidth(), GetScreenHeight(), "Mandelbrot Set Viewer", 0);
    uint64_t clay_required_memory = Clay_MinMemorySize();
    Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(clay_required_memory, malloc(clay_required_memory));

    Clay_Initialize(arena, (Clay_Dimensions) {.width = GetScreenWidth(), .height = GetScreenHeight()}, (Clay_ErrorHandler) {handleClayErrors});
    /*
    Image inputImage = LoadImage("mandelbrot.png");
    Texture2D textureFromImage = LoadTextureFromImage(inputImage);
    */
    while (!WindowShouldClose())
    {
        Clay_BeginLayout();

        Clay_Sizing layoutExpand = {
            .width = CLAY_SIZING_GROW(0),
            .height = CLAY_SIZING_GROW(0)

        };
/*
        CLAY({.id = CLAY_ID("Background Image"),
                .image = {.imageData = input},
                .layout = {
                    .sizing = layoutExpand
                }
            }){};
 */       
        CLAY({ .id = CLAY_ID("OuterContainer"),
            .backgroundColor = {255, 255, 255, 255 },
            .layout = {
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                .sizing = layoutExpand,
                .padding = CLAY_PADDING_ALL(16),
                .childGap = 16
            },
            .image = {.imageData = &textureFromImage}
        }){} 
        Clay_RenderCommandArray renderCommands = Clay_EndLayout();

        BeginDrawing();
        ClearBackground(RED);
        Clay_Raylib_Render(renderCommands, NULL);
        EndDrawing();
    }
    gdImageDestroy(mandelbrotImagePtr);
    Clay_Raylib_Close();
}

