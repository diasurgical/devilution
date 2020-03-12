#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1 megabyte
#define BUFFER_SIZE_LIMIT (1 * 1024 * 1024)

// prevent including duplicate files
#define MAX_INCLUDE_FILES 256
char IncludedNames[MAX_INCLUDE_FILES][256];

unsigned char *ConvertEOL(unsigned char *p, int bufsize, int *newsize)
{
	int i;
	unsigned char *p2;

	p2 = (unsigned char *)malloc(sizeof(unsigned char) * (bufsize + 1));
	*newsize = 0;

	for(i = 0; i < bufsize; i++) {
		if(p[i] == '\r') {
			p2[(*newsize)++] = '\n';
			if(p[i + 1] == '\n') {
				i++;
			}
		} else {
			p2[(*newsize)++] = p[i];
		}
	}
	p2[(*newsize)++] = '\0';

	return p2;
}

unsigned char *RemoveWhitespace(unsigned char *p2, int fsize)
{
	unsigned char *p, *p3, *p4;

	p = (unsigned char *)malloc(sizeof(unsigned char) * (fsize + 1));
	p3 = p;
	p4 = p2;

	while(*p4 != '\0') {
		while(*p4 == ' ' || *p4 == '\t' || *p4 == '\n') {
			p4++;
		}
		while(*p4 != '\n') {
			*p3++ = *p4++;
		}
		*p3++ = *p4++;
	}
	*p3++ = '\0';

	return p;
}

unsigned char *LoadBinaryFile(char *file, int *pdwSize)
{
	unsigned char *p;
	FILE *fp;
	int bufsize;

	fp = fopen(file, "rb");

	if(fp == NULL) {
		fprintf(stderr, "Can't open file %s\n", file);
		exit(-1);
	}

	fseek(fp, 0L, SEEK_END);
	bufsize = ftell(fp);
	p = (unsigned char *)malloc(sizeof(unsigned char) * (bufsize + 1));
	fseek(fp, 0L, SEEK_SET);
	fread(p, sizeof(char), bufsize, fp);
	fclose(fp);

	if(pdwSize != NULL) {
		*pdwSize = bufsize;
	}

	return p;
}

unsigned char *LoadTextFile(char *file, int *pdwSize)
{
	unsigned char *p, *p2;
	int bufsize, fsize;

	p = LoadBinaryFile(file, &bufsize);

	p2 = ConvertEOL(p, bufsize, &fsize);
	free(p);
	p = RemoveWhitespace(p2, fsize);
	free(p2);

	if(pdwSize != NULL) {
		*pdwSize = fsize;
	}

	return p;
}

/*
 * TODO: make recursive so all files with includes will expand into data buffer
 * - currently only the main file may call the include function
 */
unsigned char *ExpandTextFile(unsigned char *p, int *fsize)
{
	char FileName[256];
	char Include[] = "#include";
	int i, size, index;
	unsigned char *p2, *p3, *p4, *pInclude;

	p2 = (unsigned char *)malloc(sizeof(unsigned char) * (BUFFER_SIZE_LIMIT + 1));
	p3 = p2;

	*fsize = 0;
	index = 0;
	while(*p != '\0') {
		if(strncmp(p, Include, sizeof(Include) - 1) == 0) {
			p += sizeof(Include) - 1;
			while(*p == ' ' || *p == '\t') {
				p++;
			}
			if(*p != '"') {
				fprintf(stderr, "Invalid file name\n");
				exit(-1);
			}
			p++;
			i = 0;
			while(*p != '\n') {
				FileName[i++] = *p++;
				if(i >= sizeof(FileName)) {
					fprintf(stderr, "File name exceeds max path\n");
					exit(-1);
				}
			}
			p++;
			if(FileName[i - 1] != '"') {
				fprintf(stderr, "Invalid file name: %s\n", FileName);
				exit(-1);
			}
			FileName[i - 1] = '\0';
			for(i = 0; IncludedNames[i][0] != '\0'; i++) {
				if(strcmp(IncludedNames[i], FileName) == 0) {
					fprintf(stderr, "File %s already included\n", FileName);
					exit(-1);
				}
			}
			strcpy(IncludedNames[index++], FileName);
			if(index >= MAX_INCLUDE_FILES) {
				fprintf(stderr, "Including too many files\n");
				exit(-1);
			}
			pInclude = LoadTextFile(FileName, &size);
			p4 = pInclude;
			while(*p4 != '\0') {
				if(p4[0] == '/' && p4[1] == '/') {
					p4 += 2;
					while(*p4 != '\n') {
						p4++;
					}
					p4++;
				} else {
					(*fsize)++;
					*p3++ = *p4++;
				}
			}
			free(pInclude);
		} else if(p[0] == '/' && p[1] == '/') {
			p += 2;
			while(*p != '\n') {
				p++;
			}
			p++;
		} else {
			while(*p != '\n') {
				(*fsize)++;
				*p3++ = *p++;
			}
			(*fsize)++;
			*p3++ = *p++;
		}
		if(*fsize >= BUFFER_SIZE_LIMIT) {
			fprintf(stderr, "Exceeded buffer size limit\n");
			exit(-1);
		}
	}

	(*fsize)++;
	*p3++ = *p++;

	return p2;
}

void WriteDataFile(char *file, unsigned char *p, int fsize)
{
	FILE *fp;
	int i;
	char Pre[] = "\t{ ";
	char Suf[] = " },\r\n";
	char Sep[] = ", ";

	fp = fopen(file, "wb");

	if(fp == NULL) {
		fprintf(stderr, "Can't create file %s\n", file);
		exit(-1);
	}

	while(*p != '\0') {
		if(*p == '[') {
			p++;
			while(*p != ']' && *p != '\n') {
				p++;
			}
			if(*p != ']') {
				fprintf(stderr, "Error: invalid text entry\n");
				exit(-1);
			}
			p++;
			while(*p != '\n') {
				p++;
			}
			p++;
			fwrite(Pre, sizeof(char), sizeof(Pre) - 1, fp);
			for(i = 0; i < 4; i++) {
				if(*p == '[') {
					fprintf(stderr, "Error: unexpected text entry\n");
					exit(-1);
				}
				while(*p != '\n') {
					fwrite(p, sizeof(char), 1, fp);
					p++;
				}
				p++;
				if(i < 4 - 1) {
					fwrite(Sep, sizeof(char), sizeof(Sep) - 1, fp);
				}
			}
			fwrite(Suf, sizeof(char), sizeof(Suf) - 1, fp);
		} else {
			fprintf(stderr, "Error: invalid text entry\n");
			exit(-1);
		}
	}

	fclose(fp);
}

void WriteEnumFile(char *file, unsigned char *p, int fsize)
{
	int counter;
	FILE *fp;
	char EnumPre[] = "enum {\r\n";
	char EnumSuf[] = "};\r\n";
	char Tab[] = "\t";
	char EFmt[] = " = %d,\r\n";
	char Format[32];

	fp = fopen(file, "wb");

	if(fp == NULL) {
		fprintf(stderr, "Can't create file %s\n", file);
		exit(-1);
	}

	fwrite(EnumPre, sizeof(char), sizeof(EnumPre) - 1, fp);

	counter = 0;
	while(*p != '\0') {
		if(*p == '[') {
			p++;
			fwrite(Tab, sizeof(char), sizeof(Tab) - 1, fp);
			while(*p != ']') {
				fwrite(p, sizeof(char), 1, fp);
				p++;
			}
			p++;
			sprintf(Format, EFmt, counter);
			counter++;
			fwrite(Format, sizeof(char), strlen(Format), fp);
			while(*p != '\n') {
				p++;
			}
			p++;
		} else {
			while(*p != '\n') {
				p++;
			}
			p++;
		}
	}

	fwrite(EnumSuf, sizeof(char), sizeof(EnumSuf) - 1, fp);
	fclose(fp);
}

int main(int argc, char *argv[])
{
	int size, fsize;
	unsigned char *p, *p2;

	if(argc != 4) {
		fprintf(stderr, "Usage: maketext [txt] [cpp] [h]\n");
		return 0;
	}

	p = LoadTextFile(argv[1], &size);

	p2 = ExpandTextFile(p, &fsize);
	WriteDataFile(argv[2], p2, fsize);
	WriteEnumFile(argv[3], p2, fsize);

	free(p);
	free(p2);

	return 0;
}
