#include "vertexview.h"
#include <QPainter>
#include <QGraphicsView>
#include <QDebug>
#include <string>
#include <QTextItem>
#include "graphtool.h"
QRectF VertexView::boundingRect() const
{
    return QRectF(posi.x()-20.0,posi.y()+20,40.0,40.0);
}

VertexView::VertexView(QPointF pos, std::string _name){
    posi=pos;
    name=_name;
}


void VertexView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    string text=name;
    int textLength=name.length();
    int decalage=-4*textLength;
    painter->drawEllipse(posi,20,20);
    QString qText=QString::fromStdString(text);
    painter->drawText(posi+QPoint(decalage,5),qText);
}

QPainterPath VertexView::shape() const{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}




