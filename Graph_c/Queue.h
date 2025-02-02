#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 5

typedef struct Queue {
  int front;
  int rear;
  int data[MAXSIZE];
} Queue;

Queue *initQueue() {
  Queue *Q = (Queue *)malloc(sizeof(Queue));
  Q->front = Q->rear = 0;
  return Q;
}

int isFull(Queue *Q) {
  if ((Q->rear + 1) % MAXSIZE == Q->front) {
    return 1;
  } else {
    return 0;
  }
}

int isEmpty(Queue *Q) {
  if (Q->front == Q->rear) {
    return 1;
  } else {
    return 0;
  }
}

int enQueue(Queue *Q, int data) {
  if (isFull(Q)) {
    return 0;
  } else {
    Q->data[Q->rear] = data;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return 1;
  }
}

int deQueue(Queue *Q) {
  if (isEmpty(Q)) {
    return -1;
  } else {
    int data = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return data;
  }
}

