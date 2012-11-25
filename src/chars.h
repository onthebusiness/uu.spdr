#ifndef CHARS_H
#define CHARS_H

struct Chars
{
	int error;
	char* chars;
	int len;
	int capacity;
};

extern void chars_catsprintf(struct Chars* chars, const char* format, ...);
extern void chars_catjsonstr(struct Chars* chars, const char* utf8);

#endif