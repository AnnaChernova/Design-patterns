#include <iostream>
#include <random>
#include <ctime>

class IRoute
{
public:
	virtual void calc(void) const = 0;
	virtual ~IRoute() {};
};

class FootRoute : public IRoute
{
public:
	void calc(void) const
	{
		std::cout << "Foot route is created ... \n";
	}
};

class CarRoute : public IRoute
{
public:
	void calc(void) const
	{
		std::cout << "Car route is created ... \n";
	}
};

class BicycleRoute : public IRoute
{
public:
	void calc(void) const
	{
		std::cout << "Bicycle route is created ... \n";
	}
};

class Navigator
{
	IRoute* nav_route;

public:
	Navigator(IRoute* route = nullptr) : nav_route(route) {}

	void calcRoute(void)
	{
		nav_route->calc();
	};
	void setMethodOfCalc(IRoute* newRoute)
	{
		delete this->nav_route;
		nav_route = newRoute;
	};

	~Navigator()
	{
		delete this->nav_route;
	}
};

int main(void)
{
	std::mt19937 gen(time(0));
	std::uniform_int_distribution<> uid(1, 3);

	int magic_number = uid(gen);
	std::cout << "My number: " << magic_number << std::endl;

	Navigator Kirill;

	switch (magic_number)
	{
	case 1:
		Kirill.setMethodOfCalc(new FootRoute); break;
	case 2:
		Kirill.setMethodOfCalc(new CarRoute); break;
	case 3:
		Kirill.setMethodOfCalc(new BicycleRoute); break;
	}
	
	Kirill.calcRoute();

	return 0;
}