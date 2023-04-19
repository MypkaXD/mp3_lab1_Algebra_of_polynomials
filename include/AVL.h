#pragma once
#include "Table.h"
#define SPACE 10

template <class TKey, class TValue>
class AVL : public Table<TKey, TValue> {
	struct Value {
		TKey m_key = TKey(); // ключ
		TValue m_elem = TValue();  // элемент-значение
	};

	struct Node {
		Node* m_left = nullptr; // указатель на левый элемент
		Node* m_right = nullptr; // указатель на правый элемент
		Value m_data;

		Node(TKey key, TValue elem) { // конструктор, принимающий ключ и значение
			m_data.m_key = key;
			m_data.m_elem = elem;
		}
	};

	Node* m_root = nullptr; // корень дерева
	int (*comp)(TKey, TKey);

	Node* findNode(TKey key, Node* n) const {
		if (isSubTreeEmpty(n))
			return nullptr;
		else if (comp(key, n->m_data.m_key) == -1)
			n = findNode(key, n->m_left);
		else if (comp(key, n->m_data.m_key) == 1)
			n = findNode(key, n->m_right);
		return n;
	}

	Node* smallLeftRotation(Node* n) {
		Node* temp = n->m_right;
		n->m_right = n->m_right->m_left;
		temp->m_left = n;
		return temp;
	}

	Node* smallRightRotation(Node* n) {
		Node* temp = n->m_left;
		n->m_left = n->m_left->m_right;
		temp->m_right = n;
		return temp;
	}

	Node* bigLeftRotation(Node* n) {
		n->m_right = smallRightRotation(n->m_right);
		return smallLeftRotation(n);
	}

	Node* bigRightRotation(Node* n) {
		n->m_left = smallLeftRotation(n->m_left);
		return smallRightRotation(n);
	}

	Node* get_max_elem(Node* n) {
		if (isSubTreeEmpty(n))
			throw std::exception("ERROR: can't get max element in empty tree");
		else {
			Node* temp = n;

			while (temp->m_right)
				temp = temp->m_right;
			return temp;
		}
	}

	Node* get_min_elem(Node* n) {
		if (isSubTreeEmpty(n))
			throw std::exception("ERROR: can't get min element in empty tree");
		else {
			Node* temp = n;

			while (temp->m_left)
				temp = temp->m_left;
			return temp;
		}
	}

	Node* rebalance(Node* n) {
		int tempbalanceFactor = balanceFactor(n);

		if (tempbalanceFactor == 0)
			return n;
		else if (abs(tempbalanceFactor) == 1) {
			n->m_left = rebalance(n->m_left);
			n->m_right = rebalance(n->m_right);
		}
		else {
			if (tempbalanceFactor < -1) {
				if (balanceFactor(n->m_left) > 0)
					n->m_left = smallLeftRotation(n->m_left);
				n = smallRightRotation(n);
			}
			else if (tempbalanceFactor > 1) {
				if (balanceFactor(n->m_right) < 0)
					n->m_right = smallRightRotation(n->m_right);
				n = smallLeftRotation(n);
			}
		}

		return n;
	}

	Node* deleteNode(Node* n, TKey key) {
		if (isSubTreeEmpty(n))
			return nullptr;
		else if (comp(key, n->m_data.m_key) == -1)
			n->m_left = deleteNode(n->m_left, key);
		else if (comp(key, n->m_data.m_key) == 1)
			n->m_right = deleteNode(n->m_right, key);
		else {
			if (isSubTreeEmpty(n->m_left)) {
				Node* temp = n->m_right;
				delete n;
				return temp;
			}
			else if (isSubTreeEmpty(n->m_right)) {
				Node* temp = n->m_left;
				delete n;
				return temp;
			}
			else {
				Node* temp = get_min_elem(n->m_right);
				n->m_data = temp->m_data;
				n->m_right = deleteNode(n->m_right, temp->m_data.m_key);
			}
		}
		return rebalance(n);
	}

	void print2D(Node* n, int space) {
		if (isSubTreeEmpty(n))
			return;
		space += SPACE;
		print2D(n->m_right, space);
		std::cout << std::endl;
		for (int count = SPACE; count < space; count++)
			std::cout << " ";
		std::cout << "|KEY: " << n->m_data.m_key << "\n";
		for (int count = SPACE; count < space; count++)
			std::cout << " ";
		std::cout << "|ELEM: " << n->m_data.m_elem << "\n";
		print2D(n->m_left, space);
	}

public:
	AVL(int (*compPtr)(TKey, TKey)) {
		comp = compPtr;
	}

	bool isTreeEmpty() const {
		if (!m_root)
			return true;
		else return false;
	}

	bool isSubTreeEmpty(Node* n) const {
		if (!n)
			return true;
		else return false;
	}

	int height(Node* root) {
		if (isSubTreeEmpty(root))
			return -1;
		else {
			int lheight = height(root->m_left);
			int rheight = height(root->m_right);

			if (lheight > rheight)
				return (lheight + 1);
			else return (rheight + 1);
		}
	}

	int balanceFactor(Node* n) {
		if (isSubTreeEmpty(n))
			return 0;
		else return (height(n->m_right) - height(n->m_left));
	}

	Node* get_max() {
		return get_max_elem(m_root);
	}

	Node* get_min() {
		return get_min_elem(m_root);
	}

	void push(TKey key, TValue elem) {
		if (isTreeEmpty())
			m_root = new Node(key, elem);
		else {
			Node* temp = m_root;

			while (temp) {
				if (comp(temp->m_data.m_key, key) == 1) {
					if (isSubTreeEmpty(temp->m_left)){
						temp->m_left = new Node(key, elem);
						break;
					}
					else
						temp = temp->m_left;
				}
				else if (comp(temp->m_data.m_key, key) == -1) {
					if (isSubTreeEmpty(temp->m_right)) {
						temp->m_right = new Node(key, elem);
						break;
					}
					else
						temp = temp->m_right;
				}
				else if (comp(temp->m_data.m_key, key) == 0) {
					temp->m_data.m_elem = elem;
					break;
				}
			}
		}

		m_root = rebalance(m_root);
	}

	void erase(TKey key) {
		deleteNode(m_root, key);
	}

	TValue find(TKey key) const {
		if (isTreeEmpty())
			return TValue();
		Node* temp = findNode(key, m_root);
		if (temp == nullptr)
			return TValue();
		else
			return temp->m_data.m_elem;
	}

	void print() {
		print2D(m_root, SPACE);
	}

};