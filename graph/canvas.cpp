#include "canvas.h"
#include "graphtool.h"
#include "ui_graphtool.h"
#include "vertexview.h"
#include "vertex.h"
#include "graph.h"
#include <tuple>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>

using vertexSuccessor = tuple<Vertex*, int ,ArcView*>;
using vertexTuple = tuple<Vertex, VertexView*,vector<vertexSuccessor>>;
using vertexVect = vector<vertexTuple>;

Canvas::Canvas(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    firstClick=true;
    startedBFS=false;
    currentMode=NA;
    this->setSceneRect(50, 50, 350, 350);
    this->setScene(scene);
    QObject::connect(parent,SIGNAL(changedMode(mode)),this,SLOT(setMode(mode)));
}
void Canvas::mousePressEvent(QMouseEvent *event)
{
        /// VERTEX ///
        if(currentMode==addVertex){
            QPointF p=mapToScene(event->pos());
            if(event->button() == Qt::LeftButton){
                if(graphModel.CollisionAdd(p).isNull()==true){
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
                QPointF clickPos=mapToScene(event->pos());
                VertexView *clickedItem=graphModel.getItem(clickPos);
                if(clickedItem){
                    //clickedItem->setPosi(QPointF(0.0,0.0));
                    graphModel.delVertex(clickedItem);
                    scene->removeItem(clickedItem);
                    scene->update();
                }
            }
        }
        /// FIN VERTEX ///
        /// ARC ///
        if(currentMode==addArc){
            if(event->button() == Qt::LeftButton){
                if(firstClick){
                    firstClick=false;
                    fromVertexPos=mapToScene(event->pos());
                    fromVertexTuple=graphModel.getVertexTuple(fromVertexPos);
                    if(fromVertexTuple){

                    }
                    else{
                        qDebug()<<"no item clicked";
                        firstClick=true;
                    }
                }
                else{
                    firstClick=true;
                    QPointF toVertexPos=mapToScene(event->pos());
                    vertexTuple *clickedVertexTuple=graphModel.getVertexTuple(toVertexPos);
                    if(clickedVertexTuple){
                        if (!graphModel.arcExist(fromVertexTuple,clickedVertexTuple)){

                            ArcView* arc=new ArcView(std::get<1>(*fromVertexTuple)->getPosPtr(),std::get<1>(*clickedVertexTuple)->getPosPtr());

                            scene->addItem(arc);
                            scene->update();
                            vertexSuccessor clickedSuccessor;
                            qDebug()<<"fel addarc: "<<&std::get<0>(*clickedVertexTuple);
                            std::get<0>(clickedSuccessor)=&std::get<0>(*clickedVertexTuple);
                            qDebug() <<"toVertex ptr "<<&std::get<0>(*clickedVertexTuple)<<" arc pointer is "<<arc;
                            std::get<2>(clickedSuccessor)=arc;
                            std::get<2>(*fromVertexTuple).push_back(clickedSuccessor);
                        }
                        else{
                            qDebug()<<"arc exist";}

                    }
                    else{
                        qDebug()<<"no item clicked";

                    }
                }
            }
        }
        if(currentMode==deleteArc){
            if(event->button() == Qt::RightButton){
                if(firstClick){
                    firstClick=false;
                    fromVertexPos=mapToScene(event->pos());
                    fromVertexTuple=graphModel.getVertexTuple(fromVertexPos);
                    if(fromVertexTuple){

                    }
                    else{
                        qDebug()<<"no item clicked";
                        firstClick=true;
                    }
                }
                else{
                    firstClick=true;
                    QPointF toVertexPos=mapToScene(event->pos());
                    vertexTuple *clickedVertexTuple=graphModel.getVertexTuple(toVertexPos);
                    if(clickedVertexTuple){
                        ArcView *clickedSuccessorArc=graphModel.getArcView(fromVertexTuple,clickedVertexTuple);
                        if(clickedSuccessorArc){
                            graphModel.deleteArc(fromVertexTuple,clickedVertexTuple);
                            scene->removeItem(clickedSuccessorArc);
                            qDebug()<<"when deleted : "<<clickedSuccessorArc;
                            clickedSuccessorArc=nullptr;
                            scene->update();

                        }
                        scene->update();
                    }
                    else{
                        qDebug()<<"no item clicked";

                    }
                }
            }
        }
        /// FIN ARC///

        /// BFS ///
        if(currentMode==BFS){
            QPointF clickedPos=mapToScene(event->pos());
            if(event->button() == Qt::LeftButton ){
                if(startedBFS == false){
                    vertexTuple *clickedVertexTuple=graphModel.getVertexTuple(clickedPos);
                    if(clickedVertexTuple){
                        startedBFS = true ;
                        qDebug()<<"BFS started";
                        graphModel.initializeBFS(clickedVertexTuple);
                        scene->update();
                    }
                }
            }
        }
}
        /// MOVE ///
void Canvas::mouseMoveEvent(QMouseEvent *event){
    if (currentMode==NA){
        if(event->buttons()==Qt::LeftButton){
            QPointF movePoint=mapToScene(event->pos());
            VertexView *clickedItem=graphModel.getItem(movePoint);
            if(clickedItem!=nullptr){
                QPointF collisionPoint;
                if((collisionPoint=graphModel.CollisionMove(movePoint)).isNull()==false){
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

void Canvas::keyPressEvent(QKeyEvent *event){
    if(currentMode == BFS ){
        if(startedBFS==true){
            if(event->key()==Qt::Key_Space){
                qDebug()<<"Space bar clicked";
                while(!graphModel.queue_BFS.empty() || false /*delete this*/){
                    graphModel.stepBFS();
                    startedBFS = false ;
                }
            }
            if(event->key()==Qt::Key_Right){
                qDebug()<<"Right button clicked";
                graphModel.stepBFS();
                scene->update();
            }
        }
    }
}

/*void Canvas::mouseReleaseEvent(QMouseEvent *event){
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
}*/

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



