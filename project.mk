APP_NAME = cpm
VERSION = 0.0.5
INSTALL_PATH = /opt
CFLAGS += -DINSTALL_PATH=${INSTALL_PATH}

STATIC_DEP = json
SHARED_DEP =

DEPENDENCIES = Kick1911/json/v0.0.2/libjson.a

LDFLAGS += ${STATIC_DEP:%=-l%} ${SHARED_DEP:%=-l%}

LANGUAGE_EXTENSION = c
# LANGUAGE_EXTENSION = hs
