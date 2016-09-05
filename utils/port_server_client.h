#ifndef UTILS_PORT_SERVER_CLIENT_H_
#define UTILS_PORT_SERVER_CLIENT_H_


// C interface to port_server.py

int grpc_pick_port_using_server(char *server);
void grpc_free_port_using_server(char *server, int port);


#endif /* UTILS_PORT_SERVER_CLIENT_H_ */
