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
    int arcWeight ;

public:
    bool BFSflag;
    bool DFSflag;
    bool dijkstraFlag;
    bool bellman_fordFlag;
    bool is2wayArc;
    bool isFirst;
    QPainterPath shapePath;

    ArcView();
    ArcView(QPointF *fp, QPointF *tp, QColor lineColor=Qt::black, int width=1);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape () const;
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) ;

    void setWidth(int width){arcWidth=width;}
    void setWeight(int weight){arcWeight=weight;}
    void setColor(QColor color){arcColor=color;}
    void setFromPos(QPointF p){*fromPos=p;}
    void setToPos(QPointF p){*toPos=p;}
    QPointF getFromPos(){return *fromPos;}
    QPointF getToPos(){return *toPos;}
    QColor getColor(){return arcColor;}
    int getWidth(){return arcWidth;}
    int getWeight() { return arcWeight;}
};
#endif // ARCVIEW_H
