VERSION := 0.0.1

SRC_PATH := src

SRC := cpm
SRC_CODE := $(SRC:%=$(SRC_PATH)/%.c)
SRC_HEADER := $(SRC_CODE:%.c=%.h)

INCLUDE_PATH := $(SRC_PATH)

CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=2 -DVERSION=\"${VERSION}\"
CFLAGS   = ${DEBUG} -ansi -pedantic -static -Wall -Wno-deprecated-declarations ${INCLUDE_PATH:%=-I%} ${CPPFLAGS}