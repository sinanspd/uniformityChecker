#ifndef NFA_H
#define NFA_H

#include <string>
#include <set>
#include <map>
#include <list>
class NFA
{
	// Initial state
	int initial_state;

	// Set of current states
	std::set<int> current_states;

	// Set of next states
	std::set<int> next_states;

	// Map of final states, where each final state is optionally associated
	// with a token.
	std::map<int, int> final_states;

	// State transitions, associating a pair {current_state, symbol} to
	// a list of next states.
	std::map<std::pair<int, char>, std::list<int> > transitions;

	// Given a current state and a symbol, add all target states into field
	// 'next_states' affected by the associated transition.
	void addNextStates(int current_state, char symbol);

public:
	/// If true, dump debug info.
	bool debug = false;

	/// Class constructor.
	NFA(int initial_state = 0) : initial_state(initial_state)
	{
	}

	/// Set the given state as a final state, and optionally associate it
	/// with a token.
	void setFinalState(int state, int token = 0);

	// Add a state transition
	void addTransition(int from_state, char symbol, int to_state);

	/// Start parsing
	void start();

	/// Return true if any of the current states is a final state.
	bool inFinalState();
	
	/// If any of the current states is a final state, return the token with
	/// the lowest identifier greater than 0 associated with a current
	/// final state. If none of the current states is final, return 0.
	int getToken();
	
	/// Return true if the set of current states is empty, and the NFA
	/// cannot make any further progress regardless of the input.
	bool isFinished();

	/// Advance the current states of the NFA while parsing a symbol.
	void parseSymbol(char symbol);

	/// Return true if the NFA accepts the given string
	bool accepts(const std::string &s);
};
#endif
