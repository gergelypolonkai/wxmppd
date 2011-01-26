#include "module.h"

int wxmppd_mod_auth_gsasl_load(funcptr *);

const wxmppd_module_data_t module_data = {
	"auth-gsasl",
	"GNU SASL authentication extension",
	(funcptr)wxmppd_mod_auth_gsasl_load,
};

int
wxmppd_mod_auth_gsasl_load(funcptr *global_functions)
{
	/* Register authentication extension "auth-gsasl" */
}

