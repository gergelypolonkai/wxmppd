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
#include <libxml/parser.h>

#include "configfiles.h"

gchar *config_dir = NULL;
gchar *cl_modules_dir = NULL;
gchar *cl_keys_file = NULL;

wxmppd_config_t *activeConfig = NULL;

static GOptionEntry optionEntries[] = {
	{ "config-dir", 'c', 0, G_OPTION_ARG_FILENAME, &config_dir,    "Directory where configuration files can be found", "DIRECTORY" },
	{ "module-dir", 'm', 0, G_OPTION_ARG_FILENAME, &cl_modules_dir, "Directory of the module files",                    "DIRECTORY" },
	{ "keys-file",  'k', 0, G_OPTION_ARG_FILENAME, &cl_keys_file,  "Path to key store file",                           "FILE"      },
	{ NULL },
};

int
main(int argc, char **argv)
{
	GError *err;
	GOptionContext *optContext;
	gchar *configFile;
	wxmppd_config_t *configObject;

	optContext = g_option_context_new("- XMPP daemon");
	g_option_context_add_main_entries(optContext, optionEntries, NULL);

	if (!g_option_context_parse(optContext, &argc, &argv, &err))
	{
		g_print("Option parsing failed (%s)!\n", err->message);
		return 1;
	}

	if (config_dir == NULL)
	{
		config_dir = g_strdup_printf("%s/wxmppd", SYSCONFDIR);
	}

	configFile = g_strdup_printf("%s/wxmppd.xml", config_dir);

	xmlInitParser();
	LIBXML_TEST_VERSION;

	if (wxmppd_processConfigfile(configFile, 1, &configObject) != WXMPPD_CONFIG_SUCCESS)
	{
		return 1;
	}

	activeConfig = wxmppd_copyConfig(configObject);
	wxmppd_freeConfig(&configObject);

	if (cl_modules_dir != NULL)
	{
		if (activeConfig->modules_dir != NULL)
		{
			g_free(activeConfig->modules_dir);
		}
		activeConfig->modules_dir = g_strdup(cl_modules_dir);
	}

	if (activeConfig->modules_dir == NULL)
	{
		activeConfig->modules_dir = g_strdup_printf("%s/wxmppd", LIBDIR);
	}

	wxmppd_setActiveModules();

	xmlCleanupParser();

	return 0;
}

