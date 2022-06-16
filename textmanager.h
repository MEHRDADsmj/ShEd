#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <QObject>

class QPlainTextEdit;

class TextManager : public QObject
{
    Q_OBJECT
private:
    explicit TextManager(QObject *parent = nullptr, QPlainTextEdit* VertexEdit = nullptr,
                         QPlainTextEdit* FragmentEdit = nullptr);
public:
    virtual ~TextManager();
    void GetTextFromEditors(std::string& VertexSrc, std::string& FragSrc);
    void ExportFiles();
    void ImportFiles();

    QPlainTextEdit* VertexEdit;
    QPlainTextEdit* FragmentEdit;

    static TextManager* GetTextManager();

private:
    static TextManager* Manager;

signals:

};

#endif // TEXTMANAGER_H
