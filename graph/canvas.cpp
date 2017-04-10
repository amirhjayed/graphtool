#include "canvas.h"
#include "graphtool.h"
#include "ui_graphtool.h"
#include "vertexview.h"
#include "vertex.h"
#include "graph.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
Canvas::Canvas(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    graphModel = new Graph();
    currentMode=NA;
    this->setSceneRect(50, 50, 350, 350);
    this->setScene(scene);
    QObject::connect(parent,SIGNAL(changedMode(mode)),this,SLOT(setMode(mode)));
}
void Canvas::mousePressEvent(QMouseEvent *event)
{
        QPointF p=mapToScene(event->pos());
        qDebug()<<p;
        if(currentMode==addVertex){
            if(event->button() == Qt::LeftButton){
                VertexView *v1 = new VertexView(p);
                scene->addItem(v1);
                scene->update();
            }
        }
        if(currentMode==deleteVertex){
            if(event->button() == Qt::RightButton){
                scene->removeItem(scene->items().constFirst());
                scene->update();
            }
        }
}
void Canvas::scrollContentsBy(int, int)
{
    //don't do anything hah!
}

void Canvas::setMode(Canvas::mode m)
{
    if(m!=currentMode)
        currentMode=m;
}



