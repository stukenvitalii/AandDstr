#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>

class TreeNode {
public:
    char data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;
    char currentChar;

public:
    BinaryTree() : root(nullptr), currentChar('A') {}

    void generateRandomTree(int maxHeight) {
        root = generateRandomTreeHelper(maxHeight);
        assignNodeNames(root);
    }

    void manualInputTree() {
        root = manualInputTreeHelper();
        assignNodeNames(root);
    }

    int countNodesWithLessThanTwoChildren() const {
        return countNodesWithLessThanTwoChildrenHelper(root);
    }

    void displayTree() const {
        displayTreeHorizontally();
    }

    void displayInOrderTraversal() const {
        std::cout << "\nIn-Order Traversal of the Tree: ";
        displayInOrderTraversalHelper(root);
        std::cout << std::endl;
    }

private:
    TreeNode* generateRandomTreeHelper(int maxHeight) {
        if (maxHeight <= 0 || rand() % 2 == 0) {
            return new TreeNode(currentChar++);
        }

        TreeNode* newNode = new TreeNode(currentChar++);
        newNode->right = generateRandomTreeHelper(maxHeight - 1);
        newNode->left = generateRandomTreeHelper(maxHeight - 1);

        return newNode;
    }

    TreeNode* manualInputTreeHelper() {
        char userInput;
        std::cout << "Do you want to manually input a tree? (y/n): ";
        std::cin >> userInput;

        if (userInput == 'y' || userInput == 'Y') {
            char rootData;
            std::cout << "Enter data for the root node: ";
            std::cin >> rootData;

            TreeNode* newNode = new TreeNode(rootData);

            std::cout << "Does the root have a left child? (y/n): ";
            std::cin >> userInput;
            if (userInput == 'y' || userInput == 'Y') {
                newNode->left = manualInputTreeHelper();
            }

            std::cout << "Does the root have a right child? (y/n): ";
            std::cin >> userInput;
            if (userInput == 'y' || userInput == 'Y') {
                newNode->right = manualInputTreeHelper();
            }

            return newNode;
        } else {
            std::cout << "Generating a random tree.\n";
            return generateRandomTreeHelper(4);  // Adjust the maxHeight as needed
        }
    }

    void assignNodeNames(TreeNode* node) {
        if (node != nullptr) {
            assignNodeNames(node->left);
            node->data = currentChar++;
            assignNodeNames(node->right);
        }
    }

    int countNodesWithLessThanTwoChildrenHelper(TreeNode* node) const {
        if (node == nullptr) {
            return 0;
        }

        int count = 0;

        std::stack<TreeNode*> stack;
        TreeNode* current = node;

        while (current != nullptr || !stack.empty()) {
            while (current != nullptr) {
                stack.push(current);
                current = current->left;
            }

            current = stack.top();
            stack.pop();

            if (current->left == nullptr || current->right == nullptr) {
                count++;
            }

            current = current->right;
        }

        return count;
    }

    void displayTreeHorizontally() const {
        displayTreeHorizontallyHelper(root, 0, 0);
    }

    void displayTreeHorizontallyHelper(TreeNode* node, int level, int space) const {
        const int horizontalDistance = 5;

        if (node == nullptr) {
            return;
        }

        displayTreeHorizontallyHelper(node->right, level + 1, space + horizontalDistance);

        for (int i = 0; i < space; i++) {
            std::cout << " ";
        }
        std::cout << node->data << std::endl;

        displayTreeHorizontallyHelper(node->left, level + 1, space + horizontalDistance);
    }

    void displayInOrderTraversalHelper(TreeNode* node) const {
        if (node != nullptr) {
            displayInOrderTraversalHelper(node->left);
            std::cout << node->data << "_";
            displayInOrderTraversalHelper(node->right);
        }
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    BinaryTree myTree;

    char userInput;
    std::cout << "Do you want to generate a random tree or manually input a tree? (r/m): ";
    std::cin >> userInput;

    if (userInput == 'r' || userInput == 'R') {
        myTree.generateRandomTree(4);  // Adjust the maxHeight as needed
    } else if (userInput == 'm' || userInput == 'M') {
        myTree.manualInputTree();
    } else {
        std::cout << "Invalid input. Exiting program.\n";
        return 1;
    }

    std::cout << "Generated Tree:" << std::endl;
    myTree.displayTree();

    int result = myTree.countNodesWithLessThanTwoChildren();
    std::cout << "\nNumber of nodes with less than two children: " << result << std::endl;

    myTree.displayInOrderTraversal();

    return 0;
}
