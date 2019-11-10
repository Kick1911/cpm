include config.mk
include apps.mk

all: partials $(SRC)

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

$(SRC): $(SRC_CODE) $(SRC_HEADER) $(APP_OBJS)
	$(CC) $< $(APP_OBJS) $(CFLAGS) -o $@

$(APP_PHONY):
	$(eval APP := $(@:$(APPS_PATH)/%.phony=%))
	$(call add_app,$(APP))

partials: clean_partials $(APP_PHONY)

clean_partials:
	$(RM) $(APP_PARTIALS)

clean:
	$(RM) $(SRC) $(APP_PARTIALS)

.INTERMEDIATE: $(APP_OBJS)
.PHONY: clean $(APP_PHONY) clean_partials partials all