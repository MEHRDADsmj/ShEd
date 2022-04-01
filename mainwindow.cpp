#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "textmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GetEditors(QTextEdit *&Vertex, QTextEdit *&Fragment)
{
    Vertex = ui->txtVertex;
    Fragment = ui->txtFragment;
}

void MainWindow::on_btnExport_clicked()
{
    TextManager* tm = TextManager::GetTextManager();
    if(tm)
    {
        tm->ExportFiles();
    }
}


void MainWindow::on_txtVertex_textChanged()
{
    ui->widgetRenderer->MarkShaderDirty();
}


void MainWindow::on_txtFragment_textChanged()
{
    ui->widgetRenderer->MarkShaderDirty();
}

