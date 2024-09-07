#ifndef SHELL_H
#define SHELL_H


#define SUCCESS                                "Success"
#define SYNTAX_ERROR                           "Syntax error"
#define CMD_ERROR                              "No such command"
#define ARG_ERROR                              "Wrong Argument"
#define CMD_LINE_SIZE                          32
#define CMD_WORDS_SIZE                          8

typedef int8_t (*cmd_fun_t)( int8_t arg );

typedef struct
{
	char *name;
	cmd_fun_t fun;
} cmd_t;



void shell_help( void );
void shell_proc( void );
void shell_init( cmd_t *cmd_table );

#endif
