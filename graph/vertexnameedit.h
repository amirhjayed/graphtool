#ifndef VERTEXNAMEEDIT_H
#define VERTEXNAMEEDIT_H

#include <QDialog>

namespace Ui {
class VertexNameEdit;
}

class VertexNameEdit : public QDialog
{
    Q_OBJECT

public:
    explicit VertexNameEdit(QWidget *parent = 0);
    ~VertexNameEdit();
private slots:
    void on_buttonBox_accepted();

private:
    Ui::VertexNameEdit *ui;
signals:
    void accepted(QString );
};

#endif // VERTEXNAMEEDIT_H
