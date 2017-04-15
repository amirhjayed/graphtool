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
#include "arcview.h"

using vertexSuccessor = tuple<Vertex*, int ,ArcView*>;
using vertexTuple = tuple<Vertex, VertexView*,vector<vertexSuccessor>>;
using vertexVect = vector<vertexTuple>;
using matrix=vector<vector<int>> ;

class Graph
{
    unsigned date;
    unsigned ordre;
    matrix adjMatrix;
    vertexTuple *currentTuple_BFS;

public:
    vertexVect vertexTuples;
    queue<vertexTuple*> queueBFS ;

    Graph();
    VertexView *getItem(QPointF clickPos);
    vertexTuple *getVertexTuple(QPointF clickPos);
    QPointF CollisionAdd(QPointF newVertexPos);
    QPointF CollisionMove(QPointF newVertexPos);
    QPointF avoidCollisonPoint(QPointF p1, QPointF p2);
    ArcView *getArcView(vertexTuple *fromVertexTuple, vertexTuple *toVertexPos);
    //vertexTuple *getTupleFromVertex(Vertex* vertex);

    unsigned getDate(){return date;}
    unsigned getOrdre(){return ordre;}
    void setDate(unsigned d){date=d;}
    void setOrdre(unsigned o){ordre=o;}

    void delVertex(VertexView* vertexItem);
    void deleteArc(vertexTuple *fromVT ,vertexTuple *toVt);
    bool arcExist(vertexTuple *fromVT, vertexTuple *toVT);

    void initializeBFS(vertexTuple *initialVertex );
    void stepBFS();

    void createAdjMatrix();

};
#endif // GRAPH_H
