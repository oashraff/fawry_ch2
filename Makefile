CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude
TARGET = quantum_bookstore
SRCDIR = src
INCDIR = include
SOURCES = main.cpp $(SRCDIR)/QuantumBookstore.cpp $(SRCDIR)/BookTypes.cpp $(SRCDIR)/Book.cpp $(SRCDIR)/Services.cpp $(SRCDIR)/QuantumBookstoreFullTest.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)

# Individual object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
