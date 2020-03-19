# Do not modify the lines below
APP_INT_MULT_NAME  := int-mult
APP_INT_MULT_DIR   := $(SRC_DIR)/../applications/$(APP_INT_MULT_NAME)
APP_INT_MULT_SRC   := $(APP_INT_MULT_DIR)/src
APP_INT_MULT_INC   := $(APP_INT_MULT_DIR)/include
APP_INT_MULT_LIB   := app-$(APP_INT_MULT_NAME).a 

# Update these lines with your source code
APP_INT_MULT_OBJS := \
	$(APP_INT_MULT_NAME).o

#pack everithing in a single lib
$(APP_INT_MULT_LIB) : $(APP_INT_MULT_OBJS)
	ar rcs $(APP_INT_MULT_LIB) $(APP_INT_MULT_OBJS) 

#compile each individual object file
%.o: $(APP_INT_MULT_SRC)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -I$(APP_INT_MULT_INC)

#check whether .h are up to date
$(APP_INT_MULT_SRC)/%.c: $(APP_INT_MULT_INC)/%.h
