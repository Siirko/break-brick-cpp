#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include <memory>
#include <string>

class Clock
{
  private:
    uint64_t now = SDL_GetPerformanceCounter();
    uint64_t last = 0;

  public:
    double delta = 0;
    void tick()
    {
        last = now;
        now = SDL_GetPerformanceCounter();

        delta = ((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());
    }
};
class Window
{
  protected:
    std::string m_title;
    int m_width;
    int m_height;
    bool m_closed;
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
    Clock m_clock;

  public:
    Window(const std::string &title, const int width, const int height);
    ~Window();

    virtual void pollEvents(SDL_Event &event, const double delta) = 0;
    virtual void clear() = 0;
    virtual void render(double delta) = 0;
    void loop();

    inline bool isClosed() const { return m_closed; }
};
