#include "module.h"

int wxmppd_mod_socket_tcpip_load(funcptr *);

const wxmppd_module_data_t module_data = {
	"socket-tcpip",
	"Module to provide TCP/IP based sockets for interfaces",
	&wxmppd_mod_socket_tcpip_load,
};

int wxmppd_mod_socket_tcpip_load(funcptr *global_functions)
{
	/* Register socket type "tcpip" */
	return 0;
}
