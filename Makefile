CXX =  clang
LD  =  clang

CCFLAGS  = -std=c2x
CCFLAGS += -Wall
# CCFLAGS += -o3
#
BIN_DIR = bin
BIN     = $(BIN_DIR)/main

LINKFLAGS  = $(BIN_DIR)/src/if_card.o
LINKFLAGS += $(BIN_DIR)/src/socket.o

CSRC = $(wildcard src/*.c)
OBJS = $(CSRC:.c=.o)



all: main

main: $(OBJS)
	$(LD) -o $(BIN_DIR)/$@ $(LINKFLAGS) $(BIN_DIR)/src/$@.o

%.o: %.c
	$(CXX) $(CCFLAGS) -c -o $(BIN_DIR)/$@ $^

clean:
	rm -f */*.o
	rm -f *.o
	rm -f $(BIN)

r:
	sudo $(BIN)
run:
	sudo $(BIN)
