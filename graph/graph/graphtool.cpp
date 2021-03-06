#include "vertexview.h"
#include "graphtool.h"
#include "ui_graphtool.h"
#include <QGraphicsView>
graphtool::graphtool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::graphtool)
{
    currentMode=NA;
    ui->setupUi(this);
    ui->actionNavigation->setChecked(true);
    myCanvas=new Canvas(this);
    ui->centralWidget->layout()->addWidget(myCanvas);
}
graphtool::~graphtool(){
    delete ui;
}


void graphtool::on_actionExit_triggered(){
    close();
}

void graphtool::on_actionAdd_Vertex_triggered()
{
    currentMode = addVertex;
    myCanvas->startedBFS = false;
    myCanvas->graphModel.resetBFS();
    myCanvas->scene->update();
    ui->actionAdd_Vertex->setChecked(true);
    ui->actionDelete_Vertex->setChecked(false);
    ui->actionAdd_arc->setChecked(false);
    ui->actionDelete_arc->setChecked(false);
    ui->actionNavigation->setChecked(false);
    ui->actionBFS->setChecked(false);
    ui->actionDfS->setChecked(false);
    ui->actionDijkstra->setChecked(false);
    ui->actionBellman_ford->setChecked(false);
    emit changedMode(currentMode);
}

void graphtool::on_actionDelete_Vertex_triggered()
{
    currentMode = deleteVertex;
    myCanvas->startedBFS = false;
    myCanvas->graphModel.resetBFS();
    myCanvas->scene->update();
    ui->actionDelete_Vertex->setChecked(true);
    ui->actionAdd_Vertex->setChecked(false);
    ui->actionAdd_arc->setChecked(false);
    ui->actionDelete_arc->setChecked(false);
    ui->actionNavigation->setChecked(false);
    ui->actionBFS->setChecked(false);
    ui->actionDfS->setChecked(false);
    ui->actionDijkstra->setChecked(false);
    ui->actionBellman_ford->setChecked(false);
    emit changedMode(currentMode);

}

void graphtool::on_actionAdd_arc_triggered()
{
    currentMode = addArc;
    myCanvas->startedBFS = false;
    myCanvas->graphModel.resetBFS();
    myCanvas->scene->update();
    ui->actionAdd_arc->setChecked(true);
    ui->actionAdd_Vertex->setChecked(false);
    ui->actionDelete_Vertex->setChecked(false);
    ui->actionDelete_arc->setChecked(false);
    ui->actionNavigation->setChecked(false);
    ui->actionBFS->setChecked(false);
    ui->actionDfS->setChecked(false);
    ui->actionDijkstra->setChecked(false);
    ui->actionBellman_ford->setChecked(false);
    emit changedMode(currentMode);
}

void graphtool::on_actionDelete_arc_triggered()
{
    currentMode = deleteArc;
    myCanvas->startedBFS = false;
    myCanvas->graphModel.resetBFS();
    myCanvas->scene->update();
    ui->actionDelete_arc->setChecked(true);
    ui->actionAdd_Vertex->setChecked(false);
    ui->actionDelete_Vertex->setChecked(false);
    ui->actionAdd_arc->setChecked(false);
    ui->actionNavigation->setChecked(false);
    ui->actionBFS->setChecked(false);
    ui->actionDfS->setChecked(false);
    ui->actionDijkstra->setChecked(false);
    ui->actionBellman_ford->setChecked(false);
    emit changedMode(currentMode);
}



void graphtool::on_actionNavigation_triggered()
{
    currentMode = NA;
    myCanvas->startedBFS = false;
    myCanvas->graphModel.resetBFS();
    myCanvas->scene->update();
    ui->actionNavigation->setChecked(true);
    ui->actionAdd_Vertex->setChecked(false);
    ui->actionDelete_Vertex->setChecked(false);
    ui->actionAdd_arc->setChecked(false);
    ui->actionDelete_arc->setChecked(false);
    ui->actionBFS->setChecked(false);
    ui->actionDfS->setChecked(false);
    ui->actionDijkstra->setChecked(false);
    ui->actionBellman_ford->setChecked(false);
    emit changedMode(currentMode);
}

void graphtool::on_actionBFS_triggered(){
    currentMode = BFS ;
    myCanvas->startedBFS = false;
    myCanvas->graphModel.resetBFS();
    myCanvas->scene->update();
    ui->actionBFS->setChecked(true);
    ui->actionDfS->setChecked(false);
    ui->actionDijkstra->setChecked(false);
    ui->actionBellman_ford->setChecked(false);
    ui->actionNavigation->setChecked(false);
    ui->actionAdd_Vertex->setChecked(false);
    ui->actionDelete_Vertex->setChecked(false);
    ui->actionAdd_arc->setChecked(false);
    ui->actionDelete_arc->setChecked(false);
    emit changedMode(currentMode);
}

void graphtool::on_actionDfS_triggered(){
    currentMode = DFS ;
    myCanvas->startedBFS = false;
    myCanvas->graphModel.resetBFS();
    myCanvas->scene->update();
    ui->actionBFS->setChecked(false);
    ui->actionDfS->setChecked(true);
    ui->actionDijkstra->setChecked(false);
    ui->actionBellman_ford->setChecked(false);
    ui->actionNavigation->setChecked(false);
    ui->actionAdd_Vertex->setChecked(false);
    ui->actionDelete_Vertex->setChecked(false);
    ui->actionAdd_arc->setChecked(false);
    ui->actionDelete_arc->setChecked(false);
}

void graphtool::on_actionDijkstra_triggered(){
    currentMode = Dijkstra ;
    myCanvas->startedBFS = false;
    myCanvas->graphModel.resetBFS();
    myCanvas->scene->update();
    ui->actionBFS->setChecked(false);
    ui->actionDfS->setChecked(false);
    ui->actionDijkstra->setChecked(true);
    ui->actionBellman_ford->setChecked(false);
    ui->actionNavigation->setChecked(false);
    ui->actionAdd_Vertex->setChecked(false);
    ui->actionDelete_Vertex->setChecked(false);
    ui->actionAdd_arc->setChecked(false);
    ui->actionDelete_arc->setChecked(false);
    emit changedMode(currentMode);
}

void graphtool::on_actionBellman_ford_triggered(){
    myCanvas->graphModel.resetBFS();
    myCanvas->scene->update();currentMode = Bellman_ford ;
    myCanvas->startedBFS = false;
    ui->actionBFS->setChecked(false);
    ui->actionDfS->setChecked(false);
    ui->actionDijkstra->setChecked(false);
    ui->actionBellman_ford->setChecked(true);
    ui->actionNavigation->setChecked(false);
    ui->actionAdd_Vertex->setChecked(false);
    ui->actionDelete_Vertex->setChecked(false);
    ui->actionAdd_arc->setChecked(false);
    ui->actionDelete_arc->setChecked(false);
    emit changedMode(currentMode);
}

void graphtool::on_actionReset_triggered(){
    myCanvas->reset();
}
