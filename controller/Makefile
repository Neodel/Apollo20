CC=g++
CFLAGS=-WALL

DEPS = Encoder.h Controller.h Driver.h Pid.h

TARGET = Main

OBJ = Encoder.o Controller.o Driver.o Pid.o Main.o geom.o  ServerGUI.o


all : $(TARGET) doc


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $
	
	
clean:
	rm -rf $(TARGET) *.o



