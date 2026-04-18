# This is the only thing vibecoded in this project.
# Makefiles are BS and I can't be bothered to learn them.
CC = gcc
FLAGS = -g -Wall -O2 -MMD -MP -D_GNU_SOURCE

SRC_DIR = src
BUILD_DIR = build
COMPILED_DIR = compiled
HEADERS_DIR = src/headers

SOURCES = \
	$(SRC_DIR)/main.c \
	$(wildcard $(SRC_DIR)/implementations/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

TARGET = $(COMPILED_DIR)/snekkie-flashcards.bin

LIB_OBJECTS = $(filter-out $(BUILD_DIR)/main.o,$(OBJECTS))

# --- Tests ---
TESTS_SRC_DIR = tests-src
TESTS_BUILD_DIR = tests-build
TESTS_COMPILED_DIR = tests-compiled

TESTS_SOURCES = $(wildcard $(TESTS_SRC_DIR)/*.c)
TESTS_OBJECTS = $(patsubst $(TESTS_SRC_DIR)/%.c,$(TESTS_BUILD_DIR)/%.o,$(TESTS_SOURCES))
TESTS_TARGETS = $(patsubst $(TESTS_SRC_DIR)/%.c,$(TESTS_COMPILED_DIR)/%.bin,$(TESTS_SOURCES))

# ==================================================
# 🧱 Build main program
# ==================================================

build: $(TARGET)

$(TARGET): $(OBJECTS) | $(COMPILED_DIR)
	$(CC) $(OBJECTS) -o $@

# Compile any src/*.c → build/*.o (handles subdirs automatically)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -I$(HEADERS_DIR) -c $< -o $@

$(COMPILED_DIR):
	mkdir -p $@

# ==================================================
# 🧪 Build tests
# ==================================================

build_tests: build $(TESTS_TARGETS)

# Link each test with implementation objects (no main.o)
$(TESTS_COMPILED_DIR)/%.bin: $(TESTS_BUILD_DIR)/%.o $(LIB_OBJECTS) | $(TESTS_COMPILED_DIR)
	$(CC) $^ -o $@

# Compile test sources
$(TESTS_BUILD_DIR)/%.o: $(TESTS_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -I$(HEADERS_DIR) -c $< -o $@

$(TESTS_BUILD_DIR):
	mkdir -p $@

$(TESTS_COMPILED_DIR):
	mkdir -p $@

# ==================================================
# 🧹 Cleanup
# ==================================================

clean:
	rm -rf $(BUILD_DIR) $(COMPILED_DIR) $(TESTS_BUILD_DIR) $(TESTS_COMPILED_DIR)

# ==================================================
# 📦 Auto dependency tracking
# ==================================================

-include $(OBJECTS:.o=.d)
-include $(TESTS_OBJECTS:.o=.d)

.PHONY: build build_tests clean
