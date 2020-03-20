# Do not modify the lines below
APP_MNIST_EXT_MULT_NAME  := mnist_ext_mult
APP_MNIST_EXT_MULT_DIR   := $(SRC_DIR)/../applications/$(APP_MNIST_EXT_MULT_NAME)
APP_MNIST_EXT_MULT_SRC   := $(APP_MNIST_EXT_MULT_DIR)/src
APP_MNIST_EXT_MULT_INC   := $(APP_MNIST_EXT_MULT_DIR)/include
APP_MNIST_EXT_MULT_LIB   := app-$(APP_MNIST_EXT_MULT_NAME).a 

# Update these lines with your source code
APP_MNIST_EXT_MULT_OBJS := \
	$(APP_MNIST_EXT_MULT_NAME).o

#pack everithing in a single lib
$(APP_MNIST_EXT_MULT_LIB) : $(APP_MNIST_EXT_MULT_OBJS)
	ar rcs $(APP_MNIST_EXT_MULT_LIB) $(APP_MNIST_EXT_MULT_OBJS) 

#compile each individual object file
%.o: $(APP_MNIST_EXT_MULT_SRC)/%.c
	$(CPP) $(CFLAGS) -c -o $@ $< -I$(APP_MNIST_EXT_MULT_INC)

#check whether .h are up to date
$(APP_MNIST_EXT_MULT_SRC)/%.c: $(APP_MNIST_EXT_MULT_INC)/%.h
