#include "canvas.h"
#include "graphtool.h"
#include "ui_graphtool.h"
#include "vertexview.h"
#include "vertex.h"
#include "graph.h"
#include <tuple>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

using vertexSuccessor = tuple<Vertex*, int ,ArcView*>;
using vertexTuple = tuple<Vertex, VertexView*,vector<vertexSuccessor>>;
using vertexVect = vector<vertexTuple>;

Canvas::Canvas(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    currentMode=NA;
    this->setSceneRect(50, 50, 350, 350);
    this->setScene(scene);
    QObject::connect(parent,SIGNAL(changedMode(mode)),this,SLOT(setMode(mode)));
}
void Canvas::mousePressEvent(QMouseEvent *event)
{
        QPointF p=mapToScene(event->pos());
        if(currentMode==addVertex){
            if(event->button() == Qt::LeftButton){
                qDebug()<<graphModel.Collision(p).isNull();
                if(graphModel.Collision(p).isNull()==true){
                    VertexView *vertexItem = new VertexView(p);
                    vertexTuple _vertex ;
                    std::get<0>(_vertex) = Vertex() ;
                    std::get<1>(_vertex) = vertexItem ;
                    graphModel.vertexTuples.push_back(_vertex);
                    scene->addItem(vertexItem);
                    scene->update();
                }
            }
        }
        if(currentMode==deleteVertex){
            if(event->button() == Qt::RightButton){
                QPointF p=mapToScene(event->pos());
                QGraphicsItem *clickedItem=graphModel.getItem(p);
                scene->removeItem(clickedItem);
                scene->update();
            }
        }
}

void Canvas::mouseMoveEvent(QMouseEvent *event){
    if (currentMode==NA){
        if(event->buttons()==Qt::LeftButton){
            QPointF movePoint=mapToScene(event->pos());
            VertexView *clickedItem=graphModel.getItem(movePoint);
            if(clickedItem!=nullptr){
                QPointF collisionPoint;
                if((collisionPoint=graphModel.Collision(movePoint)).isNull()==false){
                    clickedItem->setPosi(graphModel.avoidCollisonPoint(collisionPoint,movePoint));
                    scene->removeItem(clickedItem);
                    scene->addItem(clickedItem);
                    scene->update();
                }
                else{
                    clickedItem->setPosi(movePoint);
                    scene->removeItem(clickedItem);
                    scene->addItem(clickedItem);
                    scene->update();
                }
            }
            update();
        }
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event){
    if (currentMode==NA){
        if(event->button()==Qt::LeftButton){
        QPointF releasePoint=mapToScene(event->pos());
        VertexView *clickedItem=graphModel.getItem(releasePoint);
        if(clickedItem){
                QPointF collisionPoint;
                if((collisionPoint=graphModel.Collision(releasePoint)).isNull()==false){
                        clickedItem->setPosi(graphModel.avoidCollisonPoint(collisionPoint,releasePoint));
                        scene->removeItem(clickedItem);
                        scene->addItem(clickedItem);
                        scene->update();
                }
            }
        }
    }
}

void Canvas::scrollContentsBy(int, int){
    //don't do anything hah!
}

Canvas::~Canvas(){
    delete scene;
}

void Canvas::setMode(Canvas::mode m){
    if(m!=currentMode)
        currentMode=m;
}



