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
        if(distanceBetween(itemPos,clickPos)<20)
            return itemView;
    }
    return nullptr;
}

QPointF Graph::Collision(QPointF newVertexPos){
    for(vertexTuple &_vertexTuple : vertexTuples)
    {
        VertexView *itemView = std::get<1>(_vertexTuple);
        QPointF itemPos=itemView->getPosi();
        if(itemPos!=newVertexPos){  qDebug()<<itemPos;
            if(distanceBetween(itemPos,newVertexPos)<60.0)
                return itemPos;}
    }

    return QPointF(0.0,0.0);
}

QPointF Graph::avoidCollisonPoint(QPointF p1, QPointF p2){
    QLineF line(p1,p2);

    //line.setP2(a);
}
