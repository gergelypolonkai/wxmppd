/* wXMPPd - (Trying to be) full featured XMPP daemon
 * Copyright (C) 2011 Gergely Polonkai
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <glib.h>
#include <gmodule.h>

#include "wxmppd.h"
#include "modules.h"
#include "module.h"

funcptr wxmppd_functionTable[] = {
};

static void
loadModuleFromList(gpointer data, gpointer user_data)
{
	(void)wxmppd_loadModule((char *)data, FALSE);
}

int
wxmppd_setActiveModules(void)
{
	g_slist_foreach(activeConfig->modules_to_load, loadModuleFromList, NULL);
}

int
wxmppd_loadModule(char *moduleName, gboolean dryRun)
{
	gchar *moduleFile;
	GModule *module;
	wxmppd_module_data_t *module_data;

	moduleFile = g_strdup_printf("%s/lib%s.so", activeConfig->modules_dir, moduleName);

	if ((module = g_module_open(moduleFile, G_MODULE_BIND_LAZY)) == NULL)
	{
		g_printf("Unable to load module: %s\n", g_module_error());
		return 1;
	}

	if (!g_module_symbol(module, "module_data", (gpointer *)&module_data))
	{
		g_printf("Bad module: %s\n", g_module_error());
		if (!g_module_close(module))
		{
			g_printf("Unable to close module: %s\n", g_module_error());
		}

		return 1;
	}

	if (module_data == NULL)
	{
		g_printf("Bad module, it contains no module data structure!\n");
		if (!g_module_close(module))
		{
			g_printf("Unable to close module: %s\n", g_module_error());
		}

		return 1;
	}

	printf("Loaded module named '%s'\n", module_data->name);

	if (!g_module_close(module))
	{
		g_printf("Unable to close module: %s\n", g_module_error());
	}
}

