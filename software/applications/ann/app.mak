# Do not modify the lines below
APP_ANN_NAME  := ann
APP_ANN_DIR   := $(SRC_DIR)/../applications/$(APP_ANN_NAME)
APP_ANN_SRC   := $(APP_ANN_DIR)/src
APP_ANN_INC   := $(APP_ANN_DIR)/include
APP_ANN_LIB   := app-$(APP_ANN_NAME).a 

# Update these lines with your source code
APP_ANN_OBJS := \
	ann.o

#pack everithing in a single lib
$(APP_ANN_LIB) : $(APP_ANN_OBJS)
	ar rcs $(APP_ANN_LIB) $(APP_ANN_OBJS) 

#compile each individual object file
%.o: $(APP_ANN_SRC)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -I$(APP_ANN_INC)

#check whether .h are up to date
$(APP_ANN_SRC)/%.c: $(APP_ANN_INC)/%.h
