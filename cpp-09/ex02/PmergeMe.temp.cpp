#include "PmergeMe.hpp"

extern int comparisons;

void print(iteratordeckdeck deck) {
	#if __cplusplus > 199711L
		const char *colors[] {
			RED,
			GREEN,
			BLUE,
			MAGENTA,
			YELLOW,
			CYAN,
		};
	#else
		const char *colors[6];
		colors[0] = RED;
		colors[1] = GREEN;
		colors[2] = BLUE;
		colors[3] = MAGENTA;
		colors[4] = YELLOW;
		colors[5] = CYAN;
	#endif

	size_t i = 0;
	for (iteratordeckdeck::iterator it = deck.begin(); it != deck.end(); ++it)
	{
		if (i == 6)
			i = 0;

		// *it is an iterator to a std::deque<int>, so dereference it once more to get the deque<int>&
		std::deque<int> &inner = *(*it);
		for (std::deque<int>::iterator it2 = inner.begin(); it2 != inner.end(); ++it2)
			std::cout << colors[i] << *it2 << " ";
		++i;
	}
	std::cout << RESET << std::endl;
}

static int nextJacobsthal(int n_jacobsthal)
{
	return(((pow(2, n_jacobsthal)) - (pow(-1, n_jacobsthal))) / 3);
}

std::deque<int>	dequePmergeMe::splice(std::deque<int> &deck, std::deque<int>::iterator first, std::deque<int>::iterator last) {

	std::deque<int>	newDeck;

	for (; first != last; )
	{
		newDeck.push_back(*first);
		std::deque<int>::iterator temp = first++;
		deck.erase(temp);
	}
	
	return (newDeck);
}

bool dequePmergeMe::comp(const int first, const std::deque<int> second)
{
	comparisons++;
	return(first < second.back());
}


void	dequePmergeMe::init_deck(char *argv[], deckdeck &sequence) {
	std::deque<int>	start;

	for (size_t i = 1; argv[i]; i++)
		start.push_back(atoi(argv[i]));
	
	for (std::deque<int>::iterator it = start.begin(); it != start.end(); it++)
	{
		std::deque<int> temp;

		temp.push_back(*it);
		sequence.push_back(temp);
	}
}

deckdeck	dequePmergeMe::merge(deckdeck deck) {
	deckdeck	newDeck;

	while (!deck.empty()) {
		deckdeck::iterator	second = deck.begin();
		deckdeck::iterator	first = second++;
		std::deque<int>	temp;
		comparisons++;
		if (first->back() < second->back()) {
			temp.insert(temp.end(), first->begin(), first->end());
			temp.insert(temp.end(), second->begin(), second->end());
		}
		else {
			temp.insert(temp.end(), second->begin(), second->end());
			temp.insert(temp.end(), first->begin(), first->end());
		}
		deck.pop_front();
		deck.pop_front();
		newDeck.push_back(temp);
	}
	
	return (newDeck);
}

deckdeck	dequePmergeMe::halve(deckdeck deck) {
	deckdeck	newDeck;

	while (!deck.empty()) {
		std::deque<int>	firstHalf;
		std::deque<int>	secondHalf;

		size_t	halfDeck = 2;
		if (deck.begin()->size() > 1)
		halfDeck = deck.begin()->size() / 2;
		
		for (size_t i = 0; i < halfDeck; i++)
		{
			firstHalf.push_back(deck.begin()->front());
			deck.begin()->pop_front();
		}
		while (!deck.begin()->empty()) {
			secondHalf.push_back(deck.begin()->front());
			deck.begin()->pop_front();
		}
		newDeck.push_back(firstHalf);
		newDeck.push_back(secondHalf);
		deck.pop_front();
	}
	return (newDeck);
}

void	dequePmergeMe::constructMainPend(deckdeck deck, deckdeck &main, deckdeck &pend, 
									iteratordeckdeck &pairs, std::deque<int> rest) {
	size_t i = 0;
	for (deckdeck::iterator it = deck.begin(); it != deck.end(); it++) {
		if (it != deck.begin() && !(std::distance(deck.begin(), it) % 2)) {
			pend.push_back(*it);
		}
		else {
			main.push_back(*it);
			if (i++ > 1)
				pairs.push_back(--main.end());
		}
	}

	if (!rest.empty()) {
		pend.push_back(rest);
		pairs.push_back(main.end());
	}
}

deckdeck::iterator	search_pair(deckdeck &main, deckdeck::iterator pendIt, deckdeck originalPend) {
	deckdeck::iterator pos = std::find(originalPend.begin(), originalPend.end(), *pendIt);
	int newPos = std::distance(originalPend.begin(), pos);
	size_t i = 2;
	for (deckdeck::iterator it = main.begin(); it != main.end(); it++) {
		if (std::find(originalPend.begin(), originalPend.end(), *it) != originalPend.end())
			i++;
	}
	return (main.begin() + newPos + i);
}

deckdeck	remove_values(deckdeck pend, size_t position)
{
	deckdeck newPend;
	deckdeck::iterator it = pend.begin();
	
	if (pend.size() == 1)
		return (newPend);

	for (size_t i = 0; i != position; i++) {
		it++;
	}
	it++;
	for (; it != pend.end(); it++) {
		newPend.push_back(*it);
	}
	return (newPend);
}

deckdeck	dequePmergeMe::insert(deckdeck &main, deckdeck pend) {
	unsigned int jacobsthalPos = 3 - 1;
	unsigned int jacobsthalPrevPos = 1; 
	size_t jacobsthalN = 3;
	iteratordeckdeck	pairs;
	deckdeck			originalPend = pend;

	for (deckdeck::iterator pendIt = pend.begin(); !pend.empty(); pendIt = pend.begin()) {
		if (pend.size() > 1 && jacobsthalPos - jacobsthalPrevPos > pend.size()) {
			std::advance(pendIt, pend.size());
		}
		else if (pend.size() > 1) {
			std::advance(pendIt, jacobsthalPos - jacobsthalPrevPos);
		}
		if (pendIt == pend.end()) {
			pendIt--;
		}
		int pos = std::distance(pend.begin(), pendIt);
		for (int currentPos = pos; currentPos >= 0; currentPos--) {
			main.insert(std::upper_bound(main.begin(), search_pair(main, pendIt, originalPend), pendIt->back(), comp), *pendIt);
			if (pendIt != pend.begin())
				pendIt--;
		}
		pend = remove_values(pend, pos);
		jacobsthalPrevPos = jacobsthalPos;
		jacobsthalPos = nextJacobsthal(++jacobsthalN) - 1;
	}

	return (main);
}

deckdeck	dequePmergeMe::mergeInsert(deckdeck deck) {
	std::deque<int> rest;

	if (deck.size() % 2) {
		rest = deck.back();
		deck.pop_back();
	}

	deck = dequePmergeMe::merge(deck);

	if (deck.size() > 1)
		deck = mergeInsert(deck);

	deck = dequePmergeMe::halve(deck);
	
	if (deck.size() < 2)
		return (deck);	

	deckdeck			main;
	deckdeck			pend;
	iteratordeckdeck	pairs;
	
	dequePmergeMe::constructMainPend(deck, main, pend, pairs, rest);
	dequePmergeMe::insert(main, pend);

	return (main);

}
