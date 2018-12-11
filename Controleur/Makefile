CC=g++
CFLAGS=-WALL

DEPS = Codeur.h Controleur.h Driver.h Pid.h

TARGET = Controleur

OBJ = Codeur.o Controleur.o Driver.o Pid.o


all : $(TARGET)


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $
	
	
clean:
	rm -rf $(TARGET) *.o