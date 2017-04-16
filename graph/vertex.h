#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vertexview.h>
using namespace std;
enum colors {white,grey,black};
class Vertex
{
    Vertex *parent;
    unsigned distance  ;
    colors color ;
public:
    Vertex();
    Vertex(Vertex* ,unsigned, unsigned);
    Vertex(const Vertex &);

    unsigned getDistance(){return distance;}
    Vertex *getParent(){return parent;}
    colors getColor(){return color;}

    void setDistance(unsigned d){distance=d;}
    void setColor(colors clr){color=clr;}
    void setParent(Vertex *p){parent=p;}

    Vertex & operator = (const Vertex &);
};

#endif // VERTEX_H
