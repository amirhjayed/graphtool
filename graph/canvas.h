#ifndef CANVAS_H
#define CANVAS_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include "graph.h"
#include "vertex.h"
#include "graph.h"
#include <QGraphicsSceneMouseEvent>

class Canvas : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);
    enum mode {NA,addVertex,deleteVertex,addArc,deleteArc};
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void scrollContentsBy(int,int);
    ~Canvas();
public slots:
    void setMode(mode m);
private:
    QGraphicsScene *scene;
    Graph graphModel;
    mode currentMode;
};
#endif // CANVAS_H
