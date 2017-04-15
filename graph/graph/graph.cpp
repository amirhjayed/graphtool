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
/*vertexTuple *Graph::getTupleFromVertex(Vertex *vertex){
    for(vertexTuple &vT : vertexTuples ){
        Vertex *vp=&std::get<0>(vT);
        if(vp==vertex)
            return &vT;
    }
    return nullptr;
}*/

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
void Graph::initializeBFS(vertexTuple *initialVertex){
    queue<vertexTuple*> empty;
    std::swap( queueBFS, empty );     //empty the queue
    int MAX_INT = std::numeric_limits<int>::max();
    for (vertexTuple &vt : vertexTuples){
        std::get<0>(vt).setColor(white);
        std::get<0>(vt).setDistance(MAX_INT);
        std::get<0>(vt).setParent(nullptr);
    }
    std::get<0>(*initialVertex).setColor(grey);
    std::get<0>(*initialVertex).setDistance(0);
    std::get<1>(*initialVertex)->setColor(Qt::red);
    std::get<1>(*initialVertex)->setWidth(3);

    currentTuple_BFS=initialVertex;
    queueBFS.push(initialVertex);
}

void Graph::stepBFS(){

}
