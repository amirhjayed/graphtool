#include "vertexnameedit.h"
#include "ui_vertexnameedit.h"
#include <QDebug>

VertexNameEdit::VertexNameEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VertexNameEdit)
{
    ui->setupUi(this);
}

VertexNameEdit::~VertexNameEdit(){
    delete ui;
}

void VertexNameEdit::on_buttonBox_accepted(){
    qDebug() << "accepted " << ui->lineEdit->text();
    emit accepted(ui->lineEdit->text()) ;
}
