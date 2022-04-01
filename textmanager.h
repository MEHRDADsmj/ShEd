#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <QObject>

class QTextEdit;

class TextManager : public QObject
{
    Q_OBJECT
private:
    explicit TextManager(QObject *parent = nullptr, QTextEdit* VertexEdit = nullptr,
                         QTextEdit* FragmentEdit = nullptr);
public:
    virtual ~TextManager();
    void GetTextFromEditors(std::string& VertexSrc, std::string& FragSrc);
    void ExportFiles();


    QTextEdit* VertexEdit;
    QTextEdit* FragmentEdit;

    static TextManager* GetTextManager();

private:
    static TextManager* Manager;

signals:

};

#endif // TEXTMANAGER_H
