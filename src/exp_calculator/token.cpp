#pragma once
#include "token.h"

const std::unordered_map<Token::Types, std::string> Token::token_map = {
	{Token::Types::VAR_DEF, "let"},
	{Token::Types::VAR_NAME, "var_name"},

	{Token::Types::ABS_FUNC_DEF, "abs"},
	{Token::Types::SQRT_FUNC_DEF, "sqrt"},
	{Token::Types::SIN_FUNC_DEF, "sin"},
	{Token::Types::COS_FUNC_DEF, "cos"},

	{Token::Types::FUNC_DEF, "func"},
	{Token::Types::FUNC_PRINT_FROM, "from"},
	{Token::Types::FUNC_PRINT_TO, "to"},
	{Token::Types::FUNC_PRINT_STEP, "step"},

};

Token::Types Token::get_type_by_name(std::string name)
{
	for (const auto& pair : token_map) {
		if (pair.second == name) {
			return pair.first;
		}
	}
	return Token::Types::UNKNOWN;
}

std::string Token::get_token_name(Token::Types type) {
	auto it = Token::token_map.find(type);
	if (it != Token::token_map.end()) {
		return it->second;
	}
	else {
		return "Unknown";
	}
}