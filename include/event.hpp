#pragma once
#include <SDL2/SDL.h>

class Event
{
  public:
    virtual void pollEvents(SDL_Event &event, const double delta) = 0;
};