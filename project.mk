APP_NAME = cpm
VERSION = 0.11.0
INSTALL_PATH = /opt
CFLAGS += -DINSTALL_PATH=${INSTALL_PATH}

STATIC_DEP = json
SHARED_DEP =

DEPENDENCIES = Kick1911/json/v0.0.2/json.h Kick1911/json/v0.0.2/libjson.a
DEPENDENCIES += Kick1911/unitest/v0.10.0/unitest.h

LDFLAGS += ${STATIC_DEP:%=-l%} ${SHARED_DEP:%=-l%}
INSTALL_STEPS = install_share_folder install_binary
