TARGET = main
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = $(wildcard *.h)
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Phony targets
.PHONY: all clean

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Generic rule for compiling .cpp to .o
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET)

# Include dependencies
-include $(OBJECTS:.o=.d)

# Rule to generate a dep file by using the C preprocessor
# (see man gcc for details on the -MM and -MT options)
%.d: %.cpp
	@$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@
