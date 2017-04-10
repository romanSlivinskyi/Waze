#ifndef WALL_H
#define WALL_H

#include <QString>
#include <QObject>
#include "game_obj.h"

class wall :  public game_obj
{
    Q_OBJECT
public:
    explicit wall(QRectF rect, QPoint vec_pos, bool is_free,
                  QObject *parent = 0)
        : game_obj(game_obj::name::wall, rect, vec_pos,
                   is_free ? QBrush(Qt::white) : QBrush(Qt::black),
                   QPen(Qt::black), parent),
          is_free_(is_free)
    {
        setAcceptHoverEvents(true);
    }

    bool is_free () const    { return is_free_; }
    void set_stan(bool stan)
    {
        is_free_ = stan;
        setBrush(is_free_ ? Qt::white : Qt::black);
        update();
    }

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override
    {
        setPen(QPen(Qt::red));
        update();
    }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override
    {
        setPen(pen_);
        update();
    }
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override
    {
//        is_free_ = !is_free_;
//        setBrush(is_free_ ? Qt::white : Qt::black);
//        update();
        emit wall_changed(vec_pos_, is_free_);
    }

protected:
    bool is_free_;

signals:
    void wall_changed(QPoint vec_pos, bool stat);
public slots:


};

#endif // WALL_H
