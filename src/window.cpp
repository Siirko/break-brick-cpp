#include "window.hpp"
#include "utils.hpp"
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

Window::Window(const std::string &title, const int width, const int height)
    : m_title(title), m_width(width), m_height(height), m_closed(false),
      m_window(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0),
               SDL_DestroyWindow),
      m_renderer(SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer)
{
    // needs to check if checkSDL can handle this case
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << std::format("Failed to initialize SDL: {}", SDL_GetError());
        throw std::runtime_error("Failed to initialize SDL");
    }
    checkSDL<SDL_Window *>(this->m_window.get(), nullptr);
    checkSDL<SDL_Renderer *>(this->m_renderer.get(), nullptr);
}

void Window::loop()
{
    SDL_Event event;
    while (!this->isClosed())
    {
        clear();
        m_clock.tick();
        pollEvents(event, m_clock.delta);
        render(m_clock.delta);
    }
}

Window::~Window()
{
    if (this->m_renderer != nullptr)
        SDL_DestroyRenderer(this->m_renderer.get());
    if (this->m_window != nullptr)
        SDL_DestroyWindow(this->m_window.get());
    SDL_Quit();
}