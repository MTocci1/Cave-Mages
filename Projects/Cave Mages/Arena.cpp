#include <SFML/Graphics.hpp>
#include "Arena.h"

int createBackground(VertexArray& rVA, IntRect arena)
{
    // Anything we do to rVA, we are actually doing to the background (in the main function)

    // How big is each tile/texture
    const int TILE_SIZE = 100; // Change this to the size of your tile
    const int VERTS_IN_QUAD = 4;

    int worldWidth = arena.width / TILE_SIZE;
    int worldHeight = arena.height / TILE_SIZE;

    // What type of primitive are we using?
    rVA.setPrimitiveType(Quads);

    // Set the size of the vertex array
    rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

    // Start at the beginning of the vertex array
    int currentVertex = 0;

    for (int w = 0; w < worldWidth; w++)
    {
        for (int h = 0; h < worldHeight; h++)
        {
            // Position each vertex in the current quad
            rVA[currentVertex + 0].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);
            rVA[currentVertex + 1].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
            rVA[currentVertex + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
            rVA[currentVertex + 3].position = Vector2f((w * TILE_SIZE), (h * TILE_SIZE) + TILE_SIZE);

            // Use the same texture for all tiles (assuming you have a texture loaded elsewhere)
            rVA[currentVertex + 0].texCoords = Vector2f(0, 0);
            rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0);
            rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE);
            rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE);

            // Position ready for the next for vertices
            currentVertex = currentVertex + VERTS_IN_QUAD;
        }
    }

    return TILE_SIZE;
}
