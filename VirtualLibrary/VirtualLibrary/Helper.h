#pragma once
#include <vector>

class Helper
{
private:
	std::vector<const char*> m_randomUserNames;
	std::vector<const char*> m_randomLibraryNames;
	std::vector<const char*> m_randomEbookNames;
	std::vector<const char*> m_randomMovieNames;

public:
	Helper() {
		// Initialize with sample data
		m_randomUserNames = {
			"Alice", "Bob", "Charlie", "Diana", "Eve",
			"Frank", "Grace", "Henry", "Ivy", "Jack",
			"Kate", "Liam", "Maya", "Noah", "Olivia",
			"Peter", "Quinn", "Rachel", "Sam", "Tara"
		};

		m_randomLibraryNames = {
			"Central Library", "Riverside Library", "Oak Street Library",
			"Downtown Library", "Westside Library", "Campus Library",
			"Sunset Library", "Harbor Library", "Mountain View Library",
			"Parkside Library", "Heritage Library", "Lakeside Library"
		};

		m_randomEbookNames = {
			"Digital Dreams", "Code Masters", "The Last Algorithm",
			"Binary Hearts", "Cyber Shadows", "Virtual Reality",
			"Tech Horizons", "The Data Vault",
			"Quantum Secrets", "Neural Networks", "Silicon Valley",
			"Cloud Atlas", "Cryptic Messages", "Blockchain Chronicles",
			"AI Uprising", "Memory Fragments"
		};

		m_randomMovieNames = {
			"The Matrix", "Inception", "Interstellar", "Blade Runner",
			"The Prestige", "Arrival", "Ex Machina", "Her",
			"Memento", "Tenet", "Looper", "Primer",
			"Moon", "District 9", "Edge of Tomorrow", "Oblivion"
		};
	}

	static Helper& get()
	{
		static Helper instance;
		return instance;
	}

	// Pop methods - get and remove a random element
	const char* popRandomUserName()
	{
		if (m_randomUserNames.empty())
		{
			return nullptr;
		}

		int index = rand() % m_randomUserNames.size();

		const char* name = m_randomUserNames[index];
		m_randomUserNames.erase(m_randomUserNames.begin() + index);
		return name;
	}

	const char* popRandomLibraryName()
	{
		if (m_randomLibraryNames.empty())
		{
			return nullptr;
		}

		int index = rand() % m_randomLibraryNames.size();

		const char* name = m_randomLibraryNames[index];
		m_randomLibraryNames.erase(m_randomLibraryNames.begin() + index);
		return name;
	}

	const char* popRandomEbookName()
	{
		if (m_randomEbookNames.empty()) 
		{
			return nullptr;
		}

		int index = rand() % m_randomEbookNames.size();

		const char* name = m_randomEbookNames[index];
		m_randomEbookNames.erase(m_randomEbookNames.begin() + index);
		return name;
	}

	const char* popRandomMovieName()
	{
		if (m_randomMovieNames.empty())
		{
			return nullptr;
		}

		int index = rand() % m_randomMovieNames.size();

		const char* name = m_randomMovieNames[index];
		m_randomMovieNames.erase(m_randomMovieNames.begin() + index);
		return name;
	}

	// Push methods - add a name back to the pool
	void pushUserName(const char* name) 
	{
		m_randomUserNames.push_back(name);
	}

	void pushLibraryName(const char* name)
	{
		m_randomLibraryNames.push_back(name);
	}

	void pushEbookName(const char* name)
	{
		m_randomEbookNames.push_back(name);
	}

	void pushMovieName(const char* name)
	{
		m_randomMovieNames.push_back(name);
	}

	// Check if pools are empty
	bool hasUserNames() const 
	{
		return !m_randomUserNames.empty(); 
	}

	bool hasLibraryNames() const 
	{ 
		return !m_randomLibraryNames.empty(); 
	}

	bool hasEbookNames() const 
	{ 
		return !m_randomEbookNames.empty();
	}

	bool hasMovieNames() const 
	{ 
		return !m_randomMovieNames.empty();
	}
};