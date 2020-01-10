include project.mk
include Makefile.in
include config.mk

all: ${APP_NAME}

${APP_NAME}: ${SRC_PATH}/${APP_NAME}.c ${COMP_O} ${UTILS_O}
	${CC} $^ -o $@ ${CFLAGS}
%.o: %.c
	${CC} -c $< -o $@ ${CFLAGS} -D STATIC

static_library: lib${APP_NAME}.a

lib${APP_NAME}.a: ${COMP_O} ${UTILS_O}
	ar -cvq $@ $^


set_pic:
	${eval CFLAGS += -fPIC}

shared_library: set_pic lib${APP_NAME}.so

lib${APP_NAME}.so: ${COMP_O} ${UTILS_O}
	${CC} -shared -Wl,-soname,$@ -o $@.0.0.1 $^
	ln -s $@.0.0.1 $@

install:
	@cp ${APP_NAME} ${CONFIG_INSTALL_PATH}/bin 2> /dev/null || :
	@cp ${INCLUDE_PATH}/* ${CONFIG_INSTALL_PATH}/include 2> /dev/null || :
	@cp lib${APP_NAME}.* ${CONFIG_INSTALL_PATH}/lib 2> /dev/null || :

clean:
	${RM} ${APP_NAME} lib${APP_NAME}.*
	${MAKE} -C tests clean
	${MAKE} -C src clean

.PHONY: install clean all set_pic

