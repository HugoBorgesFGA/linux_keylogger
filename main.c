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

const char *keyByCode(int code)
{
	switch(code)
	{
		case KEY_ESC: return "<ESC>";
		case KEY_1: return "1";
		case KEY_2: return "2";
		case KEY_3: return "3";
		case KEY_4: return "4";
		case KEY_5: return "5";
		case KEY_6: return "6";
		case KEY_7: return "7";
		case KEY_8: return "8";
		case KEY_9: return "9";
		case KEY_0: return "0";
		case KEY_MINUS: return "-";
		case KEY_EQUAL: return "+";
		case KEY_BACKSPACE: return "<BACKSPACE>";
		case KEY_TAB: return "\t";
		case KEY_Q: return "q";
		case KEY_W: return "w";
		case KEY_E: return "e";
		case KEY_R: return "r";
		case KEY_T: return "t";
		case KEY_Y: return "y";
		case KEY_U: return "u";
		case KEY_I: return "i";
		case KEY_O: return "o";
		case KEY_P: return "p";
		case KEY_LEFTBRACE: return "(";
		case KEY_RIGHTBRACE: return ")";
		case KEY_ENTER: return "\n";
		case KEY_LEFTCTRL: return "<LEFT_CTRL>";
		case KEY_A: return "a";
		case KEY_S: return "s";
		case KEY_D: return "d";
		case KEY_F: return "f";
		case KEY_G: return "g";
		case KEY_H: return "h";
		case KEY_J: return "j";
		case KEY_K: return "k";
		case KEY_L: return "l";
		case KEY_SEMICOLON: return ";";
		case KEY_APOSTROPHE: return "'";
		case KEY_GRAVE: return "`";
		case KEY_LEFTSHIFT: return "<LEFT_SHIFT>";
		case KEY_BACKSLASH: return "\\";
		case KEY_Z: return "z";
		case KEY_X: return "x";
		case KEY_C: return "c";
		case KEY_V: return "v";
		case KEY_B: return "b";
		case KEY_N: return "n";
		case KEY_M: return "m";
		case KEY_COMMA: return ",";
		case KEY_DOT: return ".";
		case KEY_SLASH: return "/";
		case KEY_RIGHTSHIFT: return "<RIGHT_SHIFT>";
		case KEY_KPASTERISK: return "*";
		case KEY_LEFTALT: return "<LEFT_ALT>";
		case KEY_SPACE: return " ";
		case KEY_CAPSLOCK: return "<CAPS_LOCK>";
		case KEY_F1: return "F1";
		case KEY_F2: return "F2";
		case KEY_F3: return "F3";
		case KEY_F4: return "F4";
		case KEY_F5: return "F5";
		case KEY_F6: return "F6";
		case KEY_F7: return "F7";
		case KEY_F8: return "F8";
		case KEY_F9: return "F9";
		case KEY_F10: return "F10";
		case KEY_NUMLOCK: return "<NUM_LOCK>";
		case KEY_SCROLLLOCK: return "<SCROLL_LOCK>";

		case KEY_102ND: return "";
		case KEY_F11: return "F11";
		case KEY_F12: return "F12";

		case KEY_RIGHTALT: return "<ALT_RIGHT>";
		case KEY_HOME: return "<HOME>";
		case KEY_UP: return "<ARROW_UP>";
		case KEY_PAGEUP: return "<PAGE_UP>";
		case KEY_LEFT: return "<ARROW_LEFT>";
		case KEY_RIGHT: return "<ARROW_RIGHT>";
		case KEY_END: return "<END>";
		case KEY_DOWN: return "<ARROW_DOWN>";
		case KEY_PAGEDOWN: return "<PAGEDOWN>";
		case KEY_INSERT: return "<INSERT>";
		case KEY_DELETE: return "<DELETE>";
		default: return "<UNKNOWN>";
	}
}


int main(int argc, char *argv[])
{
	unsigned int isCapslock = 0;

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
			if (ev.value == 1) //PRESSED
			{
	            //printf("%s 0x%04x (%d)\n", evval[ev.value], (int)ev.code, (int)ev.code);
	            printf("%s", keyByCode(ev.code));
	            fflush(stdout);
        	}
		}
	}

	fflush(stdout);
	printf("Leaving...");
	return 0;
}