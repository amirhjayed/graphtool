#include "graph.h"
#include <cmath>
#include <QDebug>
#include <limits>
#include <queue>
#include "vertexview.h"

QColor colorPalette[4]={ Qt::red ,Qt::blue,Qt::darkGreen};
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
    }
    for(auto it= successorVect.begin();it!=successorVect.end();++it){
        qDebug()<<(std::get<0>(*it) == toVertex) ;
            if(std::get<0>(*it)==toVertex ){
                return std::get<2>(*it);
            }

        }
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
}

bool Graph::arcExist(vertexTuple *fromVT, vertexTuple *toVT){
    Vertex *VT = &std::get<0>(*toVT);
    vector<vertexSuccessor> *successorVect = &std::get<2>(*fromVT);
    auto findResult = successorVect->begin();
    if(!successorVect->empty()){
        findResult = std::find(successorVect->begin(),successorVect->end(),VT);
    }
    if (findResult==successorVect->end()){
        return false;
    }
    else {
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
            std::get<1>(*currentTuple)->setColor(colorPalette[std::get<0>(*currentTuple).getDistance()%3]);
            for(auto &sT:*currentSuccessorVect){
                if(std::get<2>(sT)->BFSflag)
                    std::get<2>(sT)->setColor(colorPalette[std::get<0>(*currentTuple).getDistance()%3]);
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
            for(auto &sT:std::get<2>(*currentTuple)){
                if(std::get<2>(sT)->DFSflag)
                    std::get<2>(sT)->setColor(Qt::red);
            }
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

void Graph::resetDijkstra(){
    stack<vertexTuple*> empty;
    std::swap(stack_Dijkstra, empty);
    int MAX_INT = std::numeric_limits<int>::max();
    for (vertexTuple &vt : vertexTuples){
        std::get<0>(vt).setParent(nullptr);
        std::get<0>(vt).setDistance(MAX_INT);
        std::get<1>(vt)->setColor(Qt::black);
        std::get<1>(vt)->setWidth(2);
        for(auto &st : std::get<2>(vt)){
            std::get<2>(st)->setColor(Qt::black);
            std::get<2>(st)->setWidth(1);
            std::get<2>(st)->dijkstraFlag=false;
        }
    }
}

struct cmp {
    bool operator() (vertexTuple *v1,vertexTuple *v2)  {
        qDebug()<<"in cmp"<<v1<<"  "<<v2;
        return std::get<0>(*v1).getDistance()>std::get<0>(*v2).getDistance();
    }
};
void Graph::dijkstra(vertexTuple *initialVertex){
    std::priority_queue<vertexTuple*,std::vector<vertexTuple*>,cmp> activeVertices; // E //
    std::get<0>(*initialVertex).setDistance(0);
    for(vertexTuple &v:vertexTuples)
        activeVertices.push(&v);
    while(!activeVertices.empty()){
        vertexTuple* minVertex = activeVertices.top();
        activeVertices.pop();
        for(vertexSuccessor &vs:std::get<2>(*minVertex)){
            Vertex *V = std::get<0>(vs);
            Vertex *U = &std::get<0>(*minVertex);
            unsigned newDistance = U->getDistance()+std::get<2>(vs)->getWeight();
            if(V->getDistance()>newDistance){
                V->setDistance(newDistance);
                V->setParent(U);
            }
        }
    }
}
bool Graph::runDijkstra(vertexTuple *initialVertex, vertexTuple *destinationVertex){
    dijkstra(initialVertex);
    if(std::get<0>(*destinationVertex).getParent()!=nullptr){
        vertexTuple *vt=destinationVertex;
        while(vt!=nullptr){
            stack_Dijkstra.push(vt);
            vt=getTupleFromVertex(std::get<0>(*vt).getParent());
        }
        qDebug()<<"path exists";
        return true ;
    }
    else{
        qDebug()<<"no path ";
        return false;
    }
}

void Graph::stepDijkstra(){
    vertexTuple* pathTuple=stack_Dijkstra.top();
    stack_Dijkstra.pop();
    VertexView *pathItem=std::get<1>(*pathTuple);
    pathItem->setColor(Qt::red);
    pathItem->setWidth(3);
    for(vertexSuccessor &vs:std::get<2>(*pathTuple)){
        if(!stack_Dijkstra.empty()){
            if(getTupleFromVertex(std::get<0>(vs))==stack_Dijkstra.top()){
                std::get<2>(vs)->setColor(Qt::red);
                std::get<2>(vs)->setWidth(2);

            }
        }
    }
}

unsigned **Graph::calculateAdjMatrix() {
    adjMatrix = new unsigned*[Ordre()] ;
    for(unsigned i = 0; i < Ordre(); i++){
        adjMatrix[i] = new unsigned[Ordre()] ;
    }
    for(unsigned i = 0 ; i<Ordre(); i++)
        for(unsigned j = 0 ; j<Ordre(); j++)
            adjMatrix[i][j] = 0 ;

    for ( unsigned vertexNumber = 0 ; vertexNumber < Ordre() ; vertexNumber++ ) {
        vector<vertexSuccessor>& vsucc = std::get<2>(vertexTuples[vertexNumber]) ;
        for(unsigned i = 0 ; i < vsucc.size();i++) {
           adjMatrix[indexOf(std::get<0>(vsucc[i]))][vertexNumber] = 1 ;
        }
    }
    return adjMatrix ;
}


int Graph::indexOf(Vertex* vertex) {

    for(unsigned i = 0 ; i < Ordre() ; i++) {
        Vertex& refVertex =  std::get<0>(vertexTuples[i]) ;
        if(vertex == &refVertex)
            return i ;
    }
    return -1 ;

}
