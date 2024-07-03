#include <iostream>
#include <queue>



struct Node {
    char text;
    Node* left = nullptr;
    Node* right = nullptr;
};

/* 
Да се реализира функция printText, която получава като аргумент указател към корен на такова
дърво и извежда на стандартния изход текста, записан във върховете, спазвайки следните правила:
• съдържанието на всяко ниво (елементи с еднаква дълбочина) се извежда на отделен ред;
• ако на дадено място в нивото липсва възел, да се изведе интервал;
• дървото се извежда до последния елемент от последното ниво.
За показаното като пример дърво трябва да се изведе следния текст:
|I|
|am|
|good|
|at␣solvi|
|ng␣p␣␣roblem␣␣␣␣|
|s␣␣!|
*/

void printText(Node* root) {
    std::queue<const Node*> q;
    q.push(root);
    int curr = 1;
    int next = 0;
    while(!q.empty()) {
        const Node* n = q.front();
        q.pop();
        --curr;
        if(n) {
            std::cout << n->text;
            q.push(n->left);
            q.push(n->right);
            next += 2;
        } else {
            std::cout << " ";
        }
        if(!curr) {
            curr = next;
            next = 0;
            std::cout << std::endl;
        }
    }
}


void clear_tree(Node* root) {
    if(!root) return;
    clear_tree(root->left);
    clear_tree(root->right);

    delete root;
}

int main() {
Node* root = new Node{'I'};
root->left = new Node{'a'};
root->left->left = new Node{'g', new Node{'a', 
                                          new Node{'n', new Node{'s'}}, 
                                          new Node{'g', nullptr, new Node{'!'}}}, 
                                            new Node{'t', nullptr, new Node{'p'}}};
root->left->right = new Node{'o', nullptr, new Node{'s', new Node{'r'}, new Node{'o'}}};

root->right = new Node{'m', nullptr, new Node{'d', new Node{'v'}, new Node{'i'}}};
root->right->left = new Node{'o', new Node{'o', new Node{'b'}, new Node{'l'}}, 
                                  new Node{'d', new Node{'v'}, new Node{'i'}}};

    printText(root);

    return 0;    
}