OUT = cmandel
CFLAGS = -O3
LDFLAGS = -lgd -lz -lm

SRC_DIR := src
BUILD_DIR := build
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))


ifeq ($(shell uname -s), Darwin)
BREW_PREFIX := $(shell brew --prefix)
LIBOMP_PREFIX := $(shell brew --prefix libomp)

CFLAGS += -I$(BREW_PREFIX)/include
CFLAGS += -I$(LIBOMP_PREFIX)/include
CFLAGS += -Xpreprocessor -fopenmp

LDFLAGS += -L$(BREW_PREFIX)/lib
LDFLAGS += -L$(LIBOMP_PREFIX)/lib
LDFLAGS += -lomp
else
CFLAGS += -fopenmp 
LDFLAGS += -fopenmp
endif
.PHONY: all bld_dir clean run

all : build_dir $(OUT)

$(OUT): $(OBJS)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS)

build_dir:
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	gcc $(CFLAGS) -c $< -o $@

run: all
	./$(OUT)

clean:
	rm -rf $(BUILD_DIR) $(OUT)
