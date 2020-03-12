/**
 * @file misdat.cpp
 *
 * Implementation of data related to missiles.
 */
#include "all.h"

/** Data related to each missile ID. */
MissileData missiledata[] = {
#include "Data/xl_mis.cpp"
};

/** Data related to each missile graphic ID. */
MisFileData misfiledata[] = {
#include "Data/xl_mfile.cpp"
};
