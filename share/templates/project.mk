APP_NAME = $0
VERSION = 0.0.1
INSTALL_PATH = /opt
CFLAGS += -DINSTALL_PATH=${INSTALL_PATH}
PROD_CFLAGS = -O3 -static

STATIC_DEP =
SHARED_DEP =

DEPENDENCIES =

LDFLAGS += ${STATIC_DEP:%=-l%} ${SHARED_DEP:%=-l%}
