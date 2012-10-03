#include <stdio.h>
#include <string.h>

#include "spdr.h"

#include <math.h>
#include <unistd.h>

#ifndef TRACING_ENABLED
#define TRACING_ENABLED 0
#endif

static struct spdr* spdr;

void trace (const char* line)
{
	char buffer[512] = "";
	strncat(buffer, line, sizeof buffer - 2);
	strncat(buffer, "\n", sizeof buffer - 2);

	// fputs is thread-safe
	fputs (buffer, stderr);
}

void fun1()
{
	static double x = 0.5f;
	static double y = -0.15f;

	SPDR_SCOPE2(spdr, "Main", "fun1",
		    SPDR_FLOAT("x", x),
		    SPDR_FLOAT("y", y));

	int N = 65536;
	while (N--) {
		y = cos(x + atan2(x, y));
		x = sin(y);
	}
}

int main (int argc, char** argv)
{
	spdr_init(&spdr);
	spdr_enable_trace(spdr, TRACING_ENABLED);
	spdr_set_log_fn(spdr, trace);

	SPDR_BEGIN2(spdr, "Main", "main",
		    SPDR_INT("argc", argc),
		    SPDR_STR("argv[0]", argv[0]));

	printf ("Hello,");
	sleep (3);
	printf (" 世界.\n");

	fun1();
	fun1();
	fun1();

	SPDR_END(spdr, "Main", "main");
}