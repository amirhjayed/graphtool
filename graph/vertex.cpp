#include "vertex.h"
#include <limits>
Vertex::Vertex(){}
Vertex::Vertex(const Vertex &v){
    distance=v.distance;
    color=v.color;
}
Vertex & Vertex::operator = (const Vertex &v){
    distance=v.distance;
    color=v.color;
    return *this;
}



