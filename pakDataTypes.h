//What we were given from Allan

#ifndef PAKDATATYPES_H
#define PAKDATATYPES_H

#define VERSION_12

#include <cstdio>
#include <tinyxml2.h>
#include <stdint.h>
#include <list>
#include <VFS.h>
#include <VFSTools.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <zlib.h>
#ifdef _WIN32
	#define UNICODE
	#include <windows.h>
#endif
using namespace tinyxml2;
using namespace std;
#define i32 int32_t
#define u32 uint32_t
#define i16 int16_t
#define u16 uint32_t
#define f32	float
#define byte uint8_t
#define MAX_NUM_THREADS 128
#define RESIDMAP_ID		0xB7E44207
#define RESIDMAP_NAME	"vdata/residmap.dat"


typedef struct
{
	f32 x;
	f32 y;
} vec2;

//Mark I structures - .pak file headers
typedef struct 
{
	i32 pakVersion;
	i32 numItems;
} blobHeader;

typedef struct
{
	u32 id;
	u32 flags;
	u32 offset;
	u32 size;
} resourceHeader;

typedef struct
{
	i32 compressedSizeBytes;
	i32 uncompressedSizeBytes;
} compressedHeader;

#define FLAG_NOCOMPRESSION	0x00
#define FLAG_ZLIBCOMPRESSED	0x01

//Mark II structures - PNG headers and residmap.dat headers
typedef struct
{
	i32 count;
	i32 offset;
} BinHdrPtr;

typedef struct
{
	BinHdrPtr maps;
	BinHdrPtr stringTableBytes;
} ResidMapHeader;

typedef struct
{
	u32 resId;
	i32 strId;
} MappingHeader;

typedef struct
{
	i32 numStrings;
	i32 numPointers;
} StringTableHeader;

typedef struct
{
	i32 pointerIndex;
	i32 pointerCount;
} StringTableEntry;

typedef struct
{
	u32 languageId;
	i32 offset;
} StringPointerEntry;

#define LANGID_ENGLISH  0x656E	//"en"
#define GREYSCALE_PNG	0x08
#define STANDARD_PNG	0x01

typedef struct
{
    u32 numImages;
    //u32 imgOffset[numImages];
} pngHeader;

typedef struct
{
	u32 offset;	//point to ImageHeader
} imgOffset;

typedef struct
{
	u32 width;
	u32 height;
	u32 flags;
} ImageHeader;

//Mark IV structures - sndmanifest.dat structures
typedef struct
{
	BinHdrPtr sounds;
	BinHdrPtr takes;
} soundManifestHeader;

typedef struct
{
	u32 logicalId;
	i32 firstTakeIdx;
	i32 numTakes;
} soundTakeGroup;

typedef struct
{
	u32 resId;
	i32 channels;
	i32 samplesPerSec;
	i32 sampleCountPerChannel;
	i32 vorbisWorkingSetSizeBytes;
	i32 vorbisMarkersSizeBytes;
	i32 vorbisPacketsSizeBytes;
} takeRecord;

//Mark VII Structures - font data types
typedef struct 
{
	i32 numFonts;
} fontManifestHeader;

typedef struct
{
	u32 fontResId;
	i32 firstTexDependsIdx;
	i32 numTexDepends;
} fontManifestRecord;

typedef struct
{
	u32 texResId;
} fontManifestTexture;

typedef struct
{
	BinHdrPtr chars;
	BinHdrPtr kerns;
	i32 pointSize;
	f32 extLeading;
	f32 maxAscent;
	f32 maxDescent;
} fontResourceHeader;

typedef struct
{
	i32 codepoint;
	i32 texPageIdx;
	i16 texX, texY;
	i16 texW, texH;
	f32 offsetX;
	f32 offsetY;
	f32 advance;
} fontCharacterRecord;

typedef struct
{
	i16 codepoints[2];
	f32 kernAmount;
} fontKerningRecord;

//Structures for my use
typedef struct
{
	u32 size;
	uint8_t* data;
} virtualFile;

typedef struct
{
	u32 compressedSize;
	u32 decompressedSize;
	uint8_t* data;
} zlibData;

typedef struct
{
	compressedHeader cH;
	bool bCompressed;
	u32 dataSz;
	uint8_t* data;
} pakHelper;

typedef struct
{
	//wstring sIn;
	//wstring sFilename;
	u32 id;
	bool bCompressed;
	zlibData data;
} ThreadConvertHelper;

//global functions
string ws2s(const wstring& s);								//For converting UTF-16 to UTF-8
wstring s2ws(const string& s);								//For converting UTF-8 to UTF-16
void threadedDecompress();									//Start threaded decompression
void threadedCompress(list<wstring> resources);				//Compress resources with multiple threads
//image.cpp functions
bool convertToPNG(const wchar_t* cFilename, uint8_t* data, u32 size);
bool convertFromPNG(const wchar_t* cFilename);				//Convert a PNG image to a game image file
//sndmanifest.cpp functions
bool sndManifestToXML(const wchar_t* cFilename);			//Convert sndManifest.dat to XML
bool XMLToSndManifest(const wchar_t* cFilename);			//Convert sndManifest.dat.xml back to binary .dat form
void initSoundManifest();									//Read in sndManifest.dat so that we can have the correct filenames for all sounds
u32 getSoundId(wstring sSound);								//Get a sound ID from the filename
wstring getSoundName(u32 soundResId);						//Get a sound filename from the sound ID
//residmap.cpp functions
void initResMap();											//Read in residmap.dat so that we can have the correct filenames for all resource files
bool residMapToXML(const wchar_t* cFilename);				//Convert residmap.dat to XML
bool XMLToResidMap(const wchar_t* cFilename);				//Convert residmap.dat.xml back to binary .dat form
const wchar_t* getName(u32 resId);							//Get a resource filename from the resource ID
u32 getResID(wstring sName);								//Get a resource ID from its filename (by lookup table or by hashing if unknown)
u32 getKnownResID(wstring sName);							//Same as above, only returns 0 if unknown rather than hashing
u32 hash(wstring sFilename);								//Hash a filename to get an ID
wstring toBackslashes(const wstring s);						//Convert forward slashes in a filename to backslashes
//zpipe.cpp functions
uint8_t* compress(zlibData* zIn);							//Compress via zlib
uint8_t* decompress(const zlibData* zIn);					//Decompress via zlib
//font.cpp functions
bool fontManifestToXML(wstring sFilename);					//Convert vdata/fontmanifest.dat to XML
bool XMLToFontManifest(wstring sFilename);					//Convert vdata/fontmanifest.dat.xml back to .dat form
bool fontToXML(wstring sFilename);							//Convert font files (like data/fonts/TwCen.font.xml) to XML form
bool XMLToFont(wstring sFilename);							//Convert font XML files back to original form
//ogg.cpp functions
int binaryToOgg( const wchar_t* in, const wchar_t* out );	//Function from Allan to convert a game sound file to .ogg
int oggToBinary( const wchar_t* in, const wchar_t* out );	//Function from Allan to convert an .ogg file to the game's sound format
takeRecord getOggData( const wchar_t* cFile );				//Grab the data from an OGG file to populate sndManifest.dat
//parse.cpp functions
void writeVec2(XMLElement* elem, string sAttributeName, vec2 vec);	//Write out a vec2 as one XML attribute
void readVec2(XMLElement* elem, string sAttributeName, vec2* vec);	//Read a vec2 from one XML attribute
string stripCommas(string s);
string RGBToString(f32 r, f32 g, f32 b);
void RGBFromString(f32* r, f32* g, f32* b, string s);













#endif
