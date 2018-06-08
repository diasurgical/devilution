DIABLO_SRC=$(wildcard Source/*.cpp)
DIABLO_OBJ=$(DIABLO_SRC:.cpp=.o)

PKWARE_SRC=$(wildcard 3rdParty/PKWare/*.cpp)
PKWARE_OBJ=$(PKWARE_SRC:.cpp=.o)

all: diablo.exe

diablo.exe: $(DIABLO_OBJ) $(PKWARE_OBJ) diabloui.lib storm.lib
	i686-w64-mingw32-gcc -L./ -o $@ $^ -lgdi32 -lversion -ldiabloui -lstorm

%.o: %.cpp
	i686-w64-mingw32-gcc -c -fpermissive -o $@ $<

diabloui.lib: diabloui.dll DiabloUI/diabloui.def
	i686-w64-mingw32-dlltool -d DiabloUI/diabloui.def -D diabloui.dll -l diabloui.lib

diabloui.dll:
	echo "Please copy diabloui.dll (version 1.09b) here."
	exit 1

storm.lib: storm.dll 3rdParty/Storm/Source/storm.def
	i686-w64-mingw32-dlltool -d 3rdParty/Storm/Source/storm.def -D storm.dll -l storm.lib

storm.dll:
	echo "Please copy storm.dll (version 1.09b) here."
	exit 1

clean:
	rm -f $(DIABLO_OBJ) $(PKWARE_OBJ)

.PHONY: clean all
