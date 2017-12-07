// TreeRelations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include <assert.h>

using namespace std;

struct Node
{
    int val;
    Node* left;
    Node* right;
    Node(int v) :
        val(v),
        left(nullptr),
        right(nullptr)
    {}
};

class BinaryTree
{
public:
    BinaryTree() :
        _root(nullptr)
    {}

    Node* getRoot()
    {
        return _root;
    }

    virtual void createTree(vector<int>& input)
    {
        // TODO!
    }

protected:
    Node* _root;
};

class BinarySearchTree : public BinaryTree
{
public:
    void createTree(vector<int>& input) override
    {
        if (_root != nullptr || input.size() == 0)
        {
            return;
        }
        _root = _createBalancedBSTRecur(input, 0, input.size() - 1);
    }

private:
    Node* _createBalancedBSTRecur(vector<int>& input, int low, int high)
    {
        if (low > high)
        {
            return nullptr;
        }
        int mid = low + ((high - low) / 2);
        assert(input[mid] >= 0);
        Node* root = new Node(input[mid]);
        root->left = _createBalancedBSTRecur(input, low, mid - 1);
        root->right = _createBalancedBSTRecur(input, mid + 1, high);
        return root;
    }
};

class Properties
{
public:
    int height(BinaryTree& bt)
    {
        return _height(bt.getRoot());
    }

    bool isValidBST(BinaryTree& bt)
    {
        Node* prev = nullptr;
        return _isValidBST(bt.getRoot(), prev);
    }

private:
    bool _isValidBST(Node* root, Node*& prev)
    {
        if (root == nullptr)
        {
            return true;
        }
        bool temp = _isValidBST(root->left, prev);
        if (temp == false)
        {
            return false;
        }
        if (prev != nullptr)
        {
            if (root->val <= prev->val)
            {
                return false;
            }
        }
        prev = root;
        return _isValidBST(root->right, prev);
    }

    int _height(Node* root)
    {
        if (root == nullptr)
        {
            return 0;
        }

        int temp1 = _height(root->left);
        if (temp1 == -1)
        {
            return temp1;
        }
        int temp2 = _height(root->right);
        if (temp2 == -1)
        {
            return temp2;
        }

        // For checking complete BT, here you can check if the difference between left and right subtrees is greater than 1. Return -1 if not

        return (max(temp1, temp2) + 1);
    }
};

class Traversal
{
public:
    vector<int> preOrderRecursive(BinaryTree& bt)
    {
        vector<int> result;
        _preOrder(bt.getRoot(), result);
        return result;
    }

    vector<int> preOrderIterative(BinaryTree& bt)
    {
        vector<int> result;
        Node* root = bt.getRoot();
        stack<Node*> stk;
        while (stk.empty() == false || root != nullptr)
        {
            if (root != nullptr)
            {
                stk.push(root);
                result.push_back(root->val);
                root = root->left;
            }
            else
            {
                Node* temp = stk.top();
                stk.pop();
                root = temp->right;
            }
        }
        return result;
    }

    vector<int> inOrderRecursive(BinaryTree& bt)
    {
        vector<int> result;
        _inOrder(bt.getRoot(), result);
        return result;
    }

    vector<int> inOrderIterative(BinaryTree& bt)
    {
        vector<int> result;
        Node* root = bt.getRoot();
        stack <Node*> stk;
        while (stk.empty() == false || root != nullptr)
        {
            if (root != nullptr)
            {
                stk.push(root);
                root = root->left;
            }
            else
            {
                Node* temp = stk.top();
                stk.pop();
                result.push_back(temp->val);
                root = temp->right;
            }
        }
        return result;
    }

    vector<int> postOrderRecursive(BinaryTree& bt)
    {
        vector<int> result;
        _postOrder(bt.getRoot(), result);
        return result;
    }

    vector<int> postOrderIterative(BinaryTree& bt)
    {
        vector<int> result;
        vector<int> tempResult; // alternatively, you could use a deque and push_front to it instead of having to reverse the list later on
        Node* root = bt.getRoot();
        stack<Node*> stk;
        while (stk.empty() == false || root != nullptr)
        {
            if (root != nullptr)
            {
                tempResult.push_back(root->val);
                stk.push(root);
                root = root->right;
            }
            else
            {
                Node* temp = stk.top();
                stk.pop();
                root = temp->left;
            }
        }

        // reverse the order since this postOrder
        for (auto iter = tempResult.rbegin(); iter != tempResult.rend(); ++iter)
        {
            result.push_back(*iter);
        }
        return result;
    }

    vector<vector<int>> levelOrder(BinaryTree& bt)
    {
        vector<vector<int>> result;
        Node* root = bt.getRoot();
        if (root == nullptr)
        {
            return result;
        }
        queue<Node*> q;
        q.push(root);
        while (q.empty() == false)
        {
            int size = q.size();
            vector<int> level;
            while (size > 0)
            {
                Node* temp = q.front();
                q.pop();
                if (temp != nullptr)
                {
                    level.push_back(temp->val);
                    if (temp->left != nullptr)
                    {
                        q.push(temp->left);
                    }
                    if (temp->right != nullptr)
                    {
                        q.push(temp->right);
                    }
                }
                size--;
            }
            result.push_back(level);
        }
        return result;
    }

    vector<vector<int>> columnOrder(BinaryTree& bt)
    {
        vector<vector<int>> result;
        Node* root = bt.getRoot();
        map<int, vector<int>> columns;
        _columnOrder(root, 0, columns);

        for (auto a : columns)
        {
            result.push_back(a.second);
        }

        return result;
    }

    vector<vector<int>> zigZagOrder(BinaryTree& bt, bool startLeftToRight)
    {
        Node* root = bt.getRoot();
        vector<vector<int>> result;

        if (root == nullptr)
        {
            return result;
        }
        stack<Node*> stk1;
        stack<Node*> stk2;

        if (startLeftToRight)
        {
            stk1.push(root);
        }
        else
        {
            stk2.push(root);
        }

        while (stk1.empty() == false || stk2.empty() == false)
        {
            vector<int> level;
            while (stk1.empty() == false)
            {
                Node* temp = stk1.top();
                stk1.pop();
                level.push_back(temp->val);
                if (temp->left != nullptr)
                {
                    stk2.push(temp->left);
                }
                if (temp->right != nullptr)
                {
                    stk2.push(temp->right);
                }
            }
            if (level.size() > 0)
            {
                result.push_back(level);
                level.clear();
            }
            while (stk2.empty() == false)
            {
                Node* temp = stk2.top();
                stk2.pop();
                level.push_back(temp->val);
                if (temp->right != nullptr)
                {
                    stk1.push(temp->right);
                }
                if (temp->left != nullptr)
                {
                    stk1.push(temp->left);
                }
            }
            if (level.size() > 0)
            {
                result.push_back(level);
                level.clear();
            }
        }

        return result;
    }

    vector<int> boundaryAnticlockwise(BinaryTree& bt)
    {
        Node* root = bt.getRoot();
        vector<int> result;
        if (root == nullptr)
        {
            return result;
        }
        result.push_back(root->val);
        _leftBoundary(root->left, result);
        _bottomBoundary(root->left, result);
        _bottomBoundary(root->right, result);
        _rightBoundary(root->right, result);
        return result;
    }

private:
    void _leftBoundary(Node* root, vector<int>& result)
    {
        while (root != nullptr)
        {
            if (root->left == nullptr && root->right == nullptr)
            {
                // both left and right are null is handled in the _bottomBoundary() case
                break;
            }

            result.push_back(root->val);

            if (root->left != nullptr)
            {
                root = root->left;
            }
            else if (root->right != nullptr)
            {
                root = root->right;
            }
        }
    }

    void _bottomBoundary(Node* root, vector<int>& result)
    {
        if (root == nullptr)
        {
            return;
        }
        if (root->left == nullptr &&
            root->right == nullptr)
        {
            result.push_back(root->val);
        }
        _bottomBoundary(root->left, result);
        _bottomBoundary(root->right, result);
    }

    void _rightBoundary(Node* root, vector<int>& result)
    {
        // since the right boundary needs to be printed from bottom to top, we need to use a stack:
        //      1. we could use our own stack and make this method iterative
        //      2. OR use the system stack and make this a recursive method
        // we're going with option 1 so that this method is somewhat similar in structure to the 
        // _leftBoundary() method. Otherwise if we went with 2, we'd have to make both _leftBoundary()
        // and _rightBoundary() be recursive to achieve the goal of similar structure.
        stack<int> stk;
        while (root != nullptr)
        {
            if (root->left == nullptr && root->right == nullptr)
            {
                // both left and right are null is handled in the _bottomBoundary() case
                break;
            }

            stk.push(root->val);

            if (root->right != nullptr)
            {
                root = root->right;
            }
            else if (root->left != nullptr)
            {
                root = root->left;
            }
        }

        while (stk.empty() == false)
        {
            result.push_back(stk.top());
            stk.pop();
        }
    }

    void _columnOrder(Node* root, int column, map<int, vector<int>>& columns)
    {
        if (root == nullptr)
        {
            return;
        }
        auto iter = columns.find(column);
        if (iter == columns.end())
        {
            columns.insert(pair<int, vector<int>>(column, vector<int>{root->val}));
        }
        else
        {
            iter->second.push_back(root->val);
        }
        _columnOrder(root->left, column - 1, columns);
        _columnOrder(root->right, column + 1, columns);
    }

    void _preOrder(Node* root, vector<int>& result)
    {
        if (root == nullptr)
        {
            return;
        }
        result.push_back(root->val);
        _preOrder(root->left, result);
        _preOrder(root->right, result);
    }

    void _inOrder(Node* root, vector<int>& result)
    {
        if (root == nullptr)
        {
            return;
        }
        _inOrder(root->left, result);
        result.push_back(root->val);
        _inOrder(root->right, result);
    }

    void _postOrder(Node* root, vector<int>& result)
    {
        if (root == nullptr)
        {
            return;
        }
        _postOrder(root->left, result);
        _postOrder(root->right, result);
        result.push_back(root->val);
    }

    void _pushLeft(Node* root, stack<Node*>& stk)
    {
        while (root != nullptr)
        {
            stk.push(root);
            root = root->left;
        }
    }
};

class Search 
{
public:
    bool findValue(BinarySearchTree& bst, int val, Node** result)
    {
        Node* root = bst.getRoot();
        while (root != nullptr)
        {
            if (root->val > val)
            {
                root = root->left;
            }
            else if (root->val < val)
            {
                root = root->right;
            }
            else
            {
                break;
            }
        }

        bool ret = false;
        if (root != nullptr)
        {
            ret = true;
        }

        if (result != nullptr)
        {
            *result = (ret ? root : nullptr);
        }

        return ret;
    }

    // NOTE: This technique assumes both p and q exist in the BST!
    Node* findLowestCommonAncestor(BinarySearchTree& bst, int p, int q)
    {
        Node* root = bst.getRoot();
        if (root == nullptr)
        {
            return root;
        }

        //cout << "NOTE: This technique assumes both p and q exist in the BST!" << endl;
        // hence we'll first do a lookup for both values!
        if (findValue(bst, p, nullptr) == false ||
            findValue(bst, q, nullptr) == false)
        {
            return nullptr;
        }

        while (root != nullptr)
        {
            if (root->val > p &&
                root->val > q)
            {
                root = root->left;
            }
            else if (root->val < p &&
                    root->val < q)
            {
                root = root->right;
            }
            else
            {
                break;
            }
        }
        return root;
    }

    Node* findInorderSuccessorRecursive(BinarySearchTree& bst, int val)
    {
        Node* root = bst.getRoot();
        if (root == nullptr)
        {
            return nullptr;
        }
        Node* p = nullptr;
        bool valueExists = findValue(bst, val, &p);
        if (valueExists == false)
        {
            return nullptr;
        }
        Node* result = _findInorderSuccessorBST(root, p);
        return result;
    }

    Node* findInorderSuccessorIterative(BinarySearchTree& bst, int val)
    {
        Node* root = bst.getRoot();
        Node* p = nullptr;
        {
            // this block shouldn't be part of the complexity analysis if the Node* is passed in instead of just the value
            bool temp = findValue(bst, val, &p);
            if (temp == false)
            {
                return nullptr;
            }
        }

        if (root == nullptr || p == nullptr)
        {
            return nullptr;
        }

        //
        // Here's how the algo works: The successor of a given node can either be a (grand)child or a (grand)parent.
        // Case 1:  If the given node has a right subtree, the successor would be a grand(child). It would be 
        //          the node with the minimum value in the right subtree. That so happens to be the left-most 
        //          node in the right sub-tree.
        // Case 2:  If the given node does not have a right subtree, the successor needs to be searched for in
        //          in the ancestory of the given node. Recall the pattern of in-order traversal:
        //              visit(left)
        //              parse(data)
        //              visit(right)
        //          Case 2a:    Now if the given node is the left subchild of the immediate ancestor, it means 
        //                      that in an inorder traversal, the ancestor would not have parsed his data hence
        //                      making him that particular ancestor the successor.
        //          Case 2b:    If the given node is the right subchild of the immediate ancestor, it means that
        //                      in the inorder traversal, the ancessort is done parsing his data hence the successor
        //                      would have to be somewhere higher. In fact we keep going to older/higher ancestors
        //                      till we find a node where we are the left subchild. If not found that means, we don't
        //                      have a successor which also means the given node is the largest value in the BST.
        // Now the code below works like this:
        //      If needed, find given node (say p) from value
        //      If p has right subchild, find deepest left node in right subtree
        //          return deepest-left-node-in-right-subtree
        //      Set ancestor pointer to root
        //      Set successor pointer to nullptr
        //      Do a Binary Search on BST till you find p
        //          If you need to go left, update successor pointer. This way, we'll be getting the closest parent to
        //              (grand)parent to child that's left of child.
        //              Update ancestor to ancestor->left.
        //          If you need to go right, just update ancestor to go right
        //      return successor
        //

        if (p->right != nullptr)
        {
            return _findMinInBST(p->right);
        }

        Node* ancesstor = root;
        Node* successor = nullptr;
        while (ancesstor->val != p->val)
        {
            if (ancesstor->val > p->val)
            {
                successor = ancesstor;
                ancesstor = ancesstor->left;
            }
            else // (root->val < p->val)
            {
                ancesstor = ancesstor->right;
            }
        }

        return successor;
    }

    Node* findInorderSuccessor(BinaryTree& bt, int val)
    {
        Node* result = nullptr;
        cout << "TODO: findInorderSuccessorBT()" << endl;
        return result;
    }

    Node* findInorderPredecessorRecursive(BinarySearchTree& bst, int val)
    {
        Node* root = bst.getRoot();
        if (root == nullptr)
        {
            return nullptr;
        }

        Node* p = nullptr;
        bool valueExists = findValue(bst, val, &p);
        if (valueExists == false)
        {
            return nullptr;
        }
        Node* result = _findInorderPredecessorBST(root, p);
        return result;
    }

    Node* findInorderPredecessorIterative(BinarySearchTree& bst, int val)
    {
        Node* root = bst.getRoot();
        Node* p = nullptr;
        {
            // this block shouldn't be part of the complexity analysis if the Node* is passed in instead of just the value
            bool temp = findValue(bst, val, &p);
            if (temp == false)
            {
                return nullptr;
            }
        }

        if (root == nullptr || p == nullptr)
        {
            return nullptr;
        }

        //
        // Here's how the algo works: The predecessor of a given node can either be a (grand)child or a (grand)parent.
        // Case 1:  If the given node has a left subtree, the successor would be a grand(child). It would be 
        //          the node with the maximum value in the left subtree. That so happens to be the right-most 
        //          node in the left sub-tree.
        // Case 2:  If the given node does not have a left subtree, the successor needs to be searched for in
        //          in the ancestory of the given node. Recall the pattern of in-order traversal:
        //              visit(left)
        //              parse(data)
        //              visit(right)
        //          Case 2a:    Now if the given node is the right subchild of the immediate ancestor, it means 
        //                      that in an inorder traversal, the ancestor would have parsed his left and his data 
        //                      hence making this particular ancesstor the predecessor.
        //          Case 2b:    If the given node is the left subchild of the immediate ancestor, TODO!
        // Now the code below works like this:
        //      If needed, find given node (say p) from value
        //      If p has left subchild, find deepest right node in left subtree
        //          return deepest-right-node-in-left-subtree
        //      Set ancestor pointer to root
        //      Set predecessor pointer to nullptr
        //      Do a Binary Search on BST till you find p
        //          If you need to go right, update predecessor pointer. This way, we'll be getting the closest parent to
        //              (grand)parent to child that's right of child.
        //              Update ancestor to ancestor->left.
        //          If you need to go left, just update ancestor to go left
        //      return predecessor
        //

        if (p->left)
        {
            return _findMaxinBST(p->left);
        }

        Node* predecessor = nullptr;
        Node* ancestor = root;
        while (ancestor->val != p->val)
        {
            if (ancestor->val > p->val)
            {
                ancestor = ancestor->left;
            }
            else // ancestor->val < p->val
            {
                predecessor = ancestor;
                ancestor = ancestor->right;
            }
        }
        return predecessor;
    }

    Node* findInorderPredecessor(BinaryTree& bt, int val)
    {
        Node* result = nullptr;
        cout << "TODO: findInorderPredecessorBT()" << endl;
        return result;
    }

private:

    Node* _findMaxinBST(Node* root)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        while (root->right != nullptr)
        {
            root = root->right;
        }
        return root;
    }

    Node* _findMinInBST(Node* root)
    {
        if (root == nullptr)
        {
            return root;
        }
        while (root->left != nullptr)
        {
            root = root->left;
        }
        return root;
    }

    Node* _findInorderPredecessorBST(Node* root, Node* p)
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        // NOTE: Make sure you understand the '>=' being used here
        if (root->val >= p->val)
        {
            return _findInorderPredecessorBST(root->left, p);
        }
        else
        {
            Node* right = _findInorderPredecessorBST(root->right, p);
            if (right == nullptr)
            {
                return root;
            }
            return right;
        }
    }

    Node* _findInorderSuccessorBST(Node* root, Node* p)
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        // NOTE: Make sure you understand the '<=' being used here
        if (root->val <= p->val)
        {
            return _findInorderSuccessorBST(root->right, p);
        }
        else
        {
            Node* left = _findInorderSuccessorBST(root->left, p);
            if (left == nullptr)
            {
                return root;
            }
            return left;
        }
    }
};

void testProperties()
{
    cout << "TEST PROPERTIES OF TREES" << endl;
    vector<int> input{ 1,2,3,4,5,6,7,8,9 };
    BinarySearchTree bst;
    bst.createTree(input);

    Properties p;
    int height = p.height(bst);
    cout << "Height = " << height << endl;

    bool isValidBST = p.isValidBST(bst);
    cout << "Is Valid BST = " << isValidBST << endl;
}

void testTraversal()
{
    vector<int> input{ 1,2,3,4,5,6,7,8,9 };
    BinarySearchTree bst;
    bst.createTree(input);

    cout << "TEST TRAVERSAL" << endl;
    Traversal t;

    auto preOrderRecursive = t.preOrderRecursive(bst);
    cout << "Preorder Recursive: " << endl;
    cout << "  ";
    for (auto a : preOrderRecursive)
    {
        cout << a << " ";
    }
    cout << endl;
    auto preOrderIterative = t.preOrderIterative(bst);
    cout << "Preorder Iterative: " << endl;
    cout << "  ";
    for (auto a : preOrderIterative)
    {
        cout << a << " ";
    }
    cout << endl;
    assert(preOrderRecursive.size() == preOrderIterative.size());
    for (int i = 0; i < preOrderRecursive.size(); i++)
    {
        assert(preOrderRecursive[i] == preOrderIterative[i]);
    }

    cout << "Inorder Recursive: " << endl;
    cout << "  ";
    auto inOrderRecursive = t.inOrderRecursive(bst);
    for (auto a : inOrderRecursive)
    {
        cout << a << " ";
    }
    cout << endl;
    cout << "Inorder Iterative: " << endl;
    cout << "  ";
    auto inOrderIterative = t.inOrderIterative(bst);
    for (auto a : inOrderIterative)
    {
        cout << a << " ";
    }
    cout << endl;
    assert(inOrderRecursive.size() == inOrderIterative.size());
    for (int i = 0; i < inOrderRecursive.size(); i++)
    {
        assert(inOrderRecursive[i] == inOrderIterative[i]);
    }

    cout << "Postorder Recursive: " << endl;
    cout << "  ";
    auto postOrderRecursive = t.postOrderRecursive(bst);
    for (auto a : postOrderRecursive)
    {
        cout << a << " ";
    }
    cout << endl;
    cout << "Postorder Iterative: " << endl;
    cout << "  ";
    auto postOrderIterative = t.postOrderIterative(bst);
    for (auto a : postOrderIterative)
    {
        cout << a << " ";
    }
    cout << endl;
    assert(postOrderRecursive.size() == postOrderIterative.size());
    for (int i = 0; i < postOrderRecursive.size(); i++)
    {
        assert(postOrderRecursive[i] == postOrderIterative[i]);
    }


    cout << "LevelOrder: " << endl;
    auto levelOrder = t.levelOrder(bst);
    for (auto a : levelOrder)
    {
        cout << "  ";
        for (auto b : a)
        {
            cout << b << " ";
        }
        cout << endl;
    }
    cout << "ColumnOrder: " << endl;
    auto columnOrder = t.columnOrder(bst);
    for (auto a : columnOrder)
    {
        cout << "  ";
        for (auto b : a)
        {
            cout << b << " ";
        }
        cout << endl;
    }
    cout << "ZigZagOrder (LtR): " << endl;
    auto zigZagLtROrder = t.zigZagOrder(bst, true);
    for (auto a : zigZagLtROrder)
    {
        cout << "  ";
        for (auto b : a)
        {
            cout << b << " ";
        }
        cout << endl;
    }
    cout << "ZigZagOrder(RtL): " << endl;
    auto zigZagRtLOrder = t.zigZagOrder(bst, false);
    for (auto a : zigZagRtLOrder)
    {
        cout << "  ";
        for (auto b : a)
        {
            cout << b << " ";
        }
        cout << endl;
    }
    cout << "Boundary(Anticlockwise):" << endl;
    auto boundaryAnticlockwise = t.boundaryAnticlockwise(bst);
    cout << "  ";
    for (auto a : boundaryAnticlockwise)
    {
        cout << a << " ";
    }
    cout << endl;
}

void testSearchBST()
{
    vector<int> input{ 1,2,3,4,5,6,7,8,9 };
    BinarySearchTree bst;
    bst.createTree(input);
    Search s;

    bool tempBool = false;
    Node* tempNode = nullptr;
    int val = -1;

    {
        val = -1;
        tempBool = s.findValue(bst, val, &tempNode);
        assert(tempBool == false && tempNode == nullptr);
        val = 0;
        tempBool = s.findValue(bst, val, &tempNode);
        assert(tempBool == false && tempNode == nullptr);
        val = 1;
        tempBool = s.findValue(bst, val, &tempNode);
        assert(tempBool != false && tempNode != nullptr && tempNode->val == val);
        val = 2;
        tempBool = s.findValue(bst, val, &tempNode);
        assert(tempBool != false && tempNode != nullptr && tempNode->val == val);
        val = 3;
        tempBool = s.findValue(bst, val, &tempNode);
        assert(tempBool != false && tempNode != nullptr && tempNode->val == val);
        val = 4;
        tempBool = s.findValue(bst, val, &tempNode);
        assert(tempBool != false && tempNode != nullptr && tempNode->val == val);
        val = 5;
        tempBool = s.findValue(bst, val, &tempNode);
        assert(tempBool != false && tempNode != nullptr && tempNode->val == val);
        val = 6;
        tempBool = s.findValue(bst, val, &tempNode);
        assert(tempBool != false && tempNode != nullptr && tempNode->val == val);
        val = 7;
        tempBool = s.findValue(bst, val, &tempNode);
        assert(tempBool != false && tempNode != nullptr && tempNode->val == val);
        val = 8;
        tempBool = s.findValue(bst, val, &tempNode);
        assert(tempBool != false && tempNode != nullptr && tempNode->val == val);
        val = 9;
        tempBool = s.findValue(bst, val, &tempNode);
        assert(tempBool != false && tempNode != nullptr && tempNode->val == val);
        val = 10;
        tempBool = s.findValue(bst, val, &tempNode);
        assert(tempBool == false && tempNode == nullptr);
    }

    cout << "Find Lowest Common Ancestor in BST:" << endl;
    vector<pair<int, int>> lcaCandidates{
        { 10, 9 },
        { 1, 9 },
        { 2, 8 },
        { 3, 7 },
        { 5, 5 },
        { 5, 1 },
        { 5, 9 },
        { 6, 9 },
        { 1, 3 },
        { 0, 5 },
    };
    for (auto a : lcaCandidates)
    {
        Node* temp = s.findLowestCommonAncestor(bst, a.first, a.second);
        if (temp != nullptr)
        {
            cout << "  lca(" << a.first << "," << a.second << ")="
                << temp->val
                << endl;
        }
        else
        {
            cout << "  lca(" << a.first << "," << a.second << ")="
                << "DOESN\'T EXIST"
                << endl;
        }
    }

    {
        cout << "Inorder Successor Recursive (assumes root is BST):" << endl;
        val = -1;
        tempNode = s.findInorderSuccessorRecursive(bst, val);
        assert(tempNode == nullptr);
        val = 0;
        tempNode = s.findInorderSuccessorRecursive(bst, val);
        assert(tempNode == nullptr);
        val = 1;
        tempNode = s.findInorderSuccessorRecursive(bst, val);
        assert(tempNode != nullptr && tempNode->val == val + 1);
        val = 2;
        tempNode = s.findInorderSuccessorRecursive(bst, val);
        assert(tempNode != nullptr && tempNode->val == val + 1);
        val = 3;
        tempNode = s.findInorderSuccessorRecursive(bst, val);
        assert(tempNode != nullptr && tempNode->val == val + 1);
        val = 4;
        tempNode = s.findInorderSuccessorRecursive(bst, val);
        assert(tempNode != nullptr && tempNode->val == val + 1);
        val = 5;
        tempNode = s.findInorderSuccessorRecursive(bst, val);
        assert(tempNode != nullptr && tempNode->val == val + 1);
        val = 6;
        tempNode = s.findInorderSuccessorRecursive(bst, val);
        assert(tempNode != nullptr && tempNode->val == val + 1);
        val = 7;
        tempNode = s.findInorderSuccessorRecursive(bst, val);
        assert(tempNode != nullptr && tempNode->val == val + 1);
        val = 8;
        tempNode = s.findInorderSuccessorRecursive(bst, val);
        assert(tempNode != nullptr && tempNode->val == val + 1);
        val = 9;
        tempNode = s.findInorderSuccessorRecursive(bst, val);
        assert(tempNode == nullptr);
        val = 10;
        tempNode = s.findInorderSuccessorRecursive(bst, val);
        assert(tempNode == nullptr);
    }
    {
        cout << "Inorder Successor Iterative (assumes root is BST):" << endl;
        val = -1;
        tempNode = s.findInorderSuccessorIterative(bst, val);
        assert(tempNode == nullptr);
        val = 0;
        tempNode = s.findInorderSuccessorIterative(bst, val);
        assert(tempNode == nullptr);
        val = 1;
        tempNode = s.findInorderSuccessorIterative(bst, val);
        assert(tempNode != nullptr && tempNode->val == val + 1);
        val = 2;
        tempNode = s.findInorderSuccessorIterative(bst, val);
        assert(tempNode != nullptr && tempNode->val == val + 1);
        val = 3;
        tempNode = s.findInorderSuccessorIterative(bst, val);
        assert(tempNode != nullptr && tempNode->val == val + 1);
        val = 4;
        tempNode = s.findInorderSuccessorIterative(bst, val);
        assert(tempNode != nullptr && tempNode->val == val + 1);
        val = 5;
        tempNode = s.findInorderSuccessorIterative(bst, val);
        assert(tempNode != nullptr && tempNode->val == val + 1);
        val = 6;
        tempNode = s.findInorderSuccessorIterative(bst, val);
        assert(tempNode != nullptr && tempNode->val == val + 1);
        val = 7;
        tempNode = s.findInorderSuccessorIterative(bst, val);
        assert(tempNode != nullptr && tempNode->val == val + 1);
        val = 8;
        tempNode = s.findInorderSuccessorIterative(bst, val);
        assert(tempNode != nullptr && tempNode->val == val + 1);
        val = 9;
        tempNode = s.findInorderSuccessorIterative(bst, val);
        assert(tempNode == nullptr);
        val = 10;
        tempNode = s.findInorderSuccessorIterative(bst, val);
        assert(tempNode == nullptr);
    }

    cout << "Inorder Predecessor Recursive (assumes root is BST):" << endl;
    {
        val = -1;
        tempNode = s.findInorderPredecessorRecursive(bst, val);
        assert(tempNode == nullptr);
        val = 0;
        tempNode = s.findInorderPredecessorRecursive(bst, val);
        assert(tempNode == nullptr);
        val = 1;
        tempNode = s.findInorderPredecessorRecursive(bst, val);
        assert(tempNode == nullptr);
        val = 2;
        tempNode = s.findInorderPredecessorRecursive(bst, val);
        assert(tempNode != nullptr && tempNode->val == val - 1);
        val = 3;
        tempNode = s.findInorderPredecessorRecursive(bst, val);
        assert(tempNode != nullptr && tempNode->val == val - 1);
        val = 4;
        tempNode = s.findInorderPredecessorRecursive(bst, val);
        assert(tempNode != nullptr && tempNode->val == val - 1);
        val = 5;
        tempNode = s.findInorderPredecessorRecursive(bst, val);
        assert(tempNode != nullptr && tempNode->val == val - 1);
        val = 6;
        tempNode = s.findInorderPredecessorRecursive(bst, val);
        assert(tempNode != nullptr && tempNode->val == val - 1);
        val = 7;
        tempNode = s.findInorderPredecessorRecursive(bst, val);
        assert(tempNode != nullptr && tempNode->val == val - 1);
        val = 8;
        tempNode = s.findInorderPredecessorRecursive(bst, val);
        assert(tempNode != nullptr && tempNode->val == val - 1);
        val = 9;
        tempNode = s.findInorderPredecessorRecursive(bst, val);
        assert(tempNode != nullptr && tempNode->val == val - 1);
        val = 10;
        tempNode = s.findInorderPredecessorRecursive(bst, val);
        assert(tempNode == nullptr);
    }
    
    cout << "Inorder Predecessor Iterative (assumes root is BST):" << endl;
    {
        val = -1;
        tempNode = s.findInorderPredecessorIterative(bst, val);
        assert(tempNode == nullptr);
        val = 0;
        tempNode = s.findInorderPredecessorIterative(bst, val);
        assert(tempNode == nullptr);
        val = 1;
        tempNode = s.findInorderPredecessorIterative(bst, val);
        assert(tempNode == nullptr);
        val = 2;
        tempNode = s.findInorderPredecessorIterative(bst, val);
        assert(tempNode != nullptr && tempNode->val == val - 1);
        val = 3;
        tempNode = s.findInorderPredecessorIterative(bst, val);
        assert(tempNode != nullptr && tempNode->val == val - 1);
        val = 4;
        tempNode = s.findInorderPredecessorIterative(bst, val);
        assert(tempNode != nullptr && tempNode->val == val - 1);
        val = 5;
        tempNode = s.findInorderPredecessorIterative(bst, val);
        assert(tempNode != nullptr && tempNode->val == val - 1);
        val = 6;
        tempNode = s.findInorderPredecessorIterative(bst, val);
        assert(tempNode != nullptr && tempNode->val == val - 1);
        val = 7;
        tempNode = s.findInorderPredecessorIterative(bst, val);
        assert(tempNode != nullptr && tempNode->val == val - 1);
        val = 8;
        tempNode = s.findInorderPredecessorIterative(bst, val);
        assert(tempNode != nullptr && tempNode->val == val - 1);
        val = 9;
        tempNode = s.findInorderPredecessorIterative(bst, val);
        assert(tempNode != nullptr && tempNode->val == val - 1);
        val = 10;
        tempNode = s.findInorderPredecessorIterative(bst, val);
        assert(tempNode == nullptr);
    }
}

int main()
{
    vector<int> input{1,2,3,4,5,6,7,8,9};
    cout << "INPUT: " << endl;
    for (auto a : input)
    {
        cout << a << " ";
    }
    cout << endl;

    testProperties();

    testTraversal();

    testSearchBST();


    return 0;
}

