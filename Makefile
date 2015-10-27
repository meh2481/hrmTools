SHELL=C:/Windows/System32/cmd.exe
objects = sndmanifest.o residmap.o zpipe.o ogg.o image.o font.o parse.o tinyxml2.o
decompressobjects = $(objects) hrmDecompress.o threadDecompress.o
comressobjects = $(objects) hrmDecompress.o threadCompress.o
HEADERPATH = -I./include
LIBPATH = -L./libs
LIB = -lpng -lzlib -lttvfs -lvorbis -logg
STATICGCC = -static-libgcc -static-libstdc++

all : hrmDecompress.exe recalcSoundManifest.exe strip.exe util/hash.exe util/WinResource.exe
 
hrmDecompress.exe : $(decompressobjects)
	g++ -Wall -O2 -o $@ $(decompressobjects) $(LIBPATH) $(LIB) $(STATICGCC)
recalcSoundManifest.exe : recalcSoundManifest.o
	g++ -Wall -O2 -o $@ $< ogg.o tinyxml2.o $(LIBPATH) $(LIB) $(STATICGCC)
strip.exe : strip.o
	g++ -Wall -O2 -o $@ $< $(STATICGCC)
util/WinResource.exe : util/WinResource.o
	g++ -Wall -O2 -o $@ $< $(STATICGCC)
util/hash.exe : util/hash.o
	g++ -Wall -O2 -o $@ $< residmap.o tinyxml2.o $(STATICGCC)
	
%.o: %.cpp
	g++ -O2 -c -MMD -o $@ $< $(HEADERPATH)

-include $(objects:.o=.d)
-include $(decompressobjects:.o=.d)

.PHONY : clean
clean :
	rm -rf hrmDecompress.exe recalcSoundManifest.exe strip.exe util/hash.exe util/WinResource.exe *.o *.d
