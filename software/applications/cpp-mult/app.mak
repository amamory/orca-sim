# Do not modify the lines below
APP_CPP_MULT_NAME  := cpp-mult
APP_CPP_MULT_DIR   := $(SRC_DIR)/../applications/$(APP_CPP_MULT_NAME)
APP_CPP_MULT_SRC   := $(APP_CPP_MULT_DIR)/src
APP_CPP_MULT_INC   := $(APP_CPP_MULT_DIR)/include
APP_CPP_MULT_LIB   := app-$(APP_CPP_MULT_NAME).a 

# Update these lines with your source code
APP_CPP_MULT_OBJS := \
	$(APP_CPP_MULT_NAME).o

#pack everithing in a single lib
$(APP_CPP_MULT_LIB) : $(APP_CPP_MULT_OBJS)
	ar rcs $(APP_CPP_MULT_LIB) $(APP_CPP_MULT_OBJS) 

#compile each individual object file
%.o: $(APP_CPP_MULT_SRC)/%.c
	$(CPP) $(CFLAGS) -c -o $@ $< -I$(APP_CPP_MULT_INC)

#check whether .h are up to date
$(APP_CPP_MULT_SRC)/%.c: $(APP_CPP_MULT_INC)/%.h
