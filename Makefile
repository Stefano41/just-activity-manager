CXX      = g++
CXXFLAGS = -Wall -march=x86-64
BUILDDIR = build
BINDIR   = bin

.PHONY: all clean

all: $(BUILDDIR) $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/ActivityManager main.cpp

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BUILDDIR) $(BINDIR)
