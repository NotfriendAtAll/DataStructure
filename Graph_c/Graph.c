#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#define MAXSIZE 5

typedef struct Graph {
  char *vexs;//顶点
  int **arcs;//边
  int vexNum;
  int arcNum;
} Graph;

Graph *initGraph(int vexNum) {
  Graph *G = (Graph *)malloc(sizeof(Graph));
  G->vexs = (char *)malloc(sizeof(char) * vexNum);
  G->arcs = (int **)malloc(sizeof(int *) * vexNum);//二级指针开辟内存，这个要知道。
  for (int i = 0; i < vexNum; i++) {
    G->arcs[i] = (int *)malloc(sizeof(int) * vexNum);
  }
  G->vexNum = vexNum; //初始化一个图。
  G->arcNum = 0;
  return G;
}

//这是用邻阶矩阵所创建的。
void createGraph(Graph *G, char *vexs, int *arcs) {
  for (int i = 0; i < G->vexNum; i++) {
    G->vexs[i] = vexs[i];
    for (int j = 0; j < G->vexNum; j++) {
      G->arcs[i][j] = *(arcs + i * G->vexNum + j);//地址偏移，类似int int arr[5]; *(arr+3);不同的是，这是一个二维数组，偏移包括行(i*G->vexNum)和列(j)。
      if (G->arcs[i][j] != 0)
        G->arcNum++;
    }
  }
  G->arcNum /= 2;
}

void DFS(Graph *G, int *visited, int index) {
  printf("%c\t", G->vexs[index]);//遍历当前节点，做打印操作。
  visited[index] = 1;// visited数组用于记录遍历的节点，遍历过就设成1。同时插入队列。
  for (int i = 0; i < G->vexNum; i++) {
    if (G->arcs[index][i] == 1 && !visited[i]) {
      DFS(G, visited, i);
    }//if判断是否遍历过，如果遍历过，就遍历下一个。
  }
}

void BFS(Graph *G, int *visited, int index) {
  Queue *Q = initQueue();
  printf("%c\t", G->vexs[index]);
  visited[index] = 1;//visited数组用于记录遍历的节点，遍历过就设成1。同时插入队列。
  enQueue(Q, index);
  while (!isEmpty(Q)) {
    int i = deQueue(Q);
    for (int j = 0; j < G->vexNum; j++) {
      if (G->arcs[i][j] == 1 && !visited[j]) {
        printf("%c\t", G->vexs[j]);
        visited[j] = 1;
        enQueue(Q, j);
      }
    }
  }
}

int main() {
  Graph *G = initGraph(5);
  int *visited = (int *)malloc(sizeof(int) * G->vexNum);
  for (int i = 0; i < G->vexNum; i++)
    visited[i] = 0;
  int arcs[5][5] = {0, 1, 1, 1, 0,
                    1, 0, 1, 1, 1, 
                    1, 1, 0, 0, 0, 
                    1, 1, 0, 0, 1, 
                    0, 1, 0, 1,0};//test数组
  createGraph(G, "ABCDE", (int *)arcs);
  DFS(G, visited, 0);
  printf("\n");
  for (int i = 0; i < G->vexNum; i++)
    visited[i] = 0;
  BFS(G, visited, 0);
  printf("\n");
  return 0;
}
// 本代码来自b站up主，@tyrantlucifer。