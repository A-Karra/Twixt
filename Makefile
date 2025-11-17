# Compiler
CC = gcc

# Compiler flags:
# -Wall and -Wextra enable all common warnings
# -std=c99 specifies the C99 standard (for loop initializations)
# -g adds debugging information
CFLAGS = -Wall -Wextra -std=c99 -g -D_DEFAULT_SOURCE

# Linker flags:
# -lm links the math library (for fabs() used in isLinkValid)
LDFLAGS = -lm

# The name of the final executable
TARGET = game

# Source files
SRCS = main.c

# Object files (derived from source files)
OBJS = $(SRCS:.c=.o)

# Header files
HDRS = header.h

# --- Rules ---

# Default rule: build the target executable
all: $(TARGET)

# Rule to link the final executable
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile a .c file into a .o file
# It depends on the .c file and any headers
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule to clean up built files
clean:
	rm -f $(TARGET) $(OBJS)

# Mark 'all' and 'clean' as phony, meaning they aren't actual files
.PHONY: all clean