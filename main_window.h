#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "map.h"
#include <QGraphicsView>
#include <QGraphicsScene>

class main_window : public QMainWindow
{
    Q_OBJECT
public:
    main_window(QWidget *parent = 0) : QMainWindow(parent)
    {
        map_ = new map(QSize(10,10));
        scene_ = new QGraphicsScene(QRectF(0.,0.,300,300));
        view_ = new QGraphicsView(scene_);
        setCentralWidget(view_);
        draw_scene();
        connect(map_, SIGNAL(action_made()), this, SLOT(action_made()));
    }
    void draw_scene()
    {
        auto vec_arr = map_->get_objs();
        for(auto& vec : vec_arr)
            for(auto obj : vec)
                scene_->addItem(obj);
    }

    ~main_window();

private:
    QGraphicsScene *scene_;
    QGraphicsView *view_;
    map *map_;

public slots:
    void action_made()
    {
        scene_->update();
//        scene_ = new QGraphicsScene();
//        draw_scene();
//        view_->setScene(scene_);
    }
};

#endif // MAIN_WINDOW_H
