#include "module.h"

int wxmppd_mod_layer_gnutls_load(funcptr *);

const wxmppd_module_data_t module_data = {
	"layer-gnutls",
	"GnuTLS interface extension",
	(funcptr)wxmppd_mod_layer_gnutls_load,
};

int
wxmppd_mod_layer_gnutls_load(funcptr *global_functions)
{
	/* Register interface extension "layer-tls" */
}

