CC = gcc
CFLAGS = -Wall -Iinclude -O2
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)
TARGET = build/queue_app

# Diretórios e testes
TEST_SRC = $(wildcard tests/*.c)
TEST_TARGET = build/test_queue
TEST_OBJ = $(filter-out build/main.o, $(OBJ)) # remove main.o

# Compilação normal
all: $(TARGET)

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

# Compilar e executar testes (sem main.o)
test: $(TEST_OBJ) $(TEST_SRC) | build
	$(CC) $(CFLAGS) $(TEST_OBJ) $(TEST_SRC) -o $(TEST_TARGET)
	@echo "🚀 Running tests..."
	@./$(TEST_TARGET)

# Criar pasta build se não existir
build:
	mkdir -p build

# Limpar
clean:
	rm -rf build
