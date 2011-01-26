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

#ifndef __WXMPPD_CONFIGFILES_H
# define __WXMPPD_CONFIGFILES_H

#include <glib.h>

enum {
	WXMPPD_CONFIG_SUCCESS = 0,
	WXMPPD_CONFIG_BADFILE,
};

typedef struct _wxmppd_config_t {
	char *modules_dir;
	GSList *modules_to_load;
} wxmppd_config_t;

int wxmppd_processConfigfile(const char *file, int startup, wxmppd_config_t **config);
wxmppd_config_t *wxmppd_copyConfig(wxmppd_config_t *src);
void wxmppd_freeConfig(wxmppd_config_t **config);

#endif /* __WXMPPD_CONFIGFILES_H */

