
#include <initializer_list>
template <class T>
class List {
private:
	struct Node {
		T m_elem = T(); // ������� 
		Node* m_next = nullptr; // ��������� �� ��������� �������
		Node(T elem, Node* next) : m_elem(elem), m_next(next) {}
		Node(T elem) : m_elem(elem) {}
		Node() {}
		Node(const Node& other) {
			m_elem = other.m_elem;
			delete m_next;
			m_next = new Node();
			m_next = other.m_next;
		}
	};

	Node* m_first = nullptr;

	size_t node_distance(Node* lnode, Node* rnode) {
		Node* temp = lnode;
		size_t distance = 0;
		while (temp != rnode) {
			distance++;
			temp = temp->m_next;
		}
		return distance;
	}

	Node* before_medium_node(Node* lnode, Node* rnode) {
		Node* temp = lnode;
		for (int i = 0; i < node_distance(lnode, rnode) / 2 - 1; i++)
			temp = temp->m_next;
		return temp;
	}

	void merge(Node* before_start, Node* end) {
		Node* medium = before_medium_node(before_start->m_next, end)->m_next;
		Node* lpart = before_start->m_next, * rpart = medium, * new_list = new Node, * current = new_list;

		while (lpart != medium || rpart != end) {
			if (rpart == end || (lpart != medium && lpart->m_elem <= rpart->m_elem)) { // ��������� � ������� ����������� (<=), ���� ���� � ������� ��������, ���� ���� �� (>=) 
				current->m_next = lpart;
				lpart = lpart->m_next;
			}
			else {
				current->m_next = rpart;
				rpart = rpart->m_next;
			}
			current = current->m_next;
		}

		before_start->m_next = new_list->m_next;
		current->m_next = end;
		delete new_list;
	}


	void mergesort(Node* before_start, Node* end) {
		if (node_distance(before_start->m_next, end) > 2) {
			mergesort(before_start, before_medium_node(before_start->m_next, end)->m_next);
			mergesort(before_medium_node(before_start->m_next, end), end);
		}

		if (node_distance(before_start->m_next, end) > 1) merge(before_start, end);
	}

public:
	class iterator {
	private:
		friend class List;
		Node* m_ptr = nullptr;
	public:
		iterator(Node* ptr) : m_ptr(ptr) {}
		iterator(const iterator& other) : m_ptr(other.m_ptr) {}
		~iterator() {
			m_ptr = nullptr;
		}
		iterator& operator=(const iterator& other) {
			m_ptr = other.m_ptr;
			return *this;
		}

		iterator& operator++() {
			m_ptr = m_ptr->m_next;
			return *this;
		}
		iterator operator++(int) {
			iterator temp = m_ptr;
			m_ptr += 1;
			return temp;
		}
		iterator operator+(size_t n) { // ������� �� �� ++ � �� ������
			iterator temp(*this);
			for (size_t count = 0; count < n; ++count) {
				temp.m_ptr = temp.m_ptr->m_next;
			}
			return temp;
		}
		T& operator*() {
			return m_ptr->m_elem;
		}
		T& next() {
			return m_ptr->m_next->m_elem;
		}
		bool operator!=(iterator& second) {
			return (m_ptr != second.m_ptr);
		}
		bool operator==(const iterator& second) {
			return m_ptr == second.m_ptr;
		}
	};


	List() {}
	List(size_t size, T elem) {
		if (size == 0)
			return;
		m_first = new Node(elem);
		Node* temp = m_first;
		for (size_t count = 1; count < size; count++) {
			temp->m_next = new Node(elem);
			temp = temp->m_next;
		}
	}
	List(const List<T>& other) {
		delete m_first;
		m_first = new Node(other.m_first->m_elem);
		Node* temp = m_first;
		Node* hope = other.m_first;
		hope = hope->m_next;
		iterator count = other.begin();
		for (++count; count != other.end(); ++count) {
			temp->m_next = new Node(hope->m_elem);
			temp = temp->m_next;
			hope = hope->m_next;
		}
	}
	List(const std::initializer_list<T>& list) {
		delete m_first;
		m_first = new Node(*list.begin());
		Node* temp = m_first;
		for (auto it = list.begin() + 1; it < list.end(); ++it) {
			temp->m_next = new Node(*it);
			temp = temp->m_next;
		}
	}
	List(List&& other) noexcept {
		m_first = nullptr;
		std::swap(m_first, other.m_first);
	}
	~List() {
		Node* temp = m_first;
		while (temp) {
			Node* temp2 = temp->m_next;
			delete temp;
			temp = temp2;
		}
	}
	const List& operator=(const List& other) {
		if (this == &other)
			return *this;
		clear();
		m_first = new Node(other.m_first->m_elem);
		Node* temp1 = m_first;
		Node* temp2 = other.m_first->m_next;
		iterator count = other.begin();
		for (++count; count != other.end(); ++count) {
			temp1->m_next = new Node(temp2->m_elem);
			temp1 = temp1->m_next;
			temp2 = temp2->m_next;
		}
		return *this;
	}
	const List& operator=(List&& other) noexcept {
		if (this == &other)
			return *this;
		std::swap(m_first, other.m_first);
		return *this;
	}

	bool operator==(const List& other) const noexcept {
		if (size() != other.size())
			return false;
		else {
			iterator i = other.begin();
			for (iterator count = begin(); count != end(); ++count) {
				if (*i != *count)
					return false;
				++i;
			}
		}
		return true;
	}

	bool operator!=(const List& other) const noexcept {
		return (!(*this == other));
	}

	size_t size() const {
		Node* temp = m_first;
		size_t lenght = 0;
		for (iterator count = begin(); temp != nullptr; ++count) {
			lenght++;
			temp = temp->m_next;
		}
		return lenght;
	}

	void print() {
		Node* temp = m_first;
		for (iterator count = begin(); count != end(); ++count) {
			std::cout << temp->m_elem << "\t";
			temp = temp->m_next;
		}
	}

	void flip() {
		Node* temp = m_first;
		Node* it = m_first;
		Node* temp1 = nullptr;
		while (it) {
			temp = it->m_next;
			it->m_next = temp1;
			temp1 = it;
			it = temp;
		}
		m_first = temp1;
	}

	void merge(const List& other) {
		if (size() + other.size() == 0) return;
		Node* result = new Node(m_first->m_elem);
		Node* temp = result;
		Node* tempHop = m_first->m_next;
		iterator count = begin();
		for (++count; count != end(); ++count) {
			temp->m_next = new Node(tempHop->m_elem);
			temp = temp->m_next;
			tempHop = tempHop->m_next;
		}
		tempHop = other.m_first;
		for (iterator count = other.begin(); count != other.end(); ++count) {
			temp->m_next = new Node(tempHop->m_elem);
			temp = temp->m_next;
			tempHop = tempHop->m_next;
		}
		m_first = result;
	}

	const bool empty() const noexcept {
		//return !size();
		if (m_first == nullptr)
			return true;
		else return false;
	}

	void pop_front() {
		if (m_first == nullptr)
			throw("ERROR: the list is emptry");
		Node* temp = m_first->m_next;
		delete[] m_first;
		m_first = temp;
	}

	void push_front(const T& elem) {
		Node* temp1 = new Node(elem);
		Node* temp2 = m_first;
		m_first = temp1;
		m_first->m_next = temp2;
	}

	void assign(iterator first, iterator last) {
		Node* temp = m_first;
		while (temp) {
			Node* temp2 = temp->m_next;
			delete[] temp;
			temp = temp2;
		}
		m_first = new Node(*first);
		Node* list = m_first;
		for (++first; first != last; ++first) {
			list->m_next = new Node(*first);
			list = list->m_next;
		}
	}

	void clear() {
		if (empty())
			return;

		Node* temp1 = m_first;
		Node* temp2;
		while (temp1->m_next) {
			temp2 = temp1->m_next;
			delete temp1;
			temp1 = temp2;
		}
		m_first = nullptr;
	}

	void sort() {
		Node* before_first = new Node(T(), m_first);
		mergesort(before_first, nullptr);
		m_first = before_first->m_next;
		delete before_first;
	}

	iterator insert_after(iterator prev, T value) {
		Node* temp = new Node(value);
		temp->m_next = prev.m_ptr->m_next;
		prev.m_ptr->m_next = temp;
		return iterator(temp);
	}
	iterator erase_after(iterator prev) {
		Node* temp1 = prev.m_ptr;
		Node* temp2 = temp1->m_next;
		temp1->m_next = temp2->m_next;
		delete[] temp2;
		return iterator(temp1->m_next);
	}

	const iterator cbegin() const {
		return iterator(m_first);
	}

	iterator begin() const {
		return iterator(m_first);
	}
	const iterator cend() const {
		Node* temp = m_first;
		for (size_t count = 0; count < size(); ++count) {
			temp = temp->m_next;
		}
		return iterator(temp);
	}
	iterator end() const {
		return iterator(nullptr);
	}
};