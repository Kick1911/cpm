include project.mk
include config.mk

all: ${APP_NAME}

${APP_NAME}: ${SRC_PATH}/${APP_NAME}.c ${COMP_O} ${UTILS_O}
	${call print,BIN $@}
	${Q}${CC} $^ -o $@ ${CFLAGS} ${LDFLAGS}

%.o: %.c
	${call print,CC $< -> $@}
	${Q}${CC} -c $< -o $@ ${CFLAGS}

static_library: lib${APP_NAME}.a

lib${APP_NAME}.a: ${COMP_O} ${UTILS_O}
	${call print,AR $@}
	${Q}ar -cvq $@ $^ ${shell find lib -name '*.o'}

set_pic:
	${eval CFLAGS += -fPIC}

shared_library: set_pic lib${APP_NAME}.so

lib${APP_NAME}.so: ${COMP_O} ${UTILS_O}
	${call print,LIB $@.${VERSION}}
	${Q}${CC} -shared -Wl,-soname,$@ -o $@.${VERSION} $^ ${LDFLAGS} ${shell find lib -name '*.o'}
	${call print,'SYMLINK $@'}
	${Q}ln -sf $@.${VERSION} $@

install:
	${call print,INSTALL ${INSTALL_PATH}}
	${Q}mkdir -p ${INSTALL_PATH}/{bin,share/${APP_NAME},include,lib}
	${Q}cp ${APP_NAME} ${INSTALL_PATH}/bin 2> /dev/null || :
	${Q}cp ${INCLUDE_PATH}/* ${INSTALL_PATH}/include 2> /dev/null || :
	${Q}cp lib${APP_NAME}.* ${INSTALL_PATH}/lib 2> /dev/null || :
	${Q}cp -R ${SHARE_PATH}/* ${INSTALL_PATH}/share/${APP_NAME} 2> /dev/null || :

clean:
	${call print,CLEAN ${APP_NAME}}
	${Q}${MAKE} -C tests clean
	${Q}${RM} ${APP_NAME} lib${APP_NAME}.* ${COMP_O} ${UTILS_O}

.PHONY: install clean all set_pic
