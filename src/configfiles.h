#ifndef __WXMPPD_CONFIGFILES_H
# define __WXMPPD_CONFIGFILES_H

enum {
	WXMPPD_CONFIG_SUCCESS = 0,
	WXMPPD_CONFIG_BADFILE,
};

int wxmppd_processConfigfile(const char *file, int startup);

#endif /* __WXMPPD_CONFIGFILES_H */

