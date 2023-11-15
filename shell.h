#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/* _black.c */
int gem(info_t *);
int is_vet(char, char *);
int _isalpha(int);
int _black(char *);

/* _construct.c */
int _cloz(info_t *);
int _vec(info_t *);
int _recov(info_t *);

/* constructi.c */
int _valin(info_t *);
int _altern(info_t *);
int print_altern(list_t *node);
int unset_altern(info_t *info, char *str);
int set_altern(info_t *info, char *str);

/* _compound.c */
char *_getenv(info_t *, const char *);
int _comp(info_t *);
int _setcomp(info_t *);
int _rmcomp(info_t *);
int _incrementlist(info_t *);

/* mistakes.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* mistakesi.c */
int _mist(char *);
void print_error(info_t *, char *);
int call_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

#endif
