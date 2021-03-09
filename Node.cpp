#include "Node.h"
#include <iomanip>
#include <Windows.h>
node::node(int num, std::string tsk, std::string ctg, int cnt) {
	task = tsk;
	ID = cnt;
	number = num;
	category = ctg;
	notification = 1;
	completed = 0;
	prev = nullptr;
	next = nullptr;
	timer = { 0 };
}

std::ostream& operator<<(std::ostream& out, node const object) {
	out << "|" << std::setfill(' ') << std::setw(5) << "|" << object.ID << "|" << std::setfill(' ') << std::setw(20) << "|" << object.number << "|" << std::setfill(' ') << std::setw(20) << "|" << object.category << "|" << std::setfill(' ') << std::setw(30) << "|" << object.task << "|" << std::setw(10) << "|" << object.timer.tm_mday << "/" << object.timer.tm_mon + 1 << "/" << object.timer.tm_year + 1900 << "|" << std::setfill(' ') << std::setw(20) << "|" << object.timer.tm_hour << ":" << object.timer.tm_min << "|" << std::setw(10) << "|" <<  std::endl;
	return out;
}

void node::set_timer(int year, int month, int day, int hour, int min)
{
	timer.tm_sec = 0;
	timer.tm_min = min;
	timer.tm_hour = hour;
	timer.tm_mday = day;
	timer.tm_mon = month;
	timer.tm_year = year;
}

void node::check_alarm()
{
	time_t now;
	now = time(0);
	//cout << difftime(now, mktime(&timer)) << " ";
	if (difftime(now, mktime(&timer)) <= 10 && difftime(now, mktime(&timer)) >= -10 && notification != 0 && timer.tm_year > 0)
	{
		notification = 0;
		cout << endl<< "Alert!!	"<< endl;
		//cout<< timer.tm_mday << "/" << timer.tm_mon + 1 << "/" << timer.tm_year + 1900 << "\t \t" << timer.tm_hour << ":" << timer.tm_min << endl;
		//cout<<"Task to complete:		ID:" << ID << ":" << task << endl;
		cout << *(this)<< endl;
	}
}


