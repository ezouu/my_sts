CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS = -shared

TARGET = libsts.so
SRCS = sts_lib.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET) 