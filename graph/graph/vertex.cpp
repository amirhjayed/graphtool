#include "vertex.h"
#include <limits>
Vertex::Vertex(){}
Vertex::Vertex(const Vertex &v){
    distance=v.distance;
    debTime=v.debTime;
    endTime=v.endTime;
    color=v.color;
}
Vertex & Vertex::operator = (const Vertex &v){
    distance=v.distance;
    debTime=v.debTime;
    endTime=v.endTime;
    color=v.color;
    return *this;
}



