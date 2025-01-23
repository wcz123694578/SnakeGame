CC:= gcc
CFLAGS:= -Wall -g

BUILD_DIR:= ./build
OBJS:= ./build/snake.o \
	   ./build/map.o \
	   ./build/main.o \
	   ./build/global.o \
	   ./build/control.o
TARGETS:= $(BUILD_DIR)/snake.out

$(BUILD_DIR)/%.o: ./%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGETS): $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC) $^ -o $@


.PHONY: always clean test run

test: $(TARGETS)

clean:
	rm -rf $(BUILD_DIR)

run: $(TARGETS)
	$(TARGETS)
