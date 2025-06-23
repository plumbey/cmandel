#include "renderers/raylib/raylib.h"
#include <gd.h>
#define CLAY_IMPLEMENTATION
#include "mandelbrot.h"
#include "clay.h"
#include "renderers/raylib/clay_renderer_raylib.c"
#include <raylib.h>

void handleClayErrors(Clay_ErrorData errorData)
{
    printf("%s", errorData.errorText.chars);
}

int main(void)
{
    Clay_Raylib_Initialize(GetScreenWidth(), GetScreenHeight(), "Mandelbrot Set Viewer", 0);
    uint64_t clay_required_memory = Clay_MinMemorySize();
    Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(clay_required_memory, malloc(clay_required_memory));

    Clay_Initialize(arena, (Clay_Dimensions) {.width = GetScreenWidth(), .height = GetScreenHeight()}, (Clay_ErrorHandler) {handleClayErrors});
    while (!WindowShouldClose())
    {
        Clay_BeginLayout();

        CLAY({.image = {.imageData = mandelbrotImage}})
        
        Clay_RenderCommandArray renderCommands = Clay_EndLayout();

        BeginDrawing();
        Clay_Raylib_Render(renderCommands);
        EndDrawing();
    }
}

