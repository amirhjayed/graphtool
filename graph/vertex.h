#ifndef VERTEX_H
#define VERTEX_H

#include <string>
using namespace std;
class Vertex
{
    string name ;
    Vertex *parent;
    unsigned distance  ;
    unsigned debTime ;
    unsigned endTime ;
    unsigned color ;
public:
    Vertex();
    Vertex(Vertex* ,unsigned, unsigned);
    Vertex(const Vertex &);

    string getName(){return name;}
    unsigned getDistancce(){return distance;}
    unsigned getDebTime(){return debTime;}
    unsigned getEndTime(){return endTime;}
    unsigned getColor(){return color;}

    void setName(string n){name=n;}
    void setDistance(unsigned d){distance=d;}
    void setDebTime(unsigned dt){debTime=dt;}
    void setEndTime(unsigned et){endTime=et;}
    void setColor(unsigned clr){color=clr;}

    Vertex & operator = (const Vertex &);
};

#endif // VERTEX_H
