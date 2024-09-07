#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "../uart/uart.h"


static cmd_t *cmd;
static char cmd_line[CMD_LINE_SIZE];
static char *cmd_words[CMD_WORDS_SIZE];



static void shell_put_str( const char *str )
{
	uart_put('\n');
	uart_put('\r');

	while( *str )
	{
		if( !uart_put((uint8_t) *str) )
		{
			break;
		}
		str++;
	}

	uart_put('\n');
	uart_put('\r');
}


static int8_t shell_get_words( void )
{
	int8_t count = 0;
	int8_t in_word = 0;

	for( char *ptr = cmd_line; *ptr != '\0'; ptr++ )
	{
		if( *ptr != ' ' && !in_word )
		{
			cmd_words[count++] = ptr;
			in_word = 1;
		}
		else if( *ptr == ' ' )
		{
			in_word = 0;
			*ptr = '\0';
		}
	}

	return (count > 0 && count <= 2) ? 1 : 0;
}


static void shell_exe( void )
{
	if( shell_get_words() )
	{
		const cmd_t *cur_cmd = cmd;
		int8_t cmd_found = 0;

		while( cur_cmd->name )
		{
			if( strcasecmp(cur_cmd->name, cmd_words[0]) == 0 )
			{
				cmd_found = 1;

				if( cur_cmd->fun )
				{
					int8_t arg = 1;

					if( cmd_words[1] != 0  )
					{
						arg = (int8_t) atoi(cmd_words[1]);
					}

					shell_put_str((cur_cmd->fun(arg)) ? SUCCESS : ARG_ERROR);
				}
				break;
			}
			cur_cmd++;
		}

		if( !cmd_found )
		{
			shell_put_str(CMD_ERROR);
		}
	}
	else
	{
		shell_put_str(SYNTAX_ERROR);
	}

	memset(cmd_words, 0, sizeof(cmd_words));
}


static void shell_get_str( void )
{
	static uint8_t count;
	uint8_t byte;

	if( uart_get(&byte) == 0 )
	{
		return;
	}

	if( byte == 0x0D )
	{
		cmd_line[count] = '\0';

		shell_exe();

		memset(cmd_line, 0, sizeof(cmd_line));
		count = 0;
	}
	else if( count < CMD_LINE_SIZE - 1 )
	{
		uart_put((char) byte);
		cmd_line[count++] = (char) byte;
	}
	else
	{
		shell_put_str(CMD_ERROR);
	}
}


void shell_help( void )
{
	const cmd_t *cur_cmd = cmd;

	while( cur_cmd->name )
	{
		shell_put_str( cur_cmd->name );
		cur_cmd++;
	}
}


void shell_proc( void )
{
	shell_get_str();
}


void shell_init( cmd_t *cmd_table )
{
	cmd = cmd_table;
}
