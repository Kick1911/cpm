CPM = cpm
APP_NAME = ${shell ${CPM} json name}
VERSION = ${shell ${CPM} json version}
DEPENDENCIES = ${shell ${CPM} json dependencies}
LDFLAGS += ${DEPENDENCIES:%=-l%}
INSTALL_PATH = ${shell ${CPM} json install_path}
${eval CFLAGS += ${shell ${CPM} json cflags}}