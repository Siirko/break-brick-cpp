#pragma once

class Collidable
{
  public:
    // virtual bool collidesWindow(const int windowWidth, const int windowHeight) const = 0;
    // virtual bool collides(const Collidable &other);
    // virtual void on_collision(const Collidable &other);
    virtual ~Collidable() = default;
};