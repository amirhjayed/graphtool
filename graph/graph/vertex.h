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
    unsigned debTime ;
    unsigned endTime ;
    colors color ;
public:
    Vertex();
    Vertex(Vertex* ,unsigned, unsigned);
    Vertex(const Vertex &);

    unsigned getDistancce(){return distance;}
    unsigned getDebTime(){return debTime;}
    unsigned getEndTime(){return endTime;}
    Vertex *getParent(){return parent;}
    colors getColor(){return color;}

    void setDistance(unsigned d){distance=d;}
    void setDebTime(unsigned dt){debTime=dt;}
    void setEndTime(unsigned et){endTime=et;}
    void setColor(colors clr){color=clr;}
    void setParent(Vertex *p){parent=p;}

    Vertex & operator = (const Vertex &);
};

#endif // VERTEX_H
