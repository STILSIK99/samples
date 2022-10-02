from PyQt5 import QtWidgets
from PyQt5.QtNetwork import *
from PyQt5.QtCore import *
from mainform import Ui_MainWindow  # импорт нашего сгенерированного файла
import sys
from client import Client


class Manager(QtWidgets.QMainWindow):
    sendMes = pyqtSignal(str, tuple)

    def __init__(self):
        super(Manager, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.agents = dict()
        self.client = Client()
        self.sendMes.connect(self.client.sendMessage)
        self.client.receiveMessage.connect(self.receiveRequest)
        self.client.disconnectAgent.connect(self.disconnectAgent)
        self.listAg = []

        self.ui.pushButton.clicked.connect(self.connect_agent)
        self.ui.pushButton_2.clicked.connect(self.pushButton_2)


    def disconnectAgent(self, pair):
        if pair in self.listAg:
            self.listAg.remove(pair)

    def receiveRequest(self, text):
        self.ui.textEdit.append(text)

    def connect_agent(self):
        ip = '127.0.0.1'
        port = 55555
        if not self.client.slotMakeConnection((ip, port)):
            QtWidgets.QMessageBox.about(self, "", "Ошибка подключения агента")
        else:
            QtWidgets.QMessageBox.about(self, "", "Агент подключен")
            self.listAg.append((ip, port))

    def pushButton_2(self):
        self.sendMes.emit(self.ui.lineEdit.text(), self.listAg[0])




if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    manager = Manager()
    manager.show()
    sys.exit(app.exec())