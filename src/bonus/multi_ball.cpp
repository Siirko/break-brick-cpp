#include "entity/bonus/multi_ball.hpp"
#include "game.hpp"
#include "utils.hpp"

MultiBall::MultiBall(const float x, const float y, const int radius, const float velocity_y)
    : Circle(x, y, radius), Bonus(BonusType::MULTI_BALL), m_velocity_y(velocity_y)
{
}

void MultiBall::move(const double delta)
{
    // bonus is moving down
    m_position.y += m_velocity_y * delta;
}

void MultiBall::render(SDL_Renderer &renderer)
{
    int res = SDL_SetRenderDrawColor(&renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    checkSDL<int>(res, res == 0);
    this->drawFilledCircle(renderer);
    int width, height;
    SDL_GetRendererOutputSize(&renderer, &width, &height);
    if (m_position.y > height)
        m_out = true;
}

void MultiBall::result(Game &game)
{
    // get the ball
    auto ball = game.getBall();
    // create a 2 balls
    // first ball is going to the left
    // second ball is going to the right
    Color color = ball->getColor();
    color.a = color.a / 2;
    auto ball1 = std::make_shared<Ball>(ball->getPosition().x, ball->getPosition().y, ball->getRadius(),
                                        -ball->getVelocityX(), -ball->getVelocityY(), ball->getSpeed(), color);
    auto ball2 = std::make_shared<Ball>(ball->getPosition().x, ball->getPosition().y, ball->getRadius(),
                                        ball->getVelocityX(), -ball->getVelocityY(), ball->getSpeed(), color);

    // add the balls to the game
    game.getBalls().push_back(ball1);
    game.getBalls().push_back(ball2);
    m_out = true;
}