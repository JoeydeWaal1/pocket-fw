CXX =  clang
LD  =  clang

CCFLAGS  = -std=c2x
CCFLAGS += -Wall
# CCFLAGS += -o3

# LINKFLAGS  =

CSRC = $(wildcard src/*.c)
OBJS = $(CSRC:.c=.o)

BIN_DIR = bin
BIN     = $(BIN_DIR)/main

all: main

main: $(OBJS)
	$(LD) -o $(BIN_DIR)/$@ $(LINKFLAGS) src/$@.o

%.o: %.c
	$(CXX) $(CCFLAGS) -c -o $@ $^

clean:
	rm -f */*.o
	rm -f *.o
	rm -f $(BIN_DIR)/*

r:
	$(BIN)
run:
	$(BIN)
