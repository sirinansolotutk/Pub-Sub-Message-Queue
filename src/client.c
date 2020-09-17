/* client.c: Message Queue Client */

#include "mq/client.h"
#include "mq/logging.h"
#include "mq/socket.h"
#include "mq/string.h"

/* Internal Constants */

#define SENTINEL "SHUTDOWN"

/* Internal Prototypes */

void * mq_pusher(void *);
void * mq_puller(void *);

/* External Functions */

/**
 * Create Message Queue withs specified name, host, and port.
 * @param   name        Name of client's queue.
 * @param   host        Address of server.
 * @param   port        Port of server.
 * @return  Newly allocated Message Queue structure.
 */
MessageQueue * mq_create(const char *name, const char *host, const char *port) {
    MessageQueue *mq = calloc(1, sizeof(MessageQueue));
    if (mq) {
        mq->name = strdup((char *)name);
        mq->host = strdup((char *)host);
        mq->port = strdup((char *)port);
        mq->outgoing = calloc(1, sizeof(Queue));
        mq->incoming = calloc(1, sizeof(Queue));
        mq->shutdown = false;
    }
    return mq;
}

/**
 * Delete Message Queue structure (and internal resources).
 * @param   mq      Message Queue structure.
 */
void mq_delete(MessageQueue *mq) {
    if (mq) {
        free(mq->name);
        free(mq->host);
        free(mq->port);
        queue_delete(mq->outgoing);
        queue_delete(mq->incoming);
        free(mq);
    }
}

/**
 * Publish one message to topic (by placing new Request in outgoing queue).
 * @param   mq      Message Queue structure.
 * @param   topic   Topic to publish to.
 * @param   body    Message body to publish.
 */
void mq_publish(MessageQueue *mq, const char *topic, const char *body) {
    Request *r = request_create("PUT",topic,body);
    mq->outgoing->tail->next = r;
    mq->outgoing->tail = r;
}

/**
 * Retrieve one message (by taking Request from incoming queue).
 * @param   mq      Message Queue structure.
 * @return  Newly allocated message body (must be freed).
 */
char * mq_retrieve(MessageQueue *mq) {
    Request *r = request_create("GET", mq->incoming->head->uri, NULL);
    if (!r){
        
    }
    mq->incoming->head = mq->incoming->head->next;
    return r->body;
}

/**
 * Subscribe to specified topic.
 * @param   mq      Message Queue structure.
 * @param   topic   Topic string to subscribe to.
 **/
void mq_subscribe(MessageQueue *mq, const char *topic) {
    uri = "/subscription/" + mq->name + "/" + topic; //use sprintf
    Request *r = request_create("PUT", uri, NULL);
    queue_push(mq->outgoing, r);
}

/**
 * Unubscribe to specified topic.
 * @param   mq      Message Queue structure.
 * @param   topic   Topic string to unsubscribe from.
 **/
void mq_unsubscribe(MessageQueue *mq, const char *topic) {
    uri = "/subscription/" + mq->name + "/" + topic;
    Request *r = request_create("DELETE", uri, NULL);
}

/**
 * Start running the background threads:
 *  1. First thread should continuously send requests from outgoing queue.
 *  2. Second thread should continuously receive reqeusts to incoming queue.
 * @param   mq      Message Queue structure.
 */
void mq_start(MessageQueue *mq) {
}

/**
 * Stop the message queue client by setting shutdown attribute and sending
 * sentinel messages
 * @param   mq      Message Queue structure.
 */
void mq_stop(MessageQueue *mq) {
}

/**
 * Returns whether or not the message queue should be shutdown.
 * @param   mq      Message Queue structure.
 */
bool mq_shutdown(MessageQueue *mq) {
    return (mq->shutdown);
}

/* Internal Functions */

/**
 * Pusher thread takes messages from outgoing queue and sends them to server.
 * @param   arg     Message Queue structure.
 **/
void * mq_pusher(void *arg) {
    return NULL;
}

/**
 * Puller thread requests new messages from server and then puts them in
 * incoming queue.
 * @param   arg     Message Queue structure.
 **/
void * mq_puller(void *arg) {
    return NULL;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
