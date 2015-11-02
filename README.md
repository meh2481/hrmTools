hrmTools
=======
Tools for ecompression of Human Resource Machine .pak files

Created by Daxar (aka MOM4Evr) from the goofans forum -- http://goofans.com/user/2389

RUN ALL THESE PROGRAMS OFF A BACKUP COPY OF YOUR GAME, NOT THE ORIGINAL VERSION! You have been warned. It's also a good idea to have a backup copy of your resource.pak just in case something goes terribly horribly wrong, since errors tend to multiply rather than vanish as you compress/decompress pakfiles.

Also please note that it's best to have the the input files (Such as the HRM executable, or the pak files you want to extract) in the same directory as these tools when running them. It'll save you a lot of hassle if you're using the command line, and it'll alleviate potential working directory issues if you're clicking and dragging files into executables.


Usage
=====
strip
-----
First, you'll need the resource file "resource.pak" extracted from your game's executable. You can do this with 7zip or ResourceHacker (the files you want are in the subfolder 20480, resources 1, 2, and 3 respectively) if you so choose. liTools provides a tool to help out with this, however. Simply run:

    strip.exe "Human Resource Machine.exe"

Or click and drag "Human Resource Machine.exe" into "strip.exe". This will pull all the .pak files out of your game's executable and strip the .pak files from your executable so it will read the .pak files from disk on the next run. Note that since this does modify your executable, BACK IT UP FIRST!

hrmDecompress
------------
Once you have the .pak file extracted, you can now decompress it into a (more) useable form with hrmDecompress. Simply drag the .pak file into the executable, or run it like:

    hrmDecompress.exe resource.pak

The present version of the program attempts to reconstruct some of the resources from the extracted binary data, though something may go terribly horribly wrong. In this case, it should just spit out errors into the console and keep going. It should be fairly robust, but don't blame me if it crashes unexpectedly or does something bizarre.

After decompression, the files you're after are in data/, sdata/, and vdata/. The filenames are correct, but not all data formats are known yet, so not everything is openable.

Accepted commandline switches:
	--overwrite-progress	Writes over the previous progress indicator, to mimimize commandline output. Doesn't display filenames.
	--threads=n				Decompress with n threads. If n=0, will spawn as many threads as your computer has processor cores. Default is n=0.

liCompress
----------
Not implemented yet.

Sound modification
==================
Not implemented yet.

Mod Creation
============
Not implemented yet.

Mod Installation
================
Not implemented yet.


Building
========
Build with:

    make

These utilities depend on the following third-party libraries, which you'll need to link in:
libpng - http://www.libpng.org/pub/png/libpng.html
zlib - http://www.zlib.net/
ttvfs - https://github.com/fgenesis/ttvfs
libvorbis - http://xiph.org/downloads/
libogg - http://xiph.org/downloads/

Apologies for hastily-thrown-together code that isn't commented much at all. It should be fairly straightforward and readable, but no guarantees.


Utilities ("util" subdirectory)
===============================

WinResource.exe
----------------
This program reads all the resources from inside an executable and spits out some data about them. In moments of dire need, it probably won't help you at all. So ignore it. Or run it with:

    util/WinResource.exe "Little Inferno.exe"

Or copy "WinResource.exe" from the "util" subdirectory into the same folder as "Little Inferno.exe" and click and drag "Little Inferno.exe" into it. It'll spit out a file "resinfo.txt" containing basic information on the resources inside the Little Inferno executable. It may be useful, however, if you're unsure if your executable has been stripped or not (as if the file size alone wouldn't tell you). If resources with "Type: 20480" are all 4 bytes, you'll know it's stripped. Otherwise, probably not. At the very least, it's a fun program to play with.


hash.exe
----------------
Usage:
	hash.exe [string1] [string2] ... [stringn]

Spits out the hashed unsigned integer values of the input strings. Useful for debugging resource values and such.

