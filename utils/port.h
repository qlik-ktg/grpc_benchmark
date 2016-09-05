#ifndef UTILS_PORT_H_
#define UTILS_PORT_H_

#ifdef __cplusplus
extern "C" {
#endif

/* pick a port number that is currently unused by either tcp or udp. return
 0 on failure. */
int grpc_pick_unused_port(void);
/* pick a port number that is currently unused by either tcp or udp. abort
 on failure. */
int grpc_pick_unused_port_or_die(void);

/* Return a port which was previously returned by grpc_pick_unused_port().
 * Implementations of grpc_pick_unused_port() backed by a portserver may limit
 * the total number of ports available; this lets a binary return its allocated
 * ports back to the server if it is going to allocate a large number. */
void grpc_recycle_unused_port(int port);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_PORT_H_ */
