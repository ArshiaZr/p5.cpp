CXX := g++  # Compiler
CXXFLAGS := -std=c++17 -Wall -Wextra  # Add the -std=c++17 flag here
SRC_DIR := src
SRC_SUBDIRS := $(filter %/,$(wildcard $(SRC_DIR)/*/*/))
SRC_FILES := $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
OBJ_DIR := build/obj
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
BUILD_DIR := build
STATIC_LIB := $(BUILD_DIR)/libp5.a  # Static library file name

# SFML configuration
SFML_DIR := /opt/homebrew/Cellar/sfml/2.6.1
SFML_INCLUDE := /opt/homebrew/Cellar/sfml/2.6.1/include  # Path to SFML include directory
SFML_LIB := /opt/homebrew/Cellar/sfml/2.6.1/lib  # Path to SFML lib directory
SFML_INC_FLAGS := -I$(SFML_INCLUDE)
SFML_LIB_FLAGS := -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system

# Define the include directories dynamically
INCLUDE_DIRS := $(shell find include -type d)

# Add source file dependencies
OBJ_FILES += $(foreach subdir,$(SRC_SUBDIRS),$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(subdir)/*.cpp)))

# Combine flags
CXXFLAGS += $(SFML_INC_FLAGS) $(addprefix -I, $(INCLUDE_DIRS))
LDFLAGS += $(SFML_LIB_FLAGS)

# Targets
all: $(STATIC_LIB)

$(STATIC_LIB): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	ar rcs $@ $^
	@echo "Static library created: $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiling: $<"

# Dynamically generate object file paths for all subdirectories
$(foreach subdir,$(SRC_SUBDIRS),$(eval $(OBJ_DIR)/%.o: $(subdir)%.cpp))

clean:
	rm -rf $(BUILD_DIR)

# Packaging target
package: $(STATIC_LIB)
	@echo "Creating package..."
	@mkdir -p package/include/p5
	@cp -r include/* package/include/p5
	@cp $(STATIC_LIB) package
	@echo "Package created: package/$(STATIC_LIB)"

# Add this line in your Makefile to echo the contents of all .hpp files
echo_all_hpp:
	@echo "Contents of .hpp files:"
	@find include/core -name '*.hpp' -exec cat {} \;
