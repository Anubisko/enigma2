#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/stat.h>
#include  <pthread.h> 

#include <lib/base/eerror.h>
#include <lib/driver/vfd.h>

#if defined(HAVE_GIGABLUE_TEXTLCD)
#define VFD_DEVICE "/proc/vfd"
#endif

evfd* evfd::instance = NULL;

evfd* evfd::getInstance()
{
	if (instance == NULL)
		instance = new evfd;
	return instance;
}

evfd::evfd()
{
#if defined(HAVE_GIGABLUE_TEXTLCD)
	file_vfd = 0;
#endif
}


int vfd_init( void )
{
	evfd vfd;
#if defined(HAVE_GIGABLUE_TEXTLCD)
	vfd.vfd_led("1");
	char str[]="RED";
#elif defined(HAVE_VENTON_TEXTLCD)
	vfd.vfd_symbol_network(0);
	vfd.vfd_symbol_circle(0);
#endif
	return 0;
}

void evfd::init()
{
	vfd_init();
	return;
}

evfd::~evfd()
{
}

void evfd::vfd_led(char * led)
{
#if defined(HAVE_GIGABLUE_TEXTLCD)
	FILE *f;
	if((f = fopen("/proc/stb/fp/led0_pattern","w")) == NULL) {
		eDebug("cannot open /proc/stb/fp/led0_pattern (%m)");
		return;
	}
	
	fprintf(f,"%s", led);
	fclose(f);
#endif
}

void evfd::vfd_write_string(char * str)
{
#if defined(HAVE_GIGABLUE_TEXTLCD)
	FILE *f;
	if((f = fopen("/proc/vfd","w")) == NULL) {
		eDebug("cannotopen /proc/vfd (%m)");
	
		return;
	}
	
	fprintf(f,"%s", str);
	fclose(f);
#endif
}

void evfd::vfd_symbol_network(int net)
{
#if defined(HAVE_VENTON_TEXTLCD)
	FILE *f;
	if((f = fopen("/proc/stb/lcd/symbol_network","w")) == NULL) {
		eDebug("cannot open /proc/stb/lcd/symbol_network (%m)");
		return;
	}
	
	fprintf(f,"%i", net);
	fclose(f);
#endif
}

void evfd::vfd_symbol_circle(int cir)
{
#if defined(HAVE_VENTON_TEXTLCD)
	FILE *f;
	if((f = fopen("/proc/stb/lcd/symbol_circle","w")) == NULL) {
		eDebug("cannotopen /proc/stb/lcd/symbol_circle (%m)");
		return;
	}
	
	fprintf(f,"%i", cir);
	fclose(f);
#endif
}
