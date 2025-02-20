CLI=arduino-cli
PORT=/dev/ttyACM0

compile:
	@echo "compile"
	@$(CLI) compile -p $(PORT)

.PHONY: deploy
deploy:
	@echo "deploy"
	@$(CLI) upload -p $(PORT)

