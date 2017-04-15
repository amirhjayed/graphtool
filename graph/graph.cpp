#include "graph.h"
#include <cmath>
#include <QDebug>
#include <limits>
#include "vertexview.h"


Graph::Graph(){
}
int distanceBetween(QPointF pos1,QPointF pos2){
    int dx=pow(pos1.x()-pos2.x(),2.0);
    int dy=pow(pos1.y()-pos2.y(),2.0);
    int d=std::sqrt(dx+dy);
    return d;
}
VertexView *Graph::getItem(QPointF clickPos){
    for(vertexTuple &_vertexTuple : vertexTuples){
        VertexView *itemView = std::get<1>(_vertexTuple);
        QPointF itemPos=itemView->getPosi();
        if(distanceBetween(itemPos,clickPos)<21)
            return itemView;
    }
    return nullptr;
}

QPointF Graph::CollisionAdd(QPointF newVertexPos){
    for(vertexTuple &_vertexTuple : vertexTuples){
        VertexView *itemView = std::get<1>(_vertexTuple);
        QPointF itemPos=itemView->getPosi();
            if(distanceBetween(itemPos,newVertexPos)<60.0){
                return itemPos;
        }
    }

    return QPointF(0.0,0.0);
 }
QPointF Graph::CollisionMove(QPointF newVertexPos){
    for(vertexTuple &_vertexTuple : vertexTuples){
        VertexView *itemView = std::get<1>(_vertexTuple);
        QPointF itemPos=itemView->getPosi();
        if(distanceBetween(itemPos,newVertexPos)>20){
            if(distanceBetween(itemPos,newVertexPos)<60.0)
                return itemPos;
        }
    }
    return QPointF(0.0,0.0);
}

QPointF Graph::avoidCollisonPoint(QPointF p1, QPointF p2){
    QLineF line(p1,p2);
    float alpha=line.length()/60.0;
    float a=line.dx()/alpha+line.x1();
    float b=line.dy()/alpha+line.y1();
    line.setP2(QPointF(a,b));
    return line.p2();
}

ArcView *Graph::getArcView(vertexTuple *fromVertexTuple, vertexTuple* toVertexTuple){
    std::vector<vertexSuccessor> &successorVect = get<2>(*fromVertexTuple);
    Vertex *toVertex = &std::get<0>(*toVertexTuple);
    qDebug()<<toVertex;
    for(auto it= successorVect.begin();it!=successorVect.end();++it){
        qDebug()<<"fost el boucle: successorVertexPtr : "<<std::get<0>(*it)<<"successor Arc View ptr :"<< std::get<2>(*it);
    }
    for(auto it= successorVect.begin();it!=successorVect.end();++it){
        qDebug()<<(std::get<0>(*it) == toVertex) ;
            if(std::get<0>(*it)==toVertex ){
                return std::get<2>(*it);
            }

        }
    qDebug()<<"getArcView returned a nullptr";
    return nullptr;
}


bool operator ==(vertexTuple t,VertexView* v){
    if(std::get<1>(t)==v){

        return true;
    }
    else
        return false ;
}
void Graph::delVertex(VertexView *vertexItem){
    if(!vertexTuples.empty())
        vertexTuples.erase(std::remove(vertexTuples.begin(),vertexTuples.end(),vertexItem));
}
bool operator == (vertexSuccessor s,Vertex *vT){
    if(vT==(std::get<0>(s))){
        return true ;
    }
    else
    {
        return false ;
    }
}
void Graph::deleteArc(vertexTuple *fromVT, vertexTuple *toVT){
    Vertex *VT = &std::get<0>(*toVT);
    vector<vertexSuccessor> *successorVect = &std::get<2>(*fromVT);
    qDebug()<<successorVect->size();
    if(!successorVect->empty()){
        successorVect->erase(std::remove(successorVect->begin(),successorVect->end(),VT));
    }
    else
        qDebug()<<"successor Vect is empty";
}

bool Graph::arcExist(vertexTuple *fromVT, vertexTuple *toVT){
    Vertex *VT = &std::get<0>(*toVT);
    vector<vertexSuccessor> *successorVect = &std::get<2>(*fromVT);
    auto findResult = successorVect->begin();
    if(!successorVect->empty()){
        findResult = std::find(successorVect->begin(),successorVect->end(),VT);
    }
    if (findResult==successorVect->end()){
        qDebug()<<"arcExist returned false(arc n'esiste pas)";
        return false;
    }
    else {
        qDebug()<<"arcExist returned true";
        return true;
    }

}

vertexTuple *Graph::getVertexTuple(QPointF clickPos){
    for(vertexTuple &_vertexTuple : vertexTuples){
        VertexView *itemView = std::get<1>(_vertexTuple);
        QPointF itemPos=itemView->getPosi();
        if(distanceBetween(itemPos,clickPos)<21)
            return &_vertexTuple;
    }
    return nullptr;
}
vertexTuple *Graph::getTupleFromVertex(Vertex *vertex){
    for(vertexTuple &vT : vertexTuples ){
        Vertex *vp=&std::get<0>(vT);
        if(vp==vertex)
            return &vT;
    }
    return nullptr;
}
void Graph::initializeBFS(vertexTuple *initialVertex){
    queue<vertexTuple*> empty;
    std::swap( queue_BFS, empty );     //empty the queue
    int MAX_INT = std::numeric_limits<int>::max();
    for (vertexTuple &vt : vertexTuples){
        std::get<0>(vt).setColor(white);
        std::get<0>(vt).setDistance(MAX_INT);
        std::get<0>(vt).setParent(nullptr);
    }
    std::get<0>(*initialVertex).setColor(grey);
    std::get<0>(*initialVertex).setDistance(0);
    std::get<1>(*initialVertex)->setColor(Qt::green);
    std::get<1>(*initialVertex)->setWidth(3);
    currentSuccessor_BFS=std::get<2>(*initialVertex).begin();
    currentTuple_BFS=initialVertex;
    currentSuccessorVect_BFS=&std::get<2>(*initialVertex);
    queue_BFS.push(initialVertex);
}

void Graph::stepBFS(){
    qDebug()<<"entré stepBFS";
    if(currentTuple_BFS){
        qDebug()<<"currentTuple BFS!=null";
        Vertex *currentVertex=&std::get<0>(*currentTuple_BFS);
        vertexTuple *CurrentSuccessor_vT=getTupleFromVertex(std::get<0>(*currentSuccessor_BFS));
        if(!currentSuccessorVect_BFS->empty()){ // test if succVect is empty
            qDebug()<<"currentSuccVect non vide";
            if(std::get<0>(*currentSuccessor_BFS)->getColor() == white ){                // if successor never visited
                queue_BFS.push(CurrentSuccessor_vT);                                    // push it in the queue
                qDebug()<<"it's white";
                std::get<0>(*CurrentSuccessor_vT).setColor(grey);
                std::get<0>(*CurrentSuccessor_vT).setParent(currentVertex);
                std::get<0>(*CurrentSuccessor_vT).setDistance(currentVertex->getDistance()+1);
                std::get<1>(*CurrentSuccessor_vT)->setColor(Qt::green);
                std::get<1>(*CurrentSuccessor_vT)->setWidth(3);
                std::get<2>(*currentSuccessor_BFS)->setColor(Qt::green);
                std::get<2>(*currentSuccessor_BFS)->setWidth(2);
            }
            qDebug()<<"increment iterator";
            ++currentSuccessor_BFS;
        }
        else{ //currentSuccessorVect est vidé
            qDebug()<<"currentSuccessorVect est vidé";
            std::get<1>(*currentTuple_BFS)->setColor(Qt::red);
            currentTuple_BFS=queue_BFS.front();
            currentSuccessorVect_BFS=&std::get<2>(*currentTuple_BFS);
            currentSuccessor_BFS=currentSuccessorVect_BFS->begin();
            queue_BFS.pop();
        }
    }
}











