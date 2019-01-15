from PyQt5.QtCore import*
from PyQt5 import*
from PyQt5.QtWidgets import*
from PyQt5.QtGui import*
from PyQt5.QtCore import (QCoreApplication, QObject, QRunnable, QThread,
                          QThreadPool, pyqtSignal)

import socket
#gwew9088
import sys
from threading import Thread
from time import sleep

hote = "192.168.7.2"
port = 15555



class ReadThread(QThread):
    
    sig = pyqtSignal(str)

    def __init__(self):
        QtCore.QThread.__init__(self)

        print("start socket on " + hote + " : " + str(port))
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((hote, port))
        print("connected")

    def run(self):
    	while(1):
    	    pos=self.socket.recv(255)
    	    if(len(pos)!=0):
    	        print("recv : " + pos)
                self.sig.emit(pos)

    def send(self, msg):
        self.socket.send(msg)




class Client(QMainWindow,):



    def showPos(self,pos):
    	print("sig recieved " + pos)
        self.x_actu.setText(pos.split(',')[0])
        self.y_actu.setText(pos.split(',')[1])

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
    	msg = "s:" + str(x) + "," + str(y)
    	print("send: " + msg)

    	self.readThread.send(msg)

    def launch(self):
    	pass

    def init_pushed(self):
    	print("send: i") 
    	self.readThread.send("i")






def main():
    
    app = QApplication([])
    
    
    client = Client()
    client.init()
    client.show()
    

    app.exec_()

    
if __name__ =="__main__":  
    main()