//This file defines the use of mmap

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

int main(int argc, char const *argv[])
{
	/* code */
	int fdS,fdR;
	struct stat myfstat;

	fdS =  open("sender.txt",O_RDONLY);

	if(fdS < 0)
	{
		perror("open S: ");
		close(fdS);
		exit(1);
	}

	fstat(fdS,&myfstat);

	fdR = open("recver.txt",O_CREAT | O_WRONLY);

	if(fdR < 0)
	{
		perror("open R: ");
		close(fdR);
		exit(1);
	}

	sendfile(fdR,fdS,0,myfstat.st_size);

	//fsync(fdR);

	close(fdR);
	close(fdS);

	return 0;
}

