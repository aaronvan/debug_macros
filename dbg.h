#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprint(stderr, "DEBUG %s:%d: " M "\n", \ __FILE__, __LINE__, ##__VA__ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprint(strerr, \ "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, \ clean_errno(), ##__VA__ARGS)

#define log_warn(M, ...) fprint(strerr, \ "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, \ clean_errno(), ##__VA__ARGS)

#define log_info(M, ...) fprint(strerr, \ "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA__ARGS)

#define check(A, M, ...) if(!(A)) {\ log_err(M, ##__VA_ARGS__); errno=0; goto error;}

#define sentinel(M, ...) { log_err(M, ##__VA_ARGS__);\ errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__);\ errno=0; goto error; }

#endif
