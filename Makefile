OUT = cmandel
CFLAGS = -fopenmp
LDFLAGS = -lpng
SRC_DIR := src
BUILD_DIR := build
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

ifeq ($(shell uname -s), Darwin)
LIBPNG_PREFIX := $(shell brew --prefix libpng)
LIBOMP_PREFIX := $(shell brew --prefix libomp)
LLVM_PREFIX := $(shell brew --prefix llvm)

CC = $(LLVM_PREFIX)/bin/clang

CFLAGS += -I$(LLVM_PREFIX)/include
CFLAGS += -I$(LIBOMP_PREFIX)/include
CFLAGS += -I$(LIBPNG_PREFIX)/include
CFLAGS += -Xpreprocessor -Wno-error=unused-command-line-argument

LDFLAGS += -L$(LLVM_PREFIX)/lib
LDFLAGS += -L$(LIBPNG_PREFIX)/lib
LDFLAGS += -L$(LIBOMP_PREFIX)/lib
else
CC = gcc
endif

all: all_compile

all_compile: CFLAGS += -O3
all_compile: compile

debug: clean debug_compile

debug_compile: CFLAGS += -g -O0
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
