CC = gcc
CFLAGS = -Wall -Iinclude -O2
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)
TARGET = build/queue_app


all: $(TARGET)

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

integration-test:
	@echo "🚀 Starting server in background..."
	./$(TARGET) &          
	SERVER_PID=$$!
	sleep 1                     
	@echo "🚀 Running integration tests..."
	python test/test_queue.py          
	kill $$SERVER_PID          
	@echo "✅ Integration tests finished."

build:
	mkdir -p build

clean:
	rm -rf build
