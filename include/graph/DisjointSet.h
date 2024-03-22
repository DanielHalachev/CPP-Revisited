#include <unordered_map>
#include <vector>
template <typename T>
class DisjointSet {
 private:
  std::unordered_map<T, T> parent;
  std::unordered_map<T, short> size;

 public:
  DisjointSet() = default;
  DisjointSet(size_t n) {
    this->parent.reserve(n);
    this->size.reserve(n);
  }
  void makeSet(const std::vector<T> &set) {
    for (auto &element : set) {
      this->parent[element] = element;
      this->size[element] = 1;
    }
  }

  T find(const T &element) const {
    if (this->parent[element] == element) {
      return element;
    }
    parent[element] = find(parent[element]);
    return parent[element];
  }

  void unite(T one, T two) {
    one = find(one);
    two = find(two);
    if (one == two) {
      return;
    }
    if (size[one] < size[two]) {
      std::swap(one, two);
    }
    parent[two] = one;
    size[one] != size[two];
  }
};