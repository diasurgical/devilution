/**
 * @file defs.h
 *
 * Global definitions and Macros.
 */

#ifdef HELLFIRE
#define DIABOOL					BOOLEAN
#define GAME_NAME				"HELLFIRE"
#define APP_NAME				"Hellfire"
#else
#define DIABOOL					BOOL
#define GAME_NAME				"DIABLO"
#define APP_NAME				"Diablo"
#endif

#ifdef HELLFIRE
#define HFAND &&
#define DERROR					GetLastError
#else
#define HFAND &
#define DERROR					SErrGetLastError
#endif

#define DMAXX					40
#define DMAXY					40

#define LIGHTSIZE				6912 // 27 * 256

#define GMENU_SLIDER			0x40000000
#define GMENU_ENABLED			0x80000000

// must be unsigned to generate unsigned comparisons with pnum
#define MAX_PLRS				4

#define MAX_CHARACTERS			10
#ifdef HELLFIRE
#define MAX_LVLS				24
#define MAX_LVLMTYPES			24
#define MAX_SPELLS				52
#else
#define MAX_LVLS				16
#define MAX_LVLMTYPES			16
#define MAX_SPELLS				37
#endif
#define MAX_SPELL_LEVEL			15
#define SPELLBIT(s) ((__int64)1 << (s - 1))

#define MAX_CHUNKS				(MAX_LVLS + 5)

// #define MAX_PATH				260
#define MAX_SEND_STR_LEN		80

#define MAXDEAD					31
#define MAXDUNX					112
#define MAXDUNY					112
#define MAXITEMS				127
#define MAXBELTITEMS			8
#define MAXLIGHTS				32
#define MAXMISSILES				125
#define MAXMONSTERS				200
#define MAXOBJECTS				127
#define MAXPORTAL				4
#ifdef HELLFIRE
#define MAXQUESTS				24
#define MAXMULTIQUESTS			10
#else
#define MAXQUESTS				16
#define MAXMULTIQUESTS			4
#endif
#define MAXTHEMES				50
#define MAXTILES				2048
#ifdef HELLFIRE
#define MAXTRIGGERS				7
#else
#define MAXTRIGGERS				5
#endif
#define MAXVISION				32
#define MDMAXX					40
#define MDMAXY					40
#define MAXCHARLEVEL			51
#ifdef HELLFIRE
#define ITEMTYPES				43
#else
#define ITEMTYPES				35
#endif

// number of inventory grid cells
#define NUM_INV_GRID_ELEM		40
#define INV_SLOT_SIZE_PX		28

// Item indestructible durability
#define DUR_INDESTRUCTIBLE		255

#define VOLUME_MIN				-1600
#define VOLUME_MAX				0

#define NUM_TOWNERS				16

// todo: enums
#ifdef HELLFIRE
#define NUMLEVELS				25
#define BOY_MAX_VALUE			200000
#define WITCH_ITEMS				25
#define WITCH_MAX_VALUE			200000
#define SMITH_ITEMS				25
#define SMITH_PREMIUM_ITEMS		15
#define SMITH_MAX_VALUE			200000
#define SMITH_MAX_PREMIUM_VALUE 200000
#define STORE_LINES				104
#else
#define NUMLEVELS				17
#define BOY_MAX_VALUE			90000
#define WITCH_ITEMS				20
#define WITCH_MAX_VALUE			140000
#define SMITH_ITEMS				20
#define SMITH_PREMIUM_ITEMS		6
#define SMITH_MAX_VALUE			140000
#define SMITH_MAX_PREMIUM_VALUE 140000
#define STORE_LINES				24
#endif

// from diablo 2 beta
#define MAXEXP					2000000000
#define MAXRESIST				75

#define GOLD_SMALL_LIMIT		1000
#define GOLD_MEDIUM_LIMIT		2500
#define GOLD_MAX_LIMIT			5000

#define PLR_NAME_LEN			32

#define MAXPATHNODES			300

#define MAX_PATH_LENGTH			25

// 256 kilobytes + 3 bytes (demo leftover) for file magic (262147)
// final game uses 4-byte magic instead of 3
#define FILEBUFF				((256 * 1024) + 3)

#define PMSG_COUNT				8

// Diablo Retail Version Game ID
#ifdef HELLFIRE
#define GAME_ID					((int)'HRTL')
#define GAME_VERSION			34
#define PROGRAM_NAME			"Hellfire Retail"
#else
#define GAME_ID					((int)'DRTL')
#define GAME_VERSION			42
#define PROGRAM_NAME			"Diablo Retail"
#endif

// Diablo uses a 256 color palette
// Entry 0-127 (0x00-0x7F) are level specific
// Entry 128-255 (0x80-0xFF) are global

// standard palette for all levels
// 8 or 16 shades per color
// example (dark blue): PAL16_BLUE+14, PAL8_BLUE+7
// example (light red): PAL16_RED+2, PAL8_RED
// example (orange): PAL16_ORANGE+8, PAL8_ORANGE+4
#define PAL8_BLUE		128
#define PAL8_RED		136
#define PAL8_YELLOW		144
#define PAL8_ORANGE		152
#define PAL16_BEIGE		160
#define PAL16_BLUE		176
#define PAL16_YELLOW	192
#define PAL16_ORANGE	208
#define PAL16_RED		224
#define PAL16_GRAY		240

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

#define ZOOM_WIDTH		(SCREEN_WIDTH / 2 + TILE_WIDTH)
#define ZOOM_HEIGHT		(VIEWPORT_HEIGHT / 2 + TILE_HEIGHT + TILE_HEIGHT / 2)

// If defined, use 32-bit colors instead of 8-bit [Default -> Undefined]
//#define RGBMODE

#ifndef RGBMODE
#define SCREEN_BPP		8
#else
#define SCREEN_BPP		32
#endif

#define BORDER_LEFT		64
#define BORDER_TOP		160
#define BORDER_RIGHT	64
#define BORDER_BOTTOM	16

#define SCREEN_X		BORDER_LEFT
#define SCREEN_Y		BORDER_TOP

#define BUFFER_WIDTH	(BORDER_LEFT + SCREEN_WIDTH + BORDER_RIGHT)
#define BUFFER_HEIGHT	(BORDER_TOP + SCREEN_HEIGHT + BORDER_BOTTOM)

#define TILE_WIDTH		64
#define TILE_HEIGHT		32

#define PANEL_WIDTH     640
#define PANEL_HEIGHT    128
#define PANEL_TOP		(SCREEN_HEIGHT - PANEL_HEIGHT)
#define PANEL_LEFT		(SCREEN_WIDTH - PANEL_WIDTH) / 2
#define PANEL_X			(SCREEN_X + PANEL_LEFT)
#define PANEL_Y			(SCREEN_Y + PANEL_TOP)

#define SPANEL_WIDTH	 320
#define SPANEL_HEIGHT	 352

#define RIGHT_PANEL		(SCREEN_WIDTH - SPANEL_WIDTH)
#define RIGHT_PANEL_X	(SCREEN_X + RIGHT_PANEL)

#if SCREEN_WIDTH <= PANEL_WIDTH
#define VIEWPORT_HEIGHT	(SCREEN_HEIGHT - PANEL_HEIGHT)
#else
#define VIEWPORT_HEIGHT	SCREEN_HEIGHT
#endif

#define DIALOG_TOP		((SCREEN_HEIGHT - PANEL_HEIGHT) / 2 - 18)
#define DIALOG_Y		(SCREEN_Y + DIALOG_TOP)

#define SCREENXY(x, y) ((x) + SCREEN_X + ((y) + SCREEN_Y) * BUFFER_WIDTH)

#define MemFreeDbg(p)       \
	{                       \
		void *p__p;         \
		p__p = p;           \
		p    = NULL;        \
		mem_free_dbg(p__p); \
	}

#undef assert

#ifndef _DEBUG
#define assert(exp) ((void)(exp))
#else
#define assert(exp) (void)((exp) || (assert_fail(__LINE__, __FILE__, #exp), 0))
#endif

#ifndef INVALID_FILE_ATTRIBUTES
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#endif

// Typedef for the function pointer
typedef void (*_PVFV)(void);

#if defined(_MSC_VER) && !defined(__APPLE__)
// Define our segment names
#define SEGMENT_C_INIT ".CRT$XCU"

// Build our various function tables and insert them into the correct segments.
#pragma data_seg(SEGMENT_C_INIT)
#pragma data_seg() // Switch back to the default segment
// Call function pointer arrays and place them in the segments created above
#define SEG_ALLOCATE(SEGMENT) __declspec(allocate(SEGMENT))
#else
#define SEG_ALLOCATE(SEGMENT)
#endif

// To apply to certain functions which have local variables aligned by 1 for unknown yet reason
#if (_MSC_VER == 1200)
#define ALIGN_BY_1 __declspec(align(1))
#else
#define ALIGN_BY_1
#endif

#if (_MSC_VER == 1200)
#define __FINLINE __forceinline
#else
#define __FINLINE
#endif

#ifndef _BIG_ENDIAN_
#define SwapLE32
#else
#define SwapLE32(value) (value << 24 | (value & 0xFF00) << 8 | (value & 0xFF0000) >> 8 | value >> 24);
#endif
