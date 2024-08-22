#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <algorithm>

struct TreeNode {
    int data;
    std::list<TreeNode*> children;
    TreeNode* parent = nullptr;
};

void printBFS(const TreeNode* root) {
    if(!root) return;
    std::queue<const TreeNode*> q;
    int curr = 1;
    int next = 0;
    q.push(root);

    while(!q.empty()) {
        const TreeNode* n = q.front();
        q.pop();
        --curr;
        std::cout << n->data << " ";

        for(const TreeNode* child: n->children) {
            q.push(child);
            ++next;
        }

        if(!curr) {
            curr = next;
            next = 0;
            std::cout << "\n";
        }

    }
}


int findLevel(const TreeNode* root, const std::vector<int>& numbers) {
    if(!root) return -1;

    int level = 0;
    std::queue<const TreeNode*> q;
    std::vector<const TreeNode*> levelNodes;
    q.push(root);

    int curr = 1;
    int next = 0;

    while(!q.empty()) {
        const TreeNode* n = q.front();
        q.pop();
        --curr;
        levelNodes.push_back(n);
        for(const TreeNode* child: n->children) {
            q.push(child);
            ++next;
        }

        if(curr == 0) {
            curr = next;
            next = 0;

            if(levelNodes.size() != numbers.size()) {
                levelNodes.clear();
                level += 1;
                continue;
            }
            bool ok = true;
            for(int i = 0; i < levelNodes.size(); ++i) {
                if(levelNodes[i] ->data != numbers[i]) {
                    ok = false;
                    break;
                }
            }
            if(ok) {
                return level;
            }
            level += 1;
            levelNodes.clear();

        }

    }
    return -1;

}


void RemoveNode(TreeNode* n) {
    auto parent_pos = std::find(n->parent->children.begin(), 
                                n->parent->children.end(), n);
    for(TreeNode* child: n->children) {
        child->parent = n->parent;
    }
    n->parent->children.insert(parent_pos, 
                               n->children.begin(), 
                               n->children.end());
    n->parent->children.erase(parent_pos);
    delete n;
}


void RemoveAllLevels(TreeNode* root, const std::vector<int>& numbers) {
    if(!root) return;

    int level = 0;
    std::queue<TreeNode*> q;
    std::vector<TreeNode*> levelNodes;
    q.push(root);

    int curr = 1;
    int next = 0;

    while(!q.empty()) {
        TreeNode* n = q.front();
        q.pop();
        --curr;
        levelNodes.push_back(n);
        for(TreeNode* child: n->children) {
            q.push(child);
            ++next;
        }

        if(curr == 0) {
            curr = next;
            next = 0;

            if(levelNodes.size() != numbers.size()) {
                levelNodes.clear();
                level += 1;
                continue;
            }
            bool ok = true;
            for(int i = 0; i < levelNodes.size(); ++i) {
                if(levelNodes[i] ->data != numbers[i]) {
                    ok = false;
                    break;
                }
            }
            if(ok && level != 0) {
                for(TreeNode* n: levelNodes) {
                    RemoveNode(n);
                }
            }
            level += 1;
            levelNodes.clear();

        }

    }
    
}

void freeTree(TreeNode* root) {
    if(!root) return;
    for(TreeNode* ch : root->children) {
        freeTree(ch);
    }
    delete root;
}

int main() {
    TreeNode* root = new TreeNode{3};
    
    TreeNode* node4 = new TreeNode{4};
    TreeNode* node7 = new TreeNode{7};
    TreeNode* node8 = new TreeNode{8};
    
    TreeNode* node1 = new TreeNode{1};
    TreeNode* node2_1 = new TreeNode{2}; 
    TreeNode* node6_1 = new TreeNode{6};
    
    TreeNode* node7_1 = new TreeNode{7}; 
    TreeNode* node9_1 = new TreeNode{9}; 
    TreeNode* node9_2 = new TreeNode{9}; 
    TreeNode* node5 = new TreeNode{5};  
    TreeNode* node6_2 = new TreeNode{6}; 
    
    TreeNode* node2_2 = new TreeNode{2};
    TreeNode* node3 = new TreeNode{3};   
    TreeNode* node9_3 = new TreeNode{9}; 
    TreeNode* node2_3 = new TreeNode{2};
    
    root->children = {node4, node7, node8};
    
    node4->children = {node1, node2_1};
    node7->children = {node6_1};
    node8->children = {node7_1, node9_1};
    
    node1->children = {node9_2, node5, node6_2};
    node6_1->children = {node2_2};
    
    node7_1->children = {node3, node9_3, node2_3};
    
    node4->parent = root;
    node7->parent = root;
    node8->parent = root;
    
    node1->parent = node4;
    node2_1->parent = node4;
    
    node6_1->parent = node7;
    
    node7_1->parent = node8;
    node9_1->parent = node8;
    
    node9_2->parent = node1;
    node5->parent = node1;
    node6_2->parent = node1;
    
    node2_2->parent = node6_1;
    
    node3->parent = node7_1;
    node9_3->parent = node7_1;
    node2_3->parent = node7_1;

    std::vector<int> testNumbers = {1, 2, 6, 7, 9}; 
    //std::vector<int> testNumbers = {4, 7, 8}; 
    printBFS(root);
    int level = findLevel(root, testNumbers);
    std::cout << "The level is: " << level << std::endl;

    RemoveAllLevels(root, testNumbers);
    std::cout << "After removal: \n";
    printBFS(root);

    freeTree(root);

    return 0;
}