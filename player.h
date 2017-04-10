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
                   QBrush(Qt::green),QPen(Qt::black), parent)
    {
        setFlags(QGraphicsItem::ItemIsFocusable);
        setFocus(); 
    }

protected:
    void keyPressEvent(QKeyEvent *event) override
    {
        qDebug() << "pressed";
        switch(event->key()){
            case Qt::Key_W:
                emit player_changed(game_obj::dir::up);   break;
            case Qt::Key_S:
                emit player_changed(game_obj::dir::down); break;
            case Qt::Key_A:
                emit player_changed(game_obj::dir::left); break;
            case Qt::Key_D:
                emit player_changed(game_obj::dir::right);break;
        }
        update();
    }

signals:
    void player_changed(game_obj::dir d);
public slots:
    void change_mod(bool mod)
    {
        setBrush(QBrush(mod ? Qt::green : Qt::red));
        update();
    }
};

#endif // PLAYER_H
