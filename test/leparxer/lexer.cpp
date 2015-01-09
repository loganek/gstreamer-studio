/*
 * lexer.cpp
 *
 *  Created on: Jan 9, 2015
 *      Author: loganek
 */

#include "leparxer/lexer.h"
#include <gtest/gtest.h>

using namespace GstreamerStudio::LeParXer;

TEST(Lexer, CheckReadingToken)
{
  Lexer lexer;
  lexer.set_buffer("marcin.kolny");

  ASSERT_EQ(Token::IDENTIFIER, lexer.get_next_token());
  ASSERT_EQ("marcin", lexer.get_identifier());
  ASSERT_EQ(Token::OPERATOR, lexer.get_next_token());
  ASSERT_EQ('.', lexer.get_operator());
  ASSERT_EQ(Token::IDENTIFIER, lexer.get_next_token());
  ASSERT_EQ("kolny", lexer.get_identifier());
  ASSERT_EQ(Token::EOL, lexer.get_next_token());
}

TEST(Lexer, ReadUntilAStringArgument)
{
  Lexer lexer;
  lexer.set_buffer("marcin(\"string\", argument)");

  ASSERT_EQ(Token::IDENTIFIER, lexer.get_next_token());
  ASSERT_EQ("marcin", lexer.get_identifier());
  ASSERT_EQ(Token::OPERATOR, lexer.get_next_token());
  ASSERT_EQ('(', lexer.get_operator());
  ASSERT_EQ(Token::OPERATOR, lexer.get_next_token());
  ASSERT_EQ('"', lexer.get_operator());
  ASSERT_EQ("string", lexer.read_until('"'));
  ASSERT_EQ(Token::OPERATOR, lexer.get_next_token());
  ASSERT_EQ('"', lexer.get_operator());
  ASSERT_EQ(Token::OPERATOR, lexer.get_next_token());
  ASSERT_EQ(',', lexer.get_operator());
  ASSERT_EQ(Token::IDENTIFIER, lexer.get_next_token());
  ASSERT_EQ("argument", lexer.get_identifier());
  ASSERT_EQ(Token::OPERATOR, lexer.get_next_token());
  ASSERT_EQ(')', lexer.get_operator());
  ASSERT_EQ(Token::EOL, lexer.get_next_token());
}

TEST(Lexer, ShouldThrowExceptionBecauseOfInvalidToken)
{
  Lexer lexer;
  lexer.set_buffer("marcin.argument");

  ASSERT_ANY_THROW(lexer.get_next_token(Token::EOL | Token::OPERATOR));
}
