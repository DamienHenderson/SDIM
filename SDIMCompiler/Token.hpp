#pragma once

enum class TokenType
{
	
};
class Token
{
public:
	Token();
	virtual ~Token();

	virtual TokenType GetType() const
	{

	}
};

