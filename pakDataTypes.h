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

//Mark III structures - wordPackDict.dat headers
typedef struct
{
	BinHdrPtr words;
	BinHdrPtr stringTableBytes;
} wordPackDictHeader;

typedef struct
{
	i32 wordStrId;
	f32 probability;
} wordHeader;

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

//Mark V structures - itemmanifest.dat structures
typedef struct
{
	BinHdrPtr itemsManifest;
	BinHdrPtr normalDeps;
	BinHdrPtr soundDeps;
	BinHdrPtr effectDeps;
	BinHdrPtr itemDeps;
	BinHdrPtr itemsBinDataBytes;
} itemManifestHeader;

typedef struct
{
	u32 itemId;
	u32 animResId;
	i32 recentlyModifiedRank;
	i32 firstNormalDepends;
	i32 numNormalDepends;
	i32 firstSoundDepends;
	i32 numSoundDepends;
	i32 firstEffectDepends;
	i32 numEffectDepends;
	i32 firstItemDepends;
	i32 numItemDepends;
	u32 catalogIconColorItemTexResId;
	u32 catalogIconColorBGTexResId;
	u32 catalogIconGreyBGTexResId;
	i32 binDataOffsetBytes;
} itemManifestRecord;

typedef struct
{
	u32 normalTexResId;
} normalDependency;

typedef struct
{
	u32 soundResId;
} soundDependency;

typedef struct
{
	u32 effectResId;
} effectDependency;

typedef struct
{
	u32 itemResId;
} itemDependency;

typedef struct
{
	f32 x;
	f32 y;
} vec2;

typedef struct
{
	u32 id;
	i32	key;
} BinLocStrKey;

typedef struct
{
	BinHdrPtr skels;
	BinHdrPtr joints;
	BinHdrPtr bones;
	BinHdrPtr boneShapes;
	BinHdrPtr boneParts;
	BinHdrPtr bonePartTreeVals;
	BinHdrPtr rgnCells;
	BinHdrPtr stringTableBytes;
	BinHdrPtr burnGridUsedDataBytes;
	u32 itemId;
	i32 itemIdStrId;
	u32 animResId;
	vec2 iconAnimBoundsMin;
	vec2 iconAnimBoundsMax;
	BinLocStrKey name;
	i32 costCoins;
	i32 costStamps;
	i32 valueCoins;
	i32 valueStamps;
	BinLocStrKey desc;
	i32 unlisted;
	i32 popsCoins;
	i32 moneyItem;
	f32 animThreshold;
	f32 motorThreshold;
	i32 absPosition;
	f32 scaleVariance;
	i32 quantity;
	i32 shipTimeSec;
	u32 initialBurnExportId;
	i32 initialBurnPerGroup;
	i32 mouseGrabbable;
	f32 illuminate;
	i32 enableHFlip;
	i32 floorWallShadow;
	i32 splitJumpLastFrame;
	f32 purchaseCooldown;
	i32 allowDirectionalLight;
	u32 mouseGrabSoundResId;
	i32 instantEffects;
	i32 freezeOnCollide;
	i32 enableFreezePostAnim;
	u32 uniqueIgniteSoundResId;
	i32 collideItems;
	i32 collideEnvironment;
	i32 orbitalGravity;
	i32 allowExplodeStreaks;
	i32 burnSlowsAnim;
	i32 plagueOnCollide;
	u32 spawnLimitBurnExportId;
	u32 instAshSoundResId;
	i32 canGetPlague;
	i32 instAshDoesSplat;
	f32 modXAmpMin;
	f32 modXAmpMax;
	f32 modXFreqMin;
	f32 modXFreqMax;
	f32 modXPhaseMin;
	f32 modXPhaseMax;
	f32 modXSpeedMin;
	f32 modXSpeedMax;
	f32 modYAmpMin;
	f32 modYAmpMax;
	f32 modYFreqMin;
	f32 modYFreqMax;
	f32 modYPhaseMin;
	f32 modYPhaseMax;
	f32 modYSpeedMin;
	f32 modYSpeedMax;
} itemDataHeader;

typedef struct
{
	i32 firstJointIdx;
	i32 numJoints;
	i32 firstBoneIdx;
	i32 numBones;
	u32 burnExport;
	f32 selectWeight;
	i32 hasAnimThresh;
	f32 animThresh;
	i32 animExportStrId;
	vec2 animBoundsMin;
	vec2 animBoundsMax;
} skelsRecord;

typedef struct 
{
	f32 value;
	u32 tuneId;
} BinTuneDataFloat;

typedef struct
{
	i32 boneIdx[2];
	i32 boneBurnGridCellIdx[2];
	i32 burnable;
	i32 allowExtDamage;
	vec2 modelSpacePos;
	BinTuneDataFloat strength;
	BinTuneDataFloat angleLimit;
	BinTuneDataFloat speed;
	BinTuneDataFloat spin;
	BinTuneDataFloat wobble;
} jointRecord;

typedef struct
{
	f32 _11, _12, _13;
	f32 _21, _22, _23;
} mtx23;

typedef struct
{
	u32 id;
	i32 animBlockIdx;
	mtx23 animBlockTransform;
	vec2 itemSpacePosition;
	i32 firstBoneMainShapeIdx;
	i32 numBoneMainShapes;
	vec2 burnBoundsMin;
	vec2 burnBoundsMax;
	f32 burnGridSize;
	i32 burnGridWidth;
	i32 burnGridHeight;
	i32 firstBurnUsedIdx;
	i32 firstPartsIdx;
	i32 numParts;
	i32 firstPartTreeValIdx;
	i32 numPartTreeVals;
	i32 connectedGroupIdx;
	i32 firstRgnCellIdx;
	i32 numRgnCells;
	u32 igniteTimeEnumValId;
	u32 burnTimeEnumValId;
	u32 attackSpeedEnumValId;
	u32 attackAmountEnumValId;
	u32 decaySpeedEnumValId;
	u32 burnAmountEnumValId;
	u32 boneDensityEnumValId;
	u32 collideSoundEnumValId;
	u32 igniteSoundEnumValId;
	u32 decayParticlesEnumValId;
	u32 igniteParticlesEnumValId;
	u32 frictionEnumValId;
	u32 restitutionEnumValId;
	u32 linearDampEnumValId;
	u32 angularDampEnumValId;
	i32 behavior;
	u32 shatterExpRadiusEnumValId;
	u32 shatterExpFireAmountEnumValId;
	u32 shatterExpFireSpeedEnumValId;
	u32 shatterExpForceEnumValId;
	u32 shatterExpSoundEnumValId;
	u32 shatterExpEffectEnumValId;
	u32 shatterExpTimeRampDownEnumValId;
	u32 shatterExpTimeHoldDownEnumValId;
	u32 shatterExpTimeRampUpEnumValId;
	u32 shatterExpTimeFactorEnumValId;
	u32 shatterExpDoCamShakeEnumValId;
	u32 ashBreakMinAccelEnumValId;
	u32 ashBreakMaxAccelEnumValId;
	u32 splitSFXSmallEnumValId;
	u32 splitSFXMediumEnumValId;
	u32 splitSFXLargeEnumValId;
	u32 splitBrittleEnumValId;
	u32 splitThresholdEnumValId;
	u32 splitEffectEnumValId;
	u32 ashSplitTimeBaseEnumValId;
	u32 ashSplitTimeVarEnumValId;
	u32 splitDespawnEffectEnumValId;
	u32 stampBlackWhitePctEnumValId;
	u32 smearAmountEnumValId;
	u32 collideParticlesEnumValId;
	u32 explodeIgnoreBurnTriggerEnumValId;
	u32 postExplodeSplitTimeBaseEnumValId;
	u32 postExplodeSplitTimeVarEnumValId;
	u32 explodeIgnitePiecesEnumValId;
	u32 postExplodeAshBreakMinAccelEnumValId;
	u32 autoRotateUprightEnumValId;
	u32 mouseGrabSoundEnumValId;
	u32 instAshOnCollideEnumValId;
	u32 applyGravityEnumValId;
	u32 splatParticlesEnumValId;
} boneRecord;

typedef struct
{
	u32 flags;
	i32 numVerts;
	vec2 verts[ 8 ];
} boneShapeRecord;

typedef struct
{
	u32 flags;
	u32 texResId;
	u32 normalMapResId;
	f32 pupilMoveRange;
} bonePartRecord;

typedef struct
{
	i32 regionUID;
	i32 burnGridCellIdx;
} boneGridCellMappingRegion;

//Mark VI Structures - reverse-engineered .dat files (Thanks to Mygod)
typedef struct
{
	BinHdrPtr pictureMetadata;
	BinHdrPtr pictureBytes;
} myPicturesHeader;

typedef struct
{
	i32 width;
	i32 height;
	i32 offset;
} myPicturesMetadata;

typedef struct
{
	BinHdrPtr pictureMetadata;
	BinHdrPtr pictureBytes;
} smokeImageHeader;

typedef struct
{
	u32 id;
	i32 width;
	i32 height;
	i32 offset;
} smokeImageMetadata;

typedef struct
{
	BinHdrPtr pictureMetadata;
	BinHdrPtr pictureBytes;
} fluidPalettesHeader;

typedef struct
{
	u32 id;
	i32 offset;
	i32 width; // height always equals to 1
} fluidPalettesMetadata;

typedef struct
{
	BinHdrPtr files;
	BinHdrPtr records;
} loctexManifestHeader;

typedef struct
{
	u32 resId; // common file id
	i32 index; // record pointer
	i32 count;
} loctexFile;

typedef struct
{
	u32 languageId;
	u32 localizedResId;
} loctexRecord;

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

//Mark VIII Structures - combo database structures
typedef struct
{
	BinHdrPtr combos;
	BinHdrPtr items;
	BinHdrPtr stringTableBytes;
} comboHeader;

typedef struct
{
	u32 id;
#ifdef VERSION_12
	i32 idStrTblIdx; //This isn't here for version 1.1 or less
#endif
	BinLocStrKey title;
	i32 value;
	i32 stampValue;
	i32 firstItemIdx;
	i32 numItems;
} comboRecord;

typedef struct
{
	u32 itemId;
	i32 picTexX;
	i32 picTexY;
	i32 picTexW;
	i32 picTexH;
} comboItemRecord;

//Mark IX Structures - letterdb.dat stuff
typedef struct
{
	BinHdrPtr letters;
	BinHdrPtr pages;
	BinHdrPtr stringTableBytes;
} letterHeader;

#define BASIC_LETTER			0
#define REQUEST_LETTER			1
#define REQUESTFOLLOWUP_LETTER	2
#define ATTACHITEM_LETTER		3
#define ATTACHMONEY_LETTER		4
#define ATTACHCATALOG_LETTER	5

typedef struct
{
	i32 type;
	u32 id;
	i32 firstPageIdx;
	i32 numPages;
	u32 dependsLetterId;
	u32 borderAnimExportId;
	i32 sendTimeSec;
	i32 delayTimeSec;
	u32 postLetterSpecialExportId;
	u32 depCatalogId;
	i32 depCatalogItemCount;
	i32 depNoItems;
	i32 addTraySlots;
	i32 deliverable;
	i32 removeAfterRead;
	i32 burnableAfterRead;
	i32 depAllStars;
	i32 depAllCombo;
	i32 depAllItemsUsed;
	i32 jingleLetter;
	i32 blockNextCatalog;
	i32 deliverAfterWin;
	u32 requestedItemId[3];
	u32 reqChildWrongLetterId;
	u32 reqParentLetterId;
	u32 attachedItemId;
	i32 attachedMoneyAmount;
	u32 attachedCatalogId;
	i32 letterIdStrId;
} letter;

typedef struct
{
	u32 senderPicExportId;
	u32 specialEventExportId;
	u32 pagePicTexResId;
	f32 pagePicScale;
	u32 musicSoundResId;
	f32 musicOffset;
	u32 wordsSoundResId;
	u32 lastWordSoundResId;
	i32 allowSkip;
	f32 speedScale;
	BinLocStrKey text;
} letterPage;

//Mark X structures - catalogdb.dat stuff
typedef struct
{
	BinHdrPtr catalogs;
	BinHdrPtr items;
	BinHdrPtr stringTableBytes;
} catalogHeader;

typedef struct
{
	u32 id;
	i32 cost;
	i32 numCombos;
	BinTuneDataFloat bgRaysR;
	BinTuneDataFloat bgRaysG;
	BinTuneDataFloat bgRaysB;
	BinTuneDataFloat bgPaperR;
	BinTuneDataFloat bgPaperG;
	BinTuneDataFloat bgPaperB;
	i32 firstItemIdx;
	i32 numItems;
	u32 coverTexId;
	u32 thumbTexId;
	u32 lockedTexId;
	i32 nameStrId;
} catalog;

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
