#pragma once
#include <SDL2/SDL.h>
#include <map>

class Event
{
  public:
    std::map<SDL_Keycode, bool> keyMap;
    virtual void pollEvents(SDL_Event &event) = 0;
    virtual void applyEvents(const double delta = 1.0f) {}
};