#include "all.h"

/* todo: move text out of struct */

const TextDataStruct alltext[] = {
#ifdef SPAWN
#include "Data/Spawn/speech.cpp"
#else
#include "Data/speech.cpp"
#endif
};
/** unused */
const DWORD gdwAllTextEntries = 259;
