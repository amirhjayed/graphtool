#include "graph.h"
#include <cmath>
#include <QDebug>
#include <limits>
#include "vertexview.h"


Graph::Graph(){
    date=0;
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
void Graph::resetBFS(){
    queue<vertexTuple*> empty;
    std::swap( queue_BFS, empty );     //empty the queue
    int MAX_INT = std::numeric_limits<int>::max();
    for (vertexTuple &vt : vertexTuples){
        std::get<0>(vt).setColor(white);
        std::get<0>(vt).setDistance(MAX_INT);
        std::get<0>(vt).setParent(nullptr);
        std::get<1>(vt)->setColor(Qt::black);
        std::get<1>(vt)->setWidth(2);
        for(auto &st : std::get<2>(vt)){
            std::get<2>(st)->setColor(Qt::black);
            std::get<2>(st)->setWidth(1);
            std::get<2>(st)->BFSflag=false;
        }
    }
}
void Graph::initializeBFS(vertexTuple *initialVertex){
    std::get<0>(*initialVertex).setColor(grey);
    std::get<0>(*initialVertex).setDistance(0);
    std::get<1>(*initialVertex)->setColor(Qt::green);
    std::get<1>(*initialVertex)->setWidth(3);
    currentTuple=initialVertex;
    currentSuccessorVect=&std::get<2>(*initialVertex);
    currentSuccessor=currentSuccessorVect->begin();
    queue_BFS.push(initialVertex);
}

bool Graph::stepBFS(){
    qDebug()<<"entré stepBFS";
    if(currentTuple){
        qDebug()<<"currentTuple BFS!=null";
        qDebug()<<"queue size "<<queue_BFS.size();
        if(currentSuccessor!=currentSuccessorVect->end()){ // test if succVect is fully visited
            Vertex *currentVertex=&std::get<0>(*currentTuple);
            vertexTuple *CurrentSuccessor_vT=getTupleFromVertex(std::get<0>(*currentSuccessor));
            qDebug()<<"currentSuccVect non vide";
            if(std::get<0>(*currentSuccessor)->getColor() == white ){                // if successor never visited
                queue_BFS.push(CurrentSuccessor_vT);                                    // push it in the queue
                qDebug()<<"it's white";
                std::get<0>(*CurrentSuccessor_vT).setColor(grey);
                std::get<0>(*CurrentSuccessor_vT).setParent(currentVertex);
                std::get<0>(*CurrentSuccessor_vT).setDistance(currentVertex->getDistance()+1);
                std::get<1>(*CurrentSuccessor_vT)->setColor(Qt::green);
                std::get<1>(*CurrentSuccessor_vT)->setWidth(3);
                std::get<2>(*currentSuccessor)->setColor(Qt::green);
                std::get<2>(*currentSuccessor)->setWidth(2);
                std::get<2>(*currentSuccessor)->BFSflag=true;
            }
            return true;
        }
        else{ //currentSuccessorVect est vidé
            qDebug()<<"currentSuccessorVect est vidé";
            std::get<1>(*currentTuple)->setColor(Qt::red);
            for(auto &sT:*currentSuccessorVect){
                if(std::get<2>(sT)->BFSflag)
                    std::get<2>(sT)->setColor(Qt::red);
            }

                queue_BFS.pop();
            if(!queue_BFS.empty()){
                currentTuple=queue_BFS.front();
                currentSuccessorVect=&std::get<2>(*currentTuple);
                currentSuccessor=currentSuccessorVect->begin();
            }
            else{
                qDebug()<<"currentTuple = nullptr";
                currentTuple=nullptr;
            }
            return false;
        }
    }
    else{

        return false;
    }
}

void Graph::resetDFS(){
    date=0;
    stack<vertexTuple*> empty;
    std::swap(stack_DFS, empty);
    for (vertexTuple &vt : vertexTuples){
        std::get<0>(vt).setColor(white);
        std::get<0>(vt).setParent(nullptr);
        std::get<1>(vt)->setColor(Qt::black);
        std::get<1>(vt)->setDebTime(0);
        std::get<1>(vt)->setEndTime(0);
        std::get<1>(vt)->setWidth(2);
        for(auto &st : std::get<2>(vt)){
            std::get<2>(st)->setColor(Qt::black);
            std::get<2>(st)->setWidth(1);
            std::get<2>(st)->DFSflag=false;
        }
    }
}

void Graph::initializeDFS(vertexTuple *initialVertex){
    std::get<0>(*initialVertex).setColor(grey);
    std::get<1>(*initialVertex)->setDebTime(++date);
    std::get<1>(*initialVertex)->setColor(Qt::green);
    std::get<1>(*initialVertex)->setWidth(3);
    currentTuple=initialVertex;
    currentSuccessorVect=&std::get<2>(*initialVertex);
    currentSuccessor=currentSuccessorVect->begin();
    stack_DFS.push(initialVertex);
}

bool Graph::stepDFS(){
    qDebug()<<"entré stepDFS";
    if(currentTuple != nullptr){
        if(currentSuccessor!=currentSuccessorVect->end()){
            vertexTuple *CurrentTuple=getTupleFromVertex(std::get<0>(*currentSuccessor));
            if(std::get<0>(*CurrentTuple).getColor() == white ){
                std::get<0>(*CurrentTuple).setColor(grey);
                std::get<1>(*CurrentTuple)->setDebTime(++date);
                std::get<1>(*CurrentTuple)->setColor(Qt::green);
                std::get<1>(*CurrentTuple)->setWidth(3);
                std::get<2>(*currentSuccessor)->setColor(Qt::green);
                std::get<2>(*currentSuccessor)->setWidth(2);
                std::get<2>(*currentSuccessor)->DFSflag=true;
                currentSuccessorVect=&std::get<2>(*CurrentTuple);
                currentSuccessor=currentSuccessorVect->begin();
                stack_DFS.push(CurrentTuple);
            }
            else{// the successor was visited before (his color is not white)
                qDebug()<<"step DFS returned true";
                return true;
            }
        }
        else{
            qDebug()<<"currentSuccVect is empty";
            currentTuple=stack_DFS.top();
            std::get<0>(*currentTuple).setColor(black);
            std::get<1>(*currentTuple)->setEndTime(++date);
            std::get<1>(*currentTuple)->setColor(Qt::red);
            stack_DFS.pop();
            currentTuple=nullptr;
        }
    }
    else{
        currentTuple=stack_DFS.top();
        currentSuccessorVect=&std::get<2>(*currentTuple);
        currentSuccessor=currentSuccessorVect->begin();
    }
    return false;
}
