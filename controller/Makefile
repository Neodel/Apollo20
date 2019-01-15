CC=g++
CFLAGS=-WALL

DEPS = Encoder.h Controller.h Driver.h Pid.h

TARGET = Main

OBJ = Encoder.o Controller.o Driver.o Pid.o Main.o geom_inv.o  geom_direct.o ServerGUI.o


all : $(TARGET)


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $
	
	
clean:
	rm -rf $(TARGET) *.o
