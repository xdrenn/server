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
    connect(socket, &QTcpSocket::readyRead, this, &TCPServer::clientDataReady);
        connect(socket, &QTcpSocket::disconnected, this, &TCPServer::clientDisconnected);
    _socketsList.append(socket);
    emit newClientConnected();
}

void TCPServer::clientDataReady()
{
    auto socket = qobject_cast<QTcpSocket *>(sender());
    auto data = socket->readAll();
    emit dataReceived(QString(data));
}

void TCPServer::disconnected()
{
    emit clientDisconnected();
}

bool TCPServer::isStarted() const
{
    return _isStarted;
}

void TCPServer::sendToAll(QString message)
{
    foreach (auto socket, _socketsList){
        socket->write(message.toUtf8());
    }
}


