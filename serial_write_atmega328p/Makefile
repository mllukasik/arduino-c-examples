compile:
	@echo "compile"
	@mkdir -p build
	@avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -Os -o build/main.elf main.c
	@avr-objcopy -O ihex build/main.elf build/main.hex

.PHONY: deploy
deploy:
	@echo "deploy"
	@avrdude -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:build/main.hex:i

.PHONY: clean
clean:
	@echo "clean"
	@rm build -rf

.PHONY: objdump
objdump:
	@echo "objdump"
	@avr-objdump -d build/main.elf > build/main.asm

