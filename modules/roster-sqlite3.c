#include "module.h"

int wxmppd_mod_roster_sqlite3_load(funcptr *);

const wxmppd_module_data_t module_data = {
	"roster-sqlite3",
	"SQLite3 storage module for roster data storage",
	(funcptr)wxmppd_mod_roster_sqlite3_load,
};

int
wxmppd_mod_roster_sqlite3_load(funcptr *global_functions)
{
	/* Register roster storage extension "sqlite3" */
}

