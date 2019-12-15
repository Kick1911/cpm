VERSION := 0.0.1

ROOT ?= .
SRC_PATH := $(ROOT)/src
UTIL_PATH := $(SRC_PATH)/util
APPS_PATH := $(SRC_PATH)/apps

SRC := cpm
SRC_CODE := $(SRC:%=$(SRC_PATH)/%.c)
SRC_HEADER := $(SRC_CODE:%.c=%.h)
APPS := component init
APPS_CODE := $(APPS:%=$(APPS_PATH)/%.c)
APPS_HEADER := $(APPS_CODE:%.c=%.h)
UTIL := render util
UTIL_CODE := $(UTIL:%=$(UTIL_PATH)/%.c)
UTIL_HEADER := $(UTIL_CODE:%.c=%.h)

INCLUDE_PATH := $(SRC_PATH)

CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=2 -DVERSION=\"${VERSION}\"
CFLAGS  += ${DEBUG} -ansi -pedantic -Wall -Wno-deprecated-declarations -I${INCLUDE_PATH} ${CPPFLAGS}
