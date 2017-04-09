#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "game_obj.h"

class player : public game_obj
{
    Q_OBJECT
public:
    explicit player(QRectF rect, QPoint vec_pos, QObject *parent = 0)
        : game_obj(game_obj::name::player, rect, vec_pos,
                   QBrush(Qt::blue),QPen(Qt::black), parent)
    {
        setFocus();
    }

protected:
    void keyPressEvent(QKeyEvent *event) override
    {
        qDebug() << "pressed";
        switch(event->key())
        {
            case Qt::Key_W:// || Qt::Key_Up:
            {
                emit player_changed(game_obj::dir::up);
                //rect_.setY(rect_.y() - rect_.height());
                break;
            }
            case Qt::Key_S:// || Qt::Key_Down:
            {
                emit player_changed(game_obj::dir::down);
                //rect_.setY(rect_.y() + rect_.height());
                break;
            }
            case Qt::Key_A:// || Qt::Key_Left:
            {
                emit player_changed(game_obj::dir::left);
                //rect_.setX(rect_.x() - rect_.width());
                break;
            }
            case Qt::Key_D:// || Qt::Key_Right:
            {
                emit player_changed(game_obj::dir::right);
                //rect_.setX(rect_.x() + rect_.width());
                break;
            }
        }
        update();
    }

signals:
    void player_changed(game_obj::dir d);
public slots:
};

#endif // PLAYER_H
