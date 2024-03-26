#pragma once

class Collidable
{
  public:
    inline bool isWindowColliding(const int x, const int y, const int entity_width, const int entity_height,
                                  const int windowWidth, const int windowHeight) const
    {
        return x >= 0 && x + entity_width <= windowWidth && y >= 0 && y + entity_height <= windowHeight;
    }
    // virtual bool collides(const Collidable &other);
    // virtual void on_collision(const Collidable &other);
    virtual ~Collidable() = default;
};