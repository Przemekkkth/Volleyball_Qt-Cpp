#include "gamescene.h"
#include <QKeyEvent>
#include <QGraphicsPixmapItem>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_loopSpeed(16.6666f), m_deltaTime(0.0f), m_loopTime(0.0f)
    , m_isLeftPressed(false), m_isRightPressed(false), m_isUpPressed(false), m_isAPressed(false), m_isDPressed(false), m_isWPressed(false)
{
    loadPixmap();
    setSceneRect(0,0, Game::RESOLUTION.width(), Game::RESOLUTION.height());

    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(Game::ITERATION_VALUE);
    m_elapsedTimer.start();
}

void GameScene::loadPixmap()
{
    if(m_bgPixmap.load(Game::PATH_TO_BACKGROUND_PIXMAP))
    {
        qDebug() << "BgPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "BgPixmap is not loaded successfully";
    }

    if(m_ballPixmap.load(Game::PATH_TO_BALL_PIXMAP))
    {
        qDebug() << "BallPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "BallPixmap is not loaded successfully";
    }

    if(m_blobbyPixmap.load(Game::PATH_TO_BLOBBY_PIXMAP))
    {
        qDebug() << "BlobbyPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "BlobbyPixmap is not loaded successfully";
    }
}

void GameScene::loop()
{
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_loopTime += m_deltaTime;
    if( m_loopTime > m_loopSpeed )
    {
        for(int n = 0; n < 2; ++n)
        {
            m_game.m_world.Step(1/60.f, 8, 3);
        }
        //player1
        b2Vec2 pos = m_game.m_playerBody[0]->GetPosition();
        b2Vec2 vel = m_game.m_playerBody[0]->GetPosition();
        if(m_isRightPressed)
        {
            vel.x = 5;
        }
        else if(m_isLeftPressed)
        {
            vel.x = -5;
        }
        if(!m_isRightPressed && !m_isLeftPressed)
        {
            vel.x = 0;
        }

        if(m_isUpPressed)
        {
            if(pos.y*Game::SCALE >= 463)
            {
                vel.y = -13;
            }
        }
        else
        {
            vel.y = 0;
        }

        m_game.m_playerBody[0]->SetLinearVelocity(vel);

        //player2

        pos = m_game.m_playerBody[1]->GetPosition();
        vel = m_game.m_playerBody[1]->GetPosition();
        if(m_isDPressed)
        {
            vel.x = 5;
        }
        else if(m_isAPressed)
        {
            vel.x = -5;
        }
        if(!m_isDPressed && !m_isAPressed)
        {
            vel.x = 0;
        }

        if(m_isWPressed)
        {
            if(pos.y*Game::SCALE >= 463)
            {
                vel.y = -13;
            }
        }
        else
        {
            vel.y = 0;
        }

        m_game.m_playerBody[1]->SetLinearVelocity(vel);

        //ball
        vel = m_game.m_ballBody->GetLinearVelocity();
        m_game.m_ballBody->SetLinearVelocity( 15/vel.Length() * vel);
        //Draw
        clear();
        QGraphicsPixmapItem *bgItem = new QGraphicsPixmapItem(m_bgPixmap.scaled(Game::RESOLUTION.width(), Game::RESOLUTION.height()));
        bgItem->setTransformationMode(Qt::SmoothTransformation);
        addItem(bgItem);

        for (b2Body* it = m_game.m_world.GetBodyList(); it != 0; it = it->GetNext())
        {
            b2Vec2 pos = it->GetPosition();
            float angle = it->GetAngle();

            if (it->GetUserData().pointer == m_game.player1)
            {
                QGraphicsPixmapItem *p1Item = new QGraphicsPixmapItem(m_blobbyPixmap);
                p1Item->setTransformOriginPoint(75/2,90/2);
                p1Item->setPos(pos.x*Game::SCALE, pos.y*Game::SCALE);
                p1Item->setRotation(angle*Game::DEG);
                //sPlayer.setColor(Color::Red);
                addItem(p1Item);
            }

            if (it->GetUserData().pointer == m_game.player2)
            {
                QGraphicsPixmapItem *p1Item = new QGraphicsPixmapItem(m_blobbyPixmap);
                p1Item->setTransformOriginPoint(75/2,90/2);
                p1Item->setPos(pos.x*Game::SCALE, pos.y*Game::SCALE);
                p1Item->setRotation(angle*Game::DEG);
                //sPlayer.setColor(Color::Red);
                addItem(p1Item);
            }

            if (it->GetUserData().pointer == m_game.ball)
            {
                QGraphicsPixmapItem *ballItem = new QGraphicsPixmapItem(m_ballPixmap);
                ballItem->setTransformOriginPoint(32,32);
                ballItem->setPos(pos.x*Game::SCALE, pos.y*Game::SCALE);
                ballItem->setRotation(angle*Game::DEG);
                //sPlayer.setColor(Color::Red);
                addItem(ballItem);
            }
        }
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch ( event->key() ) {
        case Qt::LeftArrow:
    {
        m_isLeftPressed = true;
    }
        break;
    case Qt::RightArrow:
    {
        m_isRightPressed = true;
    }
        break;
    case Qt::UpArrow:
    {
        m_isUpPressed = true;
    }
        break;
    case Qt::Key_A:
    {
        m_isAPressed = true;
    }
        break;
    case Qt::Key_D:
    {
        m_isDPressed = true;
    }
        break;
    case Qt::Key_W:
    {
        m_isWPressed = true;
    }
        break;
    }
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    switch ( event->key() ) {
        case Qt::LeftArrow:
    {
        m_isLeftPressed = false;
    }
        break;
    case Qt::RightArrow:
    {
        m_isRightPressed = false;
    }
        break;
    case Qt::UpArrow:
    {
        m_isUpPressed = false;
    }
        break;
    case Qt::Key_A:
    {
        m_isAPressed = false;
    }
        break;
    case Qt::Key_D:
    {
        m_isDPressed = false;
    }
        break;
    case Qt::Key_W:
    {
        m_isWPressed = false;
    }
        break;
    }
    QGraphicsScene::keyReleaseEvent(event);
}
