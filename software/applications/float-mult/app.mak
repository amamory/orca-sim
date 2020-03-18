# Do not modify the lines below
APP_FLOAT_MULT_NAME  := float-mult
APP_FLOAT_MULT_DIR   := $(SRC_DIR)/../applications/$(APP_FLOAT_MULT_NAME)
APP_FLOAT_MULT_SRC   := $(APP_FLOAT_MULT_DIR)/src
APP_FLOAT_MULT_INC   := $(APP_FLOAT_MULT_DIR)/include
APP_FLOAT_MULT_LIB   := app-$(APP_FLOAT_MULT_NAME).a 

# Update these lines with your source code
APP_FLOAT_MULT_OBJS := \
	$(APP_FLOAT_MULT_NAME).o

#pack everithing in a single lib
$(APP_FLOAT_MULT_LIB) : $(APP_FLOAT_MULT_OBJS)
	ar rcs $(APP_FLOAT_MULT_LIB) $(APP_FLOAT_MULT_OBJS) 

#compile each individual object file
%.o: $(APP_FLOAT_MULT_SRC)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -I$(APP_FLOAT_MULT_INC)

#check whether .h are up to date
$(APP_FLOAT_MULT_SRC)/%.c: $(APP_FLOAT_MULT_INC)/%.h
