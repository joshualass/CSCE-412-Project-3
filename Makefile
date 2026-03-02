CXX = g++-15

CXXFLAGS = -Wall
# CXXFLAGS = -Wall -Werror

TARGET = loadbalancer

SRCS = main.cpp HelperFunctions.cpp LoadBalancer.cpp Request.cpp Switch.cpp Webserver.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp	
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)