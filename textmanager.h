#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <QObject>

class QTextEdit;

class TextManager : public QObject
{
    Q_OBJECT
public:
    explicit TextManager(QObject *parent = nullptr, QTextEdit* VertexEdit = nullptr,
                         QTextEdit* FragmentEdit = nullptr);

    QTextEdit* VertexEdit;
    QTextEdit* FragmentEdit;

signals:

};

#endif // TEXTMANAGER_H
