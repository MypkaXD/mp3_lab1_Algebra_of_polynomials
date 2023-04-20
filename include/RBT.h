#pragma once
#include "Table.h"
#define SPACE 10

/*
�����������:
	1) ������ ������� �������� ���� ������, ���� ������� � ����� ����� ���� �������
	2) ������ ������ ������
	3) ������ ���� �� �������� ������ � �������� ������
	4) � ������� ������� ��� ������� ������
	5) ����� ���� �� ��������-������� �� ����� ������� �������� ���������� ����� ������ ������



*/
#define RED false
#define BLACK true

template <class TKey, class TValue>
class RBT : public Table<TKey, TValue> {

	struct Value {
		TKey key = TKey(); // ����
		TValue elem = TValue();  // �������-��������
	};

	struct Node {
		Node* leftChild = nullptr; // ��������� �� ����� �������
		Node* rightChild = nullptr; // ��������� �� ������ �������
		Node* parent = nullptr; // ��������� �� ��������
		Value data;
		bool color; // 0 = red, 1 = black
		bool isNIL;
		Node(TKey key, TValue elem) { // �����������, ����������� ���� � ��������
			data.key = key;
			data.elem = elem;
			color = RED; // red
			isNIL = false;
		}
		Node(Node* parent) : parent(parent) { // NIL-����� ����� �������� ��������������� ����, �� �������� ������ � �� ������� (����)
			color = BLACK; // black
			isNIL = true;
		}
	};

	Node* root = nullptr;
	int (*comp)(TKey, TKey);

	Node* get_min_elem(Node* n) {
		if (isSubTreeEmpty(n))
			throw std::exception("ERROR: can't get min element in empty tree");
		if (n->isNIL == true)
			return n->parent;
		else
			return get_min_elem(n->leftChild);
	}

	Node* get_max_elem(Node* n) {
		if (isSubTreeEmpty(n))
			throw std::exception("ERROR: can't get max element in empty tree");
		if (n->isNIL == true) 
			return n->parent;
		else 
			return get_max_elem(n->rightChild);
	}

	void balanceInsert(Node* n) {
		if (isSubTreeEmpty(n->parent)) { // if n == root -> n->parent == nullptr
			n->color = BLACK; // root has black color
			return;
		}
		if (P(n)->color == BLACK)
			return;
		if (P(n)->color == RED && G(n)->color == BLACK && U(n)->color == RED) {
			P(n)->color = BLACK;
			U(n)->color = BLACK;
			G(n)->color = RED;
			balanceInsert(G(n));
			return;
		}
		if (P(n)->color == RED && G(n)->color == BLACK && U(n)->color == BLACK) {
			if (P(n) == G(n)->leftChild && n == P(n)->leftChild) {
				recolor(P(n));
				recolor(G(n));
				smallRightRotate(G(n));
			}
			else if (P(n) == G(n)->rightChild && n == P(n)->rightChild) {
				recolor(P(n));
				recolor(G(n));
				//std::cout << "AFTER RECOLOR" << std::endl;
				//print();
				//std::cout << "============" << std::endl;
				smallLeftRotate(G(n));
			}
		}
		else if (!isSubTreeEmpty(P(n)) && !isSubTreeEmpty(G(n))) {
			if (P(n) == G(n)->leftChild && n == P(n)->rightChild) {
				recolor(n);
				recolor(P(n));
				smallRightRotate(P(n));
				smallLeftRotate(G(n));
			}
			else if (P(n) == G(n)->rightChild && n == P(n)->leftChild) {
				recolor(n);
				recolor(P(n));
				smallLeftRotate(P(n));
				smallRightRotate(G(n));
			}
		}
	}

	void DeleteNode(TKey key, Node* n) {
		/*
			��������:
				1) ����� ��������� ������� ���� �
				2) ��������� ����� ����� � � ������
				3) ��������� �������� ��� ��� �������� ������ ������
				4) �� ���� �� ��������� ������� � ����� ������������� � ��������� �������,
					���� ���������� �������� ������-������� ������
		*/
		if (isSubTreeEmpty(n) || n->isNIL)
			return;

		Node* node = findNode(key, root);

		if (node == nullptr || node->isNIL)
			return;
		else {
			Node* prev = get_max_elem(node->leftChild);

			Node* left = node->leftChild, * right = node->rightChild;
			Node* x = prev->leftChild;
			bool colortemp = prev->color;

			Node* oldpos = swap(node, prev);

			if (oldpos->color == RED)
				recolor(oldpos);
			else if (oldpos->color == BLACK && colortemp == BLACK)
				balanceDelete(oldpos);

			delete node;
		}
	}

	void balanceDelete(Node* n) {
		if (!n->parent) 
			return;

		Node* s = S(n), * p = P(n);

		if (s->color == RED) {
			p->color = RED;
			s->color = BLACK;
			if (n == p->leftChild)
				smallLeftRotate(p);
			else
				smallRightRotate(p);
				s = S(n); p = P(n);
		}

		if (s->color == BLACK && !isSubTreeEmpty(p) && p->color == BLACK && !isSubTreeEmpty(s->leftChild) && s->leftChild->color == BLACK && !isSubTreeEmpty(s->rightChild) && s->rightChild->color == BLACK) {
			recolor(s);
			balanceDelete(p);
			return;
		}
		else if (s->color == BLACK && !isSubTreeEmpty(p) && p->color == RED && !isSubTreeEmpty(s->leftChild) && s->leftChild->color == BLACK && !isSubTreeEmpty(s->rightChild) && s->rightChild->color == BLACK) {
			recolor(s);
			recolor(p);
			return;
		}
		else if (n == p->leftChild) {
			if (!isSubTreeEmpty(s->leftChild) && s->leftChild->color == RED && !isSubTreeEmpty(s->rightChild) && s->rightChild->color == BLACK) {
				s->color = RED;
				recolor(s->leftChild);
				smallRightRotate(s);
				s = S(n); p = P(n);
			}
			s->color = p->color;
			p->color = BLACK;
			if (!isSubTreeEmpty(s) && !isSubTreeEmpty(s->rightChild))
				s->rightChild->color = BLACK;
			smallLeftRotate(p);
		}
		else if (n == p->rightChild) {
			if (!isSubTreeEmpty(s->rightChild) && s->rightChild->color == RED && !isSubTreeEmpty(s->leftChild) && s->leftChild->color == BLACK) {
				s->color = RED;
				recolor(s->rightChild);
				smallLeftRotate(s);
				s = S(n); p = P(n);
			}

			s->color = p->color;
			p->color = BLACK;
			if (!isSubTreeEmpty(s->leftChild))
				s->leftChild->color = BLACK;

			smallRightRotate(p);
		}
	}

	void smallLeftRotate(Node* n) {
		/*
			 |				 |
			{n}			   {temp}
			/ \				/   \
		   {a}{temp}  =>  {n}   {t}
			 /  \		  / \
			{b}{t}       {a}{b}		
		*/

		Node* temp = n->rightChild; // ��������� ������� ������� �� n

		n->rightChild = temp->leftChild; // ������ ������ �� n = {b}

		if (!isSubTreeEmpty(temp->leftChild))
			temp->leftChild->parent = n; // ������ �������� � {b} �� x

		temp->parent = n->parent;
		if (n->parent) {
			if (n->parent->leftChild == n)
				n->parent->leftChild = temp;
			else n->parent->rightChild = temp;
		}
		else root = temp;

		temp->leftChild = n;
		n->parent = temp;
		//std::cout << "AFTER ROTATION" << std::endl;
		//print();
		//std::cout << "============" << std::endl;
	}

	void smallRightRotate(Node* n) {
		/*
			 |			 	 |
			{n}			   {temp}
			/ \				/   \
		 {temp}{a}  =>    {b}   {n}
		  /  \					/ \
	     {b}{t}				   {t}{a}
		*/

		Node* temp = n->leftChild;

		n->leftChild = temp->rightChild;

		if (!isSubTreeEmpty(temp->rightChild))
			temp->rightChild->parent = n;

		temp->parent = n->parent;
		if (n->parent) {
			if (n->parent->rightChild == n)
				n->parent->rightChild = temp;
			else n->parent->leftChild = temp;
		}
		else root = temp;

		temp->rightChild = n;
		n->parent = temp;
	}

	void print2D(Node* n, int space) {
		if (isSubTreeEmpty(n))
			return;
		space += SPACE;
		print2D(n->rightChild, space);
		std::cout << std::endl;
		for (int count = SPACE; count < space; count++)
			std::cout << " ";
		std::cout << "|KEY: " << n->data.key << "\n";
		for (int count = SPACE; count < space; count++)
			std::cout << " ";
		std::cout << "|ELEM: " << n->data.elem << "\n";
		for (int count = SPACE; count < space; count++)
			std::cout << " ";
		std::cout << "|COLOR: ";
		if (n->color == BLACK)
			std::cout << "BLACK\n";
		else if (n->color == RED)
			std::cout << "RED\n";
		print2D(n->leftChild, space);
	}

	Node* P(Node* n) { // parent
		if (!isSubTreeEmpty(n->parent))
			return n->parent;
		return nullptr;
	}
	Node* G(Node* n) { // grandparent
		if (!isSubTreeEmpty(n) && !isSubTreeEmpty(n->parent) && !isSubTreeEmpty(n->parent->parent))
			return n->parent->parent;
		return nullptr;
	}
	Node* U(Node* n) { // uncle
		if (!isSubTreeEmpty(n) && !isSubTreeEmpty(n->parent) && !isSubTreeEmpty(n->parent->parent))
			if (n->parent == n->parent->parent->leftChild && !isSubTreeEmpty(n->parent->parent->rightChild))
				return n->parent->parent->rightChild;
			else if (n->parent == n->parent->parent->rightChild && !isSubTreeEmpty(n->parent->parent->leftChild))
				return n->parent->parent->leftChild;
		return nullptr;
	}
	Node* S(Node* n) { // sibiling
		if (!isSubTreeEmpty(n) && !isSubTreeEmpty(n->parent)) {
			if (n == n->parent->leftChild)
				return n->parent->rightChild;
			else if (n == n->parent->rightChild)
				return n->parent->leftChild;
		}
		return nullptr;
	}

	Node* findNode(TKey key, Node* n) const {
		if (isSubTreeEmpty(n))
			return nullptr;
		else if (comp(key, n->data.key) == -1) {
			if (n->leftChild->isNIL)
				return nullptr;
			else n = findNode(key, n->leftChild);
		}
		else if (comp(key, n->data.key) == 1) {
			if (n->rightChild->isNIL)
				return nullptr;
			else n = findNode(key, n->rightChild);
		}
		return n;
	}

	Node* swap(Node* n, Node* prev) {

		Node* oldpos, * x = prev->leftChild;
		if (n->parent) {
			if (n->parent->leftChild == n)
				n->parent->leftChild = prev;
			else
				n->parent->rightChild = prev;
		}

		if (n == prev) {
			n->rightChild->parent = n->parent;
			if (n->parent) {
				if (n->parent->leftChild == n)
					n->parent->leftChild = n->rightChild;
				else
					n->parent->rightChild = n->rightChild;
			}
			delete n->leftChild;
			oldpos = n->rightChild;

		}
		else if (n->leftChild != prev) {
			prev->leftChild->parent = prev->parent;
			prev->parent->rightChild = prev->leftChild;
			prev->parent = n->parent;

			oldpos = prev->leftChild;

			prev->leftChild = n->leftChild;
			n->leftChild->parent = prev;
			delete prev->rightChild;
			prev->rightChild = n->rightChild;
			n->rightChild->parent = prev;
		}
		else if (n->leftChild == prev) {
			oldpos = prev->leftChild;
			prev->parent = n->parent;
			delete prev->rightChild;
			prev->rightChild = n->rightChild;
			n->rightChild->parent = prev;
		}

		if (n == root && n == prev)
			root = prev->rightChild;
		else if (n == root)
			root = prev;

		x->color = prev->color;
		prev->color = n->color;
		return oldpos;
	}

public:

	RBT(int (*compPtr)(TKey, TKey)) {
		comp = compPtr;
	}

	bool isTreeEmpty() const {
		if (!root)
			return true;
		else return false;
	}

	bool isSubTreeEmpty(Node* n) const {
		if (!n)
			return true;
		else return false;
	}

	Node* get_max() {
		return get_max_elem(root);
	}

	Node* get_min() {
		return get_min_elem(root);
	}

	void push(TKey key, TValue elem) {
		/*
			��������:
				1) ����� ��������� �������� ���� �
				2) ��������� ����� ����� � � ������ � ������������ ���� �� �����
				3) �������� ����� �������� � ������ � �� ����� ���������� �����
				4) ������� �������, ��������� � ��� ��� �����
				5) ��������� ���������� �������� � ������� ����
				6) �� ���� � ����� ������������� � ��������� �������, ���� ���������� ������� ������-������� ������

			����� ������� ����� ���� ��������:
				1) ������ ������ �������� ������ (��� ������� �����)
				2) � ������� ������� ��� ������� ������ (���� ������ ����������� ������� �������)
		*/

		if (isTreeEmpty()) {
			root = new Node(key, elem);
			root->leftChild = new Node(root);
			root->rightChild = new Node(root);
			balanceInsert(root);
		}
		else {
			Node* temp = root;

			while (temp) {
				if (comp(temp->data.key, key) == 1) {
					if (temp->leftChild->isNIL) {
						temp->leftChild->data.elem = elem;
						temp->leftChild->data.key = key;
						temp->leftChild->parent = temp;
						temp->leftChild->isNIL = false;
						temp->leftChild->color = RED;
						temp->leftChild->leftChild = new Node(temp->leftChild);
						temp->leftChild->rightChild = new Node(temp->leftChild);
						balanceInsert(temp->leftChild);
						return;
					}
					else
						temp = temp->leftChild;
				}
				else if (comp(temp->data.key, key) == -1) {
					if (temp->rightChild->isNIL) {
						temp->rightChild->data.elem = elem;
						temp->rightChild->data.key = key;
						temp->rightChild->parent = temp;
						temp->rightChild->isNIL = false;
						temp->rightChild->color = RED;
						temp->rightChild->leftChild = new Node(temp->rightChild);
						temp->rightChild->rightChild = new Node(temp->rightChild);
						//std::cout << "AFTER INSERT" << std::endl;
						//print();
						//std::cout << "============" << std::endl;
						balanceInsert(temp->rightChild);
						return;
					}
					else
						temp = temp->rightChild;
				}
				else if (comp(temp->data.key, key) == 0) {
					temp->data.elem = elem;
					temp->color = RED; // red
					balanceInsert(temp);
					return;
				}
			}
		}
	}

	void erase(TKey key) {
		DeleteNode(key, root);
	}

	void recolor(Node* n) {
		n->color = !n->color;
	}

	TValue find(TKey key) const {
		if (isTreeEmpty())
			return TValue();
		Node* temp = findNode(key, root);
		if (temp == nullptr || temp->isNIL)
			return TValue();
		else
			return temp->data.elem;
	}

	void print() {
		print2D(root, SPACE);
	}

};


