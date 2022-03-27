# SPDX-License-Identifier: GPL-2.0

PHONY += all
all: config

export KCONFIG_DIR=$(CURDIR)/scripts/kconfig
include $(KCONFIG_DIR)/kconfig.Makefile
#include Makefile.subtrees

INCLUDES = -I include/
CFLAGS += $(INCLUDES)

include scripts/objects.Makefile

config:
	@echo "config generated"

PHONY += clean
clean:
	$(MAKE) -f scripts/build.Makefile $@
	@rm -f example

PHONY += mrproper
mrproper:
	$(MAKE) -f scripts/build.Makefile clean
	$(MAKE) -f scripts/build.Makefile $@

PHONY += help
help:
	$(MAKE) -f scripts/build.Makefile $@

.PHONY: $(PHONY)
