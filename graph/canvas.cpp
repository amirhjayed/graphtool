#include "canvas.h"
#include "graphtool.h"
#include "ui_graphtool.h"
#include "vertexview.h"
#include "vertex.h"
#include "graph.h"
#include <tuple>
#include <QMouseEvent>
#include <QMessageBox>
#include <QKeyEvent>
#include <QDebug>

using vertexSuccessor = tuple<Vertex*, int ,ArcView*>;
using vertexTuple = tuple<Vertex, VertexView*,vector<vertexSuccessor>>;
using vertexVect = vector<vertexTuple>;

Canvas::Canvas(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    VertexView::vertexID=0;
    firstClick=true;
    startedBFS=false;
    currentMode=NA;
    this->setSceneRect(50, 50, 350, 350);
    this->setScene(scene);
    vne=nullptr;
    awe=nullptr;
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
                    std::get<1>(_vertex) = vertexItem ;
                    graphModel.vertexTuples.push_back(_vertex);
                    qDebug()<<"in add"<<&graphModel.vertexTuples.front();
                    scene->addItem(vertexItem);
                }
            }
        }
        if(currentMode==deleteVertex){
            if(event->button() == Qt::RightButton){
                QPointF clickPos=mapToScene(event->pos());
                VertexView *clickedItem=graphModel.getItem(clickPos);
                if(clickedItem){
                    if(clickedItem->vertexDeg == 0 ){
                        graphModel.delVertex(clickedItem);
                        scene->removeItem(clickedItem);
                        delete clickedItem;
                    }
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
                    if(fromVertexTuple==nullptr){
                        qDebug()<<"no item clicked";
                        firstClick=true;
                    }
                    else{
                        std::get<1>(*fromVertexTuple)->setColor(Qt::darkCyan);
                    }
                }
                else{
                    firstClick=true;
                    QPointF toVertexPos=mapToScene(event->pos());
                    vertexTuple *clickedVertexTuple=graphModel.getVertexTuple(toVertexPos);
                    if(clickedVertexTuple){
                        if (!graphModel.arcExist(fromVertexTuple,clickedVertexTuple)){
                            ++std::get<1>(*fromVertexTuple)->vertexDeg;
                            ++std::get<1>(*clickedVertexTuple)->vertexDeg;
                            ArcView* arc=new ArcView(std::get<1>(*fromVertexTuple)->getPosPtr(),std::get<1>(*clickedVertexTuple)->getPosPtr());
                            arc->setZValue(-99999999);
                            scene->addItem(arc);
                            vertexSuccessor clickedSuccessor;
                            std::get<0>(clickedSuccessor)=&std::get<0>(*clickedVertexTuple);
                            std::get<2>(clickedSuccessor)=arc;
                            std::get<2>(*fromVertexTuple).push_back(clickedSuccessor);
                            if(graphModel.arcExist(clickedVertexTuple,fromVertexTuple)){
                                arc->is2wayArc=true;
                                arc->isFirst=false;
                                ArcView *otherWayArc=graphModel.getArcView(clickedVertexTuple,fromVertexTuple);
                                otherWayArc->is2wayArc=true;
                            }
                        }
                        else{
                            qDebug()<<"arc exist";
                            ArcView *av=graphModel.getArcView(fromVertexTuple,clickedVertexTuple);
                            if(av){
                                   delete awe;
                                    awe = new ArcWeightEdit() ;
                                    QObject::connect(awe, &ArcWeightEdit::accepted, [=](int weight){
                                        av->setWeight(weight);
                                        qDebug() << av->getWeight();
                                    }) ;
                                    awe->show();
                            }
                        }
                    }
                    else{
                        qDebug()<<"no item clicked";
                    }
                    std::get<1>(*fromVertexTuple)->setColor(Qt::black);
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
                        std::get<1>(*fromVertexTuple)->setColor(Qt::darkCyan);
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
                            --std::get<1>(*fromVertexTuple)->vertexDeg;
                            --std::get<1>(*clickedVertexTuple)->vertexDeg;
                            graphModel.deleteArc(fromVertexTuple,clickedVertexTuple);
                            scene->removeItem(clickedSuccessorArc);
                            delete clickedSuccessorArc;
                            clickedSuccessorArc=nullptr;
                        }
                    }
                    else{
                        qDebug()<<"no item clicked";
                    }
                    std::get<1>(*fromVertexTuple)->setColor(Qt::black);
                }
            }
        }
        /// FIN ARC///

        /// BFS ///
        if(currentMode==BFS){
            QPointF clickedPos=mapToScene(event->pos());
            if(event->button() == Qt::LeftButton){
                if(startedBFS == false){
                    vertexTuple *clickedVertexTuple=graphModel.getVertexTuple(clickedPos);
                    if(clickedVertexTuple){
                        startedBFS = true ;
                        qDebug()<<"BFS started";
                        graphModel.resetBFS();
                        graphModel.initializeBFS(clickedVertexTuple);
                    }
                }
            }
        }
        /// DFS ///
        if(currentMode==DFS){
            QPointF clickedPos=mapToScene(event->pos());
            if(event->button() == Qt::LeftButton ){
                if(startedDFS == false){
                    vertexTuple *clickedVertexTuple=graphModel.getVertexTuple(clickedPos);
                    if(clickedVertexTuple){
                        startedDFS = true ;
                        qDebug()<<"DFS started";
                        graphModel.resetDFS();
                        graphModel.initializeDFS(clickedVertexTuple);
                    }
                }
            }
        }
        if(currentMode==Dijkstra){
            if(event->button() == Qt::LeftButton){
                if(startedDijkstra==false){
                    if(firstClick){
                        firstClick=false;
                        fromVertexPos=mapToScene(event->pos());
                        fromVertexTuple=graphModel.getVertexTuple(fromVertexPos);
                        if(fromVertexTuple==nullptr){
                            qDebug()<<"no item clicked";
                            firstClick=true;
                        }
                        else{
                            std::get<1>(*fromVertexTuple)->setColor(Qt::darkCyan);
                        }
                    }
                    else{
                        firstClick=true;
                        QPointF toVertexPos=mapToScene(event->pos());
                        vertexTuple *clickedVertexTuple=graphModel.getVertexTuple(toVertexPos);
                        if(clickedVertexTuple){
                            qDebug()<<"started Dijkstra";
                            startedDijkstra=true;
                            graphModel.resetDijkstra();
                            pathExist=graphModel.runDijkstra(fromVertexTuple,clickedVertexTuple);
                            if(pathExist == false){
                                startedDijkstra=false;
                                QMessageBox box;
                                box.setText("There is no path between the two vertices");
                                box.exec();
                            }
                        std::get<1>(*fromVertexTuple)->setColor(Qt::black);
                    }
                }
            }
        }
    }
    scene->update();
}

void Canvas::mouseDoubleClickEvent(QMouseEvent *event){
    if(currentMode == addVertex){
        if (vne!=nullptr){
            delete vne;
            vne=nullptr;
        }
        qDebug() << "test double click vertex";
        QPointF clickPos =mapToScene(event->pos());
        VertexView *clickedVertex = graphModel.getItem(clickPos);
        if(clickedVertex){
            if(vne == nullptr) {
                vne = new VertexNameEdit() ;
                QObject::connect(vne, &VertexNameEdit::accepted, [=](QString _name){
                    std::string str = _name.toStdString();
                    clickedVertex->setName(str);
                    qDebug() << _name ;
                }) ;
            }
            vne->show();
        }
    }
    if(currentMode == addArc){
        if (awe!=nullptr){
            delete awe;
            awe=nullptr;
        }
        QPointF clickPos =mapToScene(event->pos());
        if(graphModel.getItem(clickPos)==nullptr){//to ensure that clicked isnt a vertex
            ArcView *av = (ArcView*)(scene->itemAt(clickPos,QTransform()));
            qDebug()<<av;
            if(av){
                qDebug() << "test double click arc"  << event->pos();
                if(awe == nullptr) {
                    awe = new ArcWeightEdit() ;
                    QObject::connect(awe, &ArcWeightEdit::accepted, [=](int weight){
                        av->setWeight(weight);
                        qDebug() << av->getWeight();
                    }) ;
                    awe->show();
                }
            }
        }
    }
}

void Canvas::keyPressEvent(QKeyEvent *event){
    if(currentMode == BFS ){
        if(startedBFS==true){
            if(event->key()==Qt::Key_Space){
                qDebug()<<"Space bar clicked";
                while(!graphModel.queue_BFS.empty()){
                    if(graphModel.stepBFS()){
                        ++graphModel.currentSuccessor;
                    }
                    startedBFS = false ;
                }
            }
            if(event->key()==Qt::Key_Right){
                if(!graphModel.queue_BFS.empty()){
                    if(graphModel.stepBFS()){
                        ++graphModel.currentSuccessor;
                    }
                }
                else{
                    startedBFS = false;
                    qDebug()<<"BFS ended";
                }
            }

        }
        if(event->key()==Qt::Key_R){
            startedBFS = false;
            graphModel.resetBFS();
        }
    }
    if(currentMode == DFS ){
        if(startedDFS==true){
            if(event->key()==Qt::Key_Space){
                while(!graphModel.stack_DFS.empty()){
                    if(graphModel.stepDFS()){
                        ++graphModel.currentSuccessor;
                    }
                    startedDFS = false ;
                }
            }

            if(event->key()==Qt::Key_Right){
                qDebug()<<"Right button clicked";
                if(!graphModel.stack_DFS.empty()){
                    if(graphModel.stepDFS()){
                        ++graphModel.currentSuccessor;
                        qDebug()<<"it increment";
                    }
                }
                else{
                    startedDFS = false;
                    qDebug()<<"DFS ended";
                }
            }
        }
        if(event->key()==Qt::Key_R){
            startedDFS = false;
            graphModel.resetDFS();
        }
    }
    if(currentMode == Dijkstra){
        if(startedDijkstra == true ){
            if(event->key() == Qt::Key_Right){
                if(!graphModel.stack_Dijkstra.empty()){
                    graphModel.stepDijkstra();
                }
                else{
                    startedDijkstra=false;
                    qDebug()<<"dijkstra ended";
                }
            }
            if(event->key() == Qt::Key_Space){
                while(!graphModel.stack_Dijkstra.empty()){
                    graphModel.stepDijkstra();
                }
                    startedDijkstra=false;
                    qDebug()<<"dijkstra ended";
            }
        }
    }
    scene->update();
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
        }
        else{
            clickedItem->setPosi(movePoint);
            scene->removeItem(clickedItem);
            scene->addItem(clickedItem);
        }
    }
}
}

scene->update();
}
void Canvas::reset(){
    scene->clear();
    scene->update();
    VertexView::vertexID=0;
    Graph empty;
    graphModel=empty;
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

