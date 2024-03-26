#pragma once

class Collidable
{
  public:
    enum class CollidableType
    {
        PADDLE = 0,
        BALL,
        BRICK,
    };

  private:
    enum CollidableType m_type;

  public:
    Collidable(enum CollidableType type) : m_type(type) {}
    inline bool isWindowColliding(const int x, const int y, const int entity_width, const int entity_height,
                                  const int windowWidth, const int windowHeight) const
    {
        return x >= 0 && x + entity_width <= windowWidth && y >= 0 && y + entity_height <= windowHeight;
    }

    inline bool isWindowColliding(const int x, const int y, const int radius, const int windowWidth,
                                  const int windowHeight) const
    {
        return x - radius >= 0 && x + radius <= windowWidth && y - radius >= 0 && y + radius <= windowHeight;
    }
    virtual ~Collidable() = default;
    inline enum CollidableType getType() const { return m_type; }
};