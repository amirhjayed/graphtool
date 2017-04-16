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

VertexView::VertexView(QPointF pos, std::string _name, QColor _color, int _width, unsigned _debTime, unsigned _endTime){
    posi=pos;
    name=_name;
    color=_color;
    width=_width;
    debTime=_debTime;
    endTime=_endTime;
}


void VertexView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(color);
    pen.setWidth(width);
    painter->setPen(pen);
    string text=name;
    int textLength=name.length();
    int decalage=-4*textLength;
    painter->drawEllipse(posi,20,20);
    qDebug()<<"debTime"<<getDebTime();
    if(getDebTime()!=0){
        painter->setPen(QPen(Qt::blue));
        string str = std::to_string(getDebTime());
        int dec=str.length();
        QString qDebT=QString::fromStdString(str);
        painter->drawText(posi+QPoint(dec*(-2),-23),qDebT);
    }
    qDebug()<<"endTime: "<<getEndTime();
    if(getEndTime()!=0){
        painter->setPen(QPen(Qt::red));
        string str = std::to_string(getEndTime());
        int dec=str.length();
        QString qEndT=QString::fromStdString(str);
        painter->drawText(posi+QPoint(dec*(-2),33),qEndT);
    }
        QString qText=QString::fromStdString(text);
        painter->drawText(posi+QPoint(decalage,5),qText);
}


QPainterPath VertexView::shape() const{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}




