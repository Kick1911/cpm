# Made with C Project Manager
# Author: Caswall Engelsman (mail@cengelsman.com)

include config.mk
include project.mk

ARCHIVE_FILES := ${APP_NAME:%=lib%.a}
LIBRARY_FILES := ${APP_NAME:%=lib%.so}
LIBRARY_FILES_VERSIONS := ${LIBRARY_FILES:%.so=%.so.${VERSION}}
DEP_PACKAGE_PATHS := ${DEPENDENCIES:%=${DEP_PATH}/%}
GITLAB_DEP := ${filter ${DEP_PATH}/gitlab/%,${DEP_PACKAGE_PATHS}}
LDFLAGS += ${DEPENDENCIES:%=-L${DEP_PATH}/%}
CFLAGS += ${DEPENDENCIES:%=-I${DEP_PATH}/%} -DVERSION='"${VERSION}"'

TAR_NAME ?= ${word 1,${APP_NAME}}-${VERSION}.tar.gz
PACKAGE_CONTENTS ?= ${APP_NAME} ${ARCHIVE_FILES}

all: set_debug_vars dep ${APP_NAME}

set_debug_vars:
	${eval DEBUG = -g3 -DLOG_LEVEL=1}

${APP_NAME}: %: ${SRC_PATH}/%.o ${COMP_O} ${UTILS_O}
	${call print,${GREEN}BIN $@}
	${Q}${CC} $^ -o $@ ${CFLAGS} ${LDFLAGS}

%.o: %.c ${shell find ${SRC_PATH} -name '*.h'}
	${call print,${CYAN}CC $@}
	${Q}${CC} -c $< -o $@ ${CFLAGS}

static_library: dep ${ARCHIVE_FILES}

${ARCHIVE_FILES}: set_pie ${DEP_PACKAGE_PATHS} ${COMP_O} ${UTILS_O}
	${call print,${BROWN}AR $@}
	${eval DEP_ARCHIVES = ${shell find ${DEP_PACKAGE_PATHS} -name '*.a'}}
	${eval OBJECT_FILES = ${filter %.o,$^}}
	${Q}for arch in ${DEP_ARCHIVES} ; do \
		ar x $$arch --output `dirname $$arch` ; \
	done
	${Q}ar -cq $@ ${OBJECT_FILES} `find ${DEP_PACKAGE_PATHS} -name '*.o'`

set_pic:
	${eval CFLAGS += -fPIC}

set_pie:
	${eval CFLAGS += -fPIE}

shared_library: dep ${LIBRARY_FILES}

${LIBRARY_FILES}: %.so: %.so.${VERSION}
	${call print,${BRIGHT_CYAN}SYMLINK $@}
	${Q}ln -sf $< $@

${LIBRARY_FILES_VERSIONS}: set_pic ${COMP_O} ${UTILS_O}
	${call print,${BRIGHT_MAGENTA}LIB $@}
	${Q}${CC} -shared -Wl,-soname,$@ -o $@ ${filter-out set_pic,$^} ${LDFLAGS}

dep: ${GITLAB_DEP} preprocess

test_compile: set_debug_vars dep ${TESTS_OUT}

test: test_compile
	@for exe in $(TESTS_OUT) ; do \
		valgrind --error-exitcode=1 --leak-check=full $$exe ; \
		if [ $$? -ne 0 ]; then return 1; fi; \
	done

${TESTS_OUT}: %.out: %.c ${COMP_O} ${UTILS_O}
	${call print,${GREEN}BIN $@}
	${Q}${CC} $^ -o $@ ${CFLAGS} ${LDFLAGS}

release:
	${call print,${GREEN}RELEASE v${VERSION}}
	${Q}git tag -a v${VERSION} -m 'Version ${VERSION}'
	${Q}git push origin v${VERSION}

${GITLAB_DEP}:
	${eval PREFIX = ${DEP_PATH}/gitlab}
	${eval CLEAN_PREFIX = ${PREFIX:./%=%}}
	${eval INFO = ${@:${CLEAN_PREFIX}/%=%}}
	${eval WORD_LIST = ${subst /, ,${INFO}}}

	${eval PROJECT = ${word 1, ${WORD_LIST}}}
	${eval VERSION = ${word 2, ${WORD_LIST}}}

	${Q}mkdir -p $@
	${call gitlab_get_file,${PROJECT},${VERSION},$@}
	${Q}cd $@ && tar xvf dist.tar.gz

${LIB_PATH}/%.a:
	${eval WORD_LIST = ${subst /, ,$@}}
	${eval ORG = ${word 2, ${WORD_LIST}}}
	${eval PROJECT = ${word 3, ${WORD_LIST}}}
	${eval VERSION = ${word 4, ${WORD_LIST}}}
	${eval FILE_NAME = ${word 5, ${WORD_LIST}}}
	${Q}mkdir -p ${dir $@}
	${call get_archive,${ORG}/${PROJECT},${VERSION},${FILE_NAME},$@}
	${Q}ln -sf ${shell pwd}/$@ ${shell pwd}/${LIB_PATH}/${FILE_NAME}

${LIB_PATH}/%.h:
	${eval WORD_LIST = ${subst /, ,$@}}
	${eval ORG = ${word 2, ${WORD_LIST}}}
	${eval PROJECT = ${word 3, ${WORD_LIST}}}
	${eval VERSION = ${word 4, ${WORD_LIST}}}
	${eval FILE_NAME = ${word 5, ${WORD_LIST}}}
	${Q}mkdir -p ${dir $@}
	${Q}mkdir -p ${INCLUDE_PATH}
	${call get_header,${ORG}/${PROJECT},${VERSION},${FILE_NAME},$@}
	${Q}ln -sf ${shell pwd}/$@ ${shell pwd}/${INCLUDE_PATH}/${FILE_NAME}

set_prod_vars:
	${eval CFLAGS = ${PROD_CFLAGS} ${CFLAGS}}

prod: set_prod_vars dep ${APP_NAME}

package: dep ${TAR_NAME}

${TAR_NAME}: ${PACKAGE_CONTENTS}
	${call print,${GREEN}TAR $@}
	${Q}mkdir -p ${DIST_PATH}
	${Q}cp -R $^ ${DIST_PATH}
	${Q}tar -czf $@ -C ${DIST_PATH} .

install: ${INSTALL_STEPS}

install_binary: ${INSTALL_PATH}/bin/
	${call print,${GREEN}INSTALL $<}
	${Q}cp ${APP_NAME} ${INSTALL_PATH}/bin/

install_static: ${ARCHIVE_FILES} ${APP_NAME:%=${SRC_PATH}/%.h} ${INSTALL_PATH}/include/ ${INSTALL_PATH}/lib/
	${call print,${GREEN}INSTALL $<}
	${Q}cp ${APP_NAME:%=${SRC_PATH}/%.h} ${INSTALL_PATH}/include/
	${Q}cp ${ARCHIVE_FILES} ${INSTALL_PATH}/lib/

install_shared: ${APP_NAME:%=lib%.so.${VERSION}} ${APP_NAME:%=${SRC_PATH}/%.h} ${INSTALL_PATH}/include/ ${INSTALL_PATH}/lib/
	${call print,${GREEN}INSTALL $<}
	${Q}cp ${APP_NAME:%=${SRC_PATH}/%.h} ${INSTALL_PATH}/include/
	${Q}cp ${APP_NAME:%=lib%.so.${VERSION}} ${INSTALL_PATH}/lib/

install_share_folder: ${APP_NAME:%=${INSTALL_PATH}/share/%}
	${call print,${GREEN}INSTALL $<}
	${Q}cp -R ${SHARE_PATH}/* ${APP_NAME:%=${INSTALL_PATH}/share/%}

${INSTALL_PATH}/%:
	${call print,${GREEN}MKDIR $@}
	${Q}mkdir -p $@

clean:
	${call print,${BRIGHT_CYAN}CLEAN ${APP_NAME}}
	${Q}${RM} ${APP_NAME} ${TAR_NAME} ${APP_NAME:%=${SRC_PATH}/%.o} ${APP_NAME:%=lib%.*} ${COMP_O} ${UTILS_O}
	${Q}${RM} -R ${DIST_PATH}
	${call print,${BRIGHT_CYAN}CLEAN tests}
	${Q}${RM} ${TESTS_OUT}

.PHONY: preprocess package test test_compile clean set_prod_vars set_debug_vars prod all set_pic install install_share_folder install_shared install_binary install_static dep
