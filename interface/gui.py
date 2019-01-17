from PyQt5.QtCore import*
from PyQt5 import*
from PyQt5.QtWidgets import*
from PyQt5.QtGui import*
from PyQt5.QtCore import (QCoreApplication, QObject, QRunnable, QThread,
                          QThreadPool, pyqtSignal)

import errno

from subprocess import Popen, PIPE
import subprocess

import socket
import sys
from threading import Thread
from time import sleep

hote = "192.168.7.2"
port = 15555



## Class ReadThread from QThread
## @brief 
##         thread for reading position on socket and send it to the guy
##        when a position is recieved, a pyqtSignal(str) is emmited
##        if form of :  <p:x.xx,y.yy> or <a:q1.q1q1,q5.q5q5>
## 



class ReadThread(QThread):
    
    sig = pyqtSignal(str) ##@attribute signal trigerd when a position is recieved


    ## __init__
    ## @brief
    ##        init the thread and open the socket to connect the beagle bone
    def __init__(self):
        QtCore.QThread.__init__(self) 
        self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._connected = 0;

    ## connect
    ## @biref try to connect to the server if it fail, do nothing
    def connect(self):
        print("start socket on " + hote + " : " + str(port))
        self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self._socket.connect((hote, port))
        except :
            sleep(0.1)
            print("not connected")
        else:  
            print("connected")
            self._connected = 1;

    ## close
    ##  @brief  close the conection to the server
    def close(self):
        self._socket.close()
        self._connected = 0;


    ## run
    ## @brief
    ##        launch in the thread, read the socket 
    ##        triger the -sig signal with read message
    def run(self):
        while(1):
            sleep(0.01)
            if self._connected ==1:
                pos=self._socket.recv(255)
                if(len(pos)!=0):
                    #print("recv : " + pos)
                    self.sig.emit(pos)

    ## send
    ## @brief
    ##        send a message to the beagle bone through the the socket
    def send(self, msg):
        if self._connected ==1:
            self._socket.send(msg)
            print("sent : " + msg)
        else:
            print("cant send " + msg + "controller not connected")


## Class Client form QMainWindow
## @brief
##        qt window with our qui  

class Client(QMainWindow,):


    ## showpos
    ## @brief
    ##             read a string with position and show it on the gui
    ##            write on x_actu, y_actu, q1 and q5
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
    ##        init the gui and add all the button and text space
    def init(self):
        QMainWindow.__init__(self)
        self.setWindowTitle("projet implementation v1.0")
        self.resize(400,400)

        self._init_bt=QPushButton("init", self)
        self._init_bt.clicked.connect(self.init_pushed)

        self._send_bt=QPushButton("send", self)
        self._send_bt.clicked.connect(self.send_pushed)
        self._send_bt.move(200,120)

        self._run_df_bt=QPushButton("run dist file", self)
        self._run_df_bt.clicked.connect(self.run_pushed)
        self._run_df_bt.move(100,330)

        self._run_lf_bt=QPushButton("run local file", self)
        self._run_lf_bt.clicked.connect(self.run_local_pushed)
        self._run_lf_bt.move(100,360)

        self._run_c_bt=QPushButton("run controller", self)
        self._run_c_bt.clicked.connect(self.launch_pushed)
        self._run_c_bt.move(100,0)

        self._kill_bt=QPushButton("kill controller", self)
        self._kill_bt.clicked.connect(self.kill_pushed)
        self._kill_bt.move(300,30)

        self._conn_bt=QPushButton("connect", self)
        self._conn_bt.clicked.connect(self.connect_pushed)
        self._conn_bt.move(200,0)

        self._end_bt=QPushButton("stop", self)
        self._end_bt.clicked.connect(self.end_pushed)
        self._end_bt.move(300,0)

        self._org_bt=QPushButton("org", self)
        self._org_bt.clicked.connect(self.org_pushed)
        self._org_bt.move(0,60)

        self._x = QTextEdit(self)
        self._x.setPlaceholderText("x")
        self._x.move(0,120)

        self._y=QTextEdit (self )
        self._y.setPlaceholderText("y")
        self._y.move(100,120)

        self._x_actu = QTextEdit(self)
        self._x_actu.setOverwriteMode(True)
        self._x_actu.move(100,180)

        self._y_actu = QTextEdit(self)
        self._y_actu.setOverwriteMode(True)
        self._y_actu.move(100,210)

        self._q1 = QTextEdit(self)
        self._q1.setOverwriteMode(True)
        self._q1.move(100,240)

        self._q5=QTextEdit (self )
        self._q5.setOverwriteMode(True)
        self._q5.move(100,270)


        self._x_actu_ = QTextEdit(self)
        self._x_actu_.setOverwriteMode(True)
        self._x_actu_.move(0,180)
        self._x_actu_.setText("x")

        self._y_actu_ = QTextEdit(self)
        self._y_actu_.setOverwriteMode(True)
        self._y_actu_.move(0,210)
        self._y_actu_.setText("y")

        self._q1_ = QTextEdit(self)
        self._q1_.setOverwriteMode(True)
        self._q1_.move(0,240)
        self._q1_.setText("q1")

        self._q5_=QTextEdit (self )
        self._q5_.setOverwriteMode(True)
        self._q5_.move(0,270)
        self._q5_.setText("q5")

        self._path=QTextEdit (self )
        self._path.setText("data.txt")
        self._path.move(0,330)

        self._local_path=QTextEdit (self )
        self._local_path.setPlaceholderText("filename")
        self._local_path.move(0,360)

        self._readThread = ReadThread()
        self._readThread.sig.connect( self.showPos )
        self._readThread.start()

    ## init_pushed
    ## @brief
    ##       trigered when the kill init is pushed
    ##       run trough ssh in the beagle bone "sudo sh /var/lib/cloud9/start.sh"
    ##       it initialise the beagle bone pwm , eqep and gpio
    def init_pushed(self):
        ps = subprocess.Popen(("ssh -tt debian@"+hote+" sudo sh /var/lib/cloud9/start.sh"),stdin=subprocess.PIPE, stdout=subprocess.PIPE, shell=True)
        output = ps.communicate()[0]
        print(output)

    ## connect_pushed
    ## @brief
    ##       trigered when the connect button is pushed
    ##       said to the _readThread to connect to the server
    def connect_pushed(self):
        self._readThread.connect();

    ## launch_pushed
    ## @brief
    ##        trigered when the run controller button is pushed
    ##        send a command trough ssh : " sudo ./../../var/lib/cloud9/controller/Main"

    def launch_pushed(self):
        ps = subprocess.Popen(("ssh -tt debian@"+hote+" sudo ./../../var/lib/cloud9/controller/Main"),stdin=subprocess.PIPE, stdout=subprocess.PIPE, shell=True)
        #output = ps.communicate()[0]
        #print(output)

    ## send_pushed
    ## @brief
    ##        trigered when the send button is pushed
    ##        send a message to the _readThread
    ##        <s:x.xx,y.yy>

    def send_pushed(self):
        try:
            x = float(self._x.toPlainText())
            y = float(self._y.toPlainText())
        except:
            print("can't read points, use only float with a point")
        else:
            msg = "s:" + str(x) + "," + str(y)
            self._readThread.send(msg)

    ## run_pushed
    ## @brief
    ##        trigered when the run dist file button is pushed
    ##        send a message to the _readThread
    ##        <r:path_file>
    def run_pushed(self): 
        self._readThread.send("r:"+"/var/lib/cloud9/controller/"+self._path.toPlainText())

    ## kill_pushed
    ## @brief
    ##       trigered when the kill button is pushed
    ##       run trough ssh in the beagle bone "sudo pkill Main" 3 times
    def kill_pushed(self): 
        ps = subprocess.Popen(("ssh -tt debian@"+hote+" sudo pkill Main"),stdin=subprocess.PIPE, stdout=subprocess.PIPE, shell=True)
        ps = subprocess.Popen(("ssh -tt debian@"+hote+" sudo pkill Main"),stdin=subprocess.PIPE, stdout=subprocess.PIPE, shell=True)
        ps = subprocess.Popen(("ssh -tt debian@"+hote+" sudo pkill Main"),stdin=subprocess.PIPE, stdout=subprocess.PIPE, shell=True)


    ## org_pushed
    ## @brief
    ##        trigered when the org button is pushed
    ##        send a message to the _readThread
    ##        <i>
    def org_pushed(self):
        self._readThread.send("i")

    ## end_pushed
    ## @brief
    ##        trigered when the stop button is pushed
    ##        send a message to the _readThread
    ##        <e>
    def end_pushed(self):
        self._readThread.send("e")
        self._readThread.close()

    ## run_local_pushed
    ## @brief
    ##        trigered when the run local file button is pushed
    ##        read a file in the filename field in form of x.xx,y,yy\n
    ##                                                     x.xx,y,yy\n*
    ##                                                     ...
    ##        send messages to the _readThread
    ##        <s:x.xx,y.yy>
    def run_local_pushed(self):
        file = open( self._local_path.toPlainText() , 'r' )
        for line in file:
            self._readThread.send("s:"+line)



## main
## @brief
##        launch the gui
def main():
    
    app = QApplication([])
    
    
    client = Client()
    client.init()
    client.show()
    

    app.exec_()

    
if __name__ =="__main__":  
    main()