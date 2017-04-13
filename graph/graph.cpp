#include "graph.h"
#include <cmath>
#include <QDebug>
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
vertexTuple *Graph::getTupleFromVertex(Vertex *vertex){
    for(vertexTuple &vT : vertexTuples ){
        Vertex *vp=&std::get<0>(vT);
        if(vp==vertex)
            return &vT;
    }
}
ArcView *Graph::getArcView(vertexTuple *fromVertexTuple, QPointF toVertexPos){
    std::vector<vertexSuccessor> &successorVect = get<2>(*fromVertexTuple);
    for(vertexSuccessor &successor : successorVect){
        Vertex *vertex=std::get<0>(successor);
        ArcView *arc = std::get<2>(successor);
        vertexTuple *successorVertexTuple = getTupleFromVertex(vertex);
        VertexView *successorView = std::get<1>(*successorVertexTuple);
        if (distanceBetween(successorView->getPosi(),toVertexPos)<21)
            return arc;
    }
    return nullptr;
}


bool operator ==(vertexTuple t,VertexView* v){
    if(std::get<1>(t)==v)
        return true;
    else
        return false ;
}
void Graph::delVertex(VertexView *vertexItem){
    if(!vertexTuples.empty())
        vertexTuples.erase(std::remove(vertexTuples.begin(),vertexTuples.end(),vertexItem));
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
