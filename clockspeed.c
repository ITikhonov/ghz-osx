#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include <sys/time.h>

static uint64_t rdtsc(void)
{
    uint32_t ret0[2];
    __asm__ __volatile__("rdtsc" : "=a"(ret0[0]), "=d"(ret0[1]));
    return ((uint64_t)ret0[1] << 32) | ret0[0];
}

static double getnow(void) {
	struct timeval tv;
	gettimeofday(&tv,0);
	double sec = tv.tv_sec;
	double usec = tv.tv_usec / 1e6;
	return sec + usec;
}

int main(int argc, const char * argv[])
{
    uint64_t startCount = rdtsc();
    uint64_t ticks;

    double start = getnow();

    for(;;) {
    	uint64_t endCount = rdtsc();
	ticks = endCount - startCount;
	if(ticks > 10000000) break;
    }

    double end = getnow();
    double t = end - start;

    double hz = ticks / t;

    printf("%.1f GHz\n", hz/1e9);

    return 0;
}
