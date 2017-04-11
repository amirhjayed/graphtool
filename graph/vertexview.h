#ifndef VERTEXVIEW_H
#define VERTEXVIEW_H


#include <QGraphicsView>
#include <QGraphicsItem>

class VertexView : public QGraphicsItem
{
    QPointF posi;
public:
    QRectF boundingRect() const;
    VertexView(QPointF position);
    QPointF getPosi(){return posi;}
    void setPosi(QPointF pos){posi=pos;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape () const;
protected:

};

#endif // VERTEXVIEW_H
