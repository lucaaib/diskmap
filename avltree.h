#pragma once
#include <iostream>
#include <string>

using namespace std;

class node {
public:
	string key;
	node* left;
	node* right;
	int height;
	string second;
	node(string k) {
		key = k;
		left = NULL;
		right = NULL;
		height = 1;
	}
	node(string k, string info) {
		key = k;
		left = NULL;
		right = NULL;
		height = 1;
		second = info;
	}
};

class AVLtree {
private:

	node* root;
	int height(node* x) {
		if (x == NULL)
			return 0;
		return x->height;
	}
	int balanceFactor(node* x) {
		if (x == NULL)
			return 0;
		return height(x->left) - height(x->right);
	}
	node* rotateRight(node* y) {
		node* x = y->left;
		node* T2 = x->right;
		x->right = y;
		y->left = T2;
		y->height = max(height(y->left), height(y->right)) + 1;
		x->height = max(height(x->left), height(x->right)) + 1;
		return x;
	}
	node* rotateLeft(node* x) {
		node* y = x->right;
		node* T2 = y->left;
		y->left = x;
		x->right = T2;
		y->height = max(height(y->left), height(y->right)) + 1;
		x->height = max(height(x->left), height(x->right)) + 1;
		return y;
	}
	node* insert(node* root, string key, string info) {
		if (root == NULL) {
			return new node(key, info);
		}
		if (key < root->key)
			root->left = insert(root->left, key, info);
		else {
			if (key > root->key)
				root->right = insert(root->right, key, info);
			else
				return root;
		}
		root->height = max(height(root->left), height(root->right)) + 1;
		int balance = balanceFactor(root);
		if (balance > 1) {
			if (balanceFactor(root->left) >= 0)
				return rotateRight(root);
			else {
				root->left = rotateLeft(root->left);
				return rotateRight(root);
			}
		}
		if (balance < -1) {
			if (balanceFactor(root->right) <= 0)
				return rotateLeft(root);
			else {
				root->right = rotateRight(root->right);
				return rotateLeft(root);
			}
		}
		return root;
	}
	node* minValueNode(node* root) {
		node* node = root;
		while (node->left != NULL)
			node = node->left;
		return node;
	}
	node* deleteNode(node* root, string key) {
		if (root == NULL)
			return root;
		if (key < root->key)
			root->left = deleteNode(root->left, key);
		else {
			if (key > root->key)
				root->right = deleteNode(root->right, key);
			else {
				if ((root->left == NULL) || (root->right == NULL)) {
					node* temp;
					if (root->left != NULL)
						temp = root->left;
					else
						temp = root->right;
					if (temp == NULL) {
						delete root;
						return NULL;
					}
					node* old;
					old = root;
					root = temp;
					delete old;
				}
				else {
					node* temp = minValueNode(root->right);
					root->key = temp->key;
					root->right = deleteNode(root->right, temp->key);
				}
			}
		}
		if (root == NULL)
			return root;
		root->height = max(height(root->left), height(root->right)) + 1;
		int balance = balanceFactor(root);
		if (balance > 1) {
			if (balanceFactor(root->left) >= 0)
				return rotateRight(root);
			else {
				root->left = rotateLeft(root->left);
				return rotateRight(root);
			}
		}
		if (balance < -1) {
			if (balanceFactor(root->right) <= 0)
				return rotateLeft(root);
			else {
				root->right = rotateRight(root->right);
				return rotateLeft(root);
			}
		}
		return root;
	}
	string search(node* root, string key) {
		if (root == NULL)
			return "not found";
		if (root->key == key)
			return root->second;
		if (key < root->key)
			return search(root->left, key);
		else
			return search(root->right, key);
	}

public:
	AVLtree() : root(nullptr) {}

	void insert(string key, string info) {
		root = insert(root, key, info);
	}
	string search(string key) {
		return search(root, key);
	}
	void remove(string key) {
		root = deleteNode(root, key);
	}
};