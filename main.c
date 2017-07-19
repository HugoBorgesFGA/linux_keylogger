#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

static const char *const evval[3] = {
	"RELEASED",
	"PRESSED",
	"REPEATED"
};

int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		printf("Missing arguments... \n");
		printf("Usage: %s <input_dev> \n", argv[0]);
		return -1;
	}

	// Get the device path by command args
	const char *dev = argv[1];
	struct input_event ev;
	ssize_t n;
	int fd;

	fd = open(dev, O_RDONLY);
	if (fd == -1)
	{
		printf("Could not open the device... \n");
		printf("Reason: %s \n", strerror(errno));
		return -2;
	}

	while(1)
	{
		n = read(fd, &ev, sizeof ev);
		if (n == (ssize_t) -1)
		{
			if (errno == EINTR)
			{
				continue; // why?
			}
			else
			{
				printf("Error: %s", strerror(errno));
				return -3;
			}
		}
		
		// Partial read of event structure
		if (n != sizeof ev)
		{
			errno = EIO;
			continue;
		}

		if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2)
		{
            printf("%s 0x%04x (%d)\n", evval[ev.value], (int)ev.code, (int)ev.code);
		}
	}

	fflush(stdout);
	printf("Leaving...");
	return 0;
}