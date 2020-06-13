CC := g++ 
SRCDIR := src
TSTDIR := test
BUILDDIR := build
TARGET := bin/tetris
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -std=c++11 -Wall -Wextra -pedantic
LIB := -L build/lib/*
INC := -I include
LINKER_FLAGS := -lSDL2

$(TARGET): $(OBJECTS)
	@mkdir -p bin
	@echo " Linking..."
	@echo "$(CC) $^ -o $(TARGET) $(LINKER_FLAGS)"; $(CC) $^ -o $(TARGET) $(LINKER_FLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BUILDDIR)/lib 
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
bin/%: $(TSTDIR)/%.$(SRCEXT)
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $< build/lib/*

test: bin/test_block

.PHONY: clean
.PHONY: test