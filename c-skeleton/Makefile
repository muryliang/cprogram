CFLAGS = -g -Wall -Wextra -rdynamic $(OPTFLAGS)
LDFLAGS = -ldl $(OPTLIBS)

SOURCES = $(wildcard src/**/*.c src/*.c)
OBJECTS = $(patsubst %.c, %.o , $(SOURCRS))

TESTS_SRC = $(wildcard tests/*_test.c)
TESTS = $(patsubst %.c,%  ,$(TESTS_SRC))

TARGET = lib/libYOUR_LIB.a
SO_TARGET = $(patsubst %.a , %.so , $(TARGET))

all: $(TARGET) $(SO_TARGET) tests
	
dev: CFLAGS = -g -Wall -Wextra -Isrc $(OPTFLAGS)
dev: all

$(TARGET): C
