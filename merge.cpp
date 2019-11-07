#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>

using namespace std;

/*
	Write an immutable function that merges the following inputs into a single list. (Feel free to use the space below or submit a link to your work.)

	Inputs:
			- Original list of strings
			- List of strings to be added
			- List of strings to be removed

	Return:
			- List shall only contain unique values
			- List shall be ordered as follows
					- Most character count to least character count
					- In the event of a tie, reverse alphabetical (? z -> a ?)

	Example:
			- Original = ['one', 'two', 'three']
			- Add List = ['one', 'two', 'five', 'six']
			- Delete List = ['two', 'five']
			
			- Result List = ['three', 'six', 'one']

	Personal Notes:
			- Seems like we must add before we delete
					- 'five' is in Add List and Delete List and does not appear in Result List

			- Immutable function so don't change input data -> return a list instead of modifying original
*/
vector<string> merge(const vector<string> original, const vector<string> toAdd, const vector<string> toDelete)
{
	vector<string> ret;

	// Add original and toAdd to the set and then remove toDelete from the set
	// Will be left with our set of unique elements
	unordered_set<string> s;
	
	for (int i = 0; i < original.size(); i++)
	{
		s.insert(original[i]);
	}

	for (int i = 0; i < toAdd.size(); i++)
	{
		s.insert(toAdd[i]);
	}

	for (int i = 0; i < toDelete.size(); i ++)
	{
		s.erase(toDelete[i]);
	}

	// Add our set of unique elements to a map
	// Key will be character count
	// Value will be a set of strings where each string contains the same character count as the key
	// Both the map and set will be ordered so we can traverse it in reverse to get the highest character counts and reverse lexigraphical order
	map<int, set<string>> m;
	
	for (auto it = s.begin(); it != s.end(); it++)
	{
		m[(*it).size()].insert(*it);
	}

	// For each key in the map (from the back of the map to the front so we get highest to lowest character count)
	// Add the strings in the set to our return list (from the back of the set to the front so we get reverse lexigraphical order for character count ties)
	for (auto it = m.rbegin(); it != m.rend(); it++)
	{
		for (auto it2 = it->second.rbegin(); it2 != it->second.rend(); it2++)
		{
			ret.push_back(*it2);
		}
	}

	return ret;
}

template <typename T>
void printVector(vector<T> arr)
{
	cout << "Contents of vector: ";

	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << ", ";
	}

	cout << endl;
}

/*
	Test the merge fucntion
*/
void testMerge(vector<string> original, vector<string> toAdd, vector<string> toDelete, vector<string> answer)
{
	if (merge(original, toAdd, toDelete) == answer)
	{
		cout << "Test Case Passed" << endl;
	}

	else
	{
		cout << "Test Case Failed" << endl;
	}

	//printVector(merge(original, toAdd, toDelete));
}

int main()
{

	// Test with lists from examples
	testMerge(vector<string>{"one", "two", "three"},	// original
		vector<string>{"one", "two", "five", "six"},	// toAdd
		vector<string>{"two", "five"},					// toDelete
		vector<string>{"three", "six", "one"});			// result

	// Test with some other cases
	// Removing elements not found, whitespace, alphanumerics
	testMerge(vector<string>{},
		vector<string>{},
		vector<string>{},
		vector<string>{});
	
	testMerge(vector<string>{},
		vector<string>{"one"},
		vector<string>{"one", "one", "two", "three", ""},
		vector<string>{});

	testMerge(vector<string>{},
		vector<string>{"one", "one", "one", "two", "two", "one"},
		vector<string>{"three", "four", "five"},
		vector<string>{"two", "one"});

	testMerge(vector<string>{},
		vector<string>{"", " ", "  "},
		vector<string>{},
		vector<string>{"  ", " ", ""});

	testMerge(vector<string>{""},
		vector<string>{" ", "   "},
		vector<string>{" ", "   "},
		vector<string>{""});

	testMerge(vector<string>{"", " ", "  "},
		vector<string>{},
		vector<string>{"", "  "},
		vector<string>{" "});

	testMerge(vector<string>{"1", "2", "3", "11", "22", "33"},
		vector<string>{"4", "5", "44", "55"},
		vector<string>{"11", "22", "4", "5"},
		vector<string>{"55", "44", "33", "3", "2", "1"});

	testMerge(vector<string>{"a1", "b2", "c3"},
		vector<string>{"1a1", "2b2", "3c3"},
		vector<string>{"2b2", "b2"},
		vector<string>{"3c3", "1a1", "c3", "a1"});

	return 0;
}