
#ifndef BST_H
#define BST_H

#include <iostream>

using namespace std;

template<typename KeyT, typename ValueT>
class BSTNode {
  public:

    /// Constructors
    explicit BSTNode(KeyT aKey, ValueT aValue) 
        : mKey(aKey), mValue(aValue), mLeft(nullptr), mRight(nullptr), mParent(nullptr)
    {}

    explicit BSTNode(KeyT aKey, ValueT aValue, 
                     BSTNode* aLeft, BSTNode* aRight, BSTNode* aParent)
        : mKey(aKey), mValue(aValue), mLeft(aLeft), mRight(aRight), mParent(aParent)
    {}

    void cleanup();

    /// Getting and setting key
    KeyT key() const { return mKey; }
    void setKey(KeyT aKey) { mKey = aKey; }

    /// Getting and setting value
    ValueT value() const { return mValue; }
    void setValue(ValueT aValue) { mValue = aValue; }

    /// Getting and setting left child node
    BSTNode* left() { return mLeft; }
    const BSTNode* left() const { return mLeft; }
    void setLeft(BSTNode* aLeft) { mLeft = aLeft; }

    /// Getting and setting right child node
    BSTNode* right() { return mRight; }
    const BSTNode* right() const { return mRight; }
    void setRight(BSTNode* aRight) { mRight = aRight; }

    /// Getting and setting the parent node
    BSTNode* parent() { return mParent; }
    const BSTNode* parent() const { return mParent; }
    void setParent(BSTNode* aParent) { mParent = aParent; }

    /// Getting preds and succs
    BSTNode* pred() const;
    BSTNode* succ() const;

    /// Some utilities
    bool swapLeft(); 
    bool swapRight();
    bool detachFromParent();
    void inorder() const;
    void preorder() const;
    void postorder() const;

    /// Find an insertion point into the BST
    BSTNode* findInsertionPoint(KeyT aKey);
    
    /// Find a node in the BST containing the given key
    BSTNode* find(KeyT aKey);

    /// Find a node in the BST containing the given key.
    /// If key is not found, return nullptr, but also set
    /// an approx match
    BSTNode* findApprox(KeyT aKey, 
                        BSTNode<KeyT,ValueT>*& approxMatchNode_lb,
                        BSTNode<KeyT,ValueT>*& approxMatchNode_ub);
    /// Find min
    KeyT getMin() const;
    /// Find max
    KeyT getMax() const;
    /// Output nodes
    void outputNodes(ostream& s) const;
    /// Output edges
    void outputEdges(ostream& s) const;
    /// Output key
    void outputKey(ostream& s) const;

  private:
    /// Key
    KeyT mKey;
    /// Value
    ValueT mValue;
    /// Left child
    BSTNode* mLeft;
    /// Right child
    BSTNode* mRight;
    /// Parent
    BSTNode* mParent;
};

template<typename KeyT, typename ValueT>
class BST {
  public:  
    BST() 
        : mRoot(nullptr)
    {}
  
    ~BST();

    /// Setting and getting root
    void setRoot(BSTNode<KeyT,ValueT>* aNode) { mRoot = aNode; }
    BSTNode<KeyT,ValueT>* root() { return mRoot; }
    const BSTNode<KeyT,ValueT>* root() const { return mRoot; }

    /// Find a node in the BST containing the given key
    BSTNode<KeyT,ValueT>* find(KeyT aKey)
    { 
        if (mRoot) 
            return mRoot->find(aKey); 
        else
            return nullptr;
    }

    /// Find a node in the BST containing the given key
    BSTNode<KeyT,ValueT>* findInsertionPoint(KeyT aKey)
    { 
        if (mRoot) 
            return mRoot->findInsertionPoint(aKey); 
        else
            return nullptr;
    }

    /// Find a node in the BST containing the given key.
    /// If not found, return nullptr and set the approx match node
    BSTNode<KeyT,ValueT>* findApprox(KeyT aKey,
                                     BSTNode<KeyT,ValueT>*& approxMatchNode_lb,
                                     BSTNode<KeyT,ValueT>*& approxMatchNode_ub)
    { 
        if (mRoot) 
            return mRoot->findApprox(aKey, approxMatchNode_lb, approxMatchNode_ub); 
        else
            return nullptr;
    }

    /// Insert a new key in the BST
    void insert(KeyT aKey, ValueT aValue);
  
    /// Find min
    KeyT getMin() const
    { 
        if (mRoot == nullptr) {
            cout << "No node in the tree." << endl;
            exit(1);
        } 
        return mRoot->getMin(); 
    }

    /// Find max
    KeyT getMax() const
    { 
        if (mRoot == nullptr) {
            cout << "No node in the tree." << endl;
            exit(1);
        } 
        return mRoot->getMax(); 
    }

    /// delete a key in the BST
    BSTNode<KeyT,ValueT>* remove(KeyT aKey);

    /// Print inorder
    void inorder() const;

    /// Print preorder
    void preorder() const;

    /// Print postorder
    void postorder() const;

    /// Trivially remove a node n
    BSTNode<KeyT,ValueT>* trivialRemove(BSTNode<KeyT,ValueT>* n);

    /// Output the tree
    void output(ostream& s) const;
 
  private:
    /// Root pointer
    BSTNode<KeyT,ValueT>* mRoot;
};


template<typename KeyT, typename ValueT>
void BSTNode<KeyT,ValueT>::cleanup()
{
    if (left()) {
        left()->cleanup();
    }
    if (right()) {
        right()->cleanup();
    }
    delete this;
}

/// Get predecessor
template<typename KeyT, typename ValueT>
BSTNode<KeyT,ValueT>* BSTNode<KeyT,ValueT>::pred() const
{
    BSTNode<KeyT,ValueT>* lc = const_cast<BSTNode<KeyT,ValueT>*>(left());
    if (lc == nullptr) {
        return nullptr;
    }
    while (lc->right() != nullptr) {
        lc = lc->right();
    }
    return lc;
}

/// Get successor
template<typename KeyT, typename ValueT>
BSTNode<KeyT,ValueT>* BSTNode<KeyT,ValueT>::succ() const
{
    BSTNode<KeyT,ValueT>* rc = const_cast<BSTNode<KeyT,ValueT>*>(right());
    if (rc == nullptr) {
        return nullptr;
    }
    while (rc->left() != nullptr) {
        rc = rc->left();
    }
    return rc;
}


/// Find min
template<typename KeyT, typename ValueT>
KeyT BSTNode<KeyT,ValueT>::getMin() const
{
    if (left() == nullptr) {
        return key();
    }
    return left()->getMin();
}

/// Find max
template<typename KeyT, typename ValueT>
KeyT BSTNode<KeyT,ValueT>::getMax() const
{
    if (right() == nullptr) {
        return key();
    }
    return right()->getMax();

}

/// Swap left
template<typename KeyT, typename ValueT>
bool BSTNode<KeyT,ValueT>::swapLeft()
{
    BSTNode<KeyT,ValueT>* p = parent();
    if (p == nullptr) {
        return false;
    }
    BSTNode<KeyT,ValueT>* c = left(); 
    if (p->left() == this) {
        p->setLeft(c);
    } else {
        p->setRight(c);
    }
    c->setParent(p);
    return true;
}

/// Swap right
template<typename KeyT, typename ValueT>
bool BSTNode<KeyT,ValueT>::swapRight()
{
    BSTNode<KeyT,ValueT>* p = parent();
    if (p == nullptr) {
        return false;
    }
    BSTNode<KeyT,ValueT>* c = right();
    if (p->left() == this) {
        p->setLeft(c);
    } else {
        p->setRight(c);
    }
    c->setParent(p);
    return true;
}


/// Detach from parent
template<typename KeyT, typename ValueT>
bool BSTNode<KeyT,ValueT>::detachFromParent() 
{
    BSTNode<KeyT,ValueT>* p = parent();
    if (p == nullptr) {
        return false;
    }
    if (p->left() == this) {
        p->setLeft(nullptr);
    } else {
        p->setRight(nullptr);
    }
    return true;
}

template<typename KeyT, typename ValueT>
void BSTNode<KeyT,ValueT>::inorder() const
{
    if (left()) {
        left()->inorder();
    }
    cout << key() << ": ";
    cout << value() << endl;
    if (right()) {
        right()->inorder();
    }
}

template<typename KeyT, typename ValueT>
void BSTNode<KeyT,ValueT>::postorder() const
{
    if (left()) {
        left()->postorder();
    }
    if (right()) {
        right()->postorder();
    }
    cout << key() << ": ";
    cout << value() << endl;
}

template<typename KeyT, typename ValueT>
void BSTNode<KeyT,ValueT>::preorder() const
{
    cout << key() << ": ";
    cout << value() << endl;
    if (left()) {
        left()->preorder();
    }
    if (right()) {
        right()->preorder();
    }
}

/// Find a node in the BST containing the given key
/// Or return an insertion point
template<typename KeyT, typename ValueT>
BSTNode<KeyT,ValueT>* BSTNode<KeyT,ValueT>::findInsertionPoint(KeyT aKey) 
{
    if (key() == aKey) {
        // found
        return this;
    }
    if (aKey < key()) {
        if (left()) {
            return left()->findInsertionPoint(aKey);
        } else {
            return this;
        }
    } else if (aKey > key()) {
        if (right()) {
            return right()->findInsertionPoint(aKey);
        } else {
            return this;
        }
    }
    return nullptr;
}


/// Find a node in the BST containing the given key
template<typename KeyT, typename ValueT>
BSTNode<KeyT,ValueT>* BSTNode<KeyT,ValueT>::find(KeyT aKey) 
{
    if (key() == aKey) {
        // found
        return this;
    }
    if (aKey < key()) {
        if (left()) {
            return left()->find(aKey);
        } 
    } else if (aKey > key()) {
        if (right()) {
            return right()->find(aKey);
        } 
    }
    // Not found
    return nullptr;
}

/// Find a node in the BST containing the given key
template<typename KeyT, typename ValueT>
BSTNode<KeyT,ValueT>* BSTNode<KeyT,ValueT>::findApprox(KeyT aKey,
                                                       BSTNode<KeyT,ValueT>*& approxMatchNode_lb,
                                                       BSTNode<KeyT,ValueT>*& approxMatchNode_ub) 
{
    if (key() == aKey) {
        // found
        return this;
    }
    if (aKey < key()) {
        approxMatchNode_ub = this;
        if (left()) {
            return left()->findApprox(aKey, approxMatchNode_lb, approxMatchNode_ub);
        } 
    } else if (aKey > key()) {
        approxMatchNode_lb = this;
        if (right()) {
            return right()->findApprox(aKey, approxMatchNode_lb, approxMatchNode_ub);
        } 
    }
    return nullptr;
}

template<typename KeyT, typename ValueT>
void BSTNode<KeyT,ValueT>::outputKey(ostream& s) const
{
    s << "\""
      << key()
      << "\" ";
}

/// Print the tree nodes starting from this node
template<typename KeyT, typename ValueT>
void BSTNode<KeyT,ValueT>::outputNodes(ostream& s) const
{
    outputKey(s);
    s << "[label =";
    s << "\""
      << key()
      << " | | "
      << value()
      << "\"";
    s << "];"
      << endl;
    if (left()) {
        left()->outputNodes(s);
    }
    if (right()) {
        right()->outputNodes(s);
    }
}

/// Print the tree edges starting from this node
template<typename KeyT, typename ValueT>
void BSTNode<KeyT,ValueT>::outputEdges(ostream& s) const
{
    static int count = 0;
    if (left() != nullptr) {
        outputKey(s);
        s << " -> ";
        left()->outputKey(s);
        s << endl; 
        left()->outputEdges(s);
    } else {
        s << "nullptr" << count << "[shape=point]" << endl;
        outputKey(s);
        s << " -> " << "nullptr" << count++ << endl;
    }
    if (right() != nullptr) {
        outputKey(s);
        s << " -> ";
        right()->outputKey(s);
        s << endl; 
        right()->outputEdges(s);
    } else {
        s << "nullptr" << count << "[shape=point]" << endl;
        outputKey(s);
        s << " -> " << "nullptr" << count++ << endl;
    }
}

///////////////////////////////////////

/// Destructor
template<typename KeyT, typename ValueT>
BST<KeyT,ValueT>::~BST()
{
    if (mRoot) {
        mRoot->cleanup();
    }
}

/// Insert a new key in the BST<KeyT,ValueT>
template<typename KeyT, typename ValueT>
void BST<KeyT,ValueT>::insert(KeyT aKey, ValueT aValue)
{
    BSTNode<KeyT,ValueT>* place = findInsertionPoint(aKey);
    if (place == nullptr) {
        // First node to be inserted
        mRoot = new BSTNode<KeyT,ValueT>(aKey, aValue);
    } else if (aKey < place->key()) {
        // Node on the left of place
        place->setLeft(new BSTNode<KeyT,ValueT>(aKey, aValue, nullptr, nullptr, place));
    } else {
        // Node on the right of place
        place->setRight(new BSTNode<KeyT,ValueT>(aKey, aValue, nullptr, nullptr, place));
    } 
}

// Cases 1, 2 and 3
template<typename KeyT, typename ValueT>
BSTNode<KeyT,ValueT>* BST<KeyT,ValueT>::trivialRemove(BSTNode<KeyT,ValueT>* n)
{
    BSTNode<KeyT,ValueT>* parentNode = n->parent();
    BSTNode<KeyT,ValueT>* leftNode = n->left();
    BSTNode<KeyT,ValueT>* rightNode = n->right();
    if (leftNode == nullptr && 
        rightNode == nullptr) {
        // Case 1: No children
        // Detach it from the parent
        n->detachFromParent();
        delete n;
        return parentNode;
    }
    if (leftNode == nullptr &&
        rightNode != nullptr) {
        // Case 2: n has only right child
        bool isDone = n->swapRight();
        delete n;
	return isDone? parentNode : rightNode;
    }
    if (rightNode == nullptr &&
        leftNode != nullptr) {
        // Case 3: n has only left child
        bool isDone = n->swapLeft();
        delete n;
	return isDone? parentNode : leftNode;
    }
    return parentNode;
}

/// delete a key in the BST<KeyT,ValueT>
template<typename KeyT, typename ValueT>
BSTNode<KeyT,ValueT>* BST<KeyT,ValueT>::remove(KeyT aKey)
{
    BSTNode<KeyT,ValueT>* n = find(aKey);
    if (n == nullptr ||
        n->key() != aKey) {
        // No node containing aKey
        return nullptr;
    }
    if (n->left() != nullptr &&
        n->right() != nullptr) {
        // Case 4: n has both left and right child
        BSTNode<KeyT,ValueT>* s = n->succ();
        n->setKey(s->key());
        n->setValue(s->value());
        return trivialRemove(s);
    } else {
        // Cases 1, 2 and 3
        BSTNode<KeyT,ValueT>* parentNode = n->parent();
        BSTNode<KeyT,ValueT>* repositionedNode = trivialRemove(n);
        if (repositionedNode != parentNode) {
            repositionedNode->setParent(nullptr);
            mRoot = repositionedNode;
        }
        if (repositionedNode == nullptr) {
            mRoot = nullptr;
        } 
        return parentNode;
    }
    return nullptr;
}

/// Print inorder
template<typename KeyT, typename ValueT>
void BST<KeyT,ValueT>::inorder() const
{
    if (mRoot) mRoot->inorder();
}

/// Print preorder
template<typename KeyT, typename ValueT>
void BST<KeyT,ValueT>::preorder() const
{
    if (mRoot) mRoot->preorder();
}

/// Print postorder
template<typename KeyT, typename ValueT>
void BST<KeyT,ValueT>::postorder() const
{
    if (mRoot) mRoot->postorder();
}

template<typename KeyT, typename ValueT>
void BST<KeyT,ValueT>::output(ostream& s) const
{
    s << "digraph{" << endl;
    // The following line ensures the edges come in the order specified.
    // This helps in getting children in the left or right appropriately.
    s << "graph [ordering=\"out\"];" << endl;
    if (mRoot) {
        // Print the node format first
        s << "node ["
          << "fontsize = \"10\""
          << "shape = \"record\""
          << "];"
          << endl;
        mRoot->outputNodes(s);
        mRoot->outputEdges(s);
    }
    s << "}" << endl;
}

template<typename KeyT, typename ValueT>
std::ostream& operator<<(std::ostream& s, const BST<KeyT,ValueT>& bst)
{
    bst.output(s);
    return s;
}

#endif
