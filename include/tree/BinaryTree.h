#ifndef BINARY_TREE
#define BINARY_TREE

#include <cstddef>
#include <ostream>
#include <string>
#include <vector>
template <typename T>
class BinaryTree {
 public:
  struct Node {
    T value;
    Node* left;
    Node* right;

    Node(const T& value, Node* left, Node* right)
        : value(value), left(left), right(right) {}
  };

 private:
  Node* root = nullptr;
  size_t size = 0;
  Node* copy(Node* other);
  void freeNode(Node* node);
  void free();
  Node* insert(Node* parent, const T& value);
  Node* remove(Node* parent, const T& value);
  Node* smallestValueNode(Node* root);
  std::string print(Node* node, unsigned int level) const;
  std::vector<T> getElements(Node* node) const;

 public:
  BinaryTree();
  BinaryTree(const BinaryTree<T>& other);
  BinaryTree& operator=(const BinaryTree<T>& other);
  BinaryTree(BinaryTree<T>&& other) noexcept;
  BinaryTree& operator=(BinaryTree<T>&& other) noexcept;
  ~BinaryTree();
  void insert(const T& element);
  void remove(const T& element);
  std::vector<T> getElements() const;

  template <typename S>
  friend std::ostream& operator<<(std::ostream& outputStream,
                                  const BinaryTree<S>& tree);
};

template <typename T>
BinaryTree<T>::Node* BinaryTree<T>::copy(Node* other) {
  if (other == nullptr) {
    return nullptr;
  }
  Node* root = new Node(other->value, nullptr, nullptr);
  root->left = copy(other->left);
  root->right = copy(other->right);
  return root;
}

template <typename T>
void BinaryTree<T>::freeNode(Node* node) {
  if (node == nullptr) {
    return;
  }
  freeNode(node->left);
  freeNode(node->right);
  delete node;
}

template <typename T>
void BinaryTree<T>::free() {
  freeNode(this->root);
  this->size = 0;
}

template <typename T>
BinaryTree<T>::Node* BinaryTree<T>::insert(Node* parent, const T& value) {
  if (parent == nullptr) {
    return new Node(value, nullptr, nullptr);
    this->size++;
  }
  if (value < parent->value) {
    parent->left = insert(parent->left, value);
  } else {
    parent->right = insert(parent->right, value);
  }
  return parent;
}

template <typename T>
BinaryTree<T>::Node* BinaryTree<T>::remove(Node* parent, const T& value) {
  if (parent == nullptr) {
    return nullptr;
  }
  this->size--;
  if (value == parent->value) {
    if (parent->left == nullptr) {
      Node* temp = parent->right;
      delete parent;
      return temp;
    }
    if (parent->right == nullptr) {
      Node* temp = parent->left;
      delete parent;
      return temp;
    }
    Node* smallestInRightTree = smallestValueNode(parent->right);
    parent->value = smallestInRightTree->value;
    parent->right = remove(parent->right, smallestInRightTree->value);
    return parent;
  }
  if (value < parent->value) {
    parent->left = remove(parent->left, value);
  } else {
    parent->right = remove(parent->right, value);
  }
  return parent;
}

template <typename T>
BinaryTree<T>::Node* BinaryTree<T>::smallestValueNode(Node* root) {
  if (root == nullptr) {
    return root;
  }
  Node* smallestValueNode = root;
  while (smallestValueNode->left != nullptr) {
    smallestValueNode = smallestValueNode->left;
  }
  return smallestValueNode;
}

template <typename T>
std::string BinaryTree<T>::print(Node* node, unsigned int level) const {
  std::string output;
  if (node != nullptr) {
    output = std::string("\t", level) + std::to_string(node->value);
    if (node->left != nullptr) {
      output += "\n" + print(node->left, level + 1);
    }
    if (node->right != nullptr) {
      output += "\n" + print(node->right, level + 1);
    }
  }
  return output;
}

template <typename T>
std::vector<T> BinaryTree<T>::getElements(Node* node) const {
  std::vector<T> elements;
  if (node != nullptr) {
    std::vector<T> left_elements = getElements(node->left);
    elements.insert(elements.end(), left_elements.begin(), left_elements.end());
    elements.push_back(node->value);
    std::vector<T> right_elements = getElements(node->right);
    elements.insert(elements.end(), right_elements.begin(),
                    right_elements.end());
  }
  return elements;
}

template <typename T>
BinaryTree<T>::BinaryTree() {
  this->root = nullptr;
  this->size = 0;
}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other)
    : size(other.size), root(copy(other.root)) {}

template <typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other) {
  if (this != &other) {
    free();
    this->size = other.size;
    this->root = copy(other.root);
  }
  return *this;
}

template <typename T>
BinaryTree<T>::BinaryTree(BinaryTree<T>&& other) noexcept {
  this->size = other.size;
  this->root = other.root;

  other.size = 0;
  other.root = nullptr;
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree<T>&& other) noexcept {
  if (this != &other) {
    free();
    this->size = other.size;
    this->root = other.root;

    other.size = 0;
    other.root = nullptr;
  }
  return *this;
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
  free();
}

template <typename T>
void BinaryTree<T>::insert(const T& element) {
  this->root = insert(this->root, element);
}

template <typename T>
void BinaryTree<T>::remove(const T& element) {
  this->root = remove(this->root, element);
}

template <typename S>
std::ostream& operator<<(std::ostream& outputStream,
                         const BinaryTree<S>& tree) {
  outputStream << tree.print(tree.root, 0);
  return outputStream;
}

template <typename T>
std::vector<T> BinaryTree<T>::getElements() const {
  return getElements(this->root);
}

#endif  // !BINARY_TREE
