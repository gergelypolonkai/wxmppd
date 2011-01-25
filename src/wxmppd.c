#include <stdio.h>
#include <glib.h>
#include <libxml/parser.h>

#include "configfiles.h"

gchar *config_dir = NULL;
gchar *cl_modules_dir = NULL;
gchar *cl_keys_file = NULL;

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

	if (cl_modules_dir != NULL)
	{
		if (configObject->modules_dir != NULL)
		{
			g_free(configObject->modules_dir);
		}
		configObject->modules_dir = g_strdup(cl_modules_dir);
	}

	if (configObject->modules_dir == NULL)
	{
		configObject->modules_dir = g_strdup_printf("%s/wxmppd", LIBDIR);
	}

	printf("%s\n", configObject->modules_dir);

	xmlCleanupParser();

	return 0;
}

