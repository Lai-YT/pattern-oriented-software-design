/*
 * This class is provided by the TAs.
 */

#pragma once

#include <SDL2/SDL.h>

class Piece
{
protected:
    SDL_Renderer *_renderer;

public:
    Piece(SDL_Renderer *renderer) : _renderer(renderer) {}
    ~Piece () {};
    virtual void draw() = 0;
};
