note on the GUI, it use ssk key wich should be seted before using it:

on client creat a ssh key : 
$ssh-keygen

copy it on the beagle bone : 
$ssh-copy-id debian@192.168.7.2

tape your pasword, it should be ok.


gui description:

init button : run the start.sh which initialize the eqep, pwm and gpoi on the beagle bone (though ssh)

run controller : run the Main controller (though ssh)

connect : connect the gui to the beagle bone with a socket

stop : end the Main (trough socket)

kill controller : kill the process of Main (don't end the pwm and gpio) (though ssh)

org : set the origin of the robot (x = 0.0125 , y = 0.110) (trough socket)

send : send the x and y in x and y area before it tho the robot (trough socket)

x area : x to send to the robot (with send button)

y area : y to send to the robot (with send button)

x : actual x location of the robot

y : actual y location of the robot

q1 : angle of the q1 joint of the robot

q5 : angle of the q5 joint of the robot

data.txt : filename of the file run by run dist file (on the beagle bone)
filename area : filename of the local file run by the run local file button (still work to do on that)

run dist file : run the file on the field before it on the beagle bone 

run local file : run the file on the field before it on the computer 


dependencies
PyQt5
errno
subprocess
socket
sys
threading
time