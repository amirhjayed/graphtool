#include "graphtool.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    graphtool w;
    w.show();
    return a.exec();
}
