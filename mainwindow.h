#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QPlainTextEdit;
class QListWidget;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void GetEditors(QPlainTextEdit*& Vertex, QPlainTextEdit*& Fragment) const;
    void GetFPS(QLabel*& FPSLabel);

public slots:
    void AddError(std::string Error);
    void ClearErrorList();

private slots:
    void Export();
    void Import();

    void on_txtVertex_textChanged();

    void on_txtFragment_textChanged();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
