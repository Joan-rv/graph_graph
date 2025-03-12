#include "graph.h"
#include <raylib.h>

int main(void) {
    const int screen_width = 800;
    const int screen_height = 450;

    struct graph_s graph = read_graph();
    print_graph(graph);

    InitWindow(screen_width, screen_height, "graph_graph");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            DrawText("Hello world", 340, 200, 20, LIGHTGRAY);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
