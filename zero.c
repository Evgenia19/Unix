#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {	

	char buffer[256];
	int count_zero = 0;
	int i = 0;
	char symbol[1];
	int text_cursor;
  int fd;
	
	if (argc == 1) {
		printf("Error: filename not received\n");
		return 1;
	}
	
	fd = open(argv[1], O_WRONLY|O_CREAT, 0640);
	
	if (fd == -1) {
		printf("Error: create or write in file\n");
		return 1;
	}

	while (1) {
		text_cursor = read(0, buffer, 256);
		if (!text_cursor) {
			break;
		}
		while(i < text_cursor) {
			symbol[0] = buffer[i];
			if (symbol[0] == 0) {
				count_zero++;
			}
			else {
				if (count_zero > 0) {
					lseek(fd, count_zero, SEEK_CUR);
				}
				write(fd, symbol, 1);
				count_zero = 0;
			}
			i++;	
		}	
		i = 0;
	}
	close(fd);
	return 0;
}
