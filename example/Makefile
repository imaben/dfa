APP_NAME := example
INCLUDE_DIRECTORY := ../dfa
LINK_DIRECTORY := ../dfa/build
LINK_LIBRARY := dfa
LINK_TARGET := $(LINK_DIRECTORY)/lib$(LINK_LIBRARY).a

ifeq ($(wildcard $(LINK_TARGET)),)
all:;@echo 'Please go to ../dfa directory and complie it first.'
else
all: $(APP_NAME)
endif

$(APP_NAME): $(APP_NAME).o $(LINK_TARGET)
	cc -o $(APP_NAME) $(APP_NAME).o -L$(LINK_DIRECTORY) -l$(LINK_LIBRARY) -g

$(APP_NAME).o: $(APP_NAME).c
	cc -o $(APP_NAME).o -c $(APP_NAME).c -I$(INCLUDE_DIRECTORY) -Wall -g

clean:
	rm -f $(APP_NAME) $(APP_NAME).o
