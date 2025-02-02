#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

class Graph {
public:
  class Node {
  public:
    std::string name;
    std::vector<std::shared_ptr<Node>> neighbors;
    explicit Node(std::string nodeName) : name(std::move(nodeName)) {}
  };
  std::unordered_map<std::string, std::shared_ptr<Node>> nodes;

  void addNode(const std::string &nodeName) {
    if (!nodes.count(nodeName)) {
      nodes[nodeName] = std::make_shared<Node>(nodeName);
    }
  }

  void addEdge(const std::string &from, const std::string &to,
               bool bidirectional = false) {
    addNode(from);
    addNode(to);
    nodes[from]->neighbors.push_back(nodes[to]);
    if (bidirectional) {
      nodes[to]->neighbors.push_back(nodes[from]);
    }
  }

  void BFS(const std::string &startNode) {
    if (!nodes.count(startNode))
      return;

    std::queue<std::shared_ptr<Node>> q;
    std::unordered_map<std::string, bool> visited;

    q.push(nodes[startNode]);
    visited[startNode] = true;

    std::cout << "BFS Traversal: ";
    while (!q.empty()) {
      auto current = q.front();
      q.pop();

      std::cout << current->name << " ";

      for (const auto &neighbor : current->neighbors) {
        if (!visited[neighbor->name]) {
          visited[neighbor->name] = true;
          q.push(neighbor);
        }
      }
    }
    std::cout << "\n";
  }

  void DFS(const std::string &startNode) {
    if (!nodes.count(startNode))
      return;

    std::stack<std::shared_ptr<Node>> s;
    std::unordered_map<std::string, bool> visited;

    s.push(nodes[startNode]);
    visited[startNode] = true;

    std::cout << "DFS Traversal: ";
    while (!s.empty()) {
      auto current = s.top();
      s.pop();

      std::cout << current->name << " ";

      // 反向迭代以保证与递归DFS的顺序一致
      for (auto it = rbegin(current->neighbors); it != rend(current->neighbors);
           ++it) {
        if (!visited[(*it)->name]) {
          visited[(*it)->name] = true;
          s.push(*it);
        }
      }
    }
    std::cout << "\n";
  }

  void printGraph() {
    std::cout << "\nGraph Structure:\n";
    for (const auto &pair : nodes) {
      std::cout << pair.first << " -> ";
      for (const auto &neighbor : pair.second->neighbors) {
        std::cout << neighbor->name << " ";
      }
      std::cout << "\n";
    }
  }
};

int main() {
  Graph cityGraph;

  // 添加带权重的边（虽然这个示例中未使用权重）
  cityGraph.addEdge("Seattle", "Chicago");
  cityGraph.addEdge("Seattle", "San Francisco");
  cityGraph.addEdge("San Francisco", "Los Angeles");
  cityGraph.addEdge("Los Angeles", "San Diego");
  cityGraph.addEdge("Chicago", "New York");
  cityGraph.addEdge("Chicago", "Denver");
  cityGraph.addEdge("Denver", "San Francisco", true); // 双向边

  cityGraph.printGraph();
  cityGraph.BFS("Seattle");
  cityGraph.DFS("Seattle");

  return 0;
}