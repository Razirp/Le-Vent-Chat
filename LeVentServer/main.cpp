#include "widget.h"
#include <QApplication>
Widget* mw = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    mw = &w;

    return a.exec();
}
