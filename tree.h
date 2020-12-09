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
		return nodeEntries(_root);
	}

	void insert(T item) {
		if (_root == nullptr) {
			_root = std::make_unique<Node>(std::move(item), nullptr, nullptr);
		} else {
			_root = nodeInsert(std::move(_root), item);
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

	static std::vector<T> nodeEntries(const std::unique_ptr<Node>& node) {
		if (node == nullptr) {
			return {};
		}

		auto result = nodeEntries(node->left);
		result.push_back(node->item);
		auto rightEntries = nodeEntries(node->right);
		result.insert(
			result.end(),
			std::make_move_iterator(rightEntries.begin()),
			std::make_move_iterator(rightEntries.end())
		);
		return result;
	}

	static std::unique_ptr<Node> nodeInsert(std::unique_ptr<Node> node, T& item) {
		if (item == node->item) {
			return node;
		}

		if (item < node->item) {
			if (node->left == nullptr) {
				node->left = std::make_unique<Node>(
					std::move(item),
					nullptr,
					nullptr
				);
			} else {
				node->left = nodeInsert(std::move(node->left), item);
				if (balance_factor(node) > 1) {
					if (balance_factor(node->left) > 0) { // Left left
						node = right_rotate(std::move(node));
					} else { // Left right
						node->left = left_rotate(std::move(node->left));
						node = right_rotate(std::move(node));
					}
				}
			}
		} else {
			if (node->right == nullptr) {
				node->right = std::make_unique<Node>(
					std::move(item),
					nullptr,
					nullptr
				);
			} else {
				node->right = nodeInsert(std::move(node->right), item);
				if (balance_factor(node) < 1) {
					if (balance_factor(node->right) > 0) { // Right left
						node->right = right_rotate(std::move(node->right));
						node = left_rotate(std::move(node));
					} else { // Right right
						node = left_rotate(std::move(node));
					}
				}
			}
		}

		return node;
	}

	static long long balance_factor(const std::unique_ptr<Node>& node) {
		return nodeHeight(node->left) - nodeHeight(node->right);
	}

	static size_t nodeHeight(const std::unique_ptr<Node>& node) {
		if (node == nullptr) {
			return 0;
		}

		return std::max(nodeHeight(node->left), nodeHeight(node->right)) + 1;
	}

	static std::unique_ptr<Node> right_rotate(std::unique_ptr<Node> node) {
		auto pivot = std::move(node->left);
		node->left = std::move(pivot->right);
		pivot->right = std::move(node);
		return std::move(pivot);
	}

	static std::unique_ptr<Node> left_rotate(std::unique_ptr<Node> node) {
		auto pivot = std::move(node->right);
		node->right = std::move(pivot->left);
		pivot->left = std::move(node);
		return std::move(pivot);
	}
};

#endif //BINARY_TREE__TREE_H_
