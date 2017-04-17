#include <QPointF>
#include <QLineF>
#include <QDebug>
#include <cmath>
#include "arcview.h"

ArcView::ArcView(){

}

ArcView::ArcView(QPointF *fp, QPointF *tp, QColor lineColor, int width)
{
    fromPos=fp;
    toPos=tp;
    arcColor=lineColor;
    arcWidth=width;
    BFSflag=false;
    DFSflag=false;
    dijkstraFlag=false;
    bellman_fordFlag=false;
}

QRectF ArcView::boundingRect() const{
    if(*fromPos!=*toPos)
        return QRectF(*fromPos,*toPos);
    else
        return QRectF(*fromPos+QPointF(-20,-20),*toPos+QPointF(20,20));
}

void ArcView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    /*if(*fromPos==QPointF(0.0,0.0) || *toPos == QPointF(0.0,0.0)){
        qDebug()<<"faza bhima fel arcview";
        painter->drawPoint(0,0);
    }*/
    //else{
        QPen pen(arcColor);
        pen.setWidth(arcWidth);
        painter->setPen(pen);
        if(*fromPos!=*toPos){
            QLineF line(*fromPos,*toPos);
            qreal angle=line.angle();
            double radangle=angle*M_PI/180;
            line.setLength(line.length()-40);
            line.translate(20*cos(radangle),-20*sin(radangle));
            painter->drawLine(line);
            QLineF flech1,flech2;
            QPointF centreDecale(line.center().x()-5*cos(radangle),line.center().y()+5*sin(radangle));
            flech1.setP1(centreDecale);
            flech1.setLength(10.0);
            flech1.setAngle(angle+150.0);
            flech2.setP1(centreDecale);
            flech2.setAngle(angle-150.0);
            flech2.setLength(10.0);
            painter->drawLine(flech1);
            painter->drawLine(flech2);
        }
        else{
            QPen pen(arcColor);
            pen.setWidth(arcWidth);
            painter->setPen(pen);
            QRectF rect;
            QLineF flech1,flech2;
            flech1.setP1(*toPos+QPointF(2,-45));
            flech1.setLength(5.0);
            flech1.setAngle(150);
            flech2.setP1(*toPos+QPointF(2,-45));
            flech2.setLength(5.0);
            flech2.setAngle(-150);
            rect.setBottomRight(*fromPos+QPointF(13,-15));
            rect.setTopLeft(*fromPos+QPointF(-13,-45));
            painter->drawArc(rect,-45*16,270*16);
            painter->drawLine(flech1);
            painter->drawLine(flech2);
        }
    //}
}

QPainterPath ArcView::shape() const{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
