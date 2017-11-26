// TreeRelations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <queue>
#include <map>

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
        Node* root = new Node(input[mid]);
        root->left = _createBalancedBSTRecur(input, low, mid - 1);
        root->right = _createBalancedBSTRecur(input, mid+1, high);
        return root;
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

int main()
{
    vector<int> input{0,1,2,3,4,5,6,7,8,9};
    cout << "INPUT: ";
    for (auto a : input)
    {
        cout << a << " ";
    }
    cout << endl;

    Node* root1 = nullptr;
    CreateBalancedBST cbb;
    root1 = cbb.createBalancedBST(input);

    Traversal t;

    auto preOrder = t.preOrder(root1);
    cout << "Preorder: " << endl;
    for (auto a : preOrder)
    {
        cout << a << " ";
    }
    cout << endl;
    cout << "Inorder: " << endl;
    auto inOrder = t.inOrder(root1);
    for (auto a : inOrder)
    {
        cout << a << " ";
    }
    cout << endl;
    cout << "Postorder: " << endl;
    auto postOrder = t.postOrder(root1);
    for (auto a : postOrder)
    {
        cout << a << " ";
    }
    cout << endl;
    cout << "LevelOrder: " << endl;
    auto levelOrder = t.levelOrder(root1);
    for (auto a : levelOrder)
    {
        for (auto b : a)
        {
            cout << b << " ";
        }
        cout << endl;
    }
    cout << "ColumnOrder: " << endl;
    auto columnOrder = t.columnOrder(root1);
    for (auto a : columnOrder)
    {
        for (auto b : a)
        {
            cout << b << " ";
        }
        cout << endl;
    }

    return 0;
}

