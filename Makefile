OUT = cmandel
LDFLAGS = -lpng
SRC_DIR := src
BUILD_DIR := build
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))


ifeq ($(shell uname -s), Darwin)
BREW_PREFIX := $(shell brew --prefix)
LIBOMP_PREFIX := $(shell brew --prefix libomp)

CFLAGS += -I$(BREW_PREFIX)/include
CFLAGS += -I$(LIBOMP_PREFIX)/include
CFLAGS += -Xpreprocessor -Wno-error=unused-command-line-argument

LDFLAGS += -L$(BREW_PREFIX)/lib
LDFLAGS += -L$(LIBOMP_PREFIX)/lib
LDFLAGS += -lomp
endif

all: all_compile

all_compile: CFLAGS += -O3
all_compile: compile

debug: clean debug_compile

debug_compile: CFLAGS += -g -O0
debug_compile: compile

compile: build_dir $(OUT)

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
