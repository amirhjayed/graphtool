#ifndef GRAPH_H
#define GRAPH_H
#include "vertex.h"
#include "vertexview.h"
#include "arcview.h"
#include <vector>
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
    vertexVect vertexs;
public:
    Graph(unsigned ord=0);

    unsigned getDate(){return date;}
    unsigned getOrdre(){return ordre;}
    void setDate(unsigned d){date=d;}
    void setOrdre(unsigned o){ordre=o;}

    void addVertex(Vertex &);
    void delVertex();
    bool vertexExist();

    void addArc();
    void delArc();
    bool arcExist();

    void createAdjMatrix();

    void BFS(int indiceSource);

    void DFS();

    void dijkstra();

    void bellman();


};
#endif // GRAPH_H
