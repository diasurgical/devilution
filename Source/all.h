/**
 * @file all.h
 *
 * Include all application headers.
 */
#ifndef __ALL_H__
#define __ALL_H__

#include "../types.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "appfat.h"
#include "automap.h"
#include "capture.h"
#include "codec.h"
#include "control.h"
#include "cursor.h"
#include "dead.h"
#include "debug.h"
#include "diablo.h"
#include "doom.h"
#include "drlg_l1.h"
#include "drlg_l2.h"
#include "drlg_l3.h"
#include "drlg_l4.h"
#include "dthread.h"
#include "dx.h"
#include "effects.h"
#include "encrypt.h"
#include "engine.h"
#include "error.h"
#include "fault.h"
#include "gamemenu.h"
#include "gendung.h"
#include "gmenu.h"
#include "help.h"
#include "init.h"
#include "interfac.h"
#include "inv.h"
#include "itemdat.h"
#include "items.h"
#include "lighting.h"
#include "loadsave.h"
#include "logging.h"
#include "mainmenu.h"
#include "minitext.h"
#include "misdat.h"
#include "missiles.h"
#include "monstdat.h"
#include "monster.h"
#include "movie.h"
#include "mpqapi.h"
#include "msg.h"
#include "msgcmd.h"
#include "multi.h"
#include "nthread.h"
#include "objdat.h"
#include "objects.h"
#include "pack.h"
#include "palette.h"
#include "path.h"
#include "pfile.h"
#include "player.h"
#include "plrmsg.h"
#include "portal.h"
#include "quests.h"
#include "restrict.h"
#include "scrollrt.h"
#include "setmaps.h"
#include "sha.h"
#include "sound.h"
#include "spelldat.h"
#include "spells.h"
#include "stores.h"
#include "sync.h"
#include "textdat.h" // check file name
#include "themes.h"
#include "tmsg.h"
#include "town.h"
#include "towners.h"
#include "track.h"
#include "trigs.h"
#include "wave.h"
#include "render.h" // linked last, likely .s/.asm
#ifdef __cplusplus
}
#endif

#endif /* __ALL_H__ */
