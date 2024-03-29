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

void MainWindow::newClientConnected()
{
    ui->console->addItem("New client connected");
}


void MainWindow::on_btnStart_clicked()
{
    if(_server == nullptr) {
       auto port = ui->spinPort->value();
       _server = new TCPServer(port);
       connect(_server, &TCPServer::newClientConnected, this, &MainWindow::newClientConnected);
       connect(_server, &TCPServer::dataReceived, this, &MainWindow::dataReceived);
       connect(_server, &TCPServer::clientDisconnected, this, &MainWindow::clientDisconnected);
    }
    auto state = (_server->isStarted()) ? "1" : "0";
    ui->status->setProperty("state", state);
    style()->polish(ui->status);
}

void MainWindow::clientDisconnected()
{
    ui->console->addItem("Client Disconnected");
}

void MainWindow::dataReceived(QString message)
{
    ui->console->addItem(message);
}


void MainWindow::on_btnSend_clicked()
{
    auto message = ui->message->text().trimmed();
    _server->sendToAll(message);
}

