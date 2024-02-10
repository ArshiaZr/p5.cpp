CXX := g++  # Compiler
CXXFLAGS := -std=c++17 -Wall -Wextra  # Add the -std=c++11 flag here
SRC_DIR := src
SRC_SUBDIRS := $(filter %/,$(wildcard $(SRC_DIR)/core/*/))
SRC_FILES := $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
OBJ_DIR := build/obj
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
BUILD_DIR := build
EXECUTABLE := $(BUILD_DIR)/p5

# SFML configuration
SFML_DIR := /opt/homebrew/Cellar/sfml/2.6.1
LIBS := -lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS := -L$(SFML_DIR)/lib
CXXFLAGS += -I$(SFML_DIR)/include

OBJ_FILES += $(foreach subdir,$(SRC_SUBDIRS),$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(subdir)/*.cpp)))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS) $(LIBS)
	@echo "Executable created: $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiling: $<"

# Dynamically generate object file paths for all subdirectories
$(foreach subdir,$(SRC_SUBDIRS),$(eval $(OBJ_DIR)/%.o: $(subdir)%.cpp))

clean:
	rm -rf $(BUILD_DIR)
