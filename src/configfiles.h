#ifndef __WXMPPD_CONFIGFILES_H
# define __WXMPPD_CONFIGFILES_H

enum {
	WXMPPD_CONFIG_SUCCESS = 0,
	WXMPPD_CONFIG_BADFILE,
};

typedef struct _wxmppd_config_t {
	char *modules_dir;
} wxmppd_config_t;

int wxmppd_processConfigfile(const char *file, int startup, wxmppd_config_t **config);

#endif /* __WXMPPD_CONFIGFILES_H */

