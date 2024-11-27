SRC=main.c
TARGET=shell.out
VFS=vfs.c
VFS_TARGET=vfs.out

all: run

$(TARGET): $(SRC) $(VFS)
	gcc $(SRC) -o $(TARGET) -lreadline -fpermissive
	gcc $(VFS) -o $(VFS_TARGET) `pkg-config --cflags --libs fuse3`

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET)
	rm -rf $(VFS_TARGET)
