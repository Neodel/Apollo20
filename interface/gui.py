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

hote = "192.168.7.2"
port = 15555



## Class ReadThread from QThread
## @brief 
## 		thread for reading position on socket and send it to the guy
##		when a position is recieved, a pyqtSignal(str) is emmited
##		if form of :  <p:x.xx,y.yy> or <a:q1.q1q1,q5.q5q5>
## 



class ReadThread(QThread):
    
    sig = pyqtSignal(str) ##@attribute signal trigerd when a position is recieved


    ## __init__
    ## @brief
    ##		init the thread and open the socket to connect the beagle bone
    def __init__(self):
        QtCore.QThread.__init__(self)

        print("start socket on " + hote + " : " + str(port))
        self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._socket.connect((hote, port))
        print("connected")

    ## run
    ## @brief
    ##		launch in the thread, read the socket 
    ##		triger the -sig signal with read message
    def run(self):
    	while(1):
    	    sleep(0.01)
    	    pos=self._socket.recv(255)
    	    if(len(pos)!=0):
    	        #print("recv : " + pos)
                self.sig.emit(pos)

    ## send
    ## @brief
    ##		send a message to the beagle bone through the the socket
    def send(self, msg):
        self._socket.send(msg)


## Class Client form QMainWindow
## @brief
##		qt window with our qui  

class Client(QMainWindow,):


	## showpos
	## @brief
	## 			read a string with position and show it on the gui
	##			write on x_actu, y_actu, q1 and q5
	## @param (str) position in form of <p:x.xx,y.yy> or <a:q1.q1q1,q5.q5q5>
    def showPos(self,pos):
    	#print("sig recieved " + pos)
    	if (pos[0] == 'a'):
    	    pos = pos.split(':')[1]
    	    pos = pos.split('p')[0]
    	    pos = pos.split('a')[0]
            self._q1.setText(pos.split(',')[0])
            self._q5.setText(pos.split(',')[1])
        if (pos[0] == 'p'):
            pos = pos.split(':')[1]
    	    pos = pos.split('p')[0]
    	    pos = pos.split('a')[0]
            self._x_actu.setText(pos.split(',')[0])
            self._y_actu.setText(pos.split(',')[1])

    ## init
    ## @brief
    ##		init the gui and add all the button and text space
    def init(self):
        QMainWindow.__init__(self)
        self.setWindowTitle("")
        self.resize(400,400)

        self._init_bt=QPushButton("init", self)
        self._init_bt.clicked.connect(self.init_pushed)

        self._send_bt=QPushButton("send", self)
        self._send_bt.clicked.connect(self.send_pushed)
        self._send_bt.move(200,60)

        self._run_bt=QPushButton("run file", self)
        self._run_bt.clicked.connect(self.run_pushed)
        self._run_bt.move(100,300)

        self._end_bt=QPushButton("stop", self)
        self._end_bt.clicked.connect(self.end_pushed)
        self._end_bt.move(100,0)

        self._x = QTextEdit(self)
        self._x.setPlaceholderText("x")
        self._x.move(0,60)

        self._y=QTextEdit (self )
        self._y.setPlaceholderText("y")
        self._y.move(100,60)

        self._x_actu = QTextEdit(self)
        self._x_actu.setOverwriteMode(True)
        self._x_actu.move(100,120)

        self._y_actu = QTextEdit(self)
        self._y_actu.setOverwriteMode(True)
        self._y_actu.move(100,150)

        self._q1 = QTextEdit(self)
        self._q1.setOverwriteMode(True)
        self._q1.move(100,180)

        self._q5=QTextEdit (self )
        self._q5.setOverwriteMode(True)
        self._q5.move(100,210)


        self._x_actu_ = QTextEdit(self)
        self._x_actu_.setOverwriteMode(True)
        self._x_actu_.move(0,120)
        self._x_actu_.setText("x")

        self._y_actu_ = QTextEdit(self)
        self._y_actu_.setOverwriteMode(True)
        self._y_actu_.move(0,150)
        self._y_actu_.setText("y")

        self._q1_ = QTextEdit(self)
        self._q1_.setOverwriteMode(True)
        self._q1_.move(0,180)
        self._q1_.setText("q1")

        self._q5_=QTextEdit (self )
        self._q5_.setOverwriteMode(True)
        self._q5_.move(0,210)
        self._q5_.setText("q5")

        self._path=QTextEdit (self )
        self._path.setText("data.txt")
        self._path.move(0,300)

        self._readThread = ReadThread()
        self._readThread.sig.connect( self.showPos )
        self._readThread.start()

    ## send_pushed
    ## @brief
    ##		trigered when the send button is pushed
    ##		send a message to the _readThread
    ##		<s:x.xx,y.yy>

    def send_pushed(self):
    	x = float(self._x.toPlainText())
    	y = float(self._y.toPlainText())
    	msg = "s:" + str(x) + "," + str(y)
    	print("send: " + msg)

    	self._readThread.send(msg)

    ## run_pushed
    ## @brief
    ##		trigered when the run file button is pushed
    ##		send a message to the _readThread
    ##		<r:path_file>
    def run_pushed(self): 
    	print("send: r" + self._path.toPlainText())
    	self._readThread.send("r:"+self._path.toPlainText())

    ## inti_pushed
    ## @brief
    ##		trigered when the init button is pushed
    ##		send a message to the _readThread
    ##		<i>
    def init_pushed(self):
    	print("send: i") 
    	self._readThread.send("i")

    ## end_pushed
    ## @brief
    ##		trigered when the stop button is pushed
    ##		send a message to the _readThread
    ##		<e>
    def end_pushed(self):
    	print("send: e") 
    	self._readThread.send("e")



## main
## @brief
##		launch the gui
def main():
    
    app = QApplication([])
    
    
    client = Client()
    client.init()
    client.show()
    

    app.exec_()

    
if __name__ =="__main__":  
    main()