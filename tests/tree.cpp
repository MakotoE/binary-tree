#include "../tree.h"
#include <gtest/gtest.h>

TEST(Tree, insert) {
	struct Test {
		std::vector<int> items;
		std::vector<int> expected;
	};

	std::vector<Test> tests {
		{
			{},
			{},
		},
		{
			{0},
			{0},
		},
		{
			{0, 1},
			{0, 1},
		},
		{
			{1, 0},
			{0, 1},
		},
		{
			{0, 1, 2},
			{0, 1, 2},
		},
		{
			{2, 1, 0},
			{0, 1, 2},
		},
		{
			{2, 0, 1},
			{0, 1, 2},
		},
		{
			{0, 0},
			{0, 0},
		},
		{
			{0, 0, 1, 0},
			{0, 0, 0, 1},
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		Tree<int> tree;
		for (auto& item : tests[i].items) {
			tree.insert(item);
		}
		EXPECT_EQ(tree.items(), tests[i].expected) << i;
	}
}

TEST(Tree, contains) {
	{
		Tree<int> tree;
		EXPECT_FALSE(tree.contains(0));
	}
	{
		Tree<int> tree;
		tree.insert(1);
		tree.insert(0);
		tree.insert(2);
		EXPECT_TRUE(tree.contains(0));
		EXPECT_TRUE(tree.contains(1));
		EXPECT_TRUE(tree.contains(2));
		EXPECT_FALSE(tree.contains(3));
	}
}