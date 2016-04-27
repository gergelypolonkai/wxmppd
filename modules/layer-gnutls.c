#include "module.h"

int wxmppd_mod_layer_gnutls_load(funcptr *);

char *wxmppd_mod_layer_gnutls_runtime_conflicts[] = {
	"layer-openssl",
};

const wxmppd_module_data_t module_data = {
	"layer-gnutls",
	"GnuTLS interface extension",
	NULL,
	NULL,
	NULL,
	&wxmppd_mod_layer_gnutls_runtime_conflicts,
	(funcptr)wxmppd_mod_layer_gnutls_load,
};

int
wxmppd_mod_layer_gnutls_load(funcptr *global_functions)
{
	/* Register interface extension "layer-tls" */
}

