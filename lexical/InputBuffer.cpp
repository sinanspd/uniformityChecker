#include <cassert>
#include <cstdlib>
#include "InputBuffer.h"
InputBuffer::InputBuffer(std::istream &stream)
{
	// Save input stream
	this->stream = &stream;

	// Initialize pointers
	lexeme_begin = 0;
	forward = 0;
}

char InputBuffer::nextChar()
{
	// Load more data
	if (forward >= (int) buffer.length())
	{
		// Attempt to read BufferSize characters
		char data[BufferSize + 1];
		stream->read(data, BufferSize);

		// No more characters left
		int length = stream->gcount();
		if (length == 0)
			return 0;

		// Null-terminate
		data[length] = '\0';

		// Add to buffer
		buffer += data;
	}

	// Get next character and advance pointer
	return buffer[forward++];
}


std::string InputBuffer::getLexeme(int length)
{
	// Check length
	if (length > (int) buffer.length() - lexeme_begin)
	{
		std::cerr << "getLexeme: length exceeds buffer size\n";
		exit(1);
	}

	// Extract lexeme
	std::string lexeme = buffer.substr(lexeme_begin, length);

	std::cout << "lexeme:" << lexeme << '\n';

	// Update pointers
	lexeme_begin += length;
	forward = lexeme_begin;

	// Free BufferSize characters, if possible
	if (lexeme_begin >= BufferSize)
	{
		buffer.erase(0, BufferSize);
		lexeme_begin -= BufferSize;
		forward -= BufferSize;
	}

	// Return the lexeme
	return lexeme;
}

std::pair<int, std::string> InputBuffer::getToken(NFA &nfa)
{
	// Length of the lexeme scanned so far
	int length = 0;

	// Last identified token
	int last_token = 0;

	// Length of last identified token
	int last_token_length = 0;

	// Restart NFA
	nfa.start();
	while (!nfa.isFinished())
	{
		// Get next symbol
		char symbol = nextChar();

		// No more symbols
		if (!symbol)
			break;

		// One more symbol scanned
		length++;

		// Feed to NFA
		nfa.parseSymbol(symbol);

		// Check if NFA found a token
		int token = nfa.getToken();
		if (token)
		{
			last_token = token;
			last_token_length = length;
		}
	}

	// No more symbols in input
	if (!last_token_length && !length)
		return std::pair<int, std::string>(0, "");

	// Unrecognized token
	if (!last_token_length && length)
	{
		std::string lexeme = getLexeme(length);
		return std::pair<int, std::string>(-1, lexeme);
	}

	// Extract lexeme
	std::string lexeme = getLexeme(last_token_length);
	return std::pair<int, std::string>(last_token, lexeme);
}




