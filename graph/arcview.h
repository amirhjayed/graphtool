#ifndef ARCVIEW_H
#define ARCVIEW_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>
#include <QColor>

class ArcView : public QGraphicsItem
{
    QPointF *fromPos;
    QPointF *toPos;
    QColor arcColor;
    int arcWidth;
public:
    ArcView();
    ArcView(QPointF *fp, QPointF *tp, QColor lineColor=Qt::black, int width=1);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape () const;

    void setWidth(int width){arcWidth=width;}
    void setColor(QColor color){arcColor=color;}
    void setFromPos(QPointF p){*fromPos=p;}
    void setToPos(QPointF p){*toPos=p;}
    QPointF getFromPos(){return *fromPos;}
    QPointF getToPos(){return *toPos;}
    QColor getColor(){return arcColor;}
    int getWidth(){return arcWidth;}

};

#endif // ARCVIEW_H
