import sys
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtNetwork import *

class Server(QTcpServer):

    def __init__(self):
        super().__init__()
        if self.listen(QHostAddress.AnyIPv4, 55555):
            print("start")
        else:
            print("error")
            self.close()
        self.blockSize = 0
        self.socket = QTcpSocket()


    def incomingConnection(self, socketDescriptor):
        self.socket = QTcpSocket()
        self.socket.setSocketDescriptor(socketDescriptor)
        self.socket.readyRead.connect(self.slotReadyRead)
        self.socket.disconnected.connect(self.socket.deleteLater)
        print("connect ", self.socket.peerAddress())


    def slotReadyRead(self):
        socket = self.sender()
        instr = QDataStream(socket)
        instr.setVersion(QDataStream.Qt_5_3)
        if self.blockSize == 0:
            if socket.bytesAvailable() < 2:
                return
            self.blockSize = instr.readUInt16()
        if socket.bytesAvailable() < self.blockSize:
            return
        self.parseMes(str(instr.readBytes(), encoding='utf-8'))
        self.blockSize = 0


    def sendToManager(self, text):
        block = QByteArray()
        out = QDataStream(block, QIODevice.ReadWrite)
        out.setVersion(QDataStream.Qt_5_0)
        out.writeUInt16(0)
        out.writeString(text.encode("utf-8"))
        out.device().seek(0)
        out.writeUInt16(block.size() - 2)
        self.socket.write(block)


    def parseMes(self, text):
        print(text)
        self.sendToManager("Agent received message")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    server = Server()
    sys.exit(app.exec())
