#ifndef BANK_QUEUE_H
#define BANK_QUEUE_H

#include <pthread.h>
#include <semaphore.h>

// Queue node
typedef struct Node {
  int customerID;
  struct Node* next;
} Node;

// Queue structure
typedef struct {
  Node* head;
  Node* tail;
  pthread_mutex_t mutex;
  sem_t customers;  // Semaphore indicating the count of customers waiting
} Queue;

// Function prototypes
void queue_init(Queue* q);
void enqueue(Queue* q, int customerID);
int dequeue(Queue* q);
void queue_destroy(Queue* q);
void* teller(void* arg);

#endif  // BANK_QUEUE_H
