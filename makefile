SRC_LIST = xml_string_codec.cpp
OBJ_LIST = $(addprefix $(BUILD)/, $(SRC_LIST:.cpp=.o))

BUILD = build

SRC_TEST_LIST = test.cpp

LIBNAME = xml_string_codec
LIBFILENAME = lib$(LIBNAME).a

CFLAGS = -MMD -MP

CXX = g++
CC = g++ -c
AR = ar

all : $(BUILD)/$(LIBFILENAME) $(BUILD)/test

.PHONY: test
test : $(BUILD)/test

$(BUILD)/test : $(SRC_TEST_LIST) $(BUILD)/$(LIBFILENAME) | $(BUILD)
	$(CXX) $(CFLAGS) -o $(@) $(SRC_TEST_LIST) -L$(BUILD) -l$(LIBNAME)

.PHONY: lib
lib : $(BUILD)/$(LIBFILENAME)

$(BUILD)/$(LIBFILENAME) : $(OBJ_LIST) | $(BUILD)
	$(AR) rcs $(@) $(^)

$(BUILD)/%.o : %.cpp makefile | $(BUILD)
	$(CC) $(CFLAGS) -o $(@) $(<)

$(BUILD) :
	mkdir $(@)

clean :
	rm -rf $(BUILD)

-include $(wildcard $(BUILD)/*.d)