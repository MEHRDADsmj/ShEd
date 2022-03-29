#include "mainwindow.h"

#include <QApplication>
#include "textmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    TextManager* tm = TextManager::GetTextManager();
    w.GetEditors(tm->VertexEdit, tm->FragmentEdit);
    w.show();
    return a.exec();
}
