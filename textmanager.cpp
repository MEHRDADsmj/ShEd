#include "textmanager.h"
#include <QTextEdit>
#include <QFile>

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

void TextManager::ExportFiles()
{
    std::string VertexSrc, FragSrc;
    GetTextFromEditors(VertexSrc, FragSrc);

    QFile VertexFile("Vertex.glsl");
    VertexFile.open(QIODeviceBase::WriteOnly);
    VertexFile.write(VertexSrc.c_str());
    VertexFile.close();

    QFile FragFile("Fragment.glsl");
    FragFile.open(QIODeviceBase::WriteOnly);
    FragFile.write(FragSrc.c_str());
    FragFile.close();
}

TextManager *TextManager::GetTextManager()
{
    static TextManager* tm = new TextManager();
    return tm;
}
