#pragma once

#include <iostream>
#include <vector>

class TreeNode {
public:
	char data;
	TreeNode** children;
	bool isTerminal;

	TreeNode(char data) 
	{
		this->data = data;
		children = new TreeNode * [26];
		for (int i = 0; i < 26; i++) 
			children[i] = nullptr;
		isTerminal = false;
	}
};

class Tree {
public:
	int count;

	Tree() 
	{
		this->count = 0;
		root = new TreeNode('\0');
	}
	bool insertWord(TreeNode* root, std::string word);
	void insertWord(std::string word);
	void complete(TreeNode* root, std::string word, std::string output, bool& possible, std::string& key);
	void autoComplete(std::string& key, bool& possible);

private:
	TreeNode* root;
};