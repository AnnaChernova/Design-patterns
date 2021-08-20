#include <iostream>
#include <list>
#include <memory>

/**
* Функции, реализующие интерфейс.
*/
class LeSujet
{
public:
	std::string Sport;
	std::string Economics;
	std::string Psychiatry;

	LeSujet(std::string s, std::string e, std::string p):
		Sport(s), Economics(e), Psychiatry(p)
	{}
	
};

class IObserver
{
public:
	virtual void update(const LeSujet news) = 0;
	virtual void removeFromObservable(void) = 0;
	virtual ~IObserver() {}
};

class IObservable
{
public:
	virtual void addObserver(IObserver* o) = 0;
	virtual void removeObserver(IObserver* o) = 0;
	virtual void notifyObservers(void) = 0;
	virtual ~IObservable() {}
};

class IDisplayable
{
public:
	virtual void display(void) const = 0;
};

/**
* Функции, реализующие классы.
*/
class LeJournal : public IObservable
{
	LeSujet& leJ_news;
	std::list<IObserver*> observers;

public:
	LeJournal(LeSujet& news) :
		leJ_news(news)
	{}

	void addObserver(IObserver* o) override
	{
		observers.push_back(o);
	}
	void removeObserver(IObserver* o) override
	{
		observers.remove(o);
	}
	void notifyObservers(void) override
	{
		for (auto& obs : observers)
		{
			obs->update(leJ_news);
		}
	}
	void setNews(std::string sport, std::string economics, std::string psychiatry)
	{
		leJ_news.Sport = sport;
		leJ_news.Economics = economics;
		leJ_news.Psychiatry = psychiatry;
		notifyObservers();
	}
	void updateSujet(LeSujet s)
	{
		leJ_news = s;
		notifyObservers();
	}
	virtual ~LeJournal() override 
	{
		//std::cout << "THAT WAS ~LeJournal" << std::endl;
	};
};

class SportPaper : public IObserver, public IDisplayable
{
	std::string sportInfo;
	IObservable& journal;

public:
	SportPaper(IObservable& j):
		journal(j)
	{
		this->journal.addObserver(this);
	}

	void update(LeSujet news) override
	{
		sportInfo = news.Sport;
		display();
	}
	void removeFromObservable(void) override
	{
		this->journal.removeObserver(this);
	}
	void display(void) const override
	{
		std::cout << "SportPaper NEW >> " << sportInfo << std::endl;
	}
	virtual ~SportPaper() override 
	{
		//std::cout << "THAT WAS ~SportPaper" << std::endl;
	}
};

class EconomicsPaper : public IObserver, public IDisplayable
{
	std::string economicsInfo;
	IObservable& journal;

public:
	EconomicsPaper(IObservable& j) :
		journal(j)
	{
		this->journal.addObserver(this);
	}

	void update(LeSujet news) override
	{
		economicsInfo = news.Economics;
		display();
	}
	void removeFromObservable(void) override
	{
		this->journal.removeObserver(this);
	}
	void display(void) const override
	{
		std::cout << "EconomicsPaper NEW >> " << economicsInfo << std::endl;
	}
	virtual ~EconomicsPaper() 
	{
		//std::cout << "THAT WAS ~EconomicsPaper" << std::endl;
	}
};

class PsychiatryPaper : public IObserver, public IDisplayable
{
	std::string psychiatryInfo;
	IObservable& journal;

public:
	PsychiatryPaper(IObservable& j) :
		journal(j)
	{
		this->journal.addObserver(this);
	}

	void update(LeSujet news) override
	{
		psychiatryInfo = news.Psychiatry;
		display();
	}
	void removeFromObservable(void) override
	{
		this->journal.removeObserver(this);
	}
	void display(void) const override
	{
		std::cout << "PsychiatryPaper NEW >> " << psychiatryInfo << std::endl;
	}
	virtual ~PsychiatryPaper() 
	{
		//std::cout << "THAT WAS ~PsychiatryPaper" << std::endl;
	}
};

/**
* Клиентский код.
*/
int main(void)
{
	LeSujet sujet("Sport", "Economy", "Psychiatry");

	LeJournal* FrenchDaily = new LeJournal(sujet);

	SportPaper* sportP = new SportPaper(*FrenchDaily);
	EconomicsPaper* economicsP = new EconomicsPaper(*FrenchDaily);
	PsychiatryPaper* psychiatryP = new PsychiatryPaper(*FrenchDaily);

	sujet.Sport = "Sport1";

	//FrenchDaily->setNews(sujet.Sport, sujet.Economics, sujet.Psychiatry); // example
	FrenchDaily->updateSujet(sujet);

	delete sportP;
	delete economicsP;
	delete psychiatryP;
	delete FrenchDaily;

	return 0;
}