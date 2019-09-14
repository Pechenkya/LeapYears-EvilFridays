#include <iostream>
#include <string>
#include <vector>

bool year_is_bissextial(int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0 && year % 400 != 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
};

struct day
{
	int day_number;
	int day_of_week;
	int month_num;
	int date;
	std::string month_name;
	std::string day_name;

	day(int in_day_num, int in_day_of_week, int in_month_num, int in_date)
	{
		day_number = in_day_num;
		day_of_week = in_day_of_week;
		month_num = in_month_num;
		date = in_date;
	}
};

void set_week_day(int & day_of_week, std::string & day_name)
{
	switch (day_of_week)
	{
	case 1:
	{
		day_name = "Monday";
		break;
	}
	case 2:
	{
		day_name = "Tuesday";
		break;
	}
	case 3:
	{
		day_name = "Wednesday";
		break;
	}
	case 4:
	{
		day_name = "Thursday";
		break;
	}
	case 5:
	{
		day_name = "Friday";
		break;
	}
	case 6:
	{
		day_name = "Saturday";
		break;
	}
	case 7:
	{
		day_name = "Sunday";
		break;
	}
	}
};

day get_first_day(int year)
{
	if (year == 1)
		return day(1, 1, 1, 1);
	else if (year == 1583)
		return day(1, 6, 1, 1);
	else if (year_is_bissextial(year))
	{
		int temp_date = get_first_day(year - 1).day_of_week + 1;
		if (temp_date > 7)
			temp_date -= 7;
		return day(1, temp_date, 1, 1);
	}
	else
	{
		int temp_date = get_first_day(year - 1).day_of_week + 1;
		if (year_is_bissextial(year - 1)) temp_date++;
		if (temp_date > 7)
			temp_date -= 7;
		return day(1, temp_date, 1, 1);
	}
};

std::vector<day> find_fridays(day first_day, int year, std::vector<int> mounth)
{
	std::vector <day> fridays_vec;
	int temp_date = first_day.day_of_week;
	int date_counter = 1;
	for (int i{ 0 }; i < mounth.size(); i++)
	{
		for (int j{1}; j <= mounth.at(i);)
		{
			if (temp_date == 5)
			{
				fridays_vec.push_back(day(date_counter, 5, i+1, j));
				set_week_day(fridays_vec.back().day_of_week, fridays_vec.back().day_name);
				j += 7;
				date_counter += 7;
			}
			else
			{
				if (temp_date == 7)
				{
					temp_date = 1;
					j++;
					date_counter++;
				}
				else
				{
					temp_date++;
					j++;
					date_counter++;
				}
			}
		}
		date_counter = 1;
		for (int k{ 0 }; k <= i; k++)
		{
			date_counter += mounth.at(k);
		}
		temp_date = 5 + (date_counter - fridays_vec.back().day_number);
		if (temp_date > 7) temp_date -= 7;
	}
	return fridays_vec;
}

std::string get_programmers_day(int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0 && year % 400 != 0)
		{
			return "Programmers day is in 13's September";
		}
		else
		{
			return "Programmers day is in 12's September";
		}
	}
	else
	{
		return "Programmers day is in 13's September";
	}
};

std::vector<day> get_evil_fridays(int year, std::vector<int> mounth)
{
	day first_day = get_first_day(year);
	set_week_day(first_day.day_of_week, first_day.day_name);
	std::vector<day> fridays = find_fridays(first_day, year, mounth);
	std::vector<int> thirtheen_numbers;

	for (int i{}, j{13}; i < mounth.size(); i++)
	{
		thirtheen_numbers.push_back(j);
		j += mounth.at(i);
	}

	std::vector<day> fridays_thirtheen;

	for (auto t : fridays)
	{
		for (auto n : thirtheen_numbers)
		{
			if (t.day_number == n)
			{
				fridays_thirtheen.push_back(t);
			}
		}
	}

	return fridays_thirtheen;
};

void set_month(day & in_day)
{
	switch (in_day.month_num)
	{
	case 1:
	{
		in_day.month_name = "January";
		break;
	}
	case 2:
	{
		in_day.month_name = "February";
		break;
	}
	case 3:
	{
		in_day.month_name = "March";
		break;
	}
	case 4:
	{
		in_day.month_name = "April";
		break;
	}
	case 5:
	{
		in_day.month_name = "May";
		break;
	}
	case 6:
	{
		in_day.month_name = "June";
		break;
	}
	case 7:
	{
		in_day.month_name = "July";
		break;
	}
	case 8:
	{
		in_day.month_name = "August";
		break;
	}
	case 9:
	{
		in_day.month_name = "September";
		break;
	}
	case 10:
	{
		in_day.month_name = "October";
		break;
	}
	case 11:
	{
		in_day.month_name = "November";
		break;
	}
	case 12:
	{
		in_day.month_name = "December";
		break;
	}
	}
};

void print_evil_fridays(std::vector<day>& fridays) 
{
	std::cout << std::endl << "Evil Fridays in this year:" << std::endl;
	for (auto t : fridays)
		std::cout << t.day_name << " - " << t.date << " " << t.month_name << std::endl;
}

int main()
{
	int year{};
	std::vector <int> mounth;
	std::vector <day> evil_fridays;

	std::cout << "Attention! Program is calculating dates by Grigorian calendar!" << std::endl;
	std::cout << "Enter date(year): ";
	std::cin >> year;

	if (year_is_bissextial(year))
		mounth = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	else
		mounth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


	std::cout << get_programmers_day(year) << std::endl;

	evil_fridays = get_evil_fridays(year, mounth);

	for (auto & t : evil_fridays)
	{
		set_month(t);
	}

	day first_day = get_first_day(year);
	set_week_day(first_day.day_of_week, first_day.day_name);
	set_month(first_day);
	std::cout << "First Day: " << std::endl << first_day.day_name << " - " << first_day.date << " " << first_day.month_name << std::endl;

	print_evil_fridays(evil_fridays);

	system("Pause");

	return 0;
}