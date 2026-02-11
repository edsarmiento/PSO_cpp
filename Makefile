# PSO_cpp — standalone Makefile (no NetBeans)
# Build: make [build]   Clean: make clean

CXX ?= g++
RM = rm -f
MKDIR = mkdir -p

# gtkmm: try gtkmm-3.0 then gtkmm3.0 (e.g. Fedora)
GTKMM_PKG := $(shell pkg-config --exists gtkmm-3.0 2>/dev/null && echo gtkmm-3.0 || echo gtkmm3.0)
CXXFLAGS = -g -std=c++14 $(shell pkg-config --cflags $(GTKMM_PKG))
LDFLAGS  = $(shell pkg-config --libs $(GTKMM_PKG))

BUILDDIR = build/Debug/GNU-Linux-x86
DISTDIR  = dist/Debug/GNU-Linux-x86
OBJDIR   = $(BUILDDIR)/src
TARGET   = $(DISTDIR)/pso_cpp

SRCS = src/PSOThread.cpp src/PSO_Interface.cpp src/Scanner.cpp \
       src/UserInterface.cpp src/main.cpp src/pso.cpp
OBJS = $(SRCS:src/%.cpp=$(OBJDIR)/%.o)
DEPS = $(OBJS:.o=.d)

.PHONY: all build clean help

all: build
build: $(TARGET)

$(TARGET): $(OBJS)
	$(MKDIR) $(DISTDIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: src/%.cpp
	$(MKDIR) $(OBJDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -MF $(OBJDIR)/$*.d -c -o $@ $<

-include $(DEPS)

clean:
	$(RM) -r $(BUILDDIR)
	$(RM) -r $(DISTDIR)

help:
	@echo "Targets: build (default), clean, help"
	@echo "  make [build]  -> $(TARGET)"
	@echo "  make clean   -> remove build/ and dist/"
