include config.mk

APPS_PATH := src/apps
APPS := init component
APP_PHONY := $(APPS:%=%.phony)
APPS := $(APPS:%=$(APPS_PATH)/%)
APP_CODE := $(APPS:%=%.c)
APP_OBJS := $(APPS:%=%.o) $(UTIL_CODE:%.c=%.o)
APP_STRUCT_PARTIAL := $(APPS_PATH)/apps_struct.h.partial
APP_FUNC_PARTIAL := $(APPS_PATH)/apps_func.h.partial
APP_PARTIALS := $(APP_STRUCT_PARTIAL) $(APP_FUNC_PARTIAL)

define add_app
	@echo 'Partial App: $(1)'
	@echo "CPM_REGISTER_APP($(1))," >> $(APP_STRUCT_PARTIAL)
	@echo "CPM_APP_FUNCTION($(1));" >> $(APP_FUNC_PARTIAL)
endef