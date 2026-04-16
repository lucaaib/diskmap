//https://www.geeksforgeeks.org/cpp/cpp-program-to-implement-avl-tree/

#include<fstream>
#include<algorithm>
using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");

template<typename T> class node {
public :
	T key;
	node *left;
	node *right;
	int height;
	node(T k) {
		// default constructor
		key = k;
		left = NULL;
		right = NULL;
		height = 1;
	}
};

template<typename T> class AVLtree {
private:
	node<T>* root;
	int height(node<T>* x) {
		if (x == NULL)
			return 0;
		return x->height;
	}
	int balanceFactor(node<T>* x) {
		if (x == NULL)
			return 0;
		return height(x->left) - height(x->right);
	}
	node<T>* rotateRight(node<T>* y) {
		// right rotation on a subtree
		// the tree is too heavy on the left

		node<T>* x = y->left;
		node<T>* T2 = x->right; // subtree

		// rotate
		x->right = y;
		y->left = T2;

		//new heights
		y->height = max(height(y->left), height(y->right)) + 1;
		x->height = max(height(x->left), height(x->right)) + 1;

		return x; // new root

	}
	node<T>* rotateLeft(node<T>* x) {
		// left rotation on a subtree
		// the tree is too heavy on the right

		node<T>* y = x->right;
		node<T>* T2 = y->left; // subtree

		// rotate
		y->left = x;
		x->right = T2;

		//new heights
		y->height = max(height(y->left), height(y->right)) + 1;
		x->height = max(height(x->left), height(x->right)) + 1;

		return y; // new root

	}

	node<T>* insert(node<T>* root, T key) {
		// root of the subtree

		if (root == NULL)
			return new node<T>(key);
		if (key < root->key)
			root->left = insert(root->left, key);
		else {
			if (key > root->key)
				root->right = insert(root->right, key);
			else
				return root;
		}

		root->height = max(height(root->left), height(root->right)) + 1;

		int balance = balanceFactor(root);

		// left heavy 
		if (balance > 1) {
			if (balanceFactor(root->left) >= 0) { // LL
				return rotateRight(root);
			}
			else { // LR
				root->left = rotateLeft(root->left);
				return rotateRight(root);
			}
		}

		// right heavy
		if (balance < -1) {
			if (balanceFactor(root->right) <= 0) { // RR
				return rotateLeft(root);
			}
			else { // RL
				root->right = rotateRight(root->right);
				return rotateLeft(root);
			}
		}
		return root;
	}

	node<T>* minValueNode(node<T>* root) {
		node<T>* node = root;
		while (node->left != NULL)
			node = node->left;
		return node;
	}

	node<T>* deleteNode(node<T>* root, T key) {
		if (root == NULL)
			return root;
		if (key < root->key)
			root->left = deleteNode(root->left, key);
		else {
			if (key > root->key)
				root->right = deleteNode(root->right, key);
			else {
				if ((root->left == NULL) || (root->right == NULL)) {
					// no child or one child
					node<T>* temp;
					if (root->left != NULL)
						temp = root->left;
					else
						temp = root->right;
					if (temp == NULL) {
						delete root;
						return NULL;
					}
					node<T>* old;
					old = root;
					root = temp;
					delete old;
				}
				else {
					node<T>* temp = minValueNode(root->right);
					root->key = temp->key;
					root->right = deleteNode(root->right, temp->key);
				}
			}

		}
		if (root == NULL) {
			return root;
		}
		root->height = max(height(root->left), height(root->right)) + 1;
		int balance = balanceFactor(root);
		// left heavy 
		if (balance > 1) {
			if (balanceFactor(root->left) >= 0) { // LL
				return rotateRight(root);
			}
			else { // LR
				root->left = rotateLeft(root->left);
				return rotateRight(root);
			}
		}

		// right heavy
		if (balance < -1) {
			if (balanceFactor(root->right) <= 0) { // RR
				return rotateLeft(root);
			}
			else { // RL
				root->right = rotateRight(root->right);
				return rotateLeft(root);
			}
		}
		return root;
	}

	bool search(node<T>* root, T key) {
		if (root == NULL)
			return false;
		if (root->key == key)
			return true;
		if (key < root->key)
			return search(root->left, key);
		else
			return search(root->right, key);
	}

	void print(node<T>* root) {
		if (root == NULL) {
			fout << 0 << " ";
			return;
		}
		fout << root->key << " ";
		print(root->left);
		print(root->right);
	}

public:

	AVLtree()
		: root(nullptr)
	{
	}

	void insert(T key) {
		root = insert(root, key);
	}
	bool search(T key) {
		return search(root, key);
	}
	void remove(T key) {
		root = deleteNode(root, key);
	}
	void print() {
		print(root);
		fout << '\n';
	}
	
};

int main() {

	AVLtree<int> T;

	T.insert(1);
	T.insert(2);
	T.insert(3);
	T.insert(5);

	fout << T.search(3) << " " << T.search(10) << '\n';

	T.remove(3);

	fout << T.search(3) << '\n';

	//T.print();
	
}