.PHONY: all clean

TARGET=test

SOURCES=$(wildcard *.c)

HEADERS=$(wildcard *.h)

OBJS=$(patsubst %.c,%.o,$(SOURCES))

LIBS=-lc

all: $(TARGET)
	@echo "build successfully. $(TARGET) has been generated."


$(TARGET): $(OBJS)
	gcc -O0 -o $(TARGET) $(OBJS) $(LIBS)

%.o:%.c
	gcc -c -g -Wint-to-pointer-cast -std=c99 -o $@ $<


clean:
	-@rm -rf $(OBJS) $(TARGET)
