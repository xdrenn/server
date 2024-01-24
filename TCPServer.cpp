#include "TCPServer.h"

TCPServer::TCPServer(int port, QObject *parent) : QObject(parent)
{
  _server = new QTcpServer(this);
  connect(_server, &QTcpServer::newConnection, this, &TCPServer::on_client_connecting);
  _isStarted =_server->listen(QHostAddress::Any, port);
  if(!_isStarted){
          qDebug() << "Can't to start the server";
  } else {
          qDebug() << "Server started...";
  }
}

void TCPServer::on_client_connecting()
{
    qDebug() << "Client connected to server";
    auto socket = _server->nextPendingConnection();
    emit newClientConnected();
}

bool TCPServer::isStarted() const
{
    return _isStarted;
}


