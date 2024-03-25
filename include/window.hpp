#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include <memory>
#include <string>

class Window
{
  private:
    std::string m_title;
    int m_width;
    int m_height;
    bool m_closed;
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;

  public:
    Window(const std::string &title, const int width, const int height);
    ~Window();

    void pollEvents(SDL_Event &event);
    void clear() const;
    void render() const;

    inline bool isClosed() const { return m_closed; }
    void loop();
};