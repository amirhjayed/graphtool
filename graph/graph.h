#ifndef GRAPH_H
#define GRAPH_H
#include "vertex.h"
#include "vertexview.h"
#include "arcview.h"
#include <vector>
#include <QGraphicsItem>
#include <QPointF>
#include <utility>
#include <tuple>

using vertexSuccessor = tuple<Vertex*, int ,ArcView*>;
using vertexTuple = tuple<Vertex, VertexView*,vector<vertexSuccessor>>;
using vertexVect = vector<vertexTuple>;
using matrix=vector<vector<int>> ;

class Graph
{
    unsigned date;
    unsigned ordre;
    matrix adjMatrix;

public:
    Graph();
    vertexVect vertexTuples;

    VertexView *getItem(QPointF clickPos);
    vertexTuple *getVertexTuple(QPointF clickPos);
    QPointF CollisionAdd(QPointF newVertexPos);
    QPointF CollisionMove(QPointF newVertexPos);
    QPointF avoidCollisonPoint(QPointF p1, QPointF p2);
    ArcView *getArcView(vertexTuple *fromVertexTuple,QPointF toVertexPos);
    vertexTuple *getTupleFromVertex(Vertex* vertex);

    unsigned getDate(){return date;}
    unsigned getOrdre(){return ordre;}
    void setDate(unsigned d){date=d;}
    void setOrdre(unsigned o){ordre=o;}

    void delVertex();
    void delVertex(VertexView* vertexItem);

    void addArc();
    void deleteArc();
    bool arcExist();

    void createAdjMatrix();

    void BFS(int indiceSource);

    void DFS();

    void dijkstra();

    void bellman();


};
#endif // GRAPH_H
