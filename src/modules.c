#include <stdio.h>
#include <glib.h>

#include "modules.h"

int
wxmppd_loadModule(char *moduleName, gboolean dryRun)
{
	printf("Will load module %s\n", moduleName);
}

