/**
 * @file sha.cpp
 *
 * Interface of functionality for calculating X-SHA-1 (a flawed implementation of SHA-1).
 */
#ifndef __SHA_H__
#define __SHA_H__

#define SHA1HashSize 20

void SHA1Clear();
void SHA1Result(int n, char Message_Digest[SHA1HashSize]);
void SHA1Calculate(int n, const char *data, char Message_Digest[SHA1HashSize]);
void SHA1Reset(int n);

#endif /* __SHA_H__ */
