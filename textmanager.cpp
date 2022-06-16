#include "textmanager.h"
#include <QPlainTextEdit>
#include <QFile>

TextManager* TextManager::Manager = nullptr;

TextManager::TextManager(QObject *parent, QPlainTextEdit* Vertex, QPlainTextEdit* Fragment)
    : QObject{parent}, VertexEdit{Vertex}, FragmentEdit{Fragment}
{
    Manager = this;
}

TextManager::~TextManager()
{
    delete Manager;
    Manager = nullptr;
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
    if (Manager == nullptr)
    {
        Manager = new TextManager();
    }

    return Manager;
}
