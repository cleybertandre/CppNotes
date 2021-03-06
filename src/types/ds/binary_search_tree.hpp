#ifndef BINARYSEARCHTREE_HPP_
#define BINARYSEARCHTREE_HPP_

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace DS {

template <typename T>
class BSTree
{
private:
    class Node
    {
    public:
        Node(T value) : m_value(value), m_left(nullptr), m_right(nullptr) {}
        ~Node();

        Node(const BSTree<T>::Node& other) = delete;
        Node& operator=(const Node& other) = delete;

        void setLeftNode(Node* left) { m_left = left; }
        Node* getLeftNode() const { return m_left; }
        void setRightNode(Node* right) { m_right = right; }
        Node* getRightNode() const { return m_right; }
        void setValue(const T& value) { m_value = value; }
        T getValue() const { return m_value; }

    private:
        T m_value;
        Node* m_left;
        Node* m_right;
    };

    Node* root;

public:
    BSTree() : root(nullptr) {}
    ~BSTree() { clear(); }

    BSTree(const BSTree<T>& other) = delete;
    BSTree<T>& operator=(const BSTree<T>& other) = delete;

    template <typename U>
    friend bool operator==(BSTree<U>& left, BSTree<U>& right);

    template <typename U>
    friend bool operator!=(BSTree<U>& left, BSTree<U>& right);

    void clear();
    int size() const;
    bool isEmpty() const;
    void insert(const T& value);
    bool contains(const T& value) const;
    void deleteValue(const T& value);
    int maxDepth() const;
    T minValue() const;
    T maxValue() const;
    std::vector<T> printTree() const;
    std::vector<T> printTreePostorder() const;
    std::vector<std::vector<T>> getPaths() const;
    void mirror();
    T getSuccessorOfValue(const T& value) const;

private:
    int calcSize(const Node* node) const;
    void insertValue(Node* node, const T& value);
    Node* findNodeWithValue(Node* node, const T& value) const;
    Node* deleteValueNode(Node* node, const T& value);
    int calcMaxDepth(const Node* node) const;
    Node* minValueNode(Node* node) const;
    Node* maxValueNode(Node* node) const;
    void printNode(const Node* node, std::vector<T>& values) const;
    void printNodePostorder(const Node* node, std::vector<T>& values) const;
    std::vector<std::vector<T>> getNodePaths(const Node* node) const;
    void mirrorNode(Node* node);
    bool isSameNodes(Node* lh, Node* rh);
};

template<typename T>
BSTree<T>::Node::~Node() {
    if (nullptr != m_left) {
        delete m_left;
        m_left = nullptr;
    }

    if (nullptr != m_right) {
        delete m_right;
        m_right = nullptr;
    }
}

template<typename T>
void BSTree<T>::clear() {
    if (nullptr != root) {
        delete root;
        root = nullptr;
    }
}

template<typename T>
int BSTree<T>::size() const {
    return calcSize(root);
}

template<typename T>
int BSTree<T>::calcSize(const Node* node) const {
    if (nullptr == node) {
        return 0;
    }

    return 1 + calcSize(node->getLeftNode()) + calcSize(node->getRightNode());
}

template<typename T>
bool BSTree<T>::isEmpty() const {
    return (nullptr == root);
}

template<typename T>
void BSTree<T>::insert(const T& value) {
    if (nullptr == root) {
        root = new Node(value);
    }
    else {
        insertValue(root, value);
    }
}

template<typename T>
void BSTree<T>::insertValue(Node* node, const T& value) {
    if (nullptr == node) {
        throw std::runtime_error("Can't insert to null node");
        return;
    }

    if (value < node->getValue()) {
        if (nullptr == node->getLeftNode()) {
            Node* leftNode = new Node(value);
            node->setLeftNode(leftNode);
        }
        else {
            insertValue(node->getLeftNode(), value);
        }
    }
    else {
        if (nullptr == node->getRightNode()) {
            Node* rightNode = new Node(value);
            node->setRightNode(rightNode);
        }
        else {
            insertValue(node->getRightNode(), value);
        }
    }
}

template<typename T>
bool BSTree<T>::contains(const T& value) const {
    return (findNodeWithValue(root, value) != nullptr);
}

template<typename T>
typename BSTree<T>::Node* BSTree<T>::findNodeWithValue(
        Node* node, const T& value) const {
    if (nullptr == node) {
        return nullptr;
    }

    if (value < node->getValue()) {
        return findNodeWithValue(node->getLeftNode(), value);
    }
    else if (value > node->getValue()) {
        return findNodeWithValue(node->getRightNode(), value);
    }

    return node;
}

template<typename T>
void BSTree<T>::deleteValue(const T& value) {
    root = deleteValueNode(root, value);
}

template<typename T>
typename BSTree<T>::Node* BSTree<T>::deleteValueNode(
        Node* node, const T& value) {
    if (nullptr == node) {
        return node;
    }

    if (value < node->getValue()) {
        Node* resultLeft = deleteValueNode(node->getLeftNode(), value);
        node->setLeftNode(resultLeft);
    }
    else if (node->getValue() < value) {
        Node* resultRight = deleteValueNode(node->getRightNode(), value);
        node->setRightNode(resultRight);
    }
    else {
        if (nullptr == node->getLeftNode()) {
            Node* temp = node->getRightNode();
            node->setRightNode(nullptr);
            delete node;
            return temp;
        }
        else if (nullptr == node->getRightNode()) {
            Node* temp = node->getLeftNode();
            node->setLeftNode(nullptr);
            delete node;
            return temp;
        }

        // node with two children: get the inorder successor (smallest
        // in the right subtree)
        Node* temp = minValueNode(node->getRightNode());
        node->setValue(temp->getValue());

        // Delete the inorder successor
        Node* newRight =
                deleteValueNode(node->getRightNode(), node->getValue());
        node->setRightNode(newRight);
    }

    return node;
}

template<typename T>
int BSTree<T>::maxDepth() const {
    return calcMaxDepth(root);
}

template<typename T>
int BSTree<T>::calcMaxDepth(const Node* node) const {
    if (nullptr == node) {
        return 0;
    }

    int leftDepth = calcMaxDepth(node->getLeftNode());
    int rightDepth = calcMaxDepth(node->getRightNode());
    return 1 + std::max(leftDepth, rightDepth);
}

template<typename T>
T BSTree<T>::minValue() const {
    if (nullptr == root) {
        return T();
    }

    Node* node = minValueNode(root);
    if (nullptr == node) {
        return T();
    }

    return node->getValue();
}

template<typename T>
typename BSTree<T>::Node* BSTree<T>::minValueNode(Node* node) const {
    if (nullptr == node) {
        return nullptr;
    }

    Node* iNode = node;
    while(iNode->getLeftNode() != nullptr) {
        iNode = iNode->getLeftNode();
    }

    return iNode;
}

template<typename T>
T BSTree<T>::maxValue() const {
    if (nullptr == root) {
        return T();
    }

    Node* node = maxValueNode(root);
    if (nullptr == node) {
        return T();
    }

    return node->getValue();
}

template<typename T>
typename BSTree<T>::Node* BSTree<T>::maxValueNode(Node* node) const {
    if (nullptr == node) {
        return nullptr;
    }

    Node* iNode = node;
    while(iNode->getRightNode() != nullptr) {
        iNode = iNode->getRightNode();
    }

    return iNode;
}

template<typename T>
std::vector<T> BSTree<T>::printTree() const {
    std::vector<T> values;
    printNode(root, values);

    return values;
}

template<typename T>
void BSTree<T>::printNode(const Node* node, std::vector<T>& values) const {
    if (nullptr == node) {
        return;
    }

    if (nullptr != node->getLeftNode()) {
        printNode(node->getLeftNode(), values);
    }

    values.push_back(node->getValue());

    if (nullptr != node->getRightNode()) {
        printNode(node->getRightNode(), values);
    }
}

template<typename T>
std::vector<T> BSTree<T>::printTreePostorder() const {
    std::vector<T> values;
    printNodePostorder(root, values);

    return values;
}

template<typename T>
void BSTree<T>::printNodePostorder(const Node* node,
        std::vector<T>& values) const {
    if (nullptr == node) {
        return;
    }

    if (nullptr != node->getLeftNode()) {
        printNodePostorder(node->getLeftNode(), values);
    }

    if (nullptr != node->getRightNode()) {
        printNodePostorder(node->getRightNode(), values);
    }

    values.push_back(node->getValue());
}

template<typename T>
std::vector<std::vector<T>> BSTree<T>::getPaths() const {
    std::vector<std::vector<T>> paths = getNodePaths(root);
    auto func = [](std::vector<T>& vec){
        std::reverse(vec.begin(), vec.end());
    };

    std::for_each(paths.begin(), paths.end(), func);

    return paths;
}

template<typename T>
std::vector<std::vector<T>> BSTree<T>::getNodePaths(const Node* node) const {
    if (nullptr == node) {
        return std::vector<std::vector<T>>();
    }

    std::vector<std::vector<T>> leftPaths, rightPaths;
    if (nullptr != node->getLeftNode()) {
        leftPaths = getNodePaths(node->getLeftNode());
    }

    if (nullptr != node->getRightNode()) {
        rightPaths = getNodePaths(node->getRightNode());
    }

    std::vector<std::vector<T>> result;
    std::copy(leftPaths.begin(), leftPaths.end(), std::back_inserter(result));
    std::copy(rightPaths.begin(), rightPaths.end(), std::back_inserter(result));
    if (result.empty()) {
        result.push_back(std::vector<T>());
    }

    const T nodeValue = node->getValue();
    auto func = [&nodeValue](std::vector<T>& vec){vec.push_back(nodeValue);};
    std::for_each(result.begin(), result.end(), func);

    return result;
}

template<typename T>
void BSTree<T>::mirror() {
    mirrorNode(root);
}

template<typename T>
void BSTree<T>::mirrorNode(Node* node) {
    if (nullptr == node) {
        return;
    }

    Node* left = node->getLeftNode();
    Node* right = node->getRightNode();
    mirrorNode(left);
    mirrorNode(right);

    node->setLeftNode(right);
    node->setRightNode(left);
}

template<typename U>
bool operator==(BSTree<U>& left, BSTree<U>& right) {
    return left.isSameNodes(left.root, right.root);
}

template<typename U>
bool operator!=(BSTree<U>& left, BSTree<U>& right) {
    return !(left == right);
}

template<typename T>
bool BSTree<T>::isSameNodes(Node* lh, Node* rh) {
    if (nullptr == lh) {
        return nullptr == rh ? true : false;
    }
    else if (nullptr == rh) {
        return false;
    }

    if (lh->getValue() == rh->getValue() &&
            isSameNodes(lh->getLeftNode(), rh->getLeftNode()) &&
            isSameNodes(lh->getRightNode(), rh->getRightNode())) {
        return true;
    }

    return false;
}

template<typename T>
T BSTree<T>::getSuccessorOfValue(const T& value) const {
    // First of all, let's find out if we have such value in our tree
    Node* target = findNodeWithValue(root, value);
    if (target != nullptr) {
        // Yes, we have. Successor of it is lying in the right subtree and it
        // has the smallest value
        Node* nodeWithSuccessorValue = minValueNode(target->getRightNode());
        if (nodeWithSuccessorValue != nullptr) {
            return nodeWithSuccessorValue->getValue();
        }
    }

    // Second variant - start searching from the root for value that is
    // minimally bigger than our value
    Node* successor = nullptr;
    Node* ancestor = root;
    while(ancestor != nullptr) {
        if (value < ancestor->getValue()) {
            successor = ancestor;
            ancestor = ancestor->getLeftNode();
        }
        else {
            ancestor = ancestor->getRightNode();
        }
    }

    return (successor != nullptr) ? successor->getValue() : T();
}

}

#endif /* BINARYSEARCHTREE_HPP_ */
