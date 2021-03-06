#ifndef FILE_SUPPORT_H
#define FILE_SUPPORT_H

#include <time.h> /* time_t */

/* types */ 
#ifdef __GNUC__
	/* if compiled with -pedantic-errors it will complain about long long not being a C90 thing. */
	__extension__ typedef unsigned long long hash_t;
#else
	typedef unsigned long long hash_t;
#endif

struct lua_State;

void install_signals(void (*abortsignal)(int));
int run_command(const char *cmd, const char *filter);

void platform_init();
void platform_shutdown();

/* threading */
void *threads_create(void (*threadfunc)(void *), void *u);
void threads_join(void *thread);
void threads_yield();
int threads_corecount();

void criticalsection_enter();
void criticalsection_leave();

/* filesystem and timestamps */
time_t timestamp();
time_t file_timestamp(const char *filename);
int file_exist(const char *filename);
int file_createdir(const char *path);
void file_touch(const char *filename);

/* plugin related */
typedef int (*PLUGINFUNC)(struct lua_State *);
PLUGINFUNC plugin_load(const char *filename);

/* string hashing function */
hash_t string_hash(const char *str_in);
hash_t string_hash_add(hash_t base, const char *str_in);
void string_hash_tostr(hash_t value, char *output);

#endif
