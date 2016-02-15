#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_nagios.h"

static function_entry nagios_functions[] = {
	PHP_FE(hello_nagios, NULL)
	{NULL, NULL, NULL}
};

zend_module_entry nagios_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_NAGIOS_EXTNAME,
    nagios_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_NAGIOS_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_HELLO
ZEND_GET_MODULE(nagios)
#endif

PHP_FUNCTION(hello_nagios)
{
    RETURN_STRING("Hello from nagios module", 1);
}
