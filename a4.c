#include "a4.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_TELLERS 3
#define NUM_CUSTOMERS 10

// Function to initialize the queue
void queue_init(Queue* q) {
  q->head = q->tail = NULL;
  pthread_mutex_init(&q->mutex, NULL);
  sem_init(&q->customers, 0, 0);  // Initialize to 0 because the queue is empty
}

// Function to enqueue a customer ID
void enqueue(Queue* q, int customerID) {
  Node* new_node = (Node*)malloc(sizeof(Node));
  if (!new_node) return;

  new_node->customerID = customerID;
  new_node->next = NULL;

  pthread_mutex_lock(&q->mutex);
  if (q->tail) {
    q->tail->next = new_node;
  } else {
    q->head = new_node;
  }
  q->tail = new_node;

  printf("Customer %d is waiting in the queue.\n", customerID);
  sem_post(&q->customers);  // Signal that a customer is waiting
  pthread_mutex_unlock(&q->mutex);
}

// Function to dequeue a customer ID
int dequeue(Queue* q) {
  sem_wait(&q->customers);  // Wait for a customer to be in the queue

  pthread_mutex_lock(&q->mutex);
  if (!q->head) {  // This should not happen as sem_wait ensures the queue is
                   // not empty
    pthread_mutex_unlock(&q->mutex);
    return -1;
  }
  Node* temp = q->head;
  int customerID = temp->customerID;
  q->head = q->head->next;
  if (!q->head) {
    q->tail = NULL;
  }
  pthread_mutex_unlock(&q->mutex);

  free(temp);
  return customerID;
}

// Function to destroy the queue
void queue_destroy(Queue* q) {
  pthread_mutex_destroy(&q->mutex);
  sem_destroy(&q->customers);
  while (q->head) {
    Node* temp = q->head;
    q->head = q->head->next;
    free(temp);
  }
}

Queue customerQueue;

// Teller thread function
void* teller(void* arg) {
  int tellerID = *(int*)arg;
  while (1) {
    printf("Teller %d is waiting for a customer.\n", tellerID);
    int customerID = dequeue(&customerQueue);
    if (customerID == -1) break;  // Stop condition (you can define your own)
    int sleepTime = rand() % 20 + 5;  // Random number between 5 and 30
    printf("Teller %d is serving customer %d for %d seconds.\n", tellerID,
           customerID, sleepTime);
    // Simulate serving time
    sleep(sleepTime);
    printf("Teller %d has finished serving customer %d.\n", tellerID,
           customerID);
  }
  return NULL;
}

int main() {
  srand(time(NULL));  // Seed the random number generator

  queue_init(&customerQueue);  // Initialize the customer queue

  pthread_t tellers[NUM_TELLERS];
  int tellerIDs[NUM_TELLERS];

  // Start teller threads
  for (int i = 0; i < NUM_TELLERS; i++) {
    tellerIDs[i] = i;
    if (pthread_create(&tellers[i], NULL, teller, &tellerIDs[i])) {
      perror("Failed to create teller thread");
    }
  }

  // Enqueue customers
  for (int i = 0; i < NUM_CUSTOMERS; i++) {
    enqueue(&customerQueue, i);
  }

  // Wait for all customers to be served
  for (int i = 0; i < NUM_TELLERS; i++) {
    pthread_join(tellers[i], NULL);
  }

  queue_destroy(&customerQueue);  // Clean up the queue

  return 0;
}
