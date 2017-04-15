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
    QColor color;
    int width;
public:
    QRectF boundingRect() const;
    VertexView(QPointF position, std::string name="", QColor _color=Qt::black, int _width = 2);

    QPointF getPosi(){return posi;}
    QPointF* getPosPtr(){return &posi;}
    QColor getColor(){return color;}
    int getWidth(){return width;}

    void setPosi(QPointF pos){posi=pos;}
    void setName(std::string _name){name=_name;}
    std::string getName(){return name;}
    void setColor(QColor c){color=c;}
    void setWidth(int w){width=w;}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape () const;
    protected:

};

#endif // VERTEXVIEW_H
