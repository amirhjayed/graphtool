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
    unsigned debTime;
    unsigned endTime;
public:
    QRectF boundingRect() const;
    VertexView(QPointF position, std::string name="", QColor _color=Qt::black, int _width = 2,unsigned _debTime=0,unsigned _endTime=0);

    QPointF getPosi(){return posi;}
    QPointF* getPosPtr(){return &posi;}

    QColor getColor(){return color;}
    int getWidth(){return width;}
    std::string getName(){return name;}
    unsigned getDebTime(){return debTime;}
    unsigned getEndTime(){return endTime;}

    void setPosi(QPointF pos){posi=pos;}
    void setName(std::string _name){name=_name;}
    void setColor(QColor c){color=c;}
    void setWidth(int w){width=w;}
    void setDebTime(unsigned debT){debTime=debT;}
    void setEndTime(unsigned endT){endTime=endT;}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape () const;
    protected:

};

#endif // VERTEXVIEW_H
