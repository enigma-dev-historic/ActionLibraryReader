# This is where we make up for a lack of -weverything in GCC. No -werror, because libpurple does not compile with -pedantic.
WARNINGS := -Wall -Wextra -Wswitch-default -pedantic -Wmain -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum
CXXFLAGS := `pkg-config --cflags glib-2.0` `pkg-config --cflags purple` -I. $(WARNINGS)
CPPFLAGS := -fPIC -g
FLAGS := 
LIBS := `pkg-config --libs purple glib-2.0`
LINKS := 
OBJDIR := .objs

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(addprefix $(OBJDIR)/,$(patsubst %.cc, %.o, $(SOURCES)))
OBJDIRS = $(sort $(dir $(OBJECTS)))

default: Release

$(OBJDIR): $(OBJDIRS)
	mkdir -p $@
$(OBJDIRS):
	mkdir -p $@

$(OBJDIR)/%.o $(OBJDIR)/%.d: %.cc | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $(OBJDIR)/$*.o

Release: $(OBJECTS)
	$(CXX) -o pidgin_plus.so -z defs -shared -fPIC $(OBJECTS) $(LIBS) $(LINKS)

clean cleanRelease:
	 rm -rf .objs

ifneq ($(MAKECMDGOALS),clean)
-include $(OBJECTS:.o=.d)
endif
