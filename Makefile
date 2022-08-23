COMPILER = g++

SRC_DIR = src

SRC_FILES = $(SRC_DIR)/main.cpp

build:
	$(COMPILER) $(SRC_FILES) -o coconut -O2
	echo 'coconut build finish'