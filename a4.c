#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Define the number of customers and tellers
#define NUM_CUSTOMERS 10
#define NUM_TELLERS 3

// Declare a semaphore
sem_t semaphore;

// Function to simulate serving a customer
void serveCustomer(int customerID) {
  // Generate a random service time between 1 and 30 seconds
  int serviceTime = rand() % 30 + 1;

  // Print a message indicating the customer is being served
  printf("Serving customer %d for %d seconds.\n", customerID, serviceTime);
  // Simulate service time
  sleep(serviceTime);
  // Print a message indicating the customer has been served
  printf("Finished serving customer %d.\n", customerID);
}

// Thread function for each customer
void* customerThread(void* arg) {
  // Extract the customer ID from the argument
  int customerID = *((int*)arg);

  // Wait for a teller (semaphore) to become available
  sem_wait(&semaphore);
  // Serve the customer
  serveCustomer(customerID);
  // Signal that the teller is now available
  sem_post(&semaphore);

  return NULL;
}

int main() {
  // Seed the random number generator
  srand(time(NULL));

  // Declare an array for the customer threads
  pthread_t threads[NUM_CUSTOMERS];
  // Declare an array to hold customer IDs
  int customerIDs[NUM_CUSTOMERS];

  // Initialize the semaphore with the number of tellers
  sem_init(&semaphore, 0, NUM_TELLERS);

  // Create a thread for each customer
  for (int i = 0; i < NUM_CUSTOMERS; i++) {
    customerIDs[i] = i;
    pthread_create(&threads[i], NULL, customerThread, &customerIDs[i]);
  }

  // Wait for all customer threads to finish
  for (int i = 0; i < NUM_CUSTOMERS; i++) {
    pthread_join(threads[i], NULL);
  }

  // Clean up the semaphore
  sem_destroy(&semaphore);

  return 0;
}
