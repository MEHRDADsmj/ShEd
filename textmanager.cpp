#include "textmanager.h"
#include <QTextEdit>

TextManager* TextManager::Manager = nullptr;

TextManager::TextManager(QObject *parent, QTextEdit* Vertex, QTextEdit* Fragment)
    : QObject{parent}, VertexEdit{Vertex}, FragmentEdit{Fragment}
{
    Manager = this;
}

TextManager::~TextManager()
{
    delete Manager;
}

void TextManager::GetTextFromEditors(std::string& VertexSrc, std::string& FragSrc)
{
    QString Src = VertexEdit->toPlainText();
    std::string String = Src.toStdString();
    VertexSrc = String;

    Src = FragmentEdit->toPlainText();
    String = Src.toStdString();
    FragSrc = String;
}

TextManager *TextManager::GetTextManager()
{
    static TextManager* tm = new TextManager();
    return tm;
}
