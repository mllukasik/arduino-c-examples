PORT=/dev/ttyACM0

run:
	@echo "run"
	@./.venv/bin/python test.py $(PORT)

.PHONY: venv
venv:
	@echo "venv"
	@python3 -m venv .venv
	@./.venv/bin/pip install pyserial

