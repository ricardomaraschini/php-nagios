#ifndef PHP_NAGIOS_H
#define PHP_NAGIOS_H 1
#define PHP_NAGIOS_VERSION "1.0"
#define PHP_NAGIOS_EXTNAME "nagios"

PHP_FUNCTION(hello_nagios);

extern zend_module_entry nagios_module_entry;
#define phpext_nagios_ptr &nagios_module_entry

#endif
