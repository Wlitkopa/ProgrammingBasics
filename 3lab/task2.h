#ifndef ENCRYPTION
#define ENCRYPTION

char* getHexAscii(const char ch[]);

char** getData(int* len, int* largest);

char* compress(char** first, const int* len, const int* largest);

char* decompress(char** first, const int* len, const int* largest);


#endif