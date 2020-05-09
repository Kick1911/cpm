include project.mk
include config.mk

all: ${APP_NAME}

${APP_NAME}: ${SRC_PATH}/${APP_NAME}.c ${COMP_O} ${UTILS_O}
	${CC} $^ -o $@ ${CFLAGS} ${LDFLAGS}

%.o: %.c
	${CC} -c $< -o $@ ${CFLAGS}

static_library: lib${APP_NAME}.a

lib${APP_NAME}.a: ${COMP_O} ${UTILS_O}
	ar -cvq $@ $^ ${shell find lib -name '*.o'}

set_pic:
	${eval CFLAGS += -fPIC}

shared_library: set_pic lib${APP_NAME}.so

lib${APP_NAME}.so: ${COMP_O} ${UTILS_O}
	${CC} -shared -Wl,-soname,$@ -o $@.${VERSION} $^ ${LDFLAGS} ${shell find lib -name '*.o'}
	ln -sf $@.${VERSION} $@

install:
	@mkdir -p ${INSTALL_PATH}/{bin,share/${APP_NAME},include,lib}
	@cp ${APP_NAME} ${INSTALL_PATH}/bin 2> /dev/null || :
	@cp ${INCLUDE_PATH}/* ${INSTALL_PATH}/include 2> /dev/null || :
	@cp lib${APP_NAME}.* ${INSTALL_PATH}/lib 2> /dev/null || :
	@cp -R ${SHARE_PATH}/* ${INSTALL_PATH}/share/${APP_NAME} 2> /dev/null || :

clean:
	${RM} ${APP_NAME} lib${APP_NAME}.* ${COMP_O} ${UTILS_O}

.PHONY: install clean all set_pic
