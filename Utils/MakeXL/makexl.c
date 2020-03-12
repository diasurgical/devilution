#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLUMNS 256

int NumCols, NumRows;
int Columns[MAX_COLUMNS];
int HasEnum;

enum {
	FIELD_INTEGER,
	FIELD_STRING,
	FIELD_ARRAY,
	FIELD_POINTER,
	FIELD_COMMENT
};

unsigned char *LoadBinaryFile(char *file, int *pdwSize)
{
	unsigned char *p, *p2;
	FILE *fp;
	int bufsize, i, fsize;

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

	p2 = (unsigned char *)malloc(sizeof(unsigned char) * (bufsize + 1));
	fsize = 0;

	for(i = 0; i < bufsize; i++) {
		if(p[i] == '\r') {
			p2[fsize++] = '\n';
			if(p[i + 1] == '\n') {
				i++;
			}
		} else {
			p2[fsize++] = p[i];
		}
	}
	p2[fsize++] = '\0';

	free(p);

	if(pdwSize != NULL) {
		*pdwSize = fsize;
	}

	return p2;
}

void WriteField(unsigned char *p, FILE *pFile, int c, int len)
{
	char BraceL[] = "{ ";
	char BraceR[] = " }";
	char Ptr[] = "&";
	char Str[] = "\"";
	char NoData[] = "0";
	char NoStr[] = "NULL";
	char Sep[] = ", ";

	switch(Columns[c]) {
	case FIELD_INTEGER:
		if(len != 0) {
			fwrite(p, sizeof(char), len, pFile);
		} else {
			fwrite(NoData, sizeof(char), sizeof(NoData) - 1, pFile);
		}
		break;
	case FIELD_STRING:
		if(len != 0 && strncmp(NoStr, p, sizeof(NoStr) - 1) != 0) {
			if(*p != '"') {
				fwrite(Str, sizeof(char), sizeof(Str) - 1, pFile);
			}
			if(len != 1 || *p != '~') {
				fwrite(p, sizeof(char), len, pFile);
			}
			if(p[len - 1] != '"') {
				fwrite(Str, sizeof(char), sizeof(Str) - 1, pFile);
			}
		} else {
			fwrite(NoStr, sizeof(char), sizeof(NoStr) - 1, pFile);
		}
		break;
	case FIELD_ARRAY:
		fwrite(BraceL, sizeof(char), sizeof(BraceL) - 1, pFile);
		if(len != 0) {
			if(p[0] == '\"' && p[len - 1] == '\"') {
				fwrite(&p[1], sizeof(char), len - 2, pFile);
			} else {
				fwrite(p, sizeof(char), len, pFile);
			}
		} else {
			fwrite(NoData, sizeof(char), sizeof(NoData) - 1, pFile);
		}
		fwrite(BraceR, sizeof(char), sizeof(BraceR) - 1, pFile);
		break;
	case FIELD_POINTER:
		if(len != 0 && strncmp(NoStr, p, sizeof(NoStr) - 1) != 0) {
			fwrite(Ptr, sizeof(char), sizeof(Ptr) - 1, pFile);
			fwrite(p, sizeof(char), len, pFile);
		} else {
			fwrite(NoStr, sizeof(char), sizeof(NoStr) - 1, pFile);
		}
		break;
	}

	if(c != NumCols - 1) {
		fwrite(Sep, sizeof(char), sizeof(Sep) - 1, pFile);
	}
}

void WriteColumn(unsigned char *p, FILE *pFile, int c)
{
	unsigned char *p2;
	int cur, len;

	cur = 0;
	while(cur != c) {
		while(*p != '\t' && *p != '\n') {
			p++;
		}
		p++;
		cur++;
	}

	p2 = p;
	len = 0;
	while(*p2 != '\t' && *p2 != '\n') {
		p2++;
		len++;
	}

	WriteField(p, pFile, c, len);
}

void ConvertTextFile(char *name, unsigned char *p, int size)
{
	unsigned char *p2;
	int c, len;
	FILE *pOutput;
	char Pre[] = "\t{ ";
	char Suf[] = " },\r\n";

	pOutput = fopen(name, "wb");

	if(pOutput == NULL) {
		fprintf(stderr, "Can't create file %s\n", name);
		exit(-1);
	}

	while(*p != '\n') {
		p++;
	}
	p++;

	while(*p != '\0') {
		p2 = p;
		len = 0;
		while(*p2 != '\n') {
			p2++;
			len++;
		}
		len++;
		fwrite(Pre, sizeof(char), sizeof(Pre) - 1, pOutput);
		for(c = 0; c < NumCols; c++) {
			if(Columns[c] != FIELD_COMMENT) {
				WriteColumn(p, pOutput, c);
			}
		}
		fwrite(Suf, sizeof(char), sizeof(Suf) - 1, pOutput);
		p += len;
	}

	fclose(pOutput);
}

void SetColumnType(char t, int c)
{
	switch(t) {
	case 'i':
		Columns[c] = FIELD_INTEGER;
		return;
	case 's':
		Columns[c] = FIELD_STRING;
		return;
	case 'a':
		Columns[c] = FIELD_ARRAY;
		return;
	case 'p':
		Columns[c] = FIELD_POINTER;
		return;
	}

	fprintf(stderr, "Invalid type '%c' column %d\n", t, c + 1);
	exit(-1);
}

void CheckMaxColumns(unsigned char *p)
{
	int num_cols;

	num_cols = 0;
	while(*p != '\n') {
		if(*p == '\t') {
			num_cols++;
		}
		p++;
	}
	num_cols++;

	if(num_cols >= MAX_COLUMNS) {
		fprintf(stderr, "%d columns exceeds limit of %d\n", num_cols, MAX_COLUMNS - 1);
		exit(-1);
	}
}

void SetupColumns(unsigned char *p)
{
	NumCols = 0;

	while(*p != '\n') {
		if(*p == '\t') {
			fprintf(stderr, "Invalid column %d\n", NumCols + 1);
			exit(-1);
		}
		if(*p == '#') {
			HasEnum = 1;
		}
		if(*p == '*' || p[0] == '#' && (p[1] == '\t' || p[1] == '\n')) {
			Columns[NumCols++] = FIELD_COMMENT;
			p++;
			while(*p != '\t' && *p != '\n') {
				p++;
			}
			if(*p != '\n') {
				p++;
			}
		} else {
			while(*p != '\t' && *p != '\n') {
				p++;
			}
			p -= 3;
			if(p[0] != '(' || p[2] != ')') {
				fprintf(stderr, "No type for column %d\n", NumCols + 1);
				exit(-1);
			}
			SetColumnType(p[1], NumCols++);
			p += 3;
			if(*p != '\n') {
				p++;
			}
		}
	}
}

void GetNumRows(unsigned char *p)
{
	NumRows = 0;
	while(*p != '\0') {
		if(*p == '\n') {
			NumRows++;
		}
		p++;
	}
}

void InitColumns(unsigned char *p)
{
	int i;

	for(i = 0; i < MAX_COLUMNS; i++) {
		Columns[i] = -1;
	}

	CheckMaxColumns(p);
	SetupColumns(p);
}

int IsValidEnum(unsigned char *p, int size)
{
	int i, valid;

	valid = 1;
	for(i = 0; i < size && valid; i++) {
		if(i != 0 && p[i] >= '0' && p[i] <= '9') {
			continue;
		}
		if(p[i] >= 'A' && p[i] <= 'Z') {
			continue;
		}
		if(p[i] >= 'a' && p[i] <= 'z') {
			continue;
		}
		if(p[i] == '_') {
			continue;
		}
		valid = 0;
	}

	return valid;
}

void WriteEnum(unsigned char *p, int c, FILE *pOutput)
{
	unsigned char *p2;
	int i, cur, size;
	char Pre[] = "enum {\r\n";
	char Tab[] = "\t";
	char Suf[] = ",\r\n";
	char End[] = "};\r\n";
	char tmp[16];

	while(*p != '\n') {
		p++;
	}
	p++;

	fwrite(Pre, sizeof(char), sizeof(Pre) - 1, pOutput);

	for(i = 0; i < NumRows - 1; i++) {
		cur = 0;
		while(cur != c) {
			while(*p != '\t' && *p != '\n') {
				p++;
			}
			p++;
			cur++;
		}
		p2 = p;
		size = 0;
		while(*p2 != '\t' && *p2 != '\n') {
			size++;
			p2++;
		}
		if(IsValidEnum(p, size)) {
			fwrite(Tab, sizeof(char), sizeof(Tab) - 1, pOutput);
			fwrite(p, sizeof(char), size, pOutput);
			sprintf(tmp, " = %d", i);
			fwrite(tmp, sizeof(char), strlen(tmp), pOutput);
			fwrite(Suf, sizeof(char), sizeof(Suf) - 1, pOutput);
		}
		p += size;
		while(*p != '\n') {
			p++;
		}
		p++;
	}

	fwrite(End, sizeof(char), sizeof(End) - 1, pOutput);
}

void WriteEnumFile(char *name, unsigned char *p, int size)
{
	int i, cur;
	unsigned char *p2;
	FILE *pOutput;

	pOutput = fopen(name, "wb");

	if(pOutput == NULL) {
		fprintf(stderr, "Can't create file %s\n", name);
		exit(-1);
	}

	for(i = 0; Columns[i] != -1; i++) {
		p2 = p;
		cur = 0;
		while(cur != i) {
			while(*p2 != '\t' && *p2 != '\n') {
				p2++;
			}
			p2++;
			cur++;
		}
		if(*p2 == '#') {
			WriteEnum(p, i, pOutput);
		}
	}

	fclose(pOutput);
}

int main(int argc, char *argv[])
{
	int size;
	unsigned char *p;

	if(argc != 3 && argc != 4) {
		fprintf(stderr, "Usage: makexl [txt] [cpp] [h]\n");
		return 0;
	}

	p = LoadBinaryFile(argv[1], &size);

	GetNumRows(p);
	if(NumRows < 2) {
		fprintf(stderr, "Not enough rows\n");
		free(p);
		return 0;
	}

	HasEnum = 0;
	InitColumns(p);

	ConvertTextFile(argv[2], p, size);

	if(argc == 4 && HasEnum) {
		WriteEnumFile(argv[3], p, size);
	}

	free(p);

	return 0;
}
