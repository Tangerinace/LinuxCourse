CUR_DIR := .
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/obj
BIN_DIR := $(CUR_DIR)/bin
LIB_DIR := $(CUR_DIR)/lib
LIB_STATIC_DIR := $(LIB_DIR)/static
LIB_SHARED_DIR := $(LIB_DIR)/shared

#shared_LIB
create_obj:
	gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o  -I $(INC_DIR)
	gcc -c -fPIC $(SRC_DIR)/MyMath.c -o $(OBJ_DIR)/MyMath.o  -I $(INC_DIR)



create_shared:
	gcc -shared $(OBJ_DIR)/MyMath.o -o $(LIB_SHARED_DIR)/libmymath.so


linking:
	gcc  $(OBJ_DIR)/main.o -L$(LIB_SHARED_DIR)  -lmymath -o $(BIN_DIR)/use-shared-library

clean:
	rm -rf $(BIN_DIR)/use-shared-library $(OBJ_DIR)/*.o $(LIB_SHARED_DIR)/libmymath.so

all: create_obj create_shared linking
	@echo "create shared library"
	
#LD_LIBRARY_PATH 

#static_LIB



create_static:
	ar rcs $(LIB_STATIC_DIR)/libmymath1.a $(OBJ_DIR)/MyMath.o 

linking1:
	gcc  $(OBJ_DIR)/main.o $(OBJ_DIR)/MyMath.o   -L$(LIB_STATIC_DIR) -lmymath1 -o $(BIN_DIR)/use-static-library
	
clean1:
	rm -rf $(BIN_DIR)/use-static-library $(OBJ_DIR)/*.o $(LIB_STATIC_DIR)/libmymath1.a

all1: create_obj create_static linking1
	@echo "create static library"
