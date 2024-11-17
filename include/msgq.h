#ifndef msgq
#define msgq

#include <double_linked_list.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

//this is the structure that will be linked in the message_queue_t list_head structures
typedef struct
{
    struct list_node node;
    char buffer[];             //we don't know how long the message is going to be
}message_t;

//this is the actul message queue
typedef struct 
{
    struct list_head qh_free; //head of the list that contains the free slots for the messages
    struct list_head qh_busy; //head of the list that contains the busy slots for the messages
    size_t msg_size;          //the maximum size of a message
    pthread_mutex_t mutex;    //used to protect the push and pop operation - it give exclusive access to a single thread at one certain point in time,
                              //to perform a certain operation operation
    sem_t slots_free;         //counting semaphore - is shows how many empty slots we have in a certain moment, if 0, then the manager thread halts
    sem_t slots_busy;         //counting semaphore - is shows how many busy slots we have in a certain moment, if 0, then the processing threads halt
} message_queue_t;

message_queue_t * create_msgq(int message_size, int queue_size);

void detele_msgq(message_queue_t * queue);

//push   (send receive)
int mq_push(message_queue_t * mq, char *buffer, size_t len);

//pop
int mq_pop(message_queue_t * mq, char *buf, size_t len);

#endif