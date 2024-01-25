#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStyle>
#include "TCPServer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newClientConnected();
    void on_btnStart_clicked();
    void clientDisconnected();
    void dataReceived(QString message);
    void on_btnSend_clicked();

private:
    Ui::MainWindow *ui;
    TCPServer *_server;
};
#endif // MAINWINDOW_H
