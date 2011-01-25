#define CONFIG_DIR "/home/polesz/Projektek/wxmppd/data"

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <libxml/parser.h>

#include "configfiles.h"

char *config_dir = NULL;

int
main(int argc, char **argv)
{
	xmlInitParser();
	LIBXML_TEST_VERSION;

	printf("%s\n", SYSCONFDIR);

	wxmppd_processConfigfile(CONFIG_DIR "/wxmppd.xml", 1);

	xmlCleanupParser();

	return 0;
}

