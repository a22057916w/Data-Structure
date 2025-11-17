#include <stdio.h>
#include <stdlib.h>

// ==== Function Interfaces (Prototypes) ====
typedef struct Node {
    int val;
    struct Node *left, *right;
} Node;

Node* createNode(int val);
Node* insert(Node* root, int val);
Node* serach(Node* root, int val);
Node* delete(Node* root, int val);

void inorder(Node* root);
void preorder(Node* root);
void postorder(Node* root);

// ==== Function Implementations ====
Node* createNode(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

Node* insert(Node* root, int val) {
    if(!root)
        return createNode(val);
    if(val < root->val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
} 

Node* search(Node* root, int val) {
    if(!root || root->val == val)
        return root;
    if(val < root->val)
        return search(root->left, val);
    else
        return search(root->right, val);
}

Node* findMin(Node* root) {
    while(root && root->left)
        root = root->left;
    return root;
}

Node* delete(Node* root, int val) {
    if(!root)
        return NULL;
    if(val < root->val)
        root->left = delete(root->left, val);
    else if(val > root->val)
        root->right = delete(root->right, val);
    else {
        // case 1: no children
        if(!root->left && !root->right) {
            free(root);
            return NULL;
        }
        // case 2: one child
        else if(!root->left) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if(!root->right) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // case 3: two children
        else {
            Node* succ = findMin(root->right);
            root->val = succ->val;
            root->right = delete(root->right, succ->val);
        }
    }
    return root;
}

void inorder(Node* root) {
    if(root) {
        inorder(root->left);
        printf("%d ", root->val);
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if(root) {
        printf("%d ", root->val);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if(root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->val);
    }
}

int main() {
    Node* root = NULL;

    int arr[] = {8, 3, 10, 1, 6, 14};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    // insert nodes
    for (int i = 0; i < arrSize; i++) {
        root = insert(root, arr[i]);
    }

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    // delete node
    printf("Deleting 8...\n");
    root = delete(root, 8);

    printf("Inorder after delete: ");
    inorder(root);
    printf("\n");

    return 0;
}