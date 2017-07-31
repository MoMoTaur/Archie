LIB_NAME := libarchie.a

UNAME := $(shell uname)

SRC_DIR := src
INC_DIR := inc
OBJ_DIR := obj

CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -std=c11
LFLAGS := -I$(INC_DIR) -L$(LIB_DIR)

AR := ar
ARFLAGS := rcs

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Linux
ifeq ($(UNAME), Linux)
LFLAGS := $(LFLAGS)
endif

# Mac OSX
ifeq ($(UNAME), Darwin)
LFLAGS := $(LFLAGS)
endif

# Add more for more platforms

# Default build target
all: lib

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INC_DIR)

lib: $(OBJS) check_name
	$(AR) $(ARFLAGS) $(LIB_NAME) $(OBJS)

# Removes all generated files
clean:
	rm -rf $(OBJ_DIR)
	rm -f $(LIB_NAME)

# Errors out if LIB_NAME is unset
check_name:
ifndef LIB_NAME
	$(error LIB_NAME is unset)
endif

.PHONY: all lib clean check_name
