SRC_DIR := Sources
OBJ_DIR := Objects
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

../poller: $(OBJ_FILES)
	g++ -g -o $@ $^ -lpthread

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -g -c -o $@ $<