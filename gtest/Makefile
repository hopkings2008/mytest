.PHONY: all clean

TARGET=test

SOURCES=$(wildcard *.cc)

HEADERS=$(wildcard *.h)

OBJS=$(patsubst %.c,%.o,$(SOURCES))

LIBS=-lstdc++ -lc

all: $(TARGET)
	@echo "build successfully. $(TARGET) has been generated."


$(TARGET): $(OBJS)
	gcc -g -O0 -o $(TARGET) $(OBJS) $(LIBS)

%.o:%.cc
	gcc -c -Wint-to-pointer-cast -o $@ $<


clean:
	-@rm -rf $(OBJS) $(TARGET)
