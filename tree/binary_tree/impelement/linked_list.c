#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

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
void levelorder(Node* root);

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

void levelorder(Node* root) {
    if(root) {
        Queue* q = queue_create();
        queue_push(q, root);

        while(!queue_isEmpty(q)) {
            Node* curr = (Node*)queue_front(q);
            queue_pop(q);

            printf("%d ", curr->val);

            if(curr->left)
                queue_push(q, curr->left);
            if(curr->right)
                queue_push(q, curr->right);
        }

        queue_free(q);
        printf("\n");
    }
}

int main() {
    Node* root = NULL;

    int arr[] = {8, 3, 10, 1, 6, 14};
    int n = sizeof(arr) / sizeof(arr[0]);

    // 插入
    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    printf("=== Testing BST ===\n");

    // 搜尋
    printf("Search 6: %s\n", search(root, 6) ? "FOUND" : "NOT FOUND");
    printf("Search 99: %s\n", search(root, 99) ? "FOUND" : "NOT FOUND");

    // Traversals
    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    printf("Level Order: ");
    levelorder(root);

    // Delete
    printf("Deleting 8...\n");
    root = delete(root, 8);

    printf("Inorder after delete: ");
    inorder(root);
    printf("\n");

    printf("Level Order after delete: ");
    levelorder(root);

    printf("=== All tests completed ===\n");

    return 0;
}