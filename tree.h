#ifndef _TREE_H_
#define _TREE_H_
#include <string>

struct 
node{
    bool op_and = false;
    bool op_xor = false;
    bool op_or = false;
    bool op_not = false;
    std::string value = "";
    struct node *left = NULL;
    struct node *right = NULL;
};

class treeNode{

     public:
        treeNode();
        treeNode(std::string formula);
        ~treeNode();

        int main();
    treeNode *left = NULL;
    treeNode *right = NULL;
    std::string value;
    bool op_and = false;
    bool op_xor = false;
        bool op_or = false;
        bool op_not = false;
        int getInputs(std::string formula);
    void printTree();
    bool checkUniformity(std::string s, int i);
    bool uniformp(std::vector<std::string> v);
    bool checkForOne(std::string s);
       // bool checkUniformity(std::string formula, int inputs);
        //bool next(std::string::iterator begin, std::string::iterator end);


    private:
        void createNode(std::string n);
        
};

#endif