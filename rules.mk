### Misc ###
GTEST_BASEDIR = thirdparty/googletest
GTEST_INCDIR = $(GTEST_BASEDIR)/googletest/include
GMOCK_INCDIR = $(GTEST_BASEDIR)/googlemock/include
GTEST_BUILDDIR = $(GTEST_BASEDIR)/build
GMOCK_LIBDIR = $(GTEST_BUILDDIR)/googlemock
GTEST_LIBDIR = $(GTEST_BUILDDIR)/googlemock/gtest

GBENCH_BASEDIR = thirdparty/benchmark
GBENCH_INCDIR = $(GBENCH_BASEDIR)/include
GBENCH_BUILDDIR = $(GBENCH_BASEDIR)/build
GBENCH_LIBDIR = $(GBENCH_BUILDDIR)/src

FINDSRCS = $(addprefix $(strip $(1))/, \
           $(notdir $(wildcard $(SRCDIR)/$(strip $(1))/$(strip $(2)))))
LIBDATASTRUCTURES_SRCS += $(call FINDSRCS, src, *.c)
TEST_SRCS += $(call FINDSRCS, test, *.cpp)
BENCH_SRCS += $(call FINDSRCS, bench, *.cpp)

### Sources ###
SRCS += $(LIBDATASTRUCTURES_SRCS)
SRCS += $(TEST_SRCS)
SRCS += $(BENCH_SRCS)

### Includes ###
INCDIRS += include
SYSINCDIRS += $(GTEST_INCDIR)
SYSINCDIRS += $(GMOCK_INCDIR)
SYSINCDIRS += $(GBENCH_INCDIR)

### Compiler ###
CC = gcc
CXX = g++
CFLAGS = -std=gnu11
CXXFLAGS = -std=gnu++11
CPPFLAGS += -Wall -Wextra -g -DDEBUG
CPPFLAGS += -MT $@ -MMD -MP -MF $(@:.o=.d)
CPPFLAGS += $(addprefix -I $(SRCDIR)/, $(INCDIRS))
CPPFLAGS += $(addprefix -isystem $(SRCDIR)/, $(SYSINCDIRS))
CPPFLAGS += -pthread
LDLIBS =
LDFLAGS = -pthread
AR = ar
ARFLAGS = -rcs

### Targets ###
# EXTLIBS: built externally, define rule below
# LIBS: built internally, define prerequisite .o files only
# PROGS: built internally, define prerequisite .o and .a files only
EXTLIBS = $(GMOCK_LIBDIR)/libgmock_main.a $(GBENCH_LIBDIR)/libbenchmark.a
LIBS = src/libdatastructures.a
PROGS = test/datastructures_test bench/datastructures_bench
OTHER = test tags

### Rules ###
src/libdatastructures.a: $(addsuffix .o, $(basename $(LIBDATASTRUCTURES_SRCS)))
test/datastructures_test: $(addsuffix .o, $(basename $(TEST_SRCS))) \
                          src/libdatastructures.a                   \
                          $(GMOCK_LIBDIR)/libgmock_main.a
bench/datastructures_bench: $(addsuffix .o, $(basename $(BENCH_SRCS))) \
                            src/libdatastructures.a                    \
                            $(GBENCH_LIBDIR)/libbenchmark.a


$(GMOCK_LIBDIR)/libgmock_main.a:
	@mkdir -p $(GTEST_BUILDDIR);      \
	cd $(GTEST_BUILDDIR);             \
	cmake $(SRCDIR)/$(GTEST_BASEDIR); \
	$(MAKE) $(MAKEFLAGS)

$(GBENCH_LIBDIR)/libbenchmark.a:
	@mkdir -p $(GBENCH_BUILDDIR);                                 \
	cd $(GBENCH_BUILDDIR);                                        \
	cmake -DCMAKE_BUILD_TYPE=Release $(SRCDIR)/$(GBENCH_BASEDIR); \
	$(MAKE) $(MAKEFLAGS)

.PHONY: test
test: test/datastructures_test
	test/datastructures_test

.PHONY: bench
bench: bench/datastructures_bench
	bench/datastructures_bench

tags: $(SRCS) $(shell find $(addprefix $(SRCDIR)/, $(INCDIRS)) -type f)
	ctags -f $@ $^

### Standard Rules ###
.DEFAULT_GOAL = all
.PHONY: all
all: $(EXTLIBS) $(LIBS) $(PROGS) $(OTHER)

VPATH = $(SRCDIR)

OBJS = $(addsuffix .o, $(basename $(SRCS)))
DEPS = $(addsuffix .d, $(basename $(SRCS)))

OBJDIRS = $(filter-out $(CURDIR)/, $(sort $(dir $(abspath $(OBJS)))))
$(OBJDIRS):
	@mkdir -p $@
$(OBJS): | $(OBJDIRS)
$(DEPS): | $(OBJDIRS)

%.o: %.c %.d
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

%.o: %.cpp %.d
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

$(LIBS):
	$(AR) $(ARFLAGS) $@ $^

$(PROGS):
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

-include $(DEPS)

print-%:
	@echo '$*=$($*)'
	@echo '  origin = $(origin $*)'
	@echo '  flavor = $(flavor $*)'
	@echo '  value  = $(value  $*)'
