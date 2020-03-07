.DEFAULT_GOAL := help

# Porcelain
# ###############
.PHONY: build test init

todo: ## list all TODOs in the project
	grep --color=always -Ri todo .

build: setup ## create artifact
	@echo "Not implemented"; false

test: ## run all tests


init: ## one time setup
	direnv allow .

# Plumbing
# ###############
.PHONY: setup

CC = g++
CFLAGS += --std=c++17

### GTEST CONFIG ###

GTEST_DIR = /opt/gtest/googletest
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread
#USER_DIR = .

# Suppresses those shitty unknown pragma region warnings
CFLAGS += -Wno-unknown-pragmas


GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
	$(CC) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
			$(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CC) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
			$(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

### MAIN ###

.PHONY: main
DEPS := main/conf.h main/business.h
FILES := test/unit.cpp
main : $(FILES) $(DEPS) gtest_main.a
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -lpthread $(FILES) gtest_main.a -o $@.out
	@./$@.out

# Utilities
# ###############
.PHONY: help
help: ## print this message
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
