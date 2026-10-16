#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
};

Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

int height(Node* root) {
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + max(leftHeight, rightHeight);
}

int main() {
    Node *asc = NULL, *desc = NULL, *random = NULL;
    int n, i;

    cout << "Enter number of elements: ";
    cin >> n;

    for (i = 1; i <= n; i++)
        asc = insert(asc, i);

    for (i = n; i >= 1; i--)
        desc = insert(desc, i);

    srand(time(0));

    int arr[100];

    for (i = 0; i < n; i++)
        arr[i] = i + 1;

    // Shuffle elements randomly
    for (i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    for (i = 0; i < n; i++)
        random = insert(random, arr[i]);

    cout << "\nBST Height Analysis\n";
    cout << "Ascending order height: " << height(asc) << endl;
    cout << "Descending order height: " << height(desc) << endl;
    cout << "Random order height: " << height(random) << endl;

    return 0;
}
