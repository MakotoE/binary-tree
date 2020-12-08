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
		++_size;
		if (_root == nullptr) {
			_root = std::make_unique<Node>(std::move(item), nullptr, nullptr);
			return;
		}

		Node* parent = parentNode(_root.get(), item);
		if (item < parent->item) {
			if (parent->left) {
				parent->left = std::make_unique<Node>(
					std::move(item),
					std::move(parent->left),
					nullptr
				);
			} else {
				parent->left = std::make_unique<Node>(
					std::move(item),
					nullptr,
					nullptr
				);
			}
		} else {
			if (parent->right) {
				parent->right = std::make_unique<Node>(
					std::move(item),
					nullptr,
					std::move(parent->right)
				);
			} else {
				parent->right = std::make_unique<Node>(
					std::move(item),
					nullptr,
					nullptr
				);
			}
		}
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

	static Node* parentNode(Node* root, const T& item) {
		Node* curr = root;
		Node* parent;
		while (curr) {
			parent = curr;
			if (item == curr->item) {
				return {parent};
			} else if (item < curr->item) {
				curr = curr->left.get();
			} else {
				curr = curr->right.get();
			}
		}
		return {parent};
	}
};

#endif //BINARY_TREE__TREE_H_
