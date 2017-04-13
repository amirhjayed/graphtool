#ifndef VERTEXVIEW_H
#define VERTEXVIEW_H


#include <QGraphicsView>
#include <QGraphicsItem>
#include <string>
#include <QColor>
class VertexView : public QGraphicsItem
{
    QPointF posi;
    std::string name;
public:
    QRectF boundingRect() const;
    VertexView(QPointF position,std::string name="");
    QPointF getPosi(){return posi;}
    QPointF* getPosPtr(){return &posi;}

    void setPosi(QPointF pos){posi=pos;}
    void setName(std::string _name){name=_name;}
    std::string getName(){return name;}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape () const;
protected:

};

#endif // VERTEXVIEW_H
