#include "textmanager.h"

TextManager::TextManager(QObject *parent, QTextEdit* Vertex, QTextEdit* Fragment)
    : QObject{parent}, VertexEdit{Vertex}, FragmentEdit{Fragment}
{

}
