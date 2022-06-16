#include "textmanager.h"
#include <QPlainTextEdit>
#include <QFile>
#include <QFileDialog>
#include <QDir>

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
    QString FilePath = QFileDialog::getSaveFileName(nullptr, "Export directory", QDir::homePath());
    std::string VertexSrc, FragSrc;
    GetTextFromEditors(VertexSrc, FragSrc);

    QFile VertexFile(FilePath + "_Vertex.glsl");
    VertexFile.open(QIODeviceBase::WriteOnly);
    VertexFile.write(VertexSrc.c_str());
    VertexFile.close();

    QFile FragFile(FilePath + "_Fragment.glsl");
    FragFile.open(QIODeviceBase::WriteOnly);
    FragFile.write(FragSrc.c_str());
    FragFile.close();
}

void TextManager::ImportFiles()
{
    QString VertexFilePath = QFileDialog::getOpenFileName(nullptr, "Import vertex shader", QDir::homePath(),
                                                          "Shader file (*.glsl) ;; Text file (*.txt) ;; Fragment file (*.VShader)");
    QString FragmentFilePath = QFileDialog::getOpenFileName(nullptr, "Import fragment shader", QDir::homePath(),
                                                          "Shader file (*.glsl) ;; Text file (*.txt) ;; Fragment file (*.FShader)");
    QFile VertexFile(VertexFilePath);
    VertexFile.open(QIODeviceBase::ReadOnly);
    VertexEdit->setPlainText(VertexFile.readAll());
    VertexFile.close();

    QFile FragmentFile(FragmentFilePath);
    FragmentFile.open(QIODeviceBase::ReadOnly);
    FragmentEdit->setPlainText(FragmentFile.readAll());
    FragmentFile.close();
}

TextManager *TextManager::GetTextManager()
{
    if (Manager == nullptr)
    {
        Manager = new TextManager();
    }

    return Manager;
}
