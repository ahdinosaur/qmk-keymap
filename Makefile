.SILENT:

MAKEFLAGS += --no-print-directory

QMK_USERSPACE := $(patsubst %/,%,$(dir $(shell realpath "$(lastword $(MAKEFILE_LIST))")))
ifeq ($(QMK_USERSPACE),)
    QMK_USERSPACE := $(shell pwd)
endif

# `qmk config -ro user.qmk_home` prints `user.qmk_home=/path (config)`.
# Pull the path field (between `=` and the first space), then drop the
# `None` sentinel that means "unset". Avoid parens in the shell here:
# Make's `$(...)` parser counts parens naively and trips on a `)` in a
# regex character class.
QMK_FIRMWARE_ROOT = $(shell qmk config -ro user.qmk_home 2>/dev/null | cut -d= -f2 | cut -d' ' -f1 | sed -e 's|^None$$||g')

.PHONY: help setup link-cheapino build flash flash-cheapino clean

help:
	@echo "Targets:"
	@echo "  make setup            one-time: install qmk_firmware + register this dir as the userspace overlay"
	@echo "  make build            compile every target listed in qmk.json (qmk userspace-compile)"
	@echo "  make flash            compile and flash ergodox_ez:dinosaur (put keyboard in bootloader first)"
	@echo "  make flash-cheapino   compile and flash cheapino:dinosaur (hold boot + tap reset on RP2040-Zero)"
	@echo "  make clean            remove build artifacts"
	@echo ""
	@echo "Or use any qmk_firmware make target directly, e.g.:"
	@echo "  make ergodox_ez:dinosaur          # compile"
	@echo "  make ergodox_ez:dinosaur:flash    # compile + flash"

setup:
	@command -v qmk >/dev/null 2>&1 || { \
		echo "qmk CLI not found. Install with one of:"; \
		echo "  brew install qmk/qmk/qmk        # macOS"; \
		echo "  pipx install qmk                # Linux/macOS"; \
		echo "  python3 -m pip install --user qmk"; \
		exit 1; }
	@test -n "$(QMK_FIRMWARE_ROOT)" -a -d "$(QMK_FIRMWARE_ROOT)" || qmk setup -y
	qmk config user.overlay_dir="$(QMK_USERSPACE)"
	$(MAKE) link-cheapino
	@echo "Setup complete. Try 'make build'."

# Cheapino isn't in mainline QMK. We vendor `keyboards/cheapino/` in this
# userspace; QMK's CLI only discovers keyboards under qmk_firmware, so
# expose it there via a symlink.
link-cheapino:
	@test -n "$(QMK_FIRMWARE_ROOT)" -a -d "$(QMK_FIRMWARE_ROOT)" || { \
		echo "qmk_firmware not found. Run 'make setup' first."; exit 1; }
	ln -sfn "$(QMK_USERSPACE)/keyboards/cheapino" "$(QMK_FIRMWARE_ROOT)/keyboards/cheapino"

build:
	qmk userspace-compile

flash:
	qmk flash -kb ergodox_ez -km dinosaur

flash-cheapino:
	qmk flash -kb cheapino -km dinosaur

clean:
	qmk clean

# Catch-all: forward everything else (e.g. `ergodox_ez:dinosaur`) to qmk_firmware's Makefile.
%:
	@test -n "$(QMK_FIRMWARE_ROOT)" -a -d "$(QMK_FIRMWARE_ROOT)" || { \
		echo "qmk_firmware not found. Run 'make setup' first."; exit 1; }
	+$(MAKE) -C $(QMK_FIRMWARE_ROOT) $(MAKECMDGOALS) QMK_USERSPACE=$(QMK_USERSPACE)
