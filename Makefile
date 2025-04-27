CC      := gcc
FLAGS   := -Wall -Werror -lm
SRC     := ./src/source
BIN     := ./bin
HEADERS := ./src/include
EXEC    := pl0
TEXT    := ./files

# Lista de arquivos .c
CFILES  := $(wildcard $(SRC)/*.c)
# Arquivos .o correspondentes
OFILES  := $(CFILES:$(SRC)/%.c=$(BIN)/%.o)

all: $(EXEC)

$(EXEC): $(OFILES)
	$(CC) -o $@ $(OFILES) $(FLAGS)

$(BIN)/%.o: $(SRC)/%.c | $(BIN)
	$(CC) -c $< -o $@ -I $(HEADERS) $(FLAGS)

$(BIN):
	mkdir -p $(BIN)

run: all
	./$(EXEC)

clean:
	rm -f $(BIN)/*.o $(EXEC)
