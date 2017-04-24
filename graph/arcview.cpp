#include <QPointF>
#include <QLineF>
#include <QDebug>
#include <cmath>
#include <QGraphicsSceneMouseEvent>
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
    setFlag(ItemIsSelectable);
    arcWeight = 0 ;
    is2wayArc=false;
    isFirst=true;
    shapePath.moveTo(*fromPos);
    shapePath.lineTo(*toPos);
}

QRectF ArcView::boundingRect() const{
    if(*fromPos!=*toPos)
        return QRectF(*fromPos,*toPos).normalized();
    else
        return QRectF(*fromPos+QPointF(-20,-20),*toPos+QPointF(20,20)).normalized();
}

void ArcView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
        QPen pen(arcColor);
        pen.setWidth(arcWidth);
        painter->setPen(pen);
        if(*fromPos!=*toPos){
            QLineF line(*fromPos,*toPos);
            qreal angle=line.angle();

            double radangle=angle*M_PI/180;
            if(is2wayArc==false){
                line.setLength(line.length()-40);
                line.translate(20*cos(radangle),-20*sin(radangle));
                QPolygonF poly;
                poly << line.p1()+QPointF(3*sin(radangle),3*cos(radangle));
                poly << line.p1()+QPointF(-3*sin(radangle),-3*cos(radangle));
                poly << line.p2()+QPointF(-3*sin(radangle),-3*cos(radangle));
                poly << line.p2()+QPointF(3*sin(radangle),3*cos(radangle));
                shapePath.addPolygon(poly);
                painter->drawLine(line);
            }
            else{
                int a(8),b(38),c(20);
                qDebug()<<"is 2 way";
                if(isFirst){
                    qDebug()<<"isFirst";
                    line.translate(-a*sin(radangle),-a*cos(radangle));//perpendiculaire
                    line.setLength(line.length()-b);
                    line.translate(c*cos(radangle),-c*sin(radangle));  //horizontal
                    painter->drawLine(line);
                    QPolygonF poly;
                    poly << line.p1()+QPointF(3*sin(radangle),3*cos(radangle));
                    poly << line.p1()+QPointF(-3*sin(radangle),-3*cos(radangle));
                    poly << line.p2()+QPointF(-3*sin(radangle),-3*cos(radangle));
                    poly << line.p2()+QPointF(3*sin(radangle),3*cos(radangle));
                    shapePath.addPolygon(poly);
                }
                else{
                    qDebug()<<"isSecond";
                    line.translate(-a*sin(radangle),-a*cos(radangle));
                    line.setLength(line.length()-b);
                    line.translate(c*cos(radangle),-c*sin(radangle));  //horizontal
                    painter->drawLine(line);
                    QPolygonF poly;
                    poly << line.p1()+QPointF(3*sin(radangle),3*cos(radangle));
                    poly << line.p1()+QPointF(-3*sin(radangle),-3*cos(radangle));
                    poly << line.p2()+QPointF(-3*sin(radangle),-3*cos(radangle));
                    poly << line.p2()+QPointF(3*sin(radangle),3*cos(radangle));
                    shapePath.addPolygon(poly);
                }
            }
            QLineF flech1,flech2;
            flech1.setP1(line.center());
            flech1.setLength(8.0);
            flech1.setAngle(angle+160.0);
            flech2.setP1(line.center());
            flech2.setAngle(angle-160.0);
            flech2.setLength(8.0);
            painter->drawLine(flech1);
            painter->drawLine(flech2);
            if(arcWeight!=0){
                QString weight_Qstr = QString::fromStdString(std::to_string(arcWeight));
                pen.setWidth(2);
                pen.setColor(Qt::darkCyan);
                painter->setPen(pen);
                painter->drawText(line.center().x(),line.center().y(),weight_Qstr);
            }
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
}

QPainterPath ArcView::shape() const{
    return shapePath;
}
