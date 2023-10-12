CFLAGS = -Wno-implicit-function-declaration
SRC_DIR = src

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, %.o, $(SRCS))
EXECUTABLE = gh0st3d

all: $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJS) main.o
	gcc $(CFLAGS) $^ -o $@

%.o: $(SRC_DIR)/%.c
	gcc $(CFLAGS) -c $<

main.o: main.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o

