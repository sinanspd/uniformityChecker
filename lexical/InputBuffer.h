#ifndef INPUT_BUFFER_H
#define INPUT_BUFFER_H
#include <iostream>
#include "NFA.h"
class InputBuffer
{
public:
	// Buffer size and maximum lexeme size
	static const int BufferSize = 128;

private:
	// Input stream
	std::istream *stream;

	// Buffer for input stream
	std::string buffer;

	// Pointers in input buffer
	int lexeme_begin;
	int forward;

public:
	/// Constructor
	InputBuffer(std::istream &stream);

	/// Return the next character in the input buffer, and advance the
	/// internal 'forward' pointer. If there are no more characters to read
	/// from the input, return 0.
	char nextChar();

	/// Extract a lexeme with the given length, starting at the 'lexemeBegin'
	/// pointer. The given length should not exceed the number of characters
	/// discovered so far with calls to nextChar().
	///
	/// The lexical analysis is restarted at the character following the
	/// extracted lexeme. Pointers 'lexemeBegin' and 'forward' are set to
	/// point of this character.
	///
	std::string getLexeme(int length);

	/// Return the next token found in the input as identified by the NFA
	/// passed in the first argument. The token is given as a pair token ID
	/// and the associated text.
	///
	/// If there are no more symbols to read from the input, the returned
	/// token ID is 0. If the next token in the input is unrecognizable,
	/// the returned token ID is -1.
	///
	std::pair<int, std::string> getToken(NFA &nfa);
};
#endif
