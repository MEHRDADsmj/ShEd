#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "textmanager.h"
#include "renderer.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->widgetRenderer, &Renderer::AddError, this, &MainWindow::AddError);
    connect(ui->widgetRenderer, &Renderer::ClearErrorList, this, &MainWindow::ClearErrorList);
    connect(ui->actionExport, &QAction::triggered, this, &MainWindow::Export);
    connect(ui->actionImport, &QAction::triggered, this, &MainWindow::Import);
    ui->widgetRenderer->SetFPSLabel(ui->lblFPS);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GetEditors(QPlainTextEdit *&Vertex, QPlainTextEdit *&Fragment) const
{
    Vertex = ui->txtVertex;
    Fragment = ui->txtFragment;
}

void MainWindow::GetFPS(QLabel *&FPSLabel)
{
    FPSLabel = ui->lblFPS;
}

void MainWindow::AddError(std::string Error)
{
    ui->listErrorList->addItem(QString::fromStdString(Error));
}

void MainWindow::ClearErrorList()
{
    ui->listErrorList->clear();
}

void MainWindow::Export()
{
    TextManager* tm = TextManager::GetTextManager();
    if(tm)
    {
        tm->ExportFiles();
    }
}

void MainWindow::Import()
{
    TextManager* tm = TextManager::GetTextManager();
    if(tm)
    {
        tm->ImportFiles();
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

