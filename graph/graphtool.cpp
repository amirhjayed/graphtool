#include "vertexview.h"
#include "graphtool.h"
#include "ui_graphtool.h"
#include "graph.h"
#include "vertex.h"
#include "arcview.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
graphtool::graphtool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::graphtool)
{
    currentMode=NA;
    ui->setupUi(this);
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
    ui->actionDelete_Vertex->setChecked(false);
    ui->actionAdd_arc->setChecked(false);
    ui->actionDelete_arc->setChecked(false);
    emit changedMode(currentMode);
}

void graphtool::on_actionDelete_Vertex_triggered()
{
    currentMode = deleteVertex;
    ui->actionAdd_Vertex->setChecked(false);
    ui->actionAdd_arc->setChecked(false);
    ui->actionDelete_arc->setChecked(false);
    emit changedMode(currentMode);

}

void graphtool::on_actionAdd_arc_triggered()
{
    currentMode = addArc;
    ui->actionAdd_Vertex->setChecked(false);
    ui->actionDelete_Vertex->setChecked(false);
    ui->actionDelete_arc->setChecked(false);
    emit changedMode(currentMode);
}

void graphtool::on_actionDelete_arc_triggered()
{
    currentMode = deleteArc;
    ui->actionAdd_Vertex->setChecked(false);
    ui->actionDelete_Vertex->setChecked(false);
    ui->actionAdd_arc->setChecked(false);
    emit changedMode(currentMode);
}


