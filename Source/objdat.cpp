/**
 * @file objdat.cpp
 *
 * Implementation of all object data.
 */
#include "all.h"

/** Maps from dun_object_id to object_id. */
int ObjTypeConv[] = {
	OBJ_L1LIGHT,
	OBJ_LEVER,
	OBJ_CRUX1,
	OBJ_CRUX2,
	OBJ_CRUX3,
	OBJ_ANGEL,
	OBJ_BANNERL,
	OBJ_BANNERM,
	OBJ_BANNERR,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_BOOK2L,
	OBJ_BOOK2R,
	OBJ_BCROSS,
	OBJ_L1LIGHT,
	OBJ_CANDLE1,
	OBJ_CANDLE2,
	OBJ_CANDLEO,
	OBJ_CAULDRON,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_FLAMEHOLE,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_MCIRCLE1,
	OBJ_MCIRCLE2,
	OBJ_SKFIRE,
	OBJ_SKPILE,
	OBJ_SKSTICK1,
	OBJ_SKSTICK2,
	OBJ_SKSTICK3,
	OBJ_SKSTICK4,
	OBJ_SKSTICK5,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_SWITCHSKL,
	OBJ_L1LIGHT,
	OBJ_TRAPL,
	OBJ_TRAPR,
	OBJ_TORTURE1,
	OBJ_TORTURE2,
	OBJ_TORTURE3,
	OBJ_TORTURE4,
	OBJ_TORTURE5,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_NUDEW2R,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_TNUDEM1,
	OBJ_TNUDEM2,
	OBJ_TNUDEM3,
	OBJ_TNUDEM4,
	OBJ_TNUDEW1,
	OBJ_TNUDEW2,
	OBJ_TNUDEW3,
	OBJ_CHEST1,
	OBJ_CHEST1,
	OBJ_CHEST1,
	OBJ_CHEST2,
	OBJ_CHEST2,
	OBJ_CHEST2,
	OBJ_CHEST3,
	OBJ_CHEST3,
	OBJ_CHEST3,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_PEDISTAL,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_ALTBOY,
	OBJ_L1LIGHT,
	OBJ_L1LIGHT,
	OBJ_WARARMOR,
	OBJ_WARWEAP,
	OBJ_TORCHR2,
	OBJ_TORCHL2,
	OBJ_MUSHPATCH,
};

/** Contains the data related to each object ID. */
ObjDataStruct AllObjects[99] = {
	// clang-format off
	// oload, ofindex,   ominlvl, omaxlvl, olvltype,        otheme,                  oquest,     oAnimFlag, oAnimDelay, oAnimLen, oAnimWidth, oSolidFlag, oMissFlag, oLightFlag, oBreak, oSelFlag, oTrapFlag
	{      1, OFILE_L1BRAZ,    1,       4, DTYPE_CATHEDRAL, THEME_NONE,              -1,                 1,          1,       26,         64, TRUE,       TRUE,      FALSE,           0,        0, FALSE     },
	{      1, OFILE_L1DOORS,   1,       4, DTYPE_CATHEDRAL, THEME_NONE,              -1,                 0,          1,        0,         64, FALSE,      FALSE,     TRUE,            0,        3, TRUE      },
	{      1, OFILE_L1DOORS,   1,       4, DTYPE_CATHEDRAL, THEME_NONE,              -1,                 0,          2,        0,         64, FALSE,      FALSE,     TRUE,            0,        3, TRUE      },
	{      3, OFILE_SKULFIRE,  0,       0, DTYPE_TOWN,      THEME_SKELROOM,          -1,                 1,          2,       11,         96, TRUE,       TRUE,      FALSE,           0,        0, FALSE     },
	{      1, OFILE_LEVER,     1,       4, DTYPE_CATHEDRAL, THEME_NONE,              -1,                 0,          1,        1,         96, TRUE,       TRUE,      TRUE,            0,        1, TRUE      },
	{      1, OFILE_CHEST1,    1,      16, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        1, TRUE      },
	{      1, OFILE_CHEST2,    1,      16, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        1, TRUE      },
	{      1, OFILE_CHEST3,    1,      16, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        1, TRUE      },
	{      2, OFILE_L1BRAZ,    0,       0, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          0,        0,          0, FALSE,      FALSE,     FALSE,           0,        0, FALSE     },
	{      3, OFILE_CANDLE2,   0,       0, DTYPE_TOWN,      THEME_SHRINE,            -1,                 1,          2,        4,         96, TRUE,       TRUE,      TRUE,            0,        0, FALSE     },
	{      2, OFILE_L1BRAZ,    0,       0, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          0,        0,          0, FALSE,      FALSE,     FALSE,           0,        0, FALSE     },
	{      3, OFILE_BANNER,    0,       0, DTYPE_TOWN,      THEME_SKELROOM,          -1,                 0,          2,        0,         96, TRUE,       TRUE,      TRUE,            0,        0, FALSE     },
	{      3, OFILE_BANNER,    0,       0, DTYPE_TOWN,      THEME_SKELROOM,          -1,                 0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        0, FALSE     },
	{      3, OFILE_BANNER,    0,       0, DTYPE_TOWN,      THEME_SKELROOM,          -1,                 0,          3,        0,         96, TRUE,       TRUE,      TRUE,            0,        0, FALSE     },
	{      2, OFILE_SKULPILE,  1,       4, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          0,        1,         96, TRUE,       TRUE,      TRUE,            0,        0, FALSE     },
	{      2, OFILE_L1BRAZ,    0,       0, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          0,        0,          0, FALSE,      FALSE,     FALSE,           0,        0, FALSE     },
	{      2, OFILE_L1BRAZ,    0,       0, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          0,        0,          0, FALSE,      FALSE,     FALSE,           0,        0, FALSE     },
	{      2, OFILE_L1BRAZ,    0,       0, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          0,        0,          0, FALSE,      FALSE,     FALSE,           0,        0, FALSE     },
	{      2, OFILE_L1BRAZ,    0,       0, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          0,        0,          0, FALSE,      FALSE,     FALSE,           0,        0, FALSE     },
	{      2, OFILE_L1BRAZ,    0,       0, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          0,        0,          0, FALSE,      FALSE,     FALSE,           0,        0, FALSE     },
	{      2, OFILE_CRUXSK1,   0,       0, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,       15,         96, TRUE,       FALSE,     TRUE,            1,        3, FALSE     },
	{      2, OFILE_CRUXSK2,   0,       0, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,       15,         96, TRUE,       FALSE,     TRUE,            1,        3, FALSE     },
	{      2, OFILE_CRUXSK3,   0,       0, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,       15,         96, TRUE,       FALSE,     TRUE,            1,        3, FALSE     },
	{      1, OFILE_ROCKSTAN,  5,       5, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        0, FALSE     },
	{      2, OFILE_ANGEL,     0,       0, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,        0,         96, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      2, OFILE_BOOK2,     0,       0, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        3, FALSE     },
	{      2, OFILE_BURNCROS,  0,       0, DTYPE_TOWN,      THEME_NONE,              -1,                 1,          0,       10,        160, TRUE,       FALSE,     FALSE,           0,        0, FALSE     },
	{      2, OFILE_NUDE2,     0,       0, DTYPE_TOWN,      THEME_NONE,              -1,                 1,          3,        6,        128, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      1, OFILE_SWITCH4,  16,      16, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        1, TRUE      },
	{      1, OFILE_TNUDEM,   13,      16, DTYPE_TOWN,      THEME_NONE,              Q_BUTCHER,          0,          1,        0,        128, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      1, OFILE_TNUDEM,   13,      16, DTYPE_TOWN,      THEME_TORTURE,           Q_BUTCHER,          0,          2,        0,        128, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      1, OFILE_TNUDEM,   13,      16, DTYPE_TOWN,      THEME_TORTURE,           Q_BUTCHER,          0,          3,        0,        128, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      1, OFILE_TNUDEM,   13,      16, DTYPE_TOWN,      THEME_TORTURE,           Q_BUTCHER,          0,          4,        0,        128, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      1, OFILE_TNUDEW,   13,      16, DTYPE_TOWN,      THEME_TORTURE,           Q_BUTCHER,          0,          1,        0,        128, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      1, OFILE_TNUDEW,   13,      16, DTYPE_TOWN,      THEME_TORTURE,           Q_BUTCHER,          0,          2,        0,        128, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      1, OFILE_TNUDEW,   13,      16, DTYPE_TOWN,      THEME_TORTURE,           Q_BUTCHER,          0,          3,        0,        128, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      1, OFILE_TSOUL,    13,      16, DTYPE_TOWN,      THEME_NONE,              Q_BUTCHER,          0,          1,        0,        128, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      1, OFILE_TSOUL,    13,      16, DTYPE_TOWN,      THEME_NONE,              Q_BUTCHER,          0,          2,        0,        128, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      1, OFILE_TSOUL,    13,      16, DTYPE_TOWN,      THEME_NONE,              Q_BUTCHER,          0,          3,        0,        128, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      1, OFILE_TSOUL,    13,      16, DTYPE_TOWN,      THEME_NONE,              Q_BUTCHER,          0,          4,        0,        128, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      1, OFILE_TSOUL,    13,      16, DTYPE_TOWN,      THEME_NONE,              Q_BUTCHER,          0,          5,        0,        128, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      1, OFILE_BOOK2,     6,       6, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          4,        0,         96, TRUE,       TRUE,      TRUE,            0,        3, FALSE     },
	{      1, OFILE_L2DOORS,   5,       8, DTYPE_CATACOMBS, THEME_NONE,              -1,                 0,          1,        0,         64, FALSE,      FALSE,     TRUE,            0,        3, TRUE      },
	{      1, OFILE_L2DOORS,   5,       8, DTYPE_CATACOMBS, THEME_NONE,              -1,                 0,          2,        0,         64, FALSE,      FALSE,     TRUE,            0,        3, FALSE     },
	{      1, OFILE_WTORCH4,   5,       8, DTYPE_CATACOMBS, THEME_NONE,              -1,                 1,          1,        9,         96, FALSE,      TRUE,      FALSE,           0,        0, FALSE     },
	{      1, OFILE_WTORCH3,   5,       8, DTYPE_CATACOMBS, THEME_NONE,              -1,                 1,          1,        9,         96, FALSE,      TRUE,      FALSE,           0,        0, FALSE     },
	{      1, OFILE_WTORCH1,   5,       8, DTYPE_CATACOMBS, THEME_NONE,              -1,                 1,          1,        9,         96, FALSE,      TRUE,      FALSE,           0,        0, FALSE     },
	{      1, OFILE_WTORCH2,   5,       8, DTYPE_CATACOMBS, THEME_NONE,              -1,                 1,          1,        9,         96, FALSE,      TRUE,      FALSE,           0,        0, FALSE     },
	{      1, OFILE_SARC,      1,       4, DTYPE_CATHEDRAL, THEME_NONE,              -1,                 0,          1,        5,        128, TRUE,       TRUE,      TRUE,            0,        3, TRUE      },
	{      2, OFILE_FLAME1,    1,       4, DTYPE_CATHEDRAL, THEME_NONE,              -1,                 0,          1,       20,         96, FALSE,      TRUE,      TRUE,            0,        0, FALSE     },
	{      2, OFILE_LEVER,     1,       4, DTYPE_CATHEDRAL, THEME_NONE,              -1,                 0,          1,        2,         96, TRUE,       TRUE,      TRUE,            0,        1, TRUE      },
	{      2, OFILE_MINIWATR,  1,       4, DTYPE_CATHEDRAL, THEME_NONE,              -1,                 1,          1,       10,         64, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      1, OFILE_BOOK1,     3,       4, DTYPE_CATHEDRAL, THEME_NONE,              -1,                 0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        3, FALSE     },
	{      1, OFILE_TRAPHOLE,  1,      16, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,        0,         64, FALSE,      TRUE,      TRUE,            0,        0, FALSE     },
	{      1, OFILE_TRAPHOLE,  1,      16, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          2,        0,         64, FALSE,      TRUE,      TRUE,            0,        0, FALSE     },
	{      2, OFILE_BCASE,     0,       0, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,        0,         96, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      2, OFILE_WEAPSTND,  0,       0, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,        0,         96, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      1, OFILE_BARREL,    1,      16, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,        9,         96, TRUE,       TRUE,      TRUE,            1,        3, FALSE     },
	{      1, OFILE_BARRELEX,  1,      16, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,       10,         96, TRUE,       TRUE,      TRUE,            1,        3, FALSE     },
	{      3, OFILE_LSHRINEG,  0,       0, DTYPE_TOWN,      THEME_SHRINE,            -1,                 0,          1,       11,        128, FALSE,      FALSE,     TRUE,            0,        3, FALSE     },
	{      3, OFILE_RSHRINEG,  0,       0, DTYPE_TOWN,      THEME_SHRINE,            -1,                 0,          1,       11,        128, FALSE,      FALSE,     TRUE,            0,        3, FALSE     },
	{      3, OFILE_BOOK2,     0,       0, DTYPE_TOWN,      THEME_SKELROOM,          -1,                 0,          4,        0,         96, TRUE,       TRUE,      TRUE,            0,        3, FALSE     },
	{      3, OFILE_BCASE,     0,       0, DTYPE_TOWN,      THEME_LIBRARY,           -1,                 0,          3,        0,         96, FALSE,      FALSE,     TRUE,            0,        3, FALSE     },
	{      3, OFILE_BCASE,     0,       0, DTYPE_TOWN,      THEME_LIBRARY,           -1,                 0,          4,        0,         96, FALSE,      FALSE,     TRUE,            0,        3, FALSE     },
	{      3, OFILE_BOOK2,     0,       0, DTYPE_TOWN,      THEME_LIBRARY,           -1,                 0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        3, FALSE     },
	{      3, OFILE_CANDLE2,   0,       0, DTYPE_TOWN,      THEME_LIBRARY,           -1,                 1,          2,        4,         96, TRUE,       TRUE,      TRUE,            0,        0, FALSE     },
	{      3, OFILE_BLOODFNT,  0,       0, DTYPE_TOWN,      THEME_BLOODFOUNTAIN,     -1,                 1,          2,       10,         96, TRUE,       TRUE,      TRUE,            0,        3, FALSE     },
	{      1, OFILE_DECAP,    13,      16, DTYPE_TOWN,      THEME_DECAPITATED,       -1,                 0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        1, FALSE     },
	{      1, OFILE_CHEST1,    1,      16, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        1, TRUE      },
	{      1, OFILE_CHEST2,    1,      16, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        1, TRUE      },
	{      1, OFILE_CHEST3,    1,      16, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        1, TRUE      },
	{      1, OFILE_BOOK1,     7,       7, DTYPE_CATACOMBS, THEME_NONE,              Q_BLIND,            0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        3, FALSE     },
	{      1, OFILE_BOOK1,     5,       5, DTYPE_CATACOMBS, THEME_NONE,              Q_BLOOD,            0,          4,        0,         96, TRUE,       TRUE,      TRUE,            0,        3, FALSE     },
	{      1, OFILE_PEDISTL,   5,       5, DTYPE_CATACOMBS, THEME_NONE,              Q_BLOOD,            0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        3, FALSE     },
	{      1, OFILE_L3DOORS,   9,      12, DTYPE_CAVES,     THEME_NONE,              -1,                 0,          1,        0,         64, FALSE,      FALSE,     TRUE,            0,        3, TRUE      },
	{      1, OFILE_L3DOORS,   9,      12, DTYPE_CAVES,     THEME_NONE,              -1,                 0,          2,        0,         64, FALSE,      FALSE,     TRUE,            0,        3, TRUE      },
	{      3, OFILE_PFOUNTN,   0,       0, DTYPE_TOWN,      THEME_PURIFYINGFOUNTAIN, -1,                 1,          2,       10,        128, TRUE,       TRUE,      TRUE,            0,        3, FALSE     },
	{      3, OFILE_ARMSTAND,  0,       0, DTYPE_TOWN,      THEME_ARMORSTAND,        -1,                 0,          1,        0,         96, TRUE,       FALSE,     TRUE,            0,        3, FALSE     },
	{      3, OFILE_ARMSTAND,  0,       0, DTYPE_TOWN,      THEME_ARMORSTAND,        -1,                 0,          2,        0,         96, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      3, OFILE_GOATSHRN,  0,       0, DTYPE_TOWN,      THEME_GOATSHRINE,        -1,                 1,          2,       10,         96, TRUE,       TRUE,      TRUE,            0,        3, FALSE     },
	{      1, OFILE_CAULDREN, 13,      16, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,        0,         96, TRUE,       FALSE,     TRUE,            0,        3, FALSE     },
	{      3, OFILE_MFOUNTN,   0,       0, DTYPE_TOWN,      THEME_MURKYFOUNTAIN,     -1,                 1,          2,       10,        128, TRUE,       TRUE,      TRUE,            0,        3, FALSE     },
	{      3, OFILE_TFOUNTN,   0,       0, DTYPE_TOWN,      THEME_TEARFOUNTAIN,      -1,                 1,          2,        4,        128, TRUE,       TRUE,      TRUE,            0,        3, FALSE     },
	{      1, OFILE_ALTBOY,    0,       0, DTYPE_CATHEDRAL, THEME_NONE,              Q_BETRAYER,         0,          1,        0,        128, TRUE,       TRUE,      TRUE,            0,        0, FALSE     },
	{      1, OFILE_MCIRL,     0,       0, DTYPE_CATHEDRAL, THEME_NONE,              Q_BETRAYER,         0,          1,        0,         96, FALSE,      TRUE,      TRUE,            0,        0, FALSE     },
	{      1, OFILE_MCIRL,     0,       0, DTYPE_CATHEDRAL, THEME_NONE,              Q_BETRAYER,         0,          1,        0,         96, FALSE,      TRUE,      TRUE,            0,        0, FALSE     },
	{      1, OFILE_BKSLBRNT,  4,      12, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        3, FALSE     },
	{      1, OFILE_CANDLE2,   2,      12, DTYPE_TOWN,      THEME_NONE,              Q_BETRAYER,         1,          2,        4,         96, TRUE,       TRUE,      TRUE,            0,        0, FALSE     },
	{      1, OFILE_BOOK1,    13,      13, DTYPE_HELL,      THEME_NONE,              Q_WARLORD,          0,          4,        0,         96, TRUE,       TRUE,      TRUE,            0,        3, FALSE     },
	{      1, OFILE_ARMSTAND, 13,      13, DTYPE_TOWN,      THEME_NONE,              Q_WARLORD,          0,          1,        0,         96, TRUE,       FALSE,     TRUE,            0,        3, FALSE     },
	{      2, OFILE_WEAPSTND, 13,      13, DTYPE_TOWN,      THEME_NONE,              Q_WARLORD,          0,          1,        0,         96, TRUE,       FALSE,     TRUE,            0,        3, FALSE     },
	{      2, OFILE_BURNCROS,  0,       0, DTYPE_TOWN,      THEME_BRNCROSS,          -1,                 1,          0,       10,        160, TRUE,       FALSE,     FALSE,           0,        0, FALSE     },
	{      2, OFILE_WEAPSTND,  0,       0, DTYPE_TOWN,      THEME_WEAPONRACK,        -1,                 0,          1,        0,         96, TRUE,       FALSE,     TRUE,            0,        3, FALSE     },
	{      2, OFILE_WEAPSTND,  0,       0, DTYPE_TOWN,      THEME_WEAPONRACK,        -1,                 0,          2,        0,         96, TRUE,       FALSE,     TRUE,            0,        0, FALSE     },
	{      2, OFILE_MUSHPTCH,  0,       0, DTYPE_TOWN,      THEME_NONE,              Q_MUSHROOM,         0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        3, TRUE      },
	{      2, OFILE_LZSTAND,   0,       0, DTYPE_TOWN,      THEME_NONE,              Q_BETRAYER,         0,          1,        0,        128, TRUE,       FALSE,     TRUE,            0,        3, FALSE     },
	{      1, OFILE_DECAP,     9,       9, DTYPE_CAVES,     THEME_NONE,              -1,                 0,          2,        0,         96, TRUE,       TRUE,      TRUE,            0,        1, FALSE     },
	{      2, OFILE_CHEST3,    0,       0, DTYPE_TOWN,      THEME_NONE,              -1,                 0,          1,        0,         96, TRUE,       TRUE,      TRUE,            0,        1, TRUE      },
	{     -1, 0,               0,       0, -1,              THEME_NONE,              -1,                 0,          0,        0,          0, FALSE,      FALSE,     FALSE,           0,        0, FALSE     }
	// clang-format on
};

/** Maps from object_graphic_id to object CEL name. */
char *ObjMasterLoadList[56] = { // might be const
	"L1Braz",
	"L1Doors",
	"Lever",
	"Chest1",
	"Chest2",
	"Banner",
	"SkulPile",
	"SkulFire",
	"SkulStik",
	"CruxSk1",
	"CruxSk2",
	"CruxSk3",
	"Book1",
	"Book2",
	"Rockstan",
	"Angel",
	"Chest3",
	"Burncros",
	"Candle2",
	"Nude2",
	"Switch4",
	"TNudeM",
	"TNudeW",
	"TSoul",
	"L2Doors",
	"WTorch4",
	"WTorch3",
	"Sarc",
	"Flame1",
	"Prsrplt1",
	"Traphole",
	"MiniWatr",
	"WTorch2",
	"WTorch1",
	"BCase",
	"BShelf",
	"WeapStnd",
	"Barrel",
	"Barrelex",
	"LShrineG",
	"RShrineG",
	"Bloodfnt",
	"Decap",
	"Pedistl",
	"L3Doors",
	"PFountn",
	"Armstand",
	"Goatshrn",
	"Cauldren",
	"MFountn",
	"TFountn",
	"Altboy",
	"Mcirl",
	"Bkslbrnt",
	"Mushptch",
	"LzStand"
};
