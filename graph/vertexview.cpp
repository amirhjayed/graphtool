#include "vertexview.h"
#include <QPainter>
#include <QGraphicsView>
#include <QDebug>
#include "graphtool.h"
QRectF VertexView::boundingRect() const
{
    return QRectF(posi.x()-20.0,posi.y()+20,40.0,40.0);
}

VertexView::VertexView(QPointF pos){
    posi=pos;
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
}


void VertexView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawEllipse(posi,20,20);
}

QPainterPath VertexView::shape() const{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}




