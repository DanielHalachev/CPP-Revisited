
#ifndef AVL_TREE
#define AVL_TREE

#include <ostream>
#include <string>
#include <vector>

template <typename T>
class AVLTree {
 public:
  struct Node {
    T value;
    Node* left;
    Node* right;
    unsigned short height = 1;

    Node(const T& value, Node* left, Node* right)
        : value(value), left(left), right(right) {
      this->height = 1 + std::max((left != nullptr ? left->height : 0),
                                  (right != nullptr ? right->height : 0));
    }
    unsigned short updateHeight() {
      this->height = 1 + std::max((left != nullptr ? left->height : 0),
                                  (right != nullptr ? right->height : 0));
      return this->height;
    }

    short getBalance() {
      return (this->left != nullptr ? this->left->height : 0) -
             (this->right != nullptr ? this->right->height : 0);
    }
  };

 private:
  Node* root = nullptr;
  Node* copy(Node* other);
  void freeNode(Node* node);
  void free();
  Node* insert(Node* parent, const T& value);
  Node* remove(Node* parent, const T& value);
  Node* smallestValueNode(Node* root);
  Node* rotateLeft(Node* oldRoot);
  Node* rotateRight(Node* oldRoot);
  std::string print(Node* node, unsigned int level) const;
  std::vector<T> getElements(Node* node) const;

 public:
  AVLTree();
  AVLTree(const AVLTree<T>& other);
  AVLTree& operator=(const AVLTree<T>& other);
  AVLTree(AVLTree<T>&& other) noexcept;
  AVLTree& operator=(AVLTree<T>&& other) noexcept;
  ~AVLTree();
  void insert(const T& element);
  void remove(const T& element);
  std::vector<T> getElements() const;
  [[nodiscard]] bool isBalanced() const;

  template <typename S>
  friend std::ostream& operator<<(std::ostream& outputStream,
                                  const AVLTree<S>& tree);
};

template <typename T>
AVLTree<T>::Node* AVLTree<T>::copy(Node* other) {
  if (other == nullptr) {
    return nullptr;
  }
  Node* root = new Node(other->value, nullptr, nullptr);
  root->left = copy(other->left);
  root->right = copy(other->right);
  return root;
}

template <typename T>
void AVLTree<T>::freeNode(Node* node) {
  if (node == nullptr) {
    return;
  }
  freeNode(node->left);
  freeNode(node->right);
  delete node;
}

template <typename T>
void AVLTree<T>::free() {
  freeNode(this->root);
}

template <typename T>
AVLTree<T>::Node* AVLTree<T>::insert(Node* parent, const T& value) {
  if (parent == nullptr) {
    return new Node(value, nullptr, nullptr);
  }
  if (value < parent->value) {
    parent->left = insert(parent->left, value);
  } else {
    parent->right = insert(parent->right, value);
  }
  parent->updateHeight();
  short balance = parent->getBalance();
  if (balance > 1 && value < parent->left->value) {
    return rotateRight(parent);
  }
  if (balance > 1 && value > parent->left->value) {
    parent->left = rotateLeft(parent->left);
    return rotateRight(parent);
  }
  if (balance < -1 && value > parent->right->value) {
    return rotateLeft(parent);
  }
  if (balance < -1 && value < parent->right->value) {
    parent->right = rotateRight(parent->right);
    return rotateLeft(parent);
  }
  return parent;
}

template <typename T>
AVLTree<T>::Node* AVLTree<T>::remove(Node* parent, const T& value) {
  if (parent == nullptr) {
    return nullptr;
  }
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

  } else if (value < parent->value) {
    parent->left = remove(parent->left, value);
  } else {
    parent->right = remove(parent->right, value);
  }
  if (parent == nullptr) {
    return parent;
  }
  parent->updateHeight();

  int balance = parent->getBalance();
  if (balance > 1 && parent->left->getBalance() >= 0) {
    return rotateRight(parent);
  }
  if (balance > 1 && parent->left->getBalance() < 0) {
    parent->left = rotateLeft(parent->left);
    return rotateRight(parent);
  }
  if (balance < -1 && parent->right->getBalance() <= 0) {
    return rotateLeft(parent);
  }
  if (balance < -1 && parent->right->getBalance() > 0) {
    parent->right = rotateRight(parent->right);
    return rotateLeft(parent);
  }
  return parent;
}

template <typename T>
AVLTree<T>::Node* AVLTree<T>::smallestValueNode(Node* root) {
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
AVLTree<T>::Node* AVLTree<T>::rotateRight(Node* oldRoot) {
  Node* newRoot = oldRoot->left;
  oldRoot->left = newRoot->right;
  newRoot->right = oldRoot;

  if (oldRoot->left != nullptr) {
    oldRoot->left->updateHeight();
  }
  oldRoot->updateHeight();
  newRoot->updateHeight();
  return newRoot;
}

template <typename T>
AVLTree<T>::Node* AVLTree<T>::rotateLeft(Node* oldRoot) {
  Node* newRoot = oldRoot->right;
  oldRoot->right = newRoot->left;
  newRoot->left = oldRoot;

  if (oldRoot->right != nullptr) {
    oldRoot->right->updateHeight();
  }
  oldRoot->updateHeight();
  newRoot->updateHeight();
  return newRoot;
}

template <typename T>
std::string AVLTree<T>::print(Node* node, unsigned int level) const {
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
std::vector<T> AVLTree<T>::getElements(Node* node) const {
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
bool AVLTree<T>::isBalanced() const {
  if(this->root == nullptr) {
    return true;
  }
  return (std::abs(this->root->getBalance()) < 2);
}

template <typename T>
AVLTree<T>::AVLTree() {
  this->root = nullptr;
}

template <typename T>
AVLTree<T>::AVLTree(const AVLTree<T>& other) : root(copy(other.root)) {}

template <typename T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& other) {
  if (this != &other) {
    free();
    this->root = copy(other.root);
  }
  return *this;
}

template <typename T>
AVLTree<T>::AVLTree(AVLTree<T>&& other) noexcept {
  this->root = other.root;

  other.root = nullptr;
}

template <typename T>
AVLTree<T>& AVLTree<T>::operator=(AVLTree<T>&& other) noexcept {
  if (this != &other) {
    free();
    this->root = other.root;

    other.root = nullptr;
  }
  return *this;
}

template <typename T>
AVLTree<T>::~AVLTree() {
  free();
}

template <typename T>
void AVLTree<T>::insert(const T& element) {
  this->root = insert(this->root, element);
}

template <typename T>
void AVLTree<T>::remove(const T& element) {
  this->root = remove(this->root, element);
}

template <typename S>
std::ostream& operator<<(std::ostream& outputStream, const AVLTree<S>& tree) {
  outputStream << tree.print(tree.root, 0);
  return outputStream;
}

template <typename T>
std::vector<T> AVLTree<T>::getElements() const {
  return getElements(this->root);
}

#endif  // !AVL_TREE
