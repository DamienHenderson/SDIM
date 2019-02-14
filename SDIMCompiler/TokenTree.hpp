#pragma once

#include "Token.hpp"

#include <vector>
struct TokenTreeNode
{
	Token* data_{ nullptr };

	std::vector<TokenTreeNode*> children_;
};
class TokenTree
{
public:
	TokenTree();
	~TokenTree();

private:
	TokenTreeNode* root_;
};

