#ifndef __WXMPPD_MODULE_H
# define __WXMPPD_MODULE_H

typedef int * (*funcptr) ();

typedef struct _wxmppd_module_data_t {
	char *name;
	char *description;
	char **load_deps;
	char **runtime_deps;
	char **load_conflicts;
	char **runtime_conflicts;
	funcptr *load_func;
} wxmppd_module_data_t;

#endif /* __WXMPPD_MODULE_H */
