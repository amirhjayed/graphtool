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
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape () const;
protected:

};

#endif // VERTEXVIEW_H
