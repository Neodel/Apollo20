CC=g++
CFLAGS=-WALL

DEPS = Codeur.h Controleur.h Driver.h Pid.h

TARGET = Main

OBJ = Codeur.o Controleur.o Driver.o Pid.o Main.o


all : $(TARGET)


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $
	
	
clean:
	rm -rf $(TARGET) *.o