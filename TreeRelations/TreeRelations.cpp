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

class CreateBalancedBST
{
public:
    Node* createBalancedBST(vector<int>& input)
    {
        if (input.size() == 0)
        {
            return nullptr;
        }

        Node* root = nullptr;

        root = _createBalancedBSTRecur(input, 0, input.size()-1);
        
        return root;
    }

private:
    Node* _createBalancedBSTRecur(vector<int>& input, int low, int high)
    {
        if (low > high)
        {
            return nullptr;
        }
        int mid = low + ((high-low) / 2);
        assert(input[mid] >= 0);
        Node* root = new Node(input[mid]);
        root->left = _createBalancedBSTRecur(input, low, mid - 1);
        root->right = _createBalancedBSTRecur(input, mid+1, high);
        return root;
    }
};

class Properties
{
public:
    int heightOfBT(Node* root)
    {
        return _heightOfBT(root);
    }

    bool isValidBST(Node* root)
    {
        Node* prev = nullptr;
        return _isValidBST(root, prev);
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

    int _heightOfBT(Node* root)
    {
        if (root == nullptr)
        {
            return 0;
        }

        int temp1 = _heightOfBT(root->left);
        if (temp1 == -1)
        {
            return temp1;
        }
        int temp2 = _heightOfBT(root->right);
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
    vector<int> preOrder(Node* root)
    {
        vector<int> result;
        _preOrder(root, result);
        return result;
    }

    vector<int> inOrder(Node* root)
    {
        vector<int> result;
        _inOrder(root, result);
        return result;
    }

    vector<int> postOrder(Node* root)
    {
        vector<int> result;
        _postOrder(root, result);
        return result;
    }

    vector<vector<int>> levelOrder(Node* root)
    {
        vector<vector<int>> result;
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

    vector<vector<int>> columnOrder(Node* root)
    {
        vector<vector<int>> result;

        map<int, vector<int>> columns;
        _columnOrder(root, 0, columns);

        for (auto a : columns)
        {
            result.push_back(a.second);
        }

        return result;
    }

    vector<vector<int>> zigZagOrder(Node* root, bool startLeftToRight)
    {
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

private:
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
};

class Search 
{
public:
    bool findValueInBST(Node* root, int val, Node** result)
    {
        if (root == nullptr)
        {
            return false;
        }
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

        if (root == nullptr)
        {
            return false;
        }

        if (result != nullptr)
        {
            *result = root;
        }

        return true;
    }

    // NOTE: This technique assumes both p and q exist in the BST!
    Node* findLowestCommonAncestorBST(Node* root, int p, int q)
    {
        if (root == nullptr)
        {
            return root;
        }

        //cout << "NOTE: This technique assumes both p and q exist in the BST!" << endl;
        // hence we'll first do a lookup for both values!
        if (findValueInBST(root, p, nullptr) == false ||
            findValueInBST(root, q, nullptr) == false)
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
            return root;
        }
    }

    Node* findInorderSuccessorBST(Node* root, int val)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        Node* p = nullptr;
        bool valueExists = findValueInBST(root, val, &p);
        if (valueExists == false)
        {
            return nullptr;
        }
        Node* result = _findInorderSuccessorBST(root, p);
        return result;
    }

    Node* findInorderSuccessorBT(Node* root, int val)
    {
        Node* result = nullptr;
        cout << "TODO: findInorderSuccessorBT()" << endl;
        return result;
    }

    Node* findInorderPredecessorBST(Node* root, int val)
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        Node* p = nullptr;
        bool valueExists = findValueInBST(root, val, &p);
        if (valueExists == false)
        {
            return nullptr;
        }
        Node* result = _findInorderPredecessorBST(root, p);
        return result;
    }

    Node* findInorderPredecessorBT(Node* root, int val)
    {
        Node* result = nullptr;
        cout << "TODO: findInorderPredecessorBT()" << endl;
        return result;
    }

private:
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

void testProperties(Node* root)
{
    cout << "TEST PROPERTIES OF TREES" << endl;
    Properties p;

    int height = p.heightOfBT(root);
    cout << "Height = " << height << endl;

    bool isValidBST = p.isValidBST(root);
    cout << "Is Valid BST = " << isValidBST << endl;
}

void testTraversal(Node* root)
{
    cout << "TEST TRAVERSAL" << endl;
    Traversal t;

    auto preOrder = t.preOrder(root);
    cout << "Preorder: " << endl;
    cout << "  ";
    for (auto a : preOrder)
    {
        cout << a << " ";
    }
    cout << endl;
    cout << "Inorder: " << endl;
    cout << "  ";
    auto inOrder = t.inOrder(root);
    for (auto a : inOrder)
    {
        cout << a << " ";
    }
    cout << endl;
    cout << "Postorder: " << endl;
    cout << "  ";
    auto postOrder = t.postOrder(root);
    for (auto a : postOrder)
    {
        cout << a << " ";
    }
    cout << endl;
    cout << "LevelOrder: " << endl;
    auto levelOrder = t.levelOrder(root);
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
    auto columnOrder = t.columnOrder(root);
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
    auto zigZagLtROrder = t.zigZagOrder(root, true);
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
    auto zigZagRtLOrder = t.zigZagOrder(root, false);
    for (auto a : zigZagRtLOrder)
    {
        cout << "  ";
        for (auto b : a)
        {
            cout << b << " ";
        }
        cout << endl;
    }
}

void testSearchBST(vector<int>& valuesToFind, Node* root)
{
    cout << "TEST SEARCH ON BSTs" << endl;
    Search s;

    cout << "Binary Search (assumes root is BST):" << endl;
    vector<bool> toFind(valuesToFind.size() + 2, false);
    for (int i = 0; i < toFind.size(); i++)
    {
        toFind[i] = s.findValueInBST(root, i, nullptr);
    }
    for (int i = 0; i < toFind.size(); i++)
    {
        cout << "  found(" << i << ")=" << toFind[i] << endl;
    }

    cout << "Find Lowest Common Ancestor in BST:" << endl;
    int p, q;
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
        Node* temp = s.findLowestCommonAncestorBST(root, a.first, a.second);
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

    cout << "Inorder Successor (assumes root is BST):" << endl;
    vector<int> toFindSuccessor(valuesToFind.size() + 2, false);
    for (int i = 0; i < toFindSuccessor.size(); i++)
    {
        Node* temp = s.findInorderSuccessorBST(root, i);
        if (temp == nullptr)
        {
            toFindSuccessor[i] = -1;
        }
        else
        {
            toFindSuccessor[i] = temp->val;
        }
    }
    for (int i = 0; i < toFindSuccessor.size(); i++)
    {
        cout << "  successor(" << i << ")=" 
            << ((toFindSuccessor[i] == -1) ? "DOESN\'T EXIST!" : to_string(toFindSuccessor[i]))
            << endl;
    }

    cout << "Inorder Predecessor (assumes root is BST):" << endl;
    vector<int> toFindPredecessor(valuesToFind.size() + 2, false);
    for (int i = 0; i < toFindPredecessor.size(); i++)
    {
        Node* temp = s.findInorderPredecessorBST(root, i);
        if (temp == nullptr)
        {
            toFindPredecessor[i] = -1;
        }
        else
        {
            toFindPredecessor[i] = temp->val;
        }
    }
    for (int i = 0; i < toFindPredecessor.size(); i++)
    {
        cout << "  predecessor(" << i << ")="
            << ((toFindPredecessor[i] == -1) ? "DOESN\'T EXIST!" : to_string(toFindPredecessor[i]))
            << endl;
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

    Node* root1 = nullptr;
    CreateBalancedBST cbb;
    root1 = cbb.createBalancedBST(input);

    testProperties(root1);

    testTraversal(root1);

    testSearchBST(input, root1);


    return 0;
}

