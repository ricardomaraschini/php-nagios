#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <zmq.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <jansson.h>
#include "../include/nebcallbacks.h"
#include "../include/nagios.h"
#include "../include/objects.h"

NEB_API_VERSION(CURRENT_NEB_API_VERSION);
static nebmodule	*mhandle;
extern struct host	*host_list;
extern struct service	*service_list;
pid_t			 phppid;

int
answer(char *msg, zmq_msg_t *out)
{
	int	 len;

	len = strlen(msg);
	zmq_msg_init_size(out, len);
	memcpy(zmq_msg_data(out), msg, len);

	return len;
}

void
requests_loop()
{
	void		*context;
	void		*responder;
	zmq_msg_t	 in;
	zmq_msg_t	 out;
	int		 len;
	char		*msg;

	context = zmq_ctx_new();
	responder = zmq_socket(context, ZMQ_REP);
	zmq_bind(responder, "tcp://*:6960");
	while(TRUE) {
		zmq_msg_init(&in);
		len = zmq_msg_recv(&in, responder, 0);

		msg = calloc(len+1, sizeof(char));
		memcpy(msg, zmq_msg_data(&in), len);
		zmq_msg_close(&in);

		len = answer(msg, &out);

		zmq_msg_send(&out, responder, ZMQ_DONTWAIT);
		zmq_msg_close(&out);
	}

}

int
handle_state_change_data(int type, void *data)
{
	/*
	FILE *fp = NULL;
	fp = fopen("/tmp/mydebug", "a");
	fprintf(fp, "+\n");
	fclose(fp);
	*/

	return OK;
}

int
nebmodule_init(int flags, char *args, void *handle)
{
	mhandle = (nebmodule *)handle;

	/*
	neb_register_callback(
	    NEBCALLBACK_SERVICE_STATUS_DATA,
	    mhandle,
	    0,
	    handle_state_change_data
	);
	neb_register_callback(
	    NEBCALLBACK_HOST_STATUS_DATA,
	    mhandle,
	    0,
	    handle_state_change_data
	);
	*/

	phppid = fork();
	if (phppid == 0)
		requests_loop();

	return OK;
}

int
nebmodule_deinit(int flags, int reason)
{
	int	 ret;

	/*
	neb_deregister_callback(
	    NEBCALLBACK_SERVICE_STATUS_DATA,
	    handle_state_change_data
	);
	neb_deregister_callback(
	    NEBCALLBACK_HOST_STATUS_DATA,
	    handle_state_change_data
	);
	*/

	kill(phppid, SIGKILL);
	waitpid(phppid, &ret, 0);

	return OK;
}
