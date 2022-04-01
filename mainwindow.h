#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTextEdit;
class QListWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void GetEditors(QTextEdit*& Vertex, QTextEdit*& Fragment) const;

public slots:
    void AddError(std::string Error);
    void ClearErrorList();

private slots:
    void Export();

    void on_txtVertex_textChanged();

    void on_txtFragment_textChanged();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
