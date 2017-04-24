#ifndef ARCWEIGHTEDIT_H
#define ARCWEIGHTEDIT_H

#include <QDialog>

namespace Ui {
class ArcWeightEdit;
}

class ArcWeightEdit : public QDialog
{
    Q_OBJECT

public:
    explicit ArcWeightEdit(QWidget *parent = 0);
    ~ArcWeightEdit();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ArcWeightEdit *ui;
signals:
    void accepted(int);
};

#endif // ARCWEIGHTEDIT_H
