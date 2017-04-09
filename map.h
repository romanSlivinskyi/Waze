#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QSize>
#include "game_obj.h"
#include "wall.h"
#include "player.h"

class map : public QObject
{
    Q_OBJECT
public:
    explicit map(QSize size, QObject *parent = 0)
        : QObject(parent),
          size_(size)
    {
        init();
        print_arr();
    }
    const auto& get_objs() const { return map_arr_; }
    void init()
    {
        char carr_[][10] =
        {
            {'.','.','.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.','.','.'},
            {'.','W','W','W','W','.','.','.','.','.'},
            {'.','.','.','.','W','.','.','.','.','.'},
            {'.','.','.','.','W','.','.','.','.','.'},
            {'.','.','.','.','W','.','.','.','.','.'},
            {'.','.','.','.','W','W','W','W','.','.'},
            {'.','.','.','.','.','.','.','W','.','.'},
            {'.','.','.','.','.','.','.','.','.','.'},
            {'.','P','.','.','.','.','.','.','.','.'}
        };

        for(int i = 0; i < size_.height(); ++i)
        {
            QVector<game_obj*> vec;
            for(int j = 0; j < size_.width(); ++j)
            {
                switch(carr_[i][j])
                {
                case 'W':
                {
                    wall* w = new wall(QRectF(j*step_, i*step_, step_-1, step_-1),QPoint(i,j), false);
                    vec.push_back(w);
                    connect(w, SIGNAL(wall_changed(QPoint,bool)),this,SLOT(wall_changed(QPoint,bool)));
                    break;
                }
                case 'P':
                {
                    player_ = new player(QRectF(j*step_, i*step_, step_-1, step_-1),QPoint(i,j));
                    vec.push_back(player_);
                    connect(player_, SIGNAL(player_changed(game_obj::dir)), this, SLOT(player_changed(game_obj::dir)));
                    break;
                }
                case '.':
                {
                    wall* w = new wall(QRectF(j*step_, i*step_, step_-1, step_-1),QPoint(i,j), true);
                    vec.push_back(w);
                    connect(w, SIGNAL(wall_changed(QPoint,bool)),this,SLOT(wall_changed(QPoint,bool)));
                    break;
                }
                }

            }
            map_arr_.push_back(std::move(vec));
        }


    }
    void print_arr() const
    {
        for(auto& vec : map_arr_)
        {
            QString str;
            for(auto obj : vec)
            {
                if(obj->name_ == game_obj::name::wall)
                {
                    if(dynamic_cast<wall*>(obj)->is_free())
                        str += ".";
                    else
                        str += "|";
                }
                else
                {
                    str += "P";
                }
            }
            qDebug() << str;
        }
        qDebug() << "--------------------------";
    }
private:
    QVector<QVector<game_obj*>> map_arr_;
    QSize size_;
    int step_ { 30 };
    player* player_;
signals:
    void action_made(); //all now
public slots:
    void wall_changed(QPoint p, bool stat)
    {
        dynamic_cast<wall*>(map_arr_[p.x()][p.y()])->set_stan(stat);
        print_arr();
    }
    void player_changed(game_obj::dir d)
    {
        int I = player_->vec_pos_.x();
        int J = player_->vec_pos_.y();
        auto check = [&](int cI, int cJ) {
            if(cI >= size_.height() || cI < 0 ||
               cJ >= size_.width()  || cJ < 0)
                return;
            if(map_arr_[cI][cJ]->name_ == game_obj::name::wall) {
                if(dynamic_cast<wall*>(map_arr_[cI][cJ])->is_free()) {
                    map_arr_[I][J] = new wall(QRectF(I*step_, J*step_, step_-1, step_-1),
                                              QPoint(I,J), true);
                    player_->set_vecpos(QPoint(cI,cJ));
                    player_->set_drawrec(QRectF(cI*step_, cJ*step_, step_-1, step_-1));
                    map_arr_[cI][cJ] = player_;
                    qDebug() << "OK"; print_arr();
                    emit action_made();
                }
            }
        };
        switch(d)
        {
            case game_obj::dir::up    : check(I-1, J); break;
            case game_obj::dir::down  : check(I+1, J); break;
            case game_obj::dir::left  : check(I, J-1); break;
            case game_obj::dir::right : check(I, J+1); break;
        }
    }
};

#endif // MAP_H
