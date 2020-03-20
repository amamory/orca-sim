# Do not modify the lines below
APP_MNIST_NAME  := mnist
APP_MNIST_DIR   := $(SRC_DIR)/../applications/$(APP_MNIST_NAME)
APP_MNIST_SRC   := $(APP_MNIST_DIR)/src
APP_MNIST_INC   := $(APP_MNIST_DIR)/include
APP_MNIST_LIB   := app-$(APP_MNIST_NAME).a 

# Update these lines with your source code
APP_MNIST_OBJS := \
	$(APP_MNIST_NAME).o

#pack everithing in a single lib
$(APP_MNIST_LIB) : $(APP_MNIST_OBJS)
	ar rcs $(APP_MNIST_LIB) $(APP_MNIST_OBJS) 

#compile each individual object file
%.o: $(APP_MNIST_SRC)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -I$(APP_MNIST_INC)

#check whether .h are up to date
$(APP_MNIST_SRC)/%.c: $(APP_MNIST_INC)/%.h
