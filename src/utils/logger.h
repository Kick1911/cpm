#ifndef _UTILS_LOGGER_H
#define _UTILS_LOGGER_H

#include <stdio.h>

#ifndef LOG_LEVEL
#define LOG_LEVEL 2
#endif


#if LOG_LEVEL == 1

#define LOG_ERROR(...) fprintf(stderr, "ERROR " __VA_ARGS__)

#define LOG_WARNING(...) fprintf(stdout, "WARNING " __VA_ARGS__)

#define LOG_INFO(...) fprintf(stdout, "INFO " __VA_ARGS__)

#define LOG_DEBUG(...) fprintf(stdout, "DEBUG " __VA_ARGS__)

#elif LOG_LEVEL == 2

#define LOG_ERROR(...) fprintf(stderr, "ERROR " __VA_ARGS__)

#define LOG_WARNING(...) fprintf(stdout, "WARNING " __VA_ARGS__)

#define LOG_INFO(...) fprintf(stdout, "INFO " __VA_ARGS__)

#define LOG_DEBUG(...)

#elif LOG_LEVEL == 3

#define LOG_ERROR(...) fprintf(stderr, "ERROR " __VA_ARGS__)

#define LOG_WARNING(...) fprintf(stdout, "WARNING " __VA_ARGS__)

#define LOG_INFO(...)

#define LOG_DEBUG(...)

#elif LOG_LEVEL == 4

#define LOG_ERROR(...) fprintf(stderr, "ERROR " __VA_ARGS__)

#define LOG_WARNING(...)

#define LOG_INFO(...)

#define LOG_DEBUG(...)

#endif

#endif /* _UTILS_LOGGER_H */
