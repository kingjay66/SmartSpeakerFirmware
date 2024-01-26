CC		 := /usr/bin/g++ -std=c++11
OUT_DIR	 := build

all:
	mkdir -p $(OUT_DIR)

	$(CC) $(PWD)/src/User.cpp -o $(PWD)/$(OUT_DIR)/User.o -Iinclude -c
	$(CC) $(PWD)/src/Speaker.cpp -o $(PWD)/$(OUT_DIR)/Speaker.o -Iinclude -c
	$(CC) $(PWD)/src/Settings.cpp -o $(PWD)/$(OUT_DIR)/Settings.o -Iinclude -c
	$(CC) $(PWD)/src/NetworkService.cpp -o $(PWD)/$(OUT_DIR)/NetworkService.o -Iinclude -lcurl -c
	$(CC) $(PWD)/src/SettingsService.cpp -o $(PWD)/$(OUT_DIR)/SettingsService.o -Iinclude -c
	$(CC) $(PWD)/src/Main.cpp -o $(PWD)/$(OUT_DIR)/Main.o -lSDL2 -Iinclude -c

	$(CC) -o $(PWD)/$(OUT_DIR)/ssf \
		$(PWD)/$(OUT_DIR)/Main.o \
		$(PWD)/$(OUT_DIR)/User.o \
		$(PWD)/$(OUT_DIR)/Speaker.o \
		$(PWD)/$(OUT_DIR)/Settings.o \
		$(PWD)/$(OUT_DIR)/NetworkService.o \
		$(PWD)/$(OUT_DIR)/SettingsService.o \
		-lSDL2 \
		-Iinclude \
		-lcurl 


clean:
	rm -rf $(OUT_DIR)

