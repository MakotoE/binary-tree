#ifndef BINARY_TREE__TREE_H_
#define BINARY_TREE__TREE_H_

#include <memory>
#include <optional>
#include <vector>

template<class T>
class Tree {
private:
	class Node {
	public:
		Node(T item, std::unique_ptr<Node> left, std::unique_ptr<Node> right)
			: item(std::move(item))
		  	, left(std::move(left))
			, right(std::move(right)) {}

		T item;
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;
	};

public:
	Tree()
		: _root(nullptr)
		, _size(0) {}

	std::vector<T> items() const {
		return nodeEntries(_root.get());
	}

	void insert(T item) {
		if (_root == nullptr) {
			_root = std::make_unique<Node>(std::move(item), nullptr, nullptr);
		} else {
			nodeInsert(_root.get(), item);
		}
		++_size;
	}

	size_t size() const {
		return _size;
	}

	bool contains(const T& item) const {
		Node* curr = _root.get();
		while (curr) {
			if (item == curr->item) {
				return true;
			} else if (item < curr->item) {
				curr = curr->left.get();
			} else {
				curr = curr->right.get();
			}
		}
		return false;
	}

private:
	std::unique_ptr<Node> _root;
	size_t _size;

	static std::vector<T> nodeEntries(const Node* node) {
		if (node == nullptr) {
			return {};
		}

		auto result = nodeEntries(node->left.get());
		result.push_back(node->item);
		auto rightEntries = nodeEntries(node->right.get());
		result.insert(
			result.end(),
			std::make_move_iterator(rightEntries.begin()),
			std::make_move_iterator(rightEntries.end())
		);
		return result;
	}

	static void nodeInsert(Node* node, T& item) {
		if (item == node->item) {
			return;
		}

		if (item < node->item) {
			if (node->left == nullptr) {
				node->left = std::make_unique<Node>(
					std::move(item),
					nullptr,
					nullptr
				);
			} else {
				nodeInsert(node->left.get(), item);
			}
		} else {
			if (node->right == nullptr) {
				node->right = std::make_unique<Node>(
					std::move(item),
					nullptr,
					nullptr
				);
			} else {
				nodeInsert(node->right.get(), item);
			}
		}
	}
};

#endif //BINARY_TREE__TREE_H_
