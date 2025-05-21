# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g
INCLUDES = -Iinc

# Folders
SRC = src
OBJDIR = build

# Source and object files
SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Output
TARGET = p2p_app

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) -lpthread

# Compile source files into object files
$(OBJDIR)/%.o: $(SRC)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJDIR) *.o $(TARGET)

.PHONY: all clean
