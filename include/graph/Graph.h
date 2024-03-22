#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <istream>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
template <typename T>
class Graph {
 private:
  std::unordered_map<T, std::unordered_set<T>> adjacencyList;

 public:
  Graph() = default;
  Graph(const Graph<T>& other) = default;
  Graph& operator=(const Graph<T>& other) = default;
  Graph(Graph<T>&& other) noexcept = default;
  Graph& operator=(Graph<T>&& other) noexcept = default;
  ~Graph() = default;

  template <typename S>
  friend std::istream& operator>>(std::istream& inputStream, Graph<S>& graph);

  std::vector<T> kuhnTopologicalSort() const;
  std::vector<T> DFSTopologicalSort() const;

 private:
  void DFSTopologicalSortUtil(std::unordered_set<T>& visited,
                              std::stack<T>& path, const T& current) const;
};

template <typename T>
std::istream& operator>>(std::istream& inputStream, Graph<T>& graph) {
  T vertice1;
  T vertice2;
  std::string userInput;
  while (true) {
    std::cout << "Enter edge: ";
    std::cin >> vertice1 >> vertice2;
    graph.adjacencyList[vertice1].insert(vertice2);
    if (!graph.adjacencyList.contains(vertice2)) {
      graph.adjacencyList[vertice2] = std::unordered_set<T>();
    }

    std::getline(std::cin, userInput);
    if (userInput == "n" || userInput == "N") {
      break;
    }
  }
  return inputStream;
}

template <typename T>
std::vector<T> Graph<T>::kuhnTopologicalSort() const {
  std::vector<T> result;
  result.reserve(this->adjacencyList.size());
  std::unordered_map<T, unsigned int> inputDegrees;
  for (auto keyValuePair : this->adjacencyList) {
    if (!inputDegrees.contains(keyValuePair.first)) {
      inputDegrees[keyValuePair.first] = 0;
    }
    for (auto vertice : keyValuePair.second) {
      inputDegrees[vertice]++;
    }
  }
  std::queue<T, std::list<T>> starts;
  for (auto pair : inputDegrees) {
    if (pair.second == 0) {
      starts.push(pair.first);
    }
  }
  while (!starts.empty()) {
    T node = starts.front();
    starts.pop();
    result.push_back(node);
    for (auto& nextNode : this->adjacencyList.at(node)) {
      inputDegrees[nextNode]--;
      if (inputDegrees[nextNode] == 0) {
        starts.push(nextNode);
      }
    }
  }
  return result;
}

template <typename T>
void Graph<T>::DFSTopologicalSortUtil(std::unordered_set<T>& visited,
                                      std::stack<T>& path,
                                      const T& current) const {
  if (visited.contains(current)) {
    return;
  }
  visited.insert(current);
  for (const auto& child : this->adjacencyList.at(current)) {
    DFSTopologicalSortUtil(visited, path, child);
  }
  path.push(current);
}

template <typename T>
std::vector<T> Graph<T>::DFSTopologicalSort() const {
  std::vector<T> result;
  std::unordered_set<T> visited;
  std::stack<T> path;
  for (auto& pair : this->adjacencyList) {
    DFSTopologicalSortUtil(visited, path, pair.first);
  }
  while (!path.empty()) {
    result.push_back(path.top());
    path.pop();
  }
  return result;
}
#endif  //! GRAPH_H