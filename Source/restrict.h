/**
 * @file restrict.h
 *
 * Interface of functionality for checking if the game will be able run on the system.
 */
#ifndef __RESTRICT_H__
#define __RESTRICT_H__

BOOL SystemSupported();
BOOL RestrictedTest();
BOOL ReadOnlyTest();

#endif /* __RESTRICT_H__ */
