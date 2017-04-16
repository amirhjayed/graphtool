#ifndef CANVAS_H
#define CANVAS_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include "graph.h"
#include "vertex.h"

class Canvas : public QGraphicsView
{
    Q_OBJECT
public:
    bool startedBFS;
    QGraphicsScene *scene;
    Graph graphModel;

    explicit Canvas(QWidget *parent = 0);
    enum mode {NA,addVertex,deleteVertex,addArc,deleteArc,BFS,DFS,Dijkstra,Bellman_ford};
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void reset();
    //void mouseReleaseEvent(QMouseEvent *event);
    void scrollContentsBy(int,int);
    ~Canvas();
public slots:
    void setMode(mode m);
private:
    mode currentMode;
    QPointF fromVertexPos;
    bool firstClick;
    vertexTuple *fromVertexTuple;
};
#endif // CANVAS_H
