//HEADER_GOES_HERE

#include "../types.h"

// BUGFIX: only the first 256 elements are ever read
USHORT automaptype[512];
static int MapX;
static int MapY;
BOOL automapflag; // idb
char AMbyte_4B7E4C[32];
unsigned char automapview[DMAXX][DMAXY];
int AutoMapScale;   // idb
int AutoMapXOfs;    // weak
int AutoMapYOfs;    // weak
int AutoMapPosBits; // weak
int AutoMapXPos;    // weak
int AutoMapYPos;    // weak
int AMPlayerX;      // weak
int AMPlayerY;      // weak

// color used to draw the player's arrow
#define COLOR_PLAYER (PAL8_ORANGE + 1)
// color for bright map lines (doors, stairs etc.)
#define COLOR_BRIGHT PAL8_YELLOW
// color for dim map lines/dots
#define COLOR_DIM (PAL16_YELLOW + 8)

#define MAPFLAG_TYPE 0x000F
// these are in the second byte
#define MAPFLAG_VERTDOOR 0x01
#define MAPFLAG_HORZDOOR 0x02
#define MAPFLAG_VERTARCH 0x04
#define MAPFLAG_HORZARCH 0x08
#define MAPFLAG_VERTGRATE 0x10
#define MAPFLAG_HORZGRATE 0x20
#define MAPFLAG_SQUARE 0x40
#define MAPFLAG_STAIRS 0x80

void __cdecl InitAutomapOnce()
{
    automapflag = FALSE;
    AutoMapScale = 50;
    AutoMapPosBits = 32;
    AutoMapXPos = 16;
    AutoMapYPos = 8;
    AMPlayerX = 4;
    AMPlayerY = 2;
}

void __cdecl InitAutomap()
{
    signed int v0;     // edi
    signed int v1;     // ecx
    int v2;            // esi
    char v3;           // al
    int v4;            // esi
    char v5;           // al
    char *v6;          // ecx
    unsigned char *v7; // eax
    int v8;            // ecx
    unsigned char *v9; // edx
    unsigned int i;    // esi
    unsigned char v11; // bl
    _BYTE *v12;        // edx
    signed int v13;    // ecx
    _BYTE *v14;        // eax
    signed int v15;    // edx
    int size;          // [esp+Ch] [ebp-4h]

    v0 = 50;
    v1 = 0;
    do {
        v2 = (v0 << 6) / 100;
        v3 = 2 * (320 / v2);
        v4 = 320 % v2;
        v5 = v3 + 1;
        AMbyte_4B7E4C[v1] = v5;
        if (v4)
            AMbyte_4B7E4C[v1] = v5 + 1;
        if (v4 >= 32 * v0 / 100)
            ++AMbyte_4B7E4C[v1];
        v0 += 5;
        ++v1;
    } while (v1 < 31);
    memset(automaptype, 0, sizeof(automaptype));
    switch (leveltype) {
    case DTYPE_CATHEDRAL:
        v6 = "Levels\\L1Data\\L1.AMP";
        break;
    case DTYPE_CATACOMBS:
        v6 = "Levels\\L2Data\\L2.AMP";
        break;
    case DTYPE_CAVES:
        v6 = "Levels\\L3Data\\L3.AMP";
        break;
    case DTYPE_HELL:
        v6 = "Levels\\L4Data\\L4.AMP";
        break;
    default:
        return;
    }
    v7 = LoadFileInMem(v6, &size);
    size = (unsigned int)size >> 1;
    v9 = v7;
    for (i = 1; i <= size; ++i) {
        v11 = *v9;
        v12 = v9 + 1;
        _LOWORD(v0) = v11;
        _LOBYTE(v8) = *v12;
        v9 = v12 + 1;
        _LOWORD(v8) = (unsigned char)v8;
        v8 = v0 + (v8 << 8);
        automaptype[i] = v8;
    }
    mem_free_dbg(v7);
    memset(automapview, 0, sizeof(automapview));
    v13 = 0;
    do {
        v14 = (unsigned char *)dFlags + v13;
        v15 = 112;
        do {
            *v14 &= ~DFLAG_EXPLORED;
            v14 += 112;
            --v15;
        } while (v15);
        ++v13;
    } while (v13 < 112);
}
// 5BB1ED: using guessed type char leveltype;

void __cdecl StartAutomap()
{
    AutoMapXOfs = 0;
    AutoMapYOfs = 0;
    automapflag = TRUE;
}

void __cdecl AutomapUp()
{
    --AutoMapXOfs;
    --AutoMapYOfs;
}

void __cdecl AutomapDown()
{
    ++AutoMapXOfs;
    ++AutoMapYOfs;
}

void __cdecl AutomapLeft()
{
    --AutoMapXOfs;
    ++AutoMapYOfs;
}

void __cdecl AutomapRight()
{
    ++AutoMapXOfs;
    --AutoMapYOfs;
}

void __cdecl AutomapZoomIn()
{
    if (AutoMapScale < 200) {
        AutoMapScale += 5;
        AutoMapPosBits = (AutoMapScale << 6) / 100;
        AutoMapXPos = AutoMapPosBits >> 1;
        AutoMapYPos = AutoMapXPos >> 1;
        AMPlayerX = AutoMapYPos >> 1;
        AMPlayerY = AMPlayerX >> 1;
    }
}

void __cdecl AutomapZoomOut()
{
    if (AutoMapScale > 50) {
        AutoMapScale -= 5;
        AutoMapPosBits = (AutoMapScale << 6) / 100;
        AutoMapXPos = AutoMapPosBits >> 1;
        AutoMapYPos = AutoMapXPos >> 1;
        AMPlayerX = AutoMapYPos >> 1;
        AMPlayerY = AMPlayerX >> 1;
    }
}

void __cdecl DrawAutomap()
{
    int cells;
    int screen_x;
    int screen_y;
    int i, j;
    int mapx, mapy;

    if (leveltype == DTYPE_TOWN) {
        DrawAutomapGame();
        return;
    }

    gpBufEnd = (unsigned char *)&gpBuffer->row[352];

    MapX = (ViewX - 16) >> 1;
    while (MapX + AutoMapXOfs < 0)
        AutoMapXOfs++;
    while (MapX + AutoMapXOfs >= DMAXX)
        AutoMapXOfs--;
    MapX += AutoMapXOfs;

    MapY = (ViewY - 16) >> 1;
    while (MapY + AutoMapYOfs < 0)
        AutoMapYOfs++;
    while (MapY + AutoMapYOfs >= DMAXY)
        AutoMapYOfs--;
    MapY += AutoMapYOfs;

    cells = AMbyte_4B7E4C[(AutoMapScale - 50) / 5];
    if (ScrollInfo._sxoff + ScrollInfo._syoff)
        cells++;
    mapx = MapX - cells;
    mapy = MapY - 1;

    if (cells & 1) {
        screen_x = 384 - AutoMapPosBits * ((cells - 1) >> 1);
        screen_y = 336 - AutoMapXPos * ((cells + 1) >> 1);
    } else {
        screen_x = 384 - AutoMapPosBits * (cells >> 1) + AutoMapXPos;
        screen_y = 336 - AutoMapXPos * (cells >> 1) - AutoMapYPos;
    }
    if (ViewX & 1) {
        screen_x -= AutoMapYPos;
        screen_y -= AMPlayerX;
    }
    if (ViewY & 1) {
        screen_x += AutoMapYPos;
        screen_y -= AMPlayerX;
    }

    screen_x += AutoMapScale * ScrollInfo._sxoff / 100 >> 1;
    screen_y += AutoMapScale * ScrollInfo._syoff / 100 >> 1;
    if (invflag || sbookflag) {
        screen_x -= 160;
    }
    if (chrflag || questlog) {
        screen_x += 160;
    }

    for (i = 0; i <= cells + 1; i++) {
        int x = screen_x;
        int y;

        for (j = 0; j < cells; j++) {
            USHORT maptype = GetAutomapType(mapx + j, mapy - j, TRUE);
            if (maptype)
                DrawAutomapType(x, screen_y, maptype);
            x += AutoMapPosBits;
        }
        mapy++;
        x = screen_x - AutoMapXPos;
        y = screen_y + AutoMapYPos;
        for (j = 0; j <= cells; j++) {
            USHORT maptype = GetAutomapType(mapx + j, mapy - j, TRUE);
            if (maptype)
                DrawAutomapType(x, y, maptype);
            x += AutoMapPosBits;
        }
        mapx++;
        screen_y += AutoMapXPos;
    }
    DrawAutomapPlr();
    DrawAutomapGame();
}
// 4B8968: using guessed type int sbookflag;
// 5BB1ED: using guessed type char leveltype;
// 69BD04: using guessed type int questlog;
// 69CF0C: using guessed type int gpBufEnd;

void __fastcall DrawAutomapType(int screen_x, int screen_y, USHORT automap_type)
{
    BOOL do_vert;
    BOOL do_horz;
    BOOL do_cave_horz;
    BOOL do_cave_vert;
    int x1, y1, x2, y2;

    UCHAR flags = automap_type >> 8;

    if (flags & MAPFLAG_SQUARE) {
        ENG_set_pixel(screen_x, screen_y, COLOR_DIM);
        ENG_set_pixel(screen_x - AMPlayerX, screen_y - AMPlayerY, COLOR_DIM);
        ENG_set_pixel(screen_x - AMPlayerX, screen_y + AMPlayerY, COLOR_DIM);
        ENG_set_pixel(screen_x + AMPlayerX, screen_y - AMPlayerY, COLOR_DIM);
        ENG_set_pixel(screen_x + AMPlayerX, screen_y + AMPlayerY, COLOR_DIM);
        ENG_set_pixel(screen_x - AutoMapYPos, screen_y, COLOR_DIM);
        ENG_set_pixel(screen_x + AutoMapYPos, screen_y, COLOR_DIM);
        ENG_set_pixel(screen_x, screen_y - AMPlayerX, COLOR_DIM);
        ENG_set_pixel(screen_x, screen_y + AMPlayerX, COLOR_DIM);
        ENG_set_pixel(screen_x + AMPlayerX - AutoMapXPos, screen_y + AMPlayerY, COLOR_DIM);
        ENG_set_pixel(screen_x - AMPlayerX + AutoMapXPos, screen_y + AMPlayerY, COLOR_DIM);
        ENG_set_pixel(screen_x - AutoMapYPos, screen_y + AMPlayerX, COLOR_DIM);
        ENG_set_pixel(screen_x + AutoMapYPos, screen_y + AMPlayerX, COLOR_DIM);
        ENG_set_pixel(screen_x - AMPlayerX, screen_y + AutoMapYPos - AMPlayerY, COLOR_DIM);
        ENG_set_pixel(screen_x + AMPlayerX, screen_y + AutoMapYPos - AMPlayerY, COLOR_DIM);
        ENG_set_pixel(screen_x, screen_y + AutoMapYPos, COLOR_DIM);
    }

    if (flags & MAPFLAG_STAIRS) {
        DrawLine(screen_x - AMPlayerX, screen_y - AMPlayerX - AMPlayerY, screen_x + AMPlayerX + AutoMapYPos, screen_y + AMPlayerY, COLOR_BRIGHT);
        DrawLine(screen_x - AutoMapYPos, screen_y - AMPlayerX, screen_x + AutoMapYPos, screen_y + AMPlayerX, COLOR_BRIGHT);
        DrawLine(screen_x - AutoMapYPos - AMPlayerX, screen_y - AMPlayerY, screen_x + AMPlayerX, screen_y + AMPlayerX + AMPlayerY, COLOR_BRIGHT);
        DrawLine(screen_x - AutoMapXPos, screen_y, screen_x, screen_y + AutoMapYPos, COLOR_BRIGHT);
    }

    do_vert = FALSE;
    do_horz = FALSE;
    do_cave_horz = FALSE;
    do_cave_vert = FALSE;
    switch (automap_type & MAPFLAG_TYPE) {
    case 1: // stand-alone column or other unpassable object
        x1 = screen_x - AutoMapYPos;
        y1 = screen_y - AutoMapYPos;
        x2 = x1 + AutoMapXPos;
        y2 = screen_y - AMPlayerX;
        DrawLine(screen_x, y1, x1, y2, COLOR_DIM);
        DrawLine(screen_x, y1, x2, y2, COLOR_DIM);
        DrawLine(screen_x, screen_y, x1, y2, COLOR_DIM);
        DrawLine(screen_x, screen_y, x2, y2, COLOR_DIM);
        return;
    case 2:
    case 5:
        do_vert = TRUE;
        break;
    case 4:
        do_vert = TRUE;
        do_horz = TRUE;
        break;
    case 3:
    case 6:
        do_horz = TRUE;
        break;
    case 8:
        do_vert = TRUE;
        do_cave_horz = TRUE;
        break;
    case 9:
        do_horz = TRUE;
        do_cave_vert = TRUE;
        break;
    case 10:
        do_cave_horz = TRUE;
        break;
    case 11:
        do_cave_vert = TRUE;
        break;
    case 12:
        do_cave_horz = TRUE;
        do_cave_vert = TRUE;
        break;
    }

    if (do_vert) {                      // right-facing obstacle
        if (flags & MAPFLAG_VERTDOOR) { // two wall segments with a door in the middle
            x1 = screen_x - AutoMapXPos;
            x2 = screen_x - AutoMapYPos;
            y1 = screen_y - AutoMapYPos;
            y2 = screen_y - AMPlayerX;

            DrawLine(screen_x, y1, screen_x - AMPlayerX, y1 + AMPlayerY, COLOR_DIM);
            DrawLine(x1, screen_y, x1 + AMPlayerX, screen_y - AMPlayerY, COLOR_DIM);
            DrawLine(x2, y1, x1, y2, COLOR_BRIGHT);
            DrawLine(x2, y1, screen_x, y2, COLOR_BRIGHT);
            DrawLine(x2, screen_y, x1, y2, COLOR_BRIGHT);
            DrawLine(x2, screen_y, screen_x, y2, COLOR_BRIGHT);
        }
        if (flags & MAPFLAG_VERTGRATE) { // right-facing half-wall
            DrawLine(screen_x - AutoMapYPos, screen_y - AMPlayerX, screen_x - AutoMapXPos, screen_y, COLOR_DIM);
            flags |= MAPFLAG_VERTARCH;
        }
        if (flags & MAPFLAG_VERTARCH) { // window or passable column
            x1 = screen_x - AutoMapYPos;
            y1 = screen_y - AutoMapYPos;
            x2 = x1 + AutoMapXPos;
            y2 = screen_y - AMPlayerX;

            DrawLine(screen_x, y1, x1, y2, COLOR_DIM);
            DrawLine(screen_x, y1, x2, y2, COLOR_DIM);
            DrawLine(screen_x, screen_y, x1, y2, COLOR_DIM);
            DrawLine(screen_x, screen_y, x2, y2, COLOR_DIM);
        }
        if (!(flags & (MAPFLAG_VERTDOOR | MAPFLAG_VERTGRATE | MAPFLAG_VERTARCH)))
            DrawLine(screen_x, screen_y - AutoMapYPos, screen_x - AutoMapXPos, screen_y, COLOR_DIM);
    }

    if (do_horz) { // left-facing obstacle
        if (flags & MAPFLAG_HORZDOOR) {
            x1 = screen_x + AutoMapYPos;
            x2 = screen_x + AutoMapXPos;
            y1 = screen_y - AutoMapYPos;
            y2 = screen_y - AMPlayerX;

            DrawLine(screen_x, y1, screen_x + AMPlayerX, y1 + AMPlayerY, COLOR_DIM);
            DrawLine(x2, screen_y, x2 - AMPlayerX, screen_y - AMPlayerY, COLOR_DIM);
            DrawLine(x1, y1, screen_x, y2, COLOR_BRIGHT);
            DrawLine(x1, y1, x2, y2, COLOR_BRIGHT);
            DrawLine(x1, screen_y, screen_x, y2, COLOR_BRIGHT);
            DrawLine(x1, screen_y, x2, y2, COLOR_BRIGHT);
        }
        if (flags & MAPFLAG_HORZGRATE) {
            DrawLine(screen_x + AutoMapYPos, screen_y - AMPlayerX, screen_x + AutoMapXPos, screen_y, COLOR_DIM);
            flags |= MAPFLAG_HORZARCH;
        }
        if (flags & MAPFLAG_HORZARCH) {
            x1 = screen_x - AutoMapYPos;
            y1 = screen_y - AutoMapYPos;
            x2 = x1 + AutoMapXPos;
            y2 = screen_y - AMPlayerX;

            DrawLine(screen_x, y1, x1, y2, COLOR_DIM);
            DrawLine(screen_x, y1, x2, y2, COLOR_DIM);
            DrawLine(screen_x, screen_y, x1, y2, COLOR_DIM);
            DrawLine(screen_x, screen_y, x2, y2, COLOR_DIM);
        }
        if (!(flags & (MAPFLAG_HORZDOOR | MAPFLAG_HORZGRATE | MAPFLAG_HORZARCH)))
            DrawLine(screen_x, screen_y - AutoMapYPos, screen_x + AutoMapXPos, screen_y, COLOR_DIM);
    }

    // for caves the horz/vert flags are switched
    if (do_cave_horz) {
        if (flags & MAPFLAG_VERTDOOR) {
            x1 = screen_x - AutoMapXPos;
            x2 = screen_x - AutoMapYPos;
            y1 = screen_y + AutoMapYPos;
            y2 = screen_y + AMPlayerX;

            DrawLine(screen_x, y1, screen_x - AMPlayerX, y1 - AMPlayerY, COLOR_DIM);
            DrawLine(x1, screen_y, x1 + AMPlayerX, screen_y + AMPlayerY, COLOR_DIM);
            DrawLine(x2, y1, x1, y2, COLOR_BRIGHT);
            DrawLine(x2, y1, screen_x, y2, COLOR_BRIGHT);
            DrawLine(x2, screen_y, x1, y2, COLOR_BRIGHT);
            DrawLine(x2, screen_y, screen_x, y2, COLOR_BRIGHT);
        } else
            DrawLine(screen_x, screen_y + AutoMapYPos, screen_x - AutoMapXPos, screen_y, COLOR_DIM);
    }

    if (do_cave_vert) {
        if (flags & MAPFLAG_HORZDOOR) {
            x1 = screen_x + AutoMapYPos;
            x2 = screen_x + AutoMapXPos;
            y1 = screen_y + AutoMapYPos;
            y2 = screen_y + AMPlayerX;

            DrawLine(screen_x, y1, screen_x + AMPlayerX, y1 - AMPlayerY, COLOR_DIM);
            DrawLine(x2, screen_y, x2 - AMPlayerX, screen_y + AMPlayerY, COLOR_DIM);
            DrawLine(x1, y1, screen_x, y2, COLOR_BRIGHT);
            DrawLine(x1, y1, x2, y2, COLOR_BRIGHT);
            DrawLine(x1, screen_y, screen_x, y2, COLOR_BRIGHT);
            DrawLine(x1, screen_y, x2, y2, COLOR_BRIGHT);
        } else
            DrawLine(screen_x, screen_y + AutoMapYPos, screen_x + AutoMapXPos, screen_y, COLOR_DIM);
    }
}

void __cdecl DrawAutomapPlr()
{
    int posx, posy;
    int x, y;

    if (plr[myplr]._pmode == PM_WALK3) {
        x = plr[myplr]._px;
        y = plr[myplr]._py;
        if (plr[myplr]._pdir == DIR_W)
            x++;
        else
            y++;
    } else {
        x = plr[myplr].WorldX;
        y = plr[myplr].WorldY;
    }
    posx = x - 2 * AutoMapXOfs - ViewX;
    posy = y - 2 * AutoMapYOfs - ViewY;

    x = (plr[myplr]._pxoff * AutoMapScale / 100 >> 1) + (ScrollInfo._sxoff * AutoMapScale / 100 >> 1) + (posx - posy) * AutoMapYPos + 384;
    y = (plr[myplr]._pyoff * AutoMapScale / 100 >> 1) + (ScrollInfo._syoff * AutoMapScale / 100 >> 1) + (posx + posy) * AMPlayerX + 336;

    if (invflag || sbookflag)
        x -= 160;
    if (chrflag || questlog)
        x += 160;
    y -= AMPlayerX;

    switch (plr[myplr]._pdir) {
    case DIR_N:
        DrawLine(x, y, x, y - AutoMapYPos, COLOR_PLAYER);
        DrawLine(x, y - AutoMapYPos, x - AMPlayerY, y - AMPlayerX, COLOR_PLAYER);
        DrawLine(x, y - AutoMapYPos, x + AMPlayerY, y - AMPlayerX, COLOR_PLAYER);
        break;
    case DIR_NE:
        DrawLine(x, y, x + AutoMapYPos, y - AMPlayerX, COLOR_PLAYER);
        DrawLine(x + AutoMapYPos, y - AMPlayerX, x + AMPlayerX, y - AMPlayerX, COLOR_PLAYER);
        DrawLine(x + AutoMapYPos, y - AMPlayerX, x + AMPlayerX + AMPlayerY, y, COLOR_PLAYER);
        break;
    case DIR_E:
        DrawLine(x, y, x + AutoMapYPos, y, COLOR_PLAYER);
        DrawLine(x + AutoMapYPos, y, x + AMPlayerX, y - AMPlayerY, COLOR_PLAYER);
        DrawLine(x + AutoMapYPos, y, x + AMPlayerX, y + AMPlayerY, COLOR_PLAYER);
        break;
    case DIR_SE:
        DrawLine(x, y, x + AutoMapYPos, y + AMPlayerX, COLOR_PLAYER);
        DrawLine(x + AutoMapYPos, y + AMPlayerX, x + AMPlayerX + AMPlayerY, y, COLOR_PLAYER);
        DrawLine(x + AutoMapYPos, y + AMPlayerX, x + AMPlayerX, y + AMPlayerX, COLOR_PLAYER);
        break;
    case DIR_S:
        DrawLine(x, y, x, y + AutoMapYPos, COLOR_PLAYER);
        DrawLine(x, y + AutoMapYPos, x + AMPlayerY, y + AMPlayerX, COLOR_PLAYER);
        DrawLine(x, y + AutoMapYPos, x - AMPlayerY, y + AMPlayerX, COLOR_PLAYER);
        break;
    case DIR_SW:
        DrawLine(x, y, x - AutoMapYPos, y + AMPlayerX, COLOR_PLAYER);
        DrawLine(x - AutoMapYPos, y + AMPlayerX, x - AMPlayerY - AMPlayerX, y, COLOR_PLAYER);
        DrawLine(x - AutoMapYPos, y + AMPlayerX, x - AMPlayerX, y + AMPlayerX, COLOR_PLAYER);
        break;
    case DIR_W:
        DrawLine(x, y, x - AutoMapYPos, y, COLOR_PLAYER);
        DrawLine(x - AutoMapYPos, y, x - AMPlayerX, y - AMPlayerY, COLOR_PLAYER);
        DrawLine(x - AutoMapYPos, y, x - AMPlayerX, y + AMPlayerY, COLOR_PLAYER);
        break;
    case DIR_NW:
        DrawLine(x, y, x - AutoMapYPos, y - AMPlayerX, COLOR_PLAYER);
        DrawLine(x - AutoMapYPos, y - AMPlayerX, x - AMPlayerX, y - AMPlayerX, COLOR_PLAYER);
        DrawLine(x - AutoMapYPos, y - AMPlayerX, x - AMPlayerY - AMPlayerX, y, COLOR_PLAYER);
    }
}

USHORT __fastcall GetAutomapType(int x, int y, BOOL view)
{
    if (view) {
        if (x == -1 && y >= 0 && y < DMAXY && automapview[0][y])
            return ~GetAutomapType(0, y, FALSE) & (MAPFLAG_SQUARE << 8);
        if (y == -1) {
            if (x < 0)
                return 0;
            if (x < DMAXX && automapview[x][0])
                return ~GetAutomapType(x, 0, FALSE) & (MAPFLAG_SQUARE << 8);
        }
    }

    if (x >= 0 && x < DMAXX && y >= 0 && y < DMAXY) {
        if (automapview[x][y] || !view) {
            USHORT type = automaptype[(UCHAR)dungeon[x][y]];
            if (type == 7 && GetAutomapType(x - 1, y, FALSE) & (MAPFLAG_HORZARCH << 8)
                && GetAutomapType(x, y - 1, FALSE) & (MAPFLAG_VERTARCH << 8)) {
                type = 1;
            }
            return type;
        }
    }
    return 0;
}

void __cdecl DrawAutomapGame()
{
    char desc[256];
    int nextline = 20;

    if (gbMaxPlayers > 1) {
        strcat(strcpy(desc, "game: "), szPlayerName);
        PrintGameStr(8, 20, desc, COL_GOLD);
        nextline = 35;
        if (szPlayerDescript[0]) {
            strcat(strcpy(desc, "password: "), szPlayerDescript);
            PrintGameStr(8, 35, desc, COL_GOLD);
            nextline = 50;
        }
    }
    if (setlevel)
        PrintGameStr(8, nextline, quest_level_names[(UCHAR)setlvlnum], COL_GOLD);
    else if (currlevel) {
        sprintf(desc, "Level: %i", currlevel);
        PrintGameStr(8, nextline, desc, COL_GOLD);
    }
}
// 5CCB10: using guessed type char setlvlnum;
// 5CF31D: using guessed type char setlevel;

void __fastcall SetAutomapView(int x, int y)
{
    int xx = (x - 16) >> 1;
    int yy = (y - 16) >> 1;

    if (xx < 0 || xx >= DMAXX || yy < 0 || yy >= DMAXY) {
        return;
    }

    automapview[xx][yy] = 1;

    USHORT maptype = GetAutomapType(xx, yy, FALSE);
    USHORT solid = maptype & 0x4000;

    switch (maptype & 0xF) {
    case 2:
        if (solid) {
            if (GetAutomapType(xx, yy + 1, FALSE) == 0x4007)
                automapview[xx][yy + 1] = 1;
        } else if (GetAutomapType(xx - 1, yy, FALSE) & 0x4000)
            automapview[xx - 1][yy] = 1;
        break;
    case 3:
        if (solid) {
            if (GetAutomapType(xx + 1, yy, FALSE) == 0x4007)
                automapview[xx + 1][yy] = 1;
        } else if (GetAutomapType(xx, yy - 1, FALSE) & 0x4000)
            automapview[xx][yy - 1] = 1;
        break;
    case 4:
        if (solid) {
            if (GetAutomapType(xx, yy + 1, FALSE) == 0x4007)
                automapview[xx][yy + 1] = 1;
            if (GetAutomapType(xx + 1, yy, FALSE) == 0x4007)
                automapview[xx + 1][yy] = 1;
        } else {
            if (GetAutomapType(xx - 1, yy, FALSE) & 0x4000)
                automapview[xx - 1][yy] = 1;
            if (GetAutomapType(xx, yy - 1, FALSE) & 0x4000)
                automapview[xx][yy - 1] = 1;
            if (GetAutomapType(xx - 1, yy - 1, FALSE) & 0x4000)
                automapview[xx - 1][yy - 1] = 1;
        }
        break;
    case 5:
        if (solid) {
            if (GetAutomapType(xx, yy - 1, FALSE) & 0x4000)
                automapview[xx][yy - 1] = 1;
            if (GetAutomapType(xx, yy + 1, FALSE) == 0x4007)
                automapview[xx][yy + 1] = 1;
        } else if (GetAutomapType(xx - 1, yy, FALSE) & 0x4000)
            automapview[xx - 1][yy] = 1;
        break;
    case 6:
        if (solid) {
            if (GetAutomapType(xx - 1, yy, FALSE) & 0x4000)
                automapview[xx - 1][yy] = 1;
            if (GetAutomapType(xx + 1, yy, FALSE) == 0x4007)
                automapview[xx + 1][yy] = 1;
        } else if (GetAutomapType(xx, yy - 1, FALSE) & 0x4000)
            automapview[xx][yy - 1] = 1;
    }
}

void __cdecl AutomapZoomReset()
{
    AutoMapXOfs = 0;
    AutoMapYOfs = 0;
    AutoMapPosBits = (AutoMapScale << 6) / 100;
    AutoMapXPos = AutoMapPosBits >> 1;
    AutoMapYPos = AutoMapXPos >> 1;
    AMPlayerX = AutoMapYPos >> 1;
    AMPlayerY = AMPlayerX >> 1;
}
