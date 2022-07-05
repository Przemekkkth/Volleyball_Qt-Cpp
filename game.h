#ifndef GAME_H
#define GAME_H
#include <QSize>
#include <box2d/box2d.h>

class Game
{
public:
    Game();
    void setWall(int x, int y, int w, int h);
    static const QSize RESOLUTION;
    static const float SCALE;
    static const float DEG;
    static const b2Vec2 GRAVITY;
    static const float ITERATION_VALUE;
    static const QString PATH_TO_BACKGROUND_PIXMAP;
    static const QString PATH_TO_BALL_PIXMAP;
    static const QString PATH_TO_BLOBBY_PIXMAP;
    static const float PLAYER_SPEED;

    b2World m_world;

    b2Body *m_playerBody[2];
    b2Body *m_ballBody;

    uintptr_t player1;
    uintptr_t player2;
    uintptr_t ball;
    uintptr_t bottomWall;

    int m_score1, m_score2;
    bool m_pause;
};

#endif // GAME_H
