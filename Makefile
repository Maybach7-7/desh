SRC=main.c
TARGET=shell

all: run

$(TARGET): $(SRC)
	gcc $(SRC) -o $(TARGET) -lreadline

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET)
