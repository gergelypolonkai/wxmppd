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
#include <libxml/xpath.h>

#include "configfiles.h"
#include "modules.h"

int
wxmppd_processConfigfile(const char *file, int startup, wxmppd_config_t **config)
{
	xmlDocPtr doc;
	xmlXPathContextPtr xpathCtx;
	xmlXPathObjectPtr xpathObject;
	int i;

	if (config)
	{
		*config = g_new0(wxmppd_config_t, 1);
	}

	if ((doc = xmlParseFile(file)) == NULL)
	{
		printf("Config file error!\n");
		return WXMPPD_CONFIG_BADFILE;
	}

	xpathCtx = xmlXPathNewContext(doc);
	if ((xpathObject = xmlXPathEvalExpression("/wxmppd/modules/load", xpathCtx)) == NULL)
	{
		printf("Config file error during xpath!\n");
		xmlXPathFreeContext(xpathCtx);
		return WXMPPD_CONFIG_BADFILE;
	}

	if (xpathObject->nodesetval)
	{
		for (i = 0; i < xpathObject->nodesetval->nodeNr; i++)
		{
			xmlNodePtr textNode;

			if (xmlChildElementCount(xpathObject->nodesetval->nodeTab[i]) > 0)
			{
				printf("Config file error! modules/load elements cannot have children!\n");
				xmlXPathFreeContext(xpathCtx);
				xmlXPathFreeObject(xpathObject);
				return WXMPPD_CONFIG_BADFILE;
			}

			if (config)
			{
				(*config)->modules_to_load = g_slist_append((*config)->modules_to_load, g_strdup(xpathObject->nodesetval->nodeTab[i]->children->content));
			}
		}
	}

	xmlXPathFreeObject(xpathObject);

	if ((xpathObject = xmlXPathEvalExpression("/wxmppd/modules/module-dir", xpathCtx)) == NULL)
	{
		printf("Config file error during xpath!\n");
		xmlXPathFreeContext(xpathCtx);
		return WXMPPD_CONFIG_BADFILE;
	}

	if (xpathObject->nodesetval)
	{
		if (xpathObject->nodesetval->nodeNr > 1)
		{
			printf("Config file cannot contain more than one module-dir definition!\n");
			xmlXPathFreeObject(xpathObject);
			xmlXPathFreeContext(xpathCtx);
			return WXMPPD_CONFIG_BADFILE;
		}
		else if (xpathObject->nodesetval->nodeNr == 1)
		{
			if (xmlChildElementCount(xpathObject->nodesetval->nodeTab[0]) > 0)
			{
				printf("Config file error! modules/load elements cannot have children!\n");
				xmlXPathFreeContext(xpathCtx);
				xmlXPathFreeObject(xpathObject);
				return WXMPPD_CONFIG_BADFILE;
			}

			if (config)
			{
				(*config)->modules_dir = g_strdup(xpathObject->nodesetval->nodeTab[0]->children->content);
			}
		}
	}

	xmlXPathFreeContext(xpathCtx);

	return WXMPPD_CONFIG_SUCCESS;
}

wxmppd_config_t *
wxmppd_copyConfig(wxmppd_config_t *src)
{
	wxmppd_config_t *temp;

	temp = g_new0(wxmppd_config_t, 1);

	if (src->modules_dir != NULL)
	{
		temp->modules_dir = g_strdup(src->modules_dir);
	}

	if (src->modules_to_load)
	{
		guint i;

		temp->modules_to_load = NULL;

		for (i = 0; i < g_slist_length(src->modules_to_load); i++)
		{
			temp->modules_to_load = g_slist_append(temp->modules_to_load, g_strdup(g_slist_nth(src->modules_to_load, i)->data));
		}
	}

	return temp;
}

static void
free_slist_data_cb(gpointer data, gpointer user_data)
{
	g_free(data);
}

void
wxmppd_freeConfig(wxmppd_config_t **config)
{
	if (*config)
	{
		if ((*config)->modules_dir)
		{
			g_free((*config)->modules_dir);
		}
		if ((*config)->modules_to_load)
		{
			g_slist_foreach((*config)->modules_to_load, free_slist_data_cb, NULL);
			g_slist_free((*config)->modules_to_load);
		}

		g_free(*config);
	}

	*config = NULL;
}

