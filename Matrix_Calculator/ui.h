#ifndef _UI_HEADER_
#define _UI_HEADER_

#include <vector>
#include <string>

using namespace std;

class MenuItem
{
public:
	string name;
	virtual void execute() = 0;
	virtual ~MenuItem() = default;
};


class ActionItem : public MenuItem
{
private:
	void (*action)();

public:
	ActionItem(const string& name, void (*action)());
	void execute() override;
};

class SubMenu : public MenuItem
{
private:
	vector<MenuItem*> items;
public:
	SubMenu(const string& name);
	void addItem(MenuItem* item);
	void execute() override;

	~SubMenu();

};


#endif // !UI_HEADER
