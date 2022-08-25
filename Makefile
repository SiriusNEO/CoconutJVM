COMPILER = g++

SRC_DIR = src
3RDPARTY_DIR = 3rdparty

SRC_FILES = $(3RDPARTY_DIR)/zip/zip.c $(3RDPARTY_DIR)/utf16/converter.c $(SRC_DIR)/main.cpp

build:
	$(COMPILER) $(SRC_FILES) -o coconut -g -O2
	echo 'coconut build finish'

run:
	./coconut --jre-path ./ --class-path testclasses TestClass 123

run1:
	./coconut --jre-path ./ --class-path lib/rt.jar java.lang.String 123

test:
	./coconut --class-path testclass/