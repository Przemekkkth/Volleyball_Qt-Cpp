#include "game.h"
#include <QDebug>

const QSize Game::RESOLUTION = QSize(800, 600);
const float Game::SCALE = 20.f;
const float Game::DEG = 57.29577f; //180/pi
const b2Vec2 Game::GRAVITY = b2Vec2(0.f, 9.8f);
const float Game::ITERATION_VALUE = 1000.0f/60.0f;

const QString Game::PATH_TO_BACKGROUND_PIXMAP = ":/res/background.png";
const QString Game::PATH_TO_BALL_PIXMAP = ":/res/ball.png";
const QString Game::PATH_TO_BLOBBY_PIXMAP = ":/res/blobby.png";

const float Game::PLAYER_SPEED = 8.0f;

Game::Game() : m_world(GRAVITY), m_score1(0), m_score2(0)
{
    setWall(400,520,2000,10); // button
    setWall(365, 450,5,200);  // middle
    setWall(-50,0,10,2000);   // left
    setWall(780,0,10,2000);   // right
    setWall(-50, -90, 1000, 1);//top

    b2BodyDef bdef;
    bdef.type=b2_dynamicBody;
    //players def
    for(int i = 0; i < 2; ++i)
    {
        bdef.position.Set(20*i,20);
        b2CircleShape circle;
        circle.m_radius=32/SCALE;
        circle.m_p.Set(0,13/SCALE);
        m_playerBody[i] = m_world.CreateBody(&bdef);
        m_playerBody[i]->CreateFixture(&circle,5);
        circle.m_radius=25/SCALE;
        circle.m_p.Set(0,-20/SCALE);
        m_playerBody[i]->CreateFixture(&circle,5);
        m_playerBody[i]->SetFixedRotation(true);
    }
    b2BodyUserData p1;
    p1.pointer = uintptr_t("player1");
    m_playerBody[0]->SetUserData(p1);
    b2BodyUserData p2;
    p2.pointer = uintptr_t("player2");
    m_playerBody[1]->SetUserData(p2);

    //ball def
    bdef.position.Set(5,1);
    b2CircleShape circle;
    circle.m_radius=32/SCALE;
    m_ballBody = m_world.CreateBody(&bdef);
    b2FixtureDef fdef;
    fdef.shape = &circle;
    fdef.restitution = 0.95;
    fdef.density = 0.2;
    m_ballBody->CreateFixture(&fdef);

    b2BodyUserData b;
    b.pointer = uintptr_t("ball");;
    m_ballBody->SetUserData(b);

    player1 = m_playerBody[0]->GetUserData().pointer;
    player2 = m_playerBody[1]->GetUserData().pointer;
    ball = m_ballBody->GetUserData().pointer;
}

void Game::setWall(int x, int y, int w, int h)
{
    b2PolygonShape gr;
    gr.SetAsBox(w/SCALE, h/SCALE);

    b2BodyDef bdef;
    bdef.position.Set(x/SCALE, y/SCALE);
    bdef.type = b2_staticBody;

    b2Body *b_ground = m_world.CreateBody(&bdef);
    b_ground->CreateFixture(&gr, 1);


    //bottom wall
    //400,520,2000,10
    if(x == 400 && y == 520 && w == 2000 && h == 10)
    {
        b2BodyUserData b;
        b.pointer = uintptr_t("bottomWall");;
        b_ground->SetUserData(b);
        bottomWall = b_ground->GetUserData().pointer;
    }
}
