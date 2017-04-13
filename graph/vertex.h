#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vertexview.h>
using namespace std;
class Vertex
{
    Vertex *parent;
    unsigned distance  ;
    unsigned debTime ;
    unsigned endTime ;
    unsigned color ;
public:
    Vertex();
    Vertex(Vertex* ,unsigned, unsigned);
    Vertex(const Vertex &);

    unsigned getDistancce(){return distance;}
    unsigned getDebTime(){return debTime;}
    unsigned getEndTime(){return endTime;}
    unsigned getColor(){return color;}

    void setDistance(unsigned d){distance=d;}
    void setDebTime(unsigned dt){debTime=dt;}
    void setEndTime(unsigned et){endTime=et;}
    void setColor(unsigned clr){color=clr;}

    Vertex & operator = (const Vertex &);
};

#endif // VERTEX_H
