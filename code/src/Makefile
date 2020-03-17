IDIR =../include
CC=clang
CFLAGS=-I$(IDIR) -lrt

ODIR=../obj
LDIR =../lib

_DEPS = config.h daemon.h file_manager.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = mattdaemon.o daemon.o file_manager.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mattdaemon: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
