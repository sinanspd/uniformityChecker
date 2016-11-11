#include <iostream>
#include "NFA.h"

void NFA::setFinalState(int state, int token)
{
	final_states[state] = token;
}

void NFA::addTransition(int from_state, char symbol, int to_state)
{
	std::pair<int, char> pair(from_state, symbol);
	transitions[pair].push_back(to_state);
}

void NFA::addNextStates(int current_state, char symbol)
{
	// If there is a transition for the given pair current_state-symbol,
	// add all its target states.
	std::pair<int, char> pair(current_state, symbol);
	if (transitions.count(pair))
	{
		for (int next_state: transitions[pair])
		{
			// Ignore if already there, to avoid infinite recursion
			if (next_states.count(next_state))
				continue;

			// Add target state
			next_states.insert(next_state);

			// Add all empty-string transitions from the target
			// state with the given symbol.
			addNextStates(next_state, 0);
		}
	}
}


void NFA::start()
{
	// Add initial state to next states
	next_states.clear();
	next_states.insert(initial_state);

	// Add all empty-string transitions to next states
	addNextStates(initial_state, 0);

	// Advance state
	current_states = next_states;
	next_states.clear();

	// Debug
	if (debug)
	{
		std::cout << "Initial states = { ";
		for (int current_state : current_states)
			std::cout << current_state << " ";
		std::cout << "}\n";
	}
}

bool NFA::inFinalState()
{
	// Check if any current state is final
	for (int current_state : current_states)
		if (final_states.count(current_state))
			return true;

	// No final state in the current states
	return false;
}

int NFA::getToken()
{
	// Assume no token
	int token = 0;

	// Traverse current final states
	for (int current_state : current_states)
	{
		// Ignore if not a final state
		if (!final_states.count(current_state))
			continue;

		// Ignore if no token associated
		if (!final_states[current_state])
			continue;

		// Record token
		if (!token || final_states[current_state] < token)
			token = final_states[current_state];
	}

	// Debug
	if (debug && token)
		std::cout << "Token " << token << " found\n";

	// Return token with min identifier
	return token;
}

bool NFA::isFinished()
{
	return current_states.size() == 0;
}


void NFA::parseSymbol(char symbol)
{
	// Check transitions for current states
	for (int current_state : current_states)
		addNextStates(current_state, symbol);
	
	// Go to next states
	current_states = next_states;
	next_states.clear();

	// Debug
	if (debug)
	{
		std::cout << "\nParsing symbol '" << symbol << "'\n";
		std::cout << "Current states = { ";

		for (int current_state : current_states)
			std::cout << current_state << " ";
		std::cout << "}\n";
	}
}

bool NFA::accepts(const std::string &s)
{
	// Initialize
	start();

	// Parse all symbols
	for (unsigned i = 0; i < s.length(); i++)
		parseSymbol(s[i]);

	// Check if accepted
	return inFinalState();
}
