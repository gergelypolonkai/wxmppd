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
wxmppd_processConfigfile(const char *file, int startup)
{
	xmlDocPtr doc;
	xmlXPathContextPtr xpathCtx;
	xmlXPathObjectPtr xpathObject;
	int i;

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

	printf("%d nodes found.\n", xpathObject->nodesetval->nodeNr);
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

		wxmppd_loadModule(xpathObject->nodesetval->nodeTab[i]->children->content);
	}

	xmlXPathFreeContext(xpathCtx);
	xmlXPathFreeObject(xpathObject);

	return WXMPPD_CONFIG_SUCCESS;
}

