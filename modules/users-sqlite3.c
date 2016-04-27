#include "module.h"

int wxmppd_mod_users_sqlite3_load(funcptr *);

const wxmppd_module_data_t module_data = {
	"users-sqlite3",
	"SQLite3 storage module for user data storage",
	NULL,
	NULL,
	NULL,
	NULL,
	(funcptr)wxmppd_mod_users_sqlite3_load,
};

int
wxmppd_mod_users_sqlite3_load(funcptr *global_functions)
{
	/* Register user storage extension "sqlite3" */
}

