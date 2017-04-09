#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QPen>
#include <QDebug>

class game_obj : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    enum class name{ wall, player, finish };
    enum class dir{ up, down, left, right };
    explicit game_obj(game_obj::name nam, QRectF rect, QPoint vec_pos,
                      QBrush brush, QPen pen, QObject *parent = 0)
        : QObject(parent),
          name_(nam),
          rect_(rect),
          vec_pos_(vec_pos),
          brush_(brush),
          pen_(pen)
        {
               setRect(rect_);
               setPen(pen_);
               setBrush(brush_);
               setFlags(QGraphicsItem::ItemIsSelectable |
                        QGraphicsItem::ItemIsFocusable);
               setAcceptHoverEvents(true);
        }
    QRectF boundingRect() const override { return rect_; }
    void set_vecpos(QPoint point){ vec_pos_ = point ; }
    void set_drawrec(QRectF rect) { rect_ = rect; }
//protected:
    name   name_;
    QRectF rect_;
    QBrush brush_;
    QPen   pen_;
    QPoint vec_pos_;

};

#endif // GAME_OBJ_H
