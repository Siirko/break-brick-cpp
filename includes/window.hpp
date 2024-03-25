#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include <string>

class Window
{
  private:
    std::string m_title;
    int m_width;
    int m_height;
    bool m_closed;

  public:
    Window(const std::string &title, int width, int height);
    ~Window();

    void pollEvents(SDL_Event &event);
    void clear() const;
    void render() const;

    inline bool isClosed() const { return m_closed; }
};