# Implementation Project - Apollo20

This project aims to control a 5R-plan drawer robot through a GUI. To do so, we used a beaglebone black and 2 controlled joint, which drive the whole system.


Authors : Loïc Kerboriou, Justin Bezieau, Nicolas Cheron, Johann Huber

Release : January 2019

Polytech Sorbonne Engineering School - Major in Robotics

Location : Paris, France

Teacher : Ludovic Saint-Bauzel


## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

Qt library (for the GUI)

```
https://wiki.qt.io/Install_Qt_5_on_Ubuntu
```
Python

```
$ sudo apt-get install python3.6
```


### Installing & initializing 

Connect components as described in the Connectic part of the user documentation (p.7).

Launch the main python script with the following command on a new shell :

```
$ python {nom du script et son path}
```

The GUI will then appears on your workstation. 

Put manually the robot effector on the origin marker, and clic on the init button

The system is now initialized, you can start drawing with Apollo 20.


## Running the test

While making sure the system has been initialized, run the path following by hitting the init button.


