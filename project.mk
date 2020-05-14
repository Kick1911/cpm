CPM = cpm
APP_NAME = ${shell ${CPM} json name}
VERSION = ${shell ${CPM} json version}
DEPENDENCIES = ${shell ${CPM} json dependencies}
INSTALL_PATH = ${shell ${CPM} json install_path}
${eval CFLAGS += ${shell ${CPM} json cflags}}

STATIC_DEP = ${shell echo ${DEPENDENCIES} | awk -v RS=' ' 'match($$0, "lib(.+).a.[0-9].[0-9].[0-9]", a) {print a[1]}'}
SHARED_DEP = ${shell echo ${DEPENDENCIES} | awk -v RS=' ' 'match($$0, "lib(.+).so.[0-9].[0-9].[0-9]", a) {print a[1]}'}
LDFLAGS += ${STATIC_DEP:%=-l%} ${SHARED_DEP:%=-l%}