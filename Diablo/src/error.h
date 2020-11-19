/**
 * @file error.h
 *
 * Interface of in-game message functions.
 */
#ifndef __ERROR_H__
#define __ERROR_H__

extern char msgdelay;
extern char msgflag;

void InitDiabloMsg(char e);
void ClrDiabloMsg();
void DrawDiabloMsg();

#endif /* __ERROR_H__ */
