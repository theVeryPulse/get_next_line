#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd0 = open("test0.txt", O_RDONLY);
	int fd1 = open("test1.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	char *s;

	for (int i = 0; i < 3; i++)
	{
		s = get_nex_line(fd0);
		printf("test0.txt:>>> (%s)\n", s);
		free(s);
		s = get_nex_line(fd1);
		printf("test1.txt:>>> (%s)\n", s);
		free(s);
		s = get_nex_line(fd2);
		printf("test2.txt:>>> (%s)\n", s);
		free(s);
	}
}