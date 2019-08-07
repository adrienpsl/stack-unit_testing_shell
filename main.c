#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


char *join(const char *s1, const char *s2)
{
	char *result = malloc(strlen(s1) + strlen(s2) + 1);

	if (result) // thanks @pmg
	{
		strcpy(result, s1);
		strcat(result, s2);
	}
	return result;
}

/*
 * Activates the raw mode and saving
 * the old configuration in t
*/
void ms_activate_raw_mode(struct termios *t)
{
	struct termios termios;

	tcgetattr(STDIN_FILENO, &termios);
	tcgetattr(STDIN_FILENO, t);
	termios.c_lflag &= ~(ICANON | ECHO);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

int main()
{
	struct termios termios;

	char *line;
	static char buff[3] = { 0 };

	ms_activate_raw_mode(&termios);
	line = strdup("");
	while (strcmp(line, "exit\n"))
	{
		line = strdup("");
		bzero(buff, 2);
		while (strcmp(buff, "\n"))
		{
			bzero(buff, 2);
			read(STDIN_FILENO, buff, 2);
			write(1, buff, 1);
			line = join(line, buff);
		}
		printf("the line is : %s", line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	return 0;
}