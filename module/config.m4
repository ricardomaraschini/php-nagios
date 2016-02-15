PHP_ARG_ENABLE(
	nagios,
	Whether to enable Nagios support,
	[ --enable-nagios   Enable Nagios support]
)

if test "$PHP_NAGIOS" = "yes"; then
	AC_DEFINE(HAVE_NAGIOS, 1, [Whether you have Nagios])
	PHP_NEW_EXTENSION(nagios, nagios.c, $ext_shared)
fi
