#ifndef GRAPHTOOL_H
#define GRAPHTOOL_H

#include <QMainWindow>
#include "canvas.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include "vertexview.h"

namespace Ui {
class graphtool;
}

class graphtool : public QMainWindow
{
    Q_OBJECT

public:
    enum mode {NA,addVertex,deleteVertex,addArc,deleteArc,BFS,DFS,Dijkstra,Bellman_ford};
    mode currentMode;
    Ui::graphtool *ui;
    explicit graphtool(QWidget *parent = 0);
    ~graphtool();
private slots:
    void on_actionExit_triggered();

    void on_actionAdd_Vertex_triggered();

    void on_actionDelete_Vertex_triggered();

    void on_actionAdd_arc_triggered();

    void on_actionDelete_arc_triggered();

    void on_actionNavigation_triggered();

    void on_actionBFS_triggered();

    void on_actionDfS_triggered();

    void on_actionDijkstra_triggered();

    void on_actionBellman_ford_triggered();

    void on_actionReset_triggered();

signals:
    void changedMode(mode newMode);
private:
    QPoint mousePressPosition;
    Canvas *myCanvas;

};


#endif // GRAPHTOOL_H
