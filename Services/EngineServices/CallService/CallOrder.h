// Christopher Stackpole, 12/06/2025

#ifndef CALL_ORDER_H
#define CALL_ORDER_H

#include <algorithm>
#include <map>
#include <vector>

// In order to ensure that parts of code run in a specfic order relative to each other (i.e. UI code can't be run until
// the render service has been setup) I am choosing to give systems the ability to specify a run priority, where higher
// priority means the relavent code will execute sooner. To this effect, the CallOrder class is a priority queue
// implementation that allows code to specify its run priority when it is registered with the CallService. By then
// carefully balancing the relative priorities of systems I can ensure that code is executed in the order I want.

template <typename T>
class CallOrder
{
public:
	void Add(T entry, int priority)
	{
		collections[priority].push_back(entry);
	}

	void Remove(T entry)
	{
		// Find entry in collections
		for (auto& [priority, collection] : collections)
		{
			// Remove all instances of entry in collections
			collection.erase(
				std::remove(
					collection.begin(),
					collection.end(),
					entry
				),
				collection.end()
			);
		}
	}

	// Returns a list of all priority levels in collection
	std::vector<int> GetPriorities()
	{
		std::vector<int> priorities;
		for (const auto& pair : collections)
		{
			priorities.push_back(pair.first);
		}
		return priorities;
	}

	// Return all entries on collection of a given priority
	std::vector<T> GetEntriesOfPriority(int priority)
	{
		if (collections.find(priority) == collections.end())
		{
			return std::vector<T>();
		}
		return collections[priority];
	}

private:
	// Use a hashmap to store collections of objects at same priority
	std::map<int, std::vector<T>> collections;
};

#endif