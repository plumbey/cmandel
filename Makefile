OUT = cmandel
LDFLAGS = -lgd -lz -lm
SRC_DIR := src
BUILD_DIR := build
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

CC := gcc

ifeq ($(shell uname -s), Darwin)
BREW_PREFIX := $(shell brew --prefix)

CFLAGS += -I$(BREW_PREFIX)/include
CFLAGS += -Xpreprocessor

LDFLAGS += -L$(BREW_PREFIX)/lib

ifeq ($(shell uname -m), arm64)
CC := arch -x86_64 gcc
endif
endif

all: all_compile

all_compile: CFLAGS += -O3
all_compile: compile

debug: clean debug_compile

debug_compile: CFLAGS += -g
debug_compile: compile

compile: build_dir $(OUT)

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

build_dir:
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(OUT)


clean:
	rm -rf $(BUILD_DIR) $(OUT)
