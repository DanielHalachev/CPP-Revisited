#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H
#include <algorithm>
#include <functional>
#include <iostream>
#include <istream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "DisjointSet.h"

template <typename T, typename S>
class WeightedGraph {
 private:
  std::unordered_map<T, std::unordered_map<T, S>> adjacencyList;

 public:
  struct Edge {
    T start;
    T end;
    T weight;
    bool operator<(const Edge &other) { return this->weight < other.weight; }
  };
  WeightedGraph() = default;
  WeightedGraph(const WeightedGraph<T, S> &other) = default;
  WeightedGraph &operator=(const WeightedGraph<T, S> &other) = default;
  WeightedGraph(WeightedGraph<T, S> &&other) = default;
  WeightedGraph &operator=(WeightedGraph<T, S> &&other) = default;
  ~WeightedGraph() = default;

  template <typename U, typename R>
  friend std::istream &operator>>(std::istream &inputStream,
                                  WeightedGraph<U, R> &graph);
  std::unordered_map<T, S> dejkstra(const T &start) const;
  std::unordered_map<T, S> bellmanFord(const T &start) const;
  std::vector<Edge> kruskalMST() const;
  std::vector<Edge> primMST(const T &start) const;
};

template <typename T, typename S>
std::istream &operator>>(std::istream &inputSteam, WeightedGraph<T, S> &graph) {
  std::string userInput;
  T vertice1;
  T vertice2;
  S weight;
  while (true) {
    std::cout << "V1 V2 Weight: ";
    std::cin >> vertice1 >> vertice2 >> weight;
    graph.adjacencyList[vertice1][vertice2] = weight;
    if (!graph.adjacencyList.contains(vertice2)) {
      graph.adjacencyList[vertice2] = std::unordered_map<T, S>();
    }
    std::cout << "Continue?\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, userInput);
    if (userInput == "n" || userInput == "N") {
      break;
    }
  }
  return inputSteam;
}

template <typename T, typename S>
std::unordered_map<T, S> WeightedGraph<T, S>::dejkstra(const T &start) const {
  std::priority_queue<std::pair<S, T>, std::vector<std::pair<S, T>>,
                      std::greater<std::pair<S, T>>>
      queue;
  std::unordered_map<T, S> distances;
  for (auto &keyValuePair : this->adjacencyList) {
    distances[keyValuePair.first] = std::numeric_limits<S>::max();
  }

  distances[start] = 0;
  queue.push(std::make_pair(0, start));

  while (!queue.empty()) {
    T node = queue.top().second;
    queue.pop();
    for (auto &childWeightPair : this->adjacencyList.at(node)) {
      T child = childWeightPair.first;
      S childWeight = childWeightPair.second;
      S newDistance = distances[node] + childWeight;
      if (newDistance < distances[child]) {
        distances[child] = newDistance;
        queue.push({newDistance, child});
      }
    }
  }
  return distances;
}

template <typename T, typename S>
std::unordered_map<T, S> WeightedGraph<T, S>::bellmanFord(
    const T &start) const {
  std::unordered_map<T, S> distances;
  for (auto &nodeChildrenPair : this->adjacencyList) {
    distances[nodeChildrenPair.first] = std::numeric_limits<S>::max();
  }
  std::unordered_map<T, T> predecessor;
  distances[start] = 0;

  for (int i = 0; i < this->adjacencyList.size() - 1; i++) {
    for (auto nodeChildrenPair : this->adjacencyList) {
      T node = nodeChildrenPair.first;
      std::unordered_map<T, S> children = nodeChildrenPair.second;
      for (auto childWeightPair : children) {
        T child = childWeightPair.first;
        S weight = childWeightPair.second;
        S tempDistance = distances[node] + weight;
        if (tempDistance < distances[child]) {
          distances[child] = tempDistance;
          predecessor[child] = node;
        }
      }
    }
  }
  return distances;
}

template <typename T, typename S>
std::vector<typename WeightedGraph<T, S>::Edge>
WeightedGraph<T, S>::kruskalMST() const {
  std::vector<Edge> result;
  std::vector<Edge> edges;
  edges.reserve(this->adjacencyList.size() - 1);
  for (auto &nodeChildrenPair : this->adjacencyList) {
    for (auto &childWeightPair : nodeChildrenPair.second) {
      edges.push_back({nodeChildrenPair.first, childWeightPair.first,
                       childWeightPair.second});
    }
  }
  DisjointSet<T> disjointSet(edges.size());
  std::sort(edges.begin(), edges.end());
  for (auto &edge : edges) {
    if (disjointSet.find(edge.start) != disjointSet.find(edge.end)) {
      result.push_back(edge);
      disjointSet.unite(edge.start, edge.end);
    }
  }
  return result;
}

template <typename T, typename S>
std::vector<typename WeightedGraph<T, S>::Edge> WeightedGraph<T, S>::primMST(
    const T &start) const {
  std::vector<Edge> result;
  std::unordered_set<T> visited;
  std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> queue;
  queue.push({start, start, 0});

  while (!queue.empty()) {
    Edge currentEdge = queue.top;
    T node = currentEdge.end;
    queue.pop();
    if (visited.find(node.second) != visited.end()) {
      continue;
    }
    visited.insert(node);
    result.push_back(currentEdge);

    for (auto &childWeightPair : this->adjacencyList.at(node)) {
      T child = childWeightPair.first;
      S childWeight = childWeightPair.second;
      if ((visited.find(child) == visited.end())) {
        queue.push({childWeight, child});
      }
    }
  }
}
#endif  //! WEIGHTED_GRAPH_H