#include "arcweightedit.h"
#include "ui_arcweightedit.h"
#include <QDebug>

ArcWeightEdit::ArcWeightEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArcWeightEdit)
{
    ui->setupUi(this);
}

ArcWeightEdit::~ArcWeightEdit()
{
    delete ui;
}

void ArcWeightEdit::on_buttonBox_accepted()
{
    qDebug() << "accepted " << ui->spinBox->value() ;
    emit accepted(ui->spinBox->value()) ;
}
