# For 32-bit build systems, the executable is just mingw32
MINGW32 ?= i686-w64-mingw32
# Used s.t. we can try to use clang to compile code
_CXX ?= g++

CXX=$(MINGW32)-$(_CXX)
ifeq ($(MINGW32), "mingw32")
	DLLTOOL=dlltool
else
	DLLTOOL=$(MINGW32)-dlltool
endif

# Clang doesn't understand permissive compilation, we need to "fix" invalid
# casts from a pointer type there using
#     static_cast<NEW_TYPE>(reinterpret_cast<uintptr_t>(ptr))
# instead of
#     (NEW_TYPE)(ptr)
CXXFLAGS=-std=c++98 -fpermissive -Wno-write-strings
CPPFLAGS=-MMD -MF $*.d
LDLIBS=-lgdi32 -lversion -ldiabloui -lstorm
LDFLAGS=-L./

all: devilution.exe

include 3rdParty/PKWare/objs.mak
include Source/objs.mak

devilution.exe: $(OBJS) $(PKWARE_OBJS) diabloui.lib storm.lib
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

diabloui.lib: diabloui.dll DiabloUI/diabloui_gcc.def
	$(DLLTOOL) -d DiabloUI/diabloui_gcc.def -D $< -l $@

diabloui.dll:
	$(error Please copy diabloui.dll (version 1.09b) here)

storm.lib: storm.dll 3rdParty/Storm/Source/storm_gcc.def
	$(DLLTOOL) -d 3rdParty/Storm/Source/storm_gcc.def -D $< -l $@

storm.dll:
	$(error Please copy storm.dll (version 1.09b) here)

clean:
	@$(RM) -v $(OBJS) $(OBJS:.o=.d) $(PKWARE_OBJS)  $(PKWARE_OBJS:.o=d) storm.lib diabloui.lib

.PHONY: clean all
