/**
 * @file itemdat.cpp
 *
 * Implementation of all item data.
 */
#include "all.h"

ItemDataStruct AllItemsList[] = {
#include "Data/xl_item.cpp"
};

const PLStruct PL_Prefix[] = {
#include "Data/xl_ipre.cpp"
};

const PLStruct PL_Suffix[] = {
#include "Data/xl_isuf.cpp"
};

const UItemStruct UniqueItemList[] = {
#include "Data/xl_uitem.cpp"
};
