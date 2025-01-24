CC:= gcc
CFLAGS:= -Wall -g

INCLUDE_DIR:= ./include
SRC_DIR:= ./src
BUILD_DIR:= ./build
OBJS:= ./build/snake.o \
	   ./build/map.o \
	   ./build/main.o \
	   ./build/global.o \
	   ./build/control.o

INCLUDE:= -I$(INCLUDE_DIR)

TARGETS:= $(BUILD_DIR)/snake.out

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(TARGETS): $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC) $^ -o $@


.PHONY: always clean test run

test: $(TARGETS)

clean:
	rm -rf $(BUILD_DIR)

run: $(TARGETS)
	$(TARGETS)
