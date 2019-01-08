cc = g++
CFLAGS = -Wall -g
SRCS = run_sim.cpp geom_inv.cpp geom_direct.cpp
PROG = run_sim

$(PROG): $(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS)

clean :
	rm -f $(PROG) *.o