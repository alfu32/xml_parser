CC := gcc
CFLAGS := -Wall -Wextra -Iinclude
LDFLAGS := -Llib
LIBS :=

SRCDIR := src
OBJDIR := obj
BINDIR := bin
TESTDIR := test

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

TEST_SOURCES := $(wildcard $(TESTDIR)/*.c)
TEST_OBJECTS := $(patsubst $(TESTDIR)/%.c,$(OBJDIR)/%.o,$(TEST_SOURCES))
TEST_TARGET := $(BINDIR)/test

all: xml_parser strings

xml_parser: $(OBJDIR)/xml_parser.o
	ar rcs lib/libxml_parser.a $^

strings: $(OBJDIR)/strings.o
	ar rcs lib/libstrings.a $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $^ $(LDFLAGS) $(LIBS)

.PHONY: clean install uninstall

clean:
	$(RM) -r $(OBJDIR)/*.o $(LIBDIR)/*.a $(BINDIR)/*

install:
	mkdir -p /usr/local/include /usr/local/lib
	cp include/*.h /usr/local/include
	cp lib/*.a /usr/local/lib

uninstall:
	$(RM) /usr/local/include/xml_parser.h /usr/local/include/strings.h /usr/local/lib/libxml_parser.a /usr/local/lib/libstrings.a
