#include <stdio.h>
#if (HAVE_MMAP == 1)
# include <mman.h>
# include <unistd.h>
#endif
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

			wxmppd_loadModule(xpathObject->nodesetval->nodeTab[i]->children->content, (config == NULL));
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

