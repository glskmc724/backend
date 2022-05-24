CC = gcc

LDFLAGS = -lpthread
TARGET = main
OBJDIR = obj
SRCDIR = src

SRCS = $(notdir $(wildcard $(SRCDIR)/*.c))
OBJS = $(SRCS:.c=.o)

OBJECTS = $(patsubst %.o, $(OBJDIR)/%.o,$(OBJS))

all: main

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -rf $(OBJECTS) $(TARGET)