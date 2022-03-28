#include "mainwindow.h"

#include <QApplication>
#include "textmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    TextManager textManager;
    w.GetEditors(textManager.VertexEdit, textManager.FragmentEdit);
    w.show();
    return a.exec();
}
