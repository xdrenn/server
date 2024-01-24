#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _server = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(_server == nullptr) {
       auto port = ui->spinPort->value();
       _server = new TCPServer(port);
       connect(_server, &TCPServer::newClientConnected, this, &MainWindow::on_newClient_connected);
    }
    auto state = (_server->isStarted()) ? "1" : "0";
    ui->status->setProperty("state", state);
    style()->polish(ui->status);
}

void MainWindow::on_newClient_connected()
{
    ui->console->addItem("New client connected");
}

