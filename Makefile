CXX      = g++
CXXFLAGS = -Wall -march=x86-64
BUILDDIR = build
BINDIR   = bin

.PHONY: all test clean

all: $(BUILDDIR) $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/ActivityManager main.cpp src/activity.cpp -I.

test: $(BUILDDIR) $(BINDIR)
	$(CXX) $(CXXFLAGS) --coverage -o $(BINDIR)/test_activity tests/test_activity.cpp src/activity.cpp -I.
	./$(BINDIR)/test_activity

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BUILDDIR) $(BINDIR) 