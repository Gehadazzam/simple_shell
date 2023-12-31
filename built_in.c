#include "shell.h"

/**
 * _myexit - exit the program (Handles the 'exit' command)
 * @info: structure contain argumentrmation
 * Return:
 * -2: specified exit status.
 * 1: an illegal number as the exit status.
*/
int _myexit(info_t *info)
{
	int i;

	if (info->argv[1])
	{
		i = _erratoi(info->argv[1]);
		if (i == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process.
 * @info: structure contain argumentrmation
 * Return: Always 0
*/
int _mycd(info_t *info)
{
	char *s, *dir, buf[1024];
	int ch_ret;

	s = getcwd(buf, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			ch_ret =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			ch_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		ch_ret =
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		ch_ret = chdir(info->argv[1]);
	if (ch_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * _myhelp - displays argumentrmation about shell commands or functions
 * @info: structure contain argumentrmation
 * Return: Always 0
*/
int _myhelp(info_t *info)
{
	char **arr = info->argv;

	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arr);
	return (0);
}
