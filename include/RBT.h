#pragma once

#define SPACE 10

/*
Определение:
	1) Каждая вершина является либо черной, либо красной и имеет ровно двух потмков
	2) Корень дерева черный
	3) Каждый лист не содержит данные и является черным
	4) У красной вершины оба потомка черные
	5) Любой путь до потомков-листьев от любой вершины содержит одинаковое число черных вершин



*/
#define RED false
#define BLACK true

template <class TKey, class TValue>
class RBT {

	struct Value {
		TKey key = TKey(); // ключ
		TValue elem = TValue();  // элемент-значение
	};

	struct Node {
		Node* leftChild = nullptr; // указатель на левый элемент
		Node* rightChild = nullptr; // указатель на правый элемент
		Node* parent = nullptr; // указатель на родителя
		Value data;
		bool color; // 0 = red, 1 = black
		bool isNIL;
		Node(TKey key, TValue elem) { // конструктор, принимающий ключ и значение
			data.key = key;
			data.elem = elem;
			color = RED; // red
			isNIL = false;
		}
		Node(Node* parent) : parent(parent) { // NIL-узлом будем называть вспомогательный узел, не хранящий данных и не имеющий (лист)
			color = BLACK; // black
			isNIL = true;
		}
	};

	Node* root = nullptr;

	Node* get_max_elem(Node* n) {
		if (isSubTreeEmpty(n))
			throw std::exception("ERROR: can't get max element in empty tree");
		else {
			Node* temp = n;

			while (temp->rightChild && !temp->rightChild->isNIL)
				temp = temp->rightChild;
			return temp;
		}
	}

	Node* get_min_elem(Node* n) {
		if (isSubTreeEmpty(n))
			throw std::exception("ERROR: can't get min element in empty tree");
		else {
			Node* temp = n;

			while (temp->leftChild && !temp->leftChild->isNIL)
				temp = temp->leftChild;
			return temp;
		}
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

	void deleteNode(Node* z, TKey key, bool check) {
		/*
			Алгоритм:
				1) Пусть требуется удалить ключ к
				2) Выполняем поиск ключа к в дереве
				3) Выполнить удаление как для обычного дерева поиска
				4) На пути от удаленной вершины к корню перекрашивать и поднимать врешины,
					если нарушаются свойства красно-черного дерева
		*/
		Node* temp;

		if (check)
			temp = findNode(key, z);
		else temp = z;

		if (temp == nullptr)
			return;
		else {
			if (temp->color == RED && !isSubTreeEmpty(temp->leftChild) && !isSubTreeEmpty(temp->rightChild) && !temp->leftChild->isNIL && !temp->rightChild->isNIL) {
				Node* y = get_max_elem(temp->leftChild);

				Node* tempvalue = temp;					//|
				temp->data.elem = y->data.elem;			//|
				temp->data.key = y->data.key;			//|=> swap
				y->data.elem = tempvalue->data.elem;	//|
				y->data.key = tempvalue->data.key;		//|

				deleteNode(y, key, false);
			}
			else if (temp->color == BLACK && !isSubTreeEmpty(temp->leftChild) && !isSubTreeEmpty(temp->rightChild) && !temp->leftChild->isNIL && !temp->rightChild->isNIL) {
				Node* y = get_min_elem(temp->rightChild);

				Node* tempvalue = temp;					//|
				temp->data.elem = y->data.elem;			//|
				temp->data.key = y->data.key;			//|=> swap
				y->data.elem = tempvalue->data.elem;	//|
				y->data.key = tempvalue->data.key;		//|

				deleteNode(y, key,false);
			}
			else if (temp->color == BLACK && ((temp->leftChild->isNIL && !temp->rightChild->isNIL) || (!temp->leftChild->isNIL && temp->rightChild->isNIL))) {
				if (temp->leftChild->isNIL && !temp->rightChild->isNIL) {
					temp->data.elem = temp->rightChild->data.elem;
					temp->data.key = temp->rightChild->data.key;
				}
				else if (!temp->leftChild->isNIL && temp->rightChild->isNIL) {
					temp->data.elem = temp->leftChild->data.elem;
					temp->data.key = temp->leftChild->data.key;
				}
			}
			else if (temp->color == RED && temp->rightChild->isNIL && temp->leftChild->isNIL) {
				if (temp == temp->parent->leftChild) {
					temp->parent->leftChild = temp->leftChild;
					temp->leftChild->parent = temp->parent;
				}
				else if (temp == temp->parent->rightChild) {
					temp->parent->rightChild = temp->leftChild;
					temp->rightChild->parent = temp->parent;
				}
				delete temp->rightChild;
				delete temp;
			}
			else if (temp->color == BLACK && temp->rightChild->isNIL && temp->leftChild->isNIL) {
				if (temp == temp->parent->leftChild) {
					temp->parent->leftChild = temp->leftChild;
					temp->leftChild->parent = temp->parent;
				}
				else if (temp == temp->parent->rightChild) {
					temp->parent->rightChild = temp->leftChild;
					temp->rightChild->parent = temp->parent;
				}
				balanceDelete(temp->parent);
				delete temp->rightChild;
				delete temp;
			}
		}
	}

	Node* balanceDelete(Node* n) {
		if (n->isNIL)
			return balanceDelete(n->parent);
		if (n->parent == nullptr)
			return n;
		if (S(n)->color == RED) {
			P(n)->color = RED;
			S(n)->color = BLACK;
			if (n == P(n)->leftChild)
				smallLeftRotate(P(n));
			else smallRightRotate(P(n));
		}
		if (S(n)->color == BLACK && S(n)->leftChild->color == BLACK && S(n)->rightChild->color == BLACK && P(n)->color == BLACK) {
			S(n)->color = RED;
			balanceDelete(P(n));
			return n;
		}
		if (S(n)->color == BLACK && S(n)->leftChild->color == BLACK && S(n)->rightChild->color == BLACK && P(n)->color == RED) {
			S(n)->color = RED;
			P(n)->color = BLACK;
			return n;
		}
		if (S(n)->color == BLACK && (P(n)->color == RED || P(n)->color == BLACK)) {
			if (n == P(n)->leftChild) {
				if (S(n)->leftChild->color == RED && S(n)->rightChild->color == BLACK) {
					S(n)->color = RED;
					S(n)->leftChild->color = BLACK;
					smallRightRotate(S(n));
				}
				S(n)->color = P(n)->color;
				P(n)->color = BLACK;
				S(n)->rightChild->color = BLACK;
				smallLeftRotate(P(n));
			}
			else if (n == P(n)->rightChild) {
				if (S(n)->rightChild->color == RED && S(n)->leftChild->color == BLACK) {
					S(n)->color = RED;
					S(n)->rightChild->color = BLACK;
					smallLeftRotate(S(n));
				}
				S(n)->color = P(n)->color;
				P(n)->color = BLACK;
				S(n)->leftChild->color = BLACK;
				smallRightRotate(P(n));
			}
		}
		return n;
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

		Node* temp = n->rightChild; // сохраняем правого ребенка от n

		n->rightChild = temp->leftChild; // правый ребёнок от n = {b}

		if (!isSubTreeEmpty(temp->leftChild))
			temp->leftChild->parent = n; // меняем родителя у {b} на x

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

	Node* findNode(TKey key, Node* n) {
		if (isSubTreeEmpty(n))
			return nullptr;
		else if (key < n->data.key) {
			if (n->leftChild->isNIL)
				return nullptr;
			else n = findNode(key, n->leftChild);
		}
		else if (key > n->data.key) {
			if (n->rightChild->isNIL)
				return nullptr;
			else n = findNode(key, n->rightChild);
		}
		return n;
	}

public:

	RBT() {
	}

	bool isTreeEmpty() {
		if (!root)
			return true;
		else return false;
	}

	bool isSubTreeEmpty(Node* n) {
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
			Алгоритм:
				1) Пусть требуется вставить ключ к
				2) Выполняем поиск ключа к в дереве с запоминанием пути от корня
				3) Вставить новую верншину с ключом к на место найденного листа
				4) Создать вершину, прикрепив к ней два листа
				5) Покрасить вствленную верншину в красный цвет
				6) На пути к корню перекрашивать и поднимать вершины, если нарушаются свойтва красно-черного дерева

			После вставки может быть нарушено:
				1) Корень дерева является черным (при вставке корня)
				2) У красной вершины оба потомка черные (если предок вставленной вершины карсный)
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
				if (temp->data.key > key) {
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
				else if (temp->data.key < key) {
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
				else if (temp->data.key == key) {
					temp->data.elem = elem;
					temp->color = RED; // red
					balanceInsert(temp);
					return;
				}
			}
		}
	}

	void erase(TKey key) {
		if (isTreeEmpty())
			throw std::exception("ERROR: can't erase elem in empty tree");
		deleteNode(root, key,true);
	}

	void recolor(Node* n) {
		n->color = !n->color;
	}

	TValue* find(TKey key) {
		if (isTreeEmpty())
			throw std::exception("ERROR: can't find elem in empty tree");
		Node* temp = findNode(key, root);
		if (temp == nullptr || temp->isNIL)
			return nullptr;
		else
			return &temp->data.elem;
	}

	void print() {
		print2D(root, SPACE);
	}

};


