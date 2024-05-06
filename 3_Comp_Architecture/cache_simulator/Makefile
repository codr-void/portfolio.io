all:
	@echo "Compiling the project..."
	gcc -o cache.exe main.c cache.c
	@echo "Compilation successful!"
	@echo "type 'make run' to start.."

run: all
	@echo "Running the executable..."
	./cache.exe

clean:
	@echo "Cleaning up..."
	rm -f cache.exe
	@echo "Clean up complete!"

.PHONY: all run clean
