LIBNAME := dfa
BUILD_DIRECTORY := build/
LIB_TARGET := $(BUILD_DIRECTORY)lib$(LIBNAME).a
HEADER_FILES := $(wildcard *.h)
OBJECT_FILES := $(addprefix $(BUILD_DIRECTORY),$(patsubst %.c,%.o,$(wildcard *.c)))
CFLAGS := -Wall
COMPILER := cc

.PHONY : clean

all: $(LIB_TARGET)

$(LIB_TARGET): $(BUILD_DIRECTORY) $(OBJECT_FILES)
	ar -cvq $(LIB_TARGET) $(OBJECT_FILES)

$(BUILD_DIRECTORY)%.o: %.c $(HEADER_FILES)
	$(COMPILER) -o $@ -c $< $(CFLAGS) -g

$(BUILD_DIRECTORY):
	@mkdir -p $(BUILD_DIRECTORY)

clean:
	rm -rf $(LIB_TARGET) $(OBJECT_FILES)
	rm -rf $(BUILD_DIRECTORY)
