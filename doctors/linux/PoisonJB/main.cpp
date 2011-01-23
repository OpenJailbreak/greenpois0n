#include <QtGui/QApplication>
#include "poisonmain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PoisonMain w;
    w.show();
    return a.exec();
}
