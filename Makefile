CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

TARGET = test/sherikGit
BUILD_DIR = build

SRCS = main.cpp \
       libs/SHA256.cpp \
       src/filesystem/file.cpp \
       src/filesystem/blob.cpp \
	   src/cli/init.cpp \
	   src/cli/cli.cpp \
	   src/cli/hash-object.cpp \
	   src/cli/cat-file.cpp

OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
