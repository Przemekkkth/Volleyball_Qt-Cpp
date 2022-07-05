#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QElapsedTimer>
#include "game.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);

signals:

private slots:
    void loop();
private:
    void loadPixmap();
    void drawScore();
    Game m_game;
    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;

    const float m_loopSpeed;
    float m_deltaTime, m_loopTime;
    bool m_isLeftPressed, m_isRightPressed, m_isUpPressed, m_isAPressed, m_isDPressed, m_isWPressed;

    QPixmap m_bgPixmap;
    QPixmap m_ballPixmap;
    QPixmap m_blobbyPixmap;
    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // GAMESCENE_H
