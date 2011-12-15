#ifndef HEADER_UTILS_H
#define HEADER_UTILS_H

#include <features.h>
#include <sys/time.h>
#include <assert.h>

#define SECTOR_SIZE (512)
#define GIGABYTES   (1024 * 1024 * 1024)

const char *adjust_unit(double *ptr_bytes);

static inline void update_dt(struct timeval *dt, const struct timeval *t1,
	const struct timeval *t2)
{
	dt->tv_sec  += t2->tv_sec  - t1->tv_sec;
	dt->tv_usec += t2->tv_usec - t1->tv_usec;
	if (dt->tv_usec >= 1000000) {
		dt->tv_sec++;
		dt->tv_usec -= 1000000;
	}
}

static inline double dt_to_s(struct timeval *dt)
{
	double ret = (double)dt->tv_sec + ((double)dt->tv_usec / 1000000.);
	assert(ret >= 0.);
	return ret > 0. ? ret : 1.;
}

#ifndef __GLIBC__

/*
 * The following functions were copied from GNU Library C to make F3
 * more portable.
 */

/* Data structure for communication with thread safe versions.  This
 * type is to be regarded as opaque.  It's only exported because users
 * have to allocate objects of this type.
 */
struct drand48_data {
	unsigned short int __x[3];	/* Current state.		    */
	unsigned short int __old_x[3];	/* Old state.			    */
	unsigned short int __c;	/* Additive const. in congruential formula. */
	unsigned short int __init;	/* Flag for initializing.	    */
	unsigned long long int __a;	/* Factor in congruential formula.  */
};

/* Seed random number generator.  */
extern int srand48_r(long int __seedval, struct drand48_data *__buffer)
	__attribute__ ((nonnull(2)));

/* Return non-negative, long integer in [0,2^31).  */
extern int lrand48_r(struct drand48_data *__restrict __buffer,
	long int *__restrict __result) __attribute__ ((nonnull(1, 2)));

#endif	/* __GLIBC__ */

#endif	/* HEADER_UTILS_H */