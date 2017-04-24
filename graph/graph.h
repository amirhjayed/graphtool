#ifndef GRAPH_H
#define GRAPH_H
#include "vertex.h"
#include "vertexview.h"

#include <vector>
#include <QGraphicsItem>
#include <QPointF>
#include <utility>
#include <tuple>
#include <queue>
#include <stack>
#include "arcview.h"

using vertexSuccessor = tuple<Vertex*, int/*useless*/ ,ArcView*/*weight is here*/>;
using vertexTuple = tuple<Vertex, VertexView*,vector<vertexSuccessor>>;
using vertexVect = vector<vertexTuple>;

class Graph
{
    unsigned date; // DFS //
    unsigned **adjMatrix;
    unsigned ordre;
    vertexTuple *currentTuple;
    vector<vertexSuccessor> *currentSuccessorVect;

public:
    vertexVect vertexTuples;
    queue<vertexTuple*> queue_BFS ;
    stack<vertexTuple*> stack_DFS ;
    stack<vertexTuple*> stack_Dijkstra ;

    vector<vertexSuccessor>::iterator currentSuccessor;

    Graph();
    VertexView *getItem(QPointF clickPos);
    vertexTuple *getVertexTuple(QPointF clickPos);
    QPointF CollisionAdd(QPointF newVertexPos);
    QPointF CollisionMove(QPointF newVertexPos);
    QPointF avoidCollisonPoint(QPointF p1, QPointF p2);
    ArcView *getArcView(vertexTuple *fromVertexTuple, vertexTuple *toVertexPos);
    vertexTuple *getTupleFromVertex(Vertex* vertex);

    unsigned getDate(){return date;}
    unsigned getOrdre(){return ordre;}
    void setDate(unsigned d){date=d;}
    void setOrdre(unsigned o){ordre=o;}

    void delVertex(VertexView* vertexItem);
    void deleteArc(vertexTuple *fromVT ,vertexTuple *toVt);
    bool arcExist(vertexTuple *fromVT, vertexTuple *toVT);

    void resetBFS();
    void initializeBFS(vertexTuple *initialVertex );
    bool stepBFS();

    void resetDFS();
    void initializeDFS(vertexTuple *initialVertex);
    bool stepDFS();

    void resetDijkstra();
    void dijkstra(vertexTuple *initialVertex);
    bool runDijkstra(vertexTuple *initialVertex, vertexTuple *destinationVertex);
    void stepDijkstra();

    unsigned Ordre() {
        return vertexTuples.size() ;
    }
    unsigned** calculateAdjMatrix() ;

    int indexOf(Vertex*) ;
    unsigned** getAdjMatrix() {
        return adjMatrix ;
    }
};
#endif // GRAPH_H
