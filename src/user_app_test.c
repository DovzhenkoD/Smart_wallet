#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

#define BEES_TWERK _IO('a', 0)
#define SEL_BUF_SIZE _IOW('a', 1, int *)

int main(int argc, char* argv[])
{
	int fd, fd_2, num, w_r, our_buf;

	fd = open("/dev/hive_dev", O_RDWR);
	fd_2 = open("/dev/hive_dev", O_RDWR);

	char buf[] = "";

	char magic_phrase[] = "Wow, we made these bees TWERK!";

	if (fd_2 < 0) {
        	printf("Can't open device\n");
        	printf("fd_2 is = %d\n", fd_2);
        	return 0;
     	} else 
		printf("Open a device 2: %d\n", fd_2);


	if (fd < 0) {
        	printf("Can't open device\n");
        	printf("fd is = %d\n", fd);
        	return 0;
     	} else 
		printf("Open a device 1: %d\n", fd);

	ioctl(fd, BEES_TWERK, 0);
	int phrase_size = sizeof(magic_phrase);
	w_r = write(fd_2, magic_phrase, phrase_size);
	
   	if (w_r < 0) {
      		printf("Failed to write the message to the device.");
      		return 0;
   	} else 
		printf ("SOME MAGIC _write_:  %s\n", magic_phrase);
	int of_s = w_r;
	memset(magic_phrase, 0, phrase_size);
	lseek(fd_2, -of_s, 1);


	w_r = read(fd_2, magic_phrase, phrase_size);
	if (w_r < 0) {
      		printf("Failed to read the message from the device.");
      		return 0;
   	} else
		printf ("SOME MAGIC _read_:, %s\n", magic_phrase);



	printf("\nType a buffersize and press ENTER:\n");
	scanf("%d", &num);
	getchar();

	ioctl(fd, SEL_BUF_SIZE, (int *) &num);
	printf("Type some text to write and press ENTER:\n");
	scanf("%[^\n]%*c", buf);
	int buf_size = sizeof(buf);

	our_buf = write(fd, buf, buf_size);
	if (our_buf < 0) {
      		printf("Failed to write the message to the device `our_buf`.");
      		return 0;
   	} else 
		printf ("Written line: %s\n", buf);
	
	memset(buf, 0, buf_size);
	lseek(fd, 0, SEEK_SET);
	printf("Press ENTER to to read!");
	getchar();
    	
	our_buf = read(fd, buf, buf_size);
	if (our_buf < 0){
      		printf("Failed to read the message from the device `our_buf`.");
      		return 0;
   	} else
		printf ("Read line: %s\n", buf);
	
	close(fd);
	return 0;
}

