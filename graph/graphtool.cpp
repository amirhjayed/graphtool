#include "vertexview.h"
#include "graphtool.h"
#include "ui_graphtool.h"
#include <QGraphicsView>
#include <QDebug>
#include <QMessageBox>
#include <QTableWidget>

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
    ui->statusBar->showMessage("A new vertex will be created in click Position, if the position is avaible",5000);
    myCanvas->startedBFS = false;
    myCanvas->startedDFS = false;
    myCanvas->startedDijkstra = false;
    myCanvas->startedBellman_ford = false;
    myCanvas->graphModel.resetBFS();
    myCanvas->graphModel.resetDFS();
    myCanvas->graphModel.resetDijkstra();
    ////myCanvas->graphModel.resetBellman_ford();
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
    ui->statusBar->showMessage("click on a vertex to delete it, a vertex will only be deleted if there are no arcs connected to it",5000);
    myCanvas->startedBFS = false;
    myCanvas->startedDFS = false;
    myCanvas->startedDijkstra = false;
    myCanvas->startedBellman_ford = false;
    myCanvas->graphModel.resetBFS();
    myCanvas->graphModel.resetDFS();
    myCanvas->graphModel.resetDijkstra();
    ////myCanvas->graphModel.resetBellman_ford();
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
    ui->statusBar->showMessage("Select two vertexs to create an arc in between",5000);
    myCanvas->startedDFS = false;
    myCanvas->startedDijkstra = false;
    myCanvas->startedBellman_ford = false;
    myCanvas->startedBFS = false;
    myCanvas->graphModel.resetBFS();
    myCanvas->graphModel.resetDFS();
    myCanvas->graphModel.resetDijkstra();
    //myCanvas->graphModel.resetBellman_ford();
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
    ui->statusBar->showMessage("Select two vertexs to delete the arc in between, if it exists.",5000);
    myCanvas->startedBFS = false;
    myCanvas->startedDFS = false;
    myCanvas->startedDijkstra = false;
    myCanvas->startedBellman_ford = false;
    myCanvas->graphModel.resetBFS();
    myCanvas->graphModel.resetDFS();
    myCanvas->graphModel.resetDijkstra();
    //myCanvas->graphModel.resetBellman_ford();
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
    ui->statusBar->showMessage("Move vertexs by clicking and draging them");

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
    ui->statusBar->showMessage("Select a starting vertex, use right arrow key to advance, space bar to fastforward, R to restart");
    myCanvas->startedBFS = false;
    myCanvas->startedDFS = false;
    myCanvas->startedDijkstra = false;
    myCanvas->startedBellman_ford = false;
    myCanvas->graphModel.resetBFS();
    myCanvas->graphModel.resetDFS();
    myCanvas->graphModel.resetDijkstra();
    //myCanvas->graphModel.resetBellman_ford();
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
    ui->statusBar->showMessage("Select a starting vertex, use right arrow key to advance, space bar to fastforward, R to restart");
    myCanvas->startedBFS = false;
    myCanvas->startedDFS = false;
    myCanvas->startedDijkstra = false;
    myCanvas->startedBellman_ford = false;
    myCanvas->graphModel.resetBFS();
    myCanvas->graphModel.resetDFS();
    myCanvas->graphModel.resetDijkstra();
    //myCanvas->graphModel.resetBellman_ford();
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
    emit changedMode(currentMode);
}

void graphtool::on_actionDijkstra_triggered(){
    currentMode = Dijkstra ;
    myCanvas->startedBFS = false;
    myCanvas->startedDFS = false;
    myCanvas->startedDijkstra = false;
    myCanvas->startedBellman_ford = false;
    myCanvas->graphModel.resetBFS();
    myCanvas->graphModel.resetDFS();
    myCanvas->graphModel.resetDijkstra();
    //myCanvas->graphModel.resetBellman_ford();
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
    currentMode = Bellman_ford ;
    myCanvas->startedBFS = false;
    myCanvas->startedDFS = false;
    myCanvas->startedDijkstra = false;
    myCanvas->startedBellman_ford = false;
    myCanvas->graphModel.resetBFS();
    myCanvas->graphModel.resetDFS();
    myCanvas->graphModel.resetDijkstra();
    //myCanvas->graphModel.resetBellman_ford();
    myCanvas->scene->update();

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


void graphtool::on_actionReset_triggered(){ /// THIS DOESNT WORK /// (Matrix is correct ,Affichage is not!)
    QMessageBox box;
    box.setText("Warning! This will remove everything");
    box.setStandardButtons(QMessageBox::Cancel|QMessageBox::Reset);
    int ret = box.exec();
    if(ret == QMessageBox::Reset)
        myCanvas->reset();
}

void graphtool::on_actionMatrice_d_adjacence_triggered(){
    unsigned** adjMatrix = myCanvas->graphModel.calculateAdjMatrix() ;
    QFrame* myMatrixView =  new QFrame() ;
    int rows = myCanvas->graphModel.Ordre() ; // get from matrix
    int columns = rows ;// get from matrix
    QPainter *painter;
    painter = new QPainter(myMatrixView);
    myMatrixView->resize(rows*50,columns*50);
    for ( int r = 0; r != rows; ++r ){
       for ( int c = 0; c != columns; ++c ){
           QString str = QString::fromStdString(std::to_string(adjMatrix[r][c]));
           qDebug()<<str;
           painter->drawText(r*5+5,c*5+5,str);
       }
    }
    myMatrixView->setVisible(true);
    myMatrixView->update();
}
