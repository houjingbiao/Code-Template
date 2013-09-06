//combine of adater, decorator and factory
//设计模式的一个重要原则是保证应用程序的借口不变，而去改变各个类的内容，比如工厂
#include <stdio.h>
#include <string.h>
#include <set>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

class QuackObserverable;
class Observer{
public:
	virtual void update(QuackObserverable* duck) = NULL;
};

class Quackologist: public Observer{
public:
	void update(QuackObserverable* duck){
		printf("Quackologist: duck just quacked\n");
	}
};

class QuackObserverable{
public:
	virtual void registerObserver(Observer* observer){};
	virtual void notifyObserver(){};
};

class Observable: public QuackObserverable{//decorator of quackable
public:
	Observable(QuackObserverable* d){
		this->duck = d;
	}
	void registerObserver(Observer* observer){
		observers.push_back(observer);
	}

	void notifyObservers(){
		vector<Observer*>::iterator ite = observers.begin();
		while(ite != observers.end()){
			(*ite)->update(duck);
			ite++;
		}
	}

private:
	vector<Observer*> observers;
	QuackObserverable* duck;
};


class Quackable: public QuackObserverable{
public:
	virtual void quack(){};
};

class MallardDuck: public Quackable{
public:
	MallardDuck(){
		observable = new Observable(this);
	}
	void quack(){
		printf("Quack\n");
	}
	void registerObserver(Observer* observer){
		observable->registerObserver(observer);
	}
	void notifyObservers()
	{
		observable->notifyObservers();
	}
private:
	Observable* observable;
};
class RedheadDuck: public Quackable{
public:
	void quack(){
		printf("Quack\n");
	}
};

class DuckCall: public Quackable{
public:
	void quack(){
		printf("Kwak\n");
	}
};

class RubberDuck: public Quackable{
public:
	void quack(){
		printf("Squeak\n");
	}
};

class Goose{
public:
	void honk(){
		printf("honk\n");
	}
};

class GooseAdapter: public Quackable{
public:
	GooseAdapter(Goose& g){
		goose = g;
	}
	void quack(){
		goose.honk();
	}
private:
	Goose goose;
};

class QuackCounter: public Quackable{//decorator
public:
	QuackCounter(Quackable* d){
		duck = d;
		numberOfQuacks++;
	}
	static int getQuacks(){
		return numberOfQuacks;
	}
	void quack(){
		this->duck->quack();
	}
private:
	static int numberOfQuacks;
	Quackable* duck;
};

int QuackCounter::numberOfQuacks = 0;

class AbstractDuckFactory{
public:
	virtual Quackable* createMallardDuck() = 0;
	virtual Quackable* createRedheadDuck() = 0;
	virtual Quackable* createDuckCall() = 0;
	virtual Quackable* createRubberDuck() = 0;
	//also ok
	/*virtual Quackable& createMallardDuck_1() = 0;
	virtual Quackable& createRedheadDuck_1() = 0;
	virtual Quackable& createDuckCall_1() = 0;
	virtual Quackable& createRubberDuck_1() = 0;*/
	//not ok
	/*virtual Quackable createMallardDuck() = 0;
	virtual Quackable createRedheadDuck() = 0;
	virtual Quackable createDuckCall() = 0;
	virtual Quackable createRubberDuck() = 0;*/
};
class DuckFactory: public AbstractDuckFactory{
public:
	Quackable* createMallardDuck(){
		return new MallardDuck();
	}
	Quackable* createRedheadDuck(){
		return new RedheadDuck();
	}
	Quackable* createDuckCall(){
		return new DuckCall();
	}
	Quackable* createRubberDuck(){
		return new RubberDuck();
	}
};

class CountingDuckFactory: public AbstractDuckFactory{
public:
	Quackable* createMallardDuck(){
		return new QuackCounter(new MallardDuck());
	}
	Quackable* createRedheadDuck(){
		return new QuackCounter(new RedheadDuck());
	}
	Quackable* createDuckCall(){
		return new QuackCounter(new DuckCall());
	}
	Quackable* createRubberDuck(){
		return new QuackCounter(new RubberDuck());
	} 
};

class Flock: public Quackable{
public:
	void add(Quackable* quacker){
		quackers.push_back(quacker);
	}
	void quack(){
		vector<Quackable*>::iterator ite = quackers.begin();
		while(ite != quackers.end()){
			(*ite)->quack();
			ite++;
		}
	}
private:
	vector<Quackable*> quackers;
};


class DuckSimulator{
public:
	void simulator(){
		printf("Duck simulator: with gooseadapter\n");
		/*Quackable* mallardDuck = new QuackCounter(new MallardDuck());
		Quackable* redheadDuck= new QuackCounter(new RedheadDuck());
		Quackable* duckCall = new QuackCounter(new DuckCall());
		Quackable* rubberDuck = new QuackCounter(new RubberDuck());
		Quackable* googseDuck = new GooseAdapter(*(new Goose()));*/
		AbstractDuckFactory* duckFactory = new CountingDuckFactory();
		Quackable* mallardDuck = duckFactory->createMallardDuck();
		Quackable* redheadDuck= duckFactory->createRedheadDuck();
		Quackable* duckCall = duckFactory->createDuckCall();
		Quackable* rubberDuck = duckFactory->createRubberDuck();
		Quackable* googseDuck = new GooseAdapter(*(new Goose()));
		simulate(mallardDuck);
		simulate(redheadDuck);
		simulate(duckCall);
		simulate(rubberDuck);
		simulate(googseDuck);

		/*simulate(*mallardDuck);
		simulate(*redheadDuck);
		simulate(*duckCall);
		simulate(*rubberDuck);*/
		Flock* flockOfDucks = new Flock();
		flockOfDucks->add(redheadDuck);
		flockOfDucks->add(duckCall);
		flockOfDucks->add(rubberDuck);
		flockOfDucks->add(googseDuck);
		printf("\nsimulater flockOfDucks\n");
		simulate(flockOfDucks);

		Flock* flockOfMallards = new Flock();
		Quackable* mallardOne = duckFactory->createMallardDuck();
		Quackable* mallardTwo = duckFactory->createMallardDuck();
		Quackable* mallardThree = duckFactory->createMallardDuck();
		Quackable* mallardFour = duckFactory->createMallardDuck();
		flockOfMallards->add(mallardOne);
		flockOfMallards->add(mallardTwo);
		flockOfMallards->add(mallardThree);
		flockOfMallards->add(mallardFour);
		printf("\nsimulater flockOfMallards\n");
		simulate(flockOfMallards);

		printf("\nobserver\n");
		Quackologist* quacklogist = new Quackologist();
		flockOfDucks->registerObserver(quacklogist);
		simulate(flockOfDucks);
		printf("\nThe ducks quacked %d times\n", QuackCounter::getQuacks());
	}
	void simulate(Quackable* duck){
		duck->quack();
	}
	void simulate(Quackable& duck){
		duck.quack();
	}
};

int main(){
	DuckSimulator ds;
	ds.simulator();
	return 0;
}