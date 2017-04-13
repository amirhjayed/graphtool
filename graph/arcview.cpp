#include "arcview.h"
#include <QPointF>
#include <QLineF>
#include <QDebug>
#include <cmath>
ArcView::ArcView()
{

}

ArcView::ArcView(QPointF* fp, QPointF* tp, QColor lineColor, int width)
{
    fromPos=fp;
    toPos=tp;
    arcColor=lineColor;
    arcWidth=width;
}

QRectF ArcView::boundingRect() const{
    return QRectF(*fromPos,*toPos);
}

void ArcView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    if(*fromPos==QPointF(0.0,0.0) || *toPos == QPointF(0.0,0.0)){
        qDebug()<<"j'ai entré";
        painter->drawPoint(0,0);
    }
    else{
        QPen pen(arcColor);
        pen.setWidth(arcWidth);
        painter->setPen(pen);
        QLineF line(*fromPos,*toPos);
        qreal angle=line.angle();
        double radangle=angle*M_PI/180;
        line.setLength(line.length()-40);
        line.translate(20*cos(radangle),-20*sin(radangle));
        painter->drawLine(line);
        QLineF flech1,flech2;
        flech1.setP1(line.center());
        flech1.setLength(10.0);
        flech1.setAngle(angle+150.0);
        flech2.setP1(line.center());
        flech2.setAngle(angle-150.0);
        flech2.setLength(10.0);
        painter->drawLine(flech1);
        painter->drawLine(flech2);
    }
}

QPainterPath ArcView::shape() const{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
