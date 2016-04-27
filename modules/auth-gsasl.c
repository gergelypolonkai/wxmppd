#include "module.h"

int wxmppd_mod_auth_gsasl_load(funcptr *);

char *wxmppd_mod_auth_gsasl_runtime_conflicts = {
	"auth-cyrus-sasl",
	NULL,
};

const wxmppd_module_data_t module_data = {
	"auth-gsasl",
	"GNU SASL authentication extension",
	NULL,
	NULL,
	NULL,
	&wxmppd_mod_auth_gsasl_runtime_conflicts,
	(funcptr)wxmppd_mod_auth_gsasl_load,
};

int
wxmppd_mod_auth_gsasl_load(funcptr *global_functions)
{
	/* Register authentication extension "auth-gsasl" */
}

