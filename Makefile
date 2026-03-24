.PHONY: help build run install uninstall clean

help:
	@echo "SpeedFetch - Make targets:"
	@echo "  make build      - Build the project"
	@echo "  make run        - Build and run"
	@echo "  make install    - Install to /usr/local/bin"
	@echo "  make uninstall  - Remove from system"
	@echo "  make clean      - Clean build directory"

build:
	@if [ ! -d build ]; then mkdir build; fi
	@cd build && cmake .. && make
	@echo "Build complete! Binary: ./build/speedfetch"

run: build
	@./build/speedfetch

install: build
	@echo "Installing speedfetch to /usr/local/bin..."
	@cp build/speedfetch /usr/local/bin/speedfetch
	@chmod +x /usr/local/bin/speedfetch
	@echo "Installation complete! Use 'speedfetch' command."

uninstall:
	@echo "Removing speedfetch..."
	@rm -f /usr/local/bin/speedfetch
	@echo "Uninstalled successfully."

clean:
	@echo "Cleaning build directory..."
	@rm -rf build
	@echo "Clean complete."
