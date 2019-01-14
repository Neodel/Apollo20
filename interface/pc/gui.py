from PyQt5.QtCore import*
from PyQt5 import*
from PyQt5.QtWidgets import*
from PyQt5.QtGui import*
from PyQt5.QtCore import (QCoreApplication, QObject, QRunnable, QThread,
                          QThreadPool, pyqtSignal)

import socket

import sys
from threading import Thread
from time import sleep


class ReadThread(QThread):
    
    sig = pyqtSignal(str)

    def __init__(self):
        QtCore.QThread.__init__(self)

    def run(self):
        count = 0
        while count < 5:
            sleep(1)
            print("A Increasing")
            count += 1
            success = count
            self.sig.emit("1.0,2.0")


class Client(QMainWindow,):



    def showPos(self,pos):
    	print("sig recieved " + pos)
        self.y_actu.setText(pos.split(',')[0])
        self.x_actu.setText(pos.split(',')[1])

    def init(self):
        #window
        QMainWindow.__init__(self)
        self.setWindowTitle("")
        self.resize(400,600)

        self.init_bt=QPushButton("init", self)
        self.init_bt.clicked.connect(self.init_pushed)

        self.send_bt=QPushButton("send", self)
        self.send_bt.clicked.connect(self.send_pushed)
        self.send_bt.move(0,30)

        self.x = QTextEdit(self)
        self.x.setPlaceholderText("x")
        self.x.move(0,60)

        self.y=QTextEdit (self )
        self.y.setPlaceholderText("y")
        self.y.move(0,90)

        self.x_actu = QTextEdit(self)
        self.x_actu.setOverwriteMode(True)
        self.x_actu.move(0,120)

        self.y_actu = QTextEdit(self)
        self.y_actu.setOverwriteMode(True)
        self.y_actu.move(0,150)

        self.readThread = ReadThread()
        self.readThread.sig.connect( self.showPos )
        self.readThread.start()


    def send_pushed(self):
    	x = float(self.x.toPlainText())
    	y = float(self.y.toPlainText())
    	print("send: " + x + " " + y)

    def launch(self):
    	pass

    def init_pushed(self):
    	pass # do server stuff






def main():
    
    app = QApplication([])
    
    
    client = Client()
    client.init()
    client.show()
    

    app.exec_()

    
if __name__ =="__main__":  
    main()