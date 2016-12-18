// implement your main entry point and any supporting code for the hviewer applicaiton here

#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include "dynamic_array_list.h"

int main(int argc, char *argv[])
{

	auto now = std::chrono::system_clock::now();
	auto as_time_t = std::chrono::system_clock::to_time_t(now);
	auto as_tm = std::localtime(&as_time_t);
	//reads in the current time values
	DynamicArrayList<std::string> date,name,loc;
	DynamicArrayList<int> position;
	//creates a date, name, location and position list
	char* fileIn;
	if(argc > 1)
	{
		fileIn = argv[1];
	}
	else
	{
		fileIn = "history.csv";
	}
	//if there is a parameter in the execution of the program, it will open the specified file, but will default to "history.csv"
	std::fstream myfile;
	myfile.open(fileIn, std::ios::in || std::ios::out);
	std::string dateread;
	std::string nameread;
	std::string locread;
	//opens an ifstream and sets string reads for each list
	while (std::getline(myfile, dateread,','))
	{
		std::getline(myfile, nameread, ',');
		std::getline(myfile, locread);
		//reads in each line
		for(double count = 0; count <= date.getLength(); count++)
		{
			if (count == date.getLength())
			{
				date.insert(count, dateread);
				name.insert(count, nameread);
				loc.insert(count, locread);
				break;
			}
			else if (dateread > date.getEntry(count))
			{
				date.insert(count, dateread);
				name.insert(count, nameread);
				loc.insert(count, locread);
				break;
			}
			//sorts items in reverse chronological order
		}
	}
	myfile.close();
	std::string command;
	std::cout << "Search and edit browser history.\nType C - z to halt.\nCommand:" << std::endl;
	while (std::cin >> command)
	{
		//runs cin whenever there isnt another process
		if (command == "s")
		{
			std::string timeElapseds;
			std::cin >> timeElapseds;
			int timeElapsed = stoi(timeElapseds);
			//reads in the time period to show past entries
			if (timeElapsed >= 0 && timeElapsed <= 4) //checks if it's valid
			{
				std::string splitDate;
				if (timeElapsed == 0)//if input is 0, then reads in all entries
				{
					int i = 0;
					for (i = 0; i < date.getLength(); i++)
					{
						std::cout << i + 1 << ". " << name.getEntry(i) << ", " << loc.getEntry(i) << std::endl;
						position.insert(i, i);
					}
					if (i == 0)
						std::cout << "No entries\n";
				}
				else if (timeElapsed == 1)//if input is 1, then reads in all today's entries
				{
					int counter = 0;
					for (int i = 0; i < date.getLength(); i++)
					{
						splitDate = date.getEntry(i);
						std::string todaySval = splitDate.substr(6, 2);
						std::string monthSval = splitDate.substr(4, 2);
						std::string yearSval = splitDate.substr(0, 4);
						int todayIval = stoi(todaySval);
						int monthIval = stoi(monthSval);
						int yearIval = stoi(yearSval);
						//reads in values for year, month, and date
						if (todayIval == as_tm->tm_mday && monthIval == as_tm->tm_mon + 1 && yearIval == 1900 + as_tm->tm_year)
						{
							std::cout << counter + 1 << ". " << name.getEntry(i) << ", " << loc.getEntry(i) << std::endl;
							position.insert(counter, i);
							counter++;
							//if the values in the file are the same as today, then displays them and stores them in the position array
						}
					}
					if (counter == 0)
						std::cout << "No entries\n";
				}
				else if (timeElapsed == 2)//if input is 2, then reads in all yesterday's entries
				{
					int counter = 0;
					for (int i = 0; i < date.getLength(); i++)
					{
						splitDate = date.getEntry(i);
						std::string yesterdaySval = splitDate.substr(6, 2);
						std::string monthSval = splitDate.substr(4, 2);
						std::string yearSval = splitDate.substr(0, 4);
						int yesterdayIval = stoi(yesterdaySval);
						int monthIval = stoi(monthSval);
						int yearIval = stoi(yearSval);
						//gets values for date, month, and year
						if (as_tm->tm_mday - 1 == 0)
						{
							//checks to see in yesterday was in the previous month
							if (monthIval == 0)
							{
								yearIval--;
								monthIval = 12;
								yesterdayIval = 31;
							}
							else if (monthIval == 1 || monthIval == 3 || monthIval == 5 || monthIval == 7 || monthIval == 8 || monthIval == 10)
							{
								monthIval--;
								yesterdayIval = 31;
							}
							else if (monthIval == 4 || monthIval == 6 || monthIval == 9 || monthIval == 11)
							{
								monthIval--;
								yesterdayIval = 30;
							}
							else if (monthIval == 2)
							{
								monthIval--;
								yesterdayIval = 28;
							}
						}
						if (yesterdayIval == as_tm->tm_mday - 1 && monthIval == as_tm->tm_mon + 1 && yearIval == 1900 + as_tm->tm_year)
						{
							std::cout << counter + 1 << ". " << name.getEntry(i) << ", " << loc.getEntry(i) << std::endl;
							position.insert(counter, i + 1);
							counter++;
							//if the values in the file are the same as today, then displays them and stores them in the position array
						}
					}
					if (counter == 0)
						std::cout << "No entries\n";
				}
				else if (timeElapsed == 3)//if input is 3, then reads in all last week's entries
				{
					int counter = 0;
					for (int j = 0; j < date.getLength(); j++)
					{
						splitDate = date.getEntry(j);
						std::string daySval = splitDate.substr(6, 2);
						std::string monthSval = splitDate.substr(4, 2);
						std::string yearSval = splitDate.substr(0, 4);
						int weekIval[7];
						int dayIval = stoi(daySval);
						int monthIval = stoi(monthSval);
						int yearIval = stoi(yearSval);
						//stores values for date, month, and year
						bool janSto = false;
						bool change28 = false;
						bool change30 = false;
						bool change31 = false;
						int dayCounter = 1;
						//initializes some helper variables
						for (int i = 0; i < 7; i++)
						{
							if (as_tm->tm_mday - i == 0)
							{
								//checks to see if any of the past 7 days were in the previous month
								if (as_tm->tm_mon == 0 && change31 == false)
								{
									as_tm->tm_year--;
									as_tm->tm_mon = 12;
									weekIval[i] = 31;
									change31 = true;
									janSto = true;
									//checks if the month is january and if the month has changed or not
								}
								else if ((as_tm->tm_mon == 1 || as_tm->tm_mon == 3 || as_tm->tm_mon == 5 || as_tm->tm_mon == 7 || as_tm->tm_mon == 8 || as_tm->tm_mon == 10) && change31 == false)
								{
									as_tm->tm_mon--;
									weekIval[i] = 31;
									change31 = true;
									//checks if the previous month has 31 days and if the month has changed or not
								}
								else if ((as_tm->tm_mon == 4 || as_tm->tm_mon == 6 || as_tm->tm_mon == 9 || as_tm->tm_mon == 11) && change30 == false)
								{
									as_tm->tm_mon--;
									weekIval[i] = 30;
									change30 = true;
									//checks if the previous month has 30 days and if the month has changed or not
								}
								else if (as_tm->tm_mon == 2 && change28 == false)
								{
									as_tm->tm_mon--;
									weekIval[i] = 28;
									change28 = true;
									//checks if the previous month has 28 days and if the month has changed or not
								}
							}
							else if (change28) // if the previous month was february, continues counting from the 28th
							{
								weekIval[i] = 28 - dayCounter;
								dayCounter++;
							}
							else if (change30)// if the previous month had 30 days, continues counting from the 30th
							{
								weekIval[i] = 30 - dayCounter;
								dayCounter++;
							}
							else if (change31)// if the previous month had 31 days, continues counting from the 31st
							{
								weekIval[i] = 31 - dayCounter;
								dayCounter++;
							}
							else
							{
								weekIval[i] = as_tm->tm_mday - i;
							}
							
							if (dayIval == weekIval[i] && monthIval == as_tm->tm_mon + 1 && yearIval == 1900 + as_tm->tm_year)
							{
								std::cout << counter + 1 << ". " << name.getEntry(j) << ", " << loc.getEntry(j) << std::endl;
								position.insert(counter, j);
								counter++;
								//if the values in the file are the same as the past week, then displays them and stores them in the position array
							}
						}
					}
					if (counter == 0)
						std::cout << "No entries\n";

					now = std::chrono::system_clock::now();
					as_time_t = std::chrono::system_clock::to_time_t(now);
					as_tm = std::localtime(&as_time_t);
					//resets the clock for future use
				}
				else if (timeElapsed == 4)
				{
					int counter = 0;
					for (int i = 0; i < date.getLength(); i++)
					{
						std::string splitDate = date.getEntry(i);
						std::string yearSval = splitDate.substr(0, 4);
						std::string monthSval = splitDate.substr(4, 2);
						int monthIval = stoi(monthSval);
						int yearIval = stoi(yearSval);
						//takes in values for month and year
						if (monthIval == as_tm->tm_mon + 1 && yearIval == 1900 + as_tm->tm_year)
						{
							std::cout << counter + 1 << ". " << name.getEntry(i) << ", " << loc.getEntry(i) << std::endl;
							position.insert(counter, i);
							counter++;
							//if the values in the file are the same as this month, then displays them and stores them in the position array
						}
					}
					if (counter == 0)
					{
						std::cout << "No entries\n";
					}
				}
			}
			else
				std::cout << "Invalid command\n";
		}
		else if (command == "f")
		{
			std::string nameLocation;
			std::cin >> nameLocation;
			int posCount = 0;
			position.clear();
			for (int i = 0; i < date.getLength(); i++)
			{
				int found1 = name.getEntry(i).find(nameLocation,0);
				int found2 = loc.getEntry(i).find(nameLocation,0);
				int found3 = found1 + found2;
				if (found3 != -2) //checks both arrays and adds the result together. If it isn't -2, or -1 + -1, then one of the strings has been found
				{
					position.insert(posCount, i);
					posCount++;
					//adds the array to the position list
				}

			}
			posCount = 0;
			while (posCount < position.getLength())
			{
				std::cout << posCount + 1 << ". " << name.getEntry(position.getEntry(posCount)) << ", " << loc.getEntry(position.getEntry(posCount)) << std::endl;
				posCount++;
				//displays the position list
			}
			if (posCount = 0)
				std::cout << "No Matches";
		}
		else if (command == "r")
		{
			std::string Spos;
			std::cin >> Spos;
			int pos = stoi(Spos);
			//takes in an index to remove
			if (pos == 0)
			{
				while (!position.isEmpty())
				{
					date.remove(position.getEntry(position.getLength()-1));
					name.remove(position.getEntry(position.getLength()-1));
					loc.remove(position.getEntry(position.getLength()-1));
					position.remove(position.getLength()-1);
					//removes all elements from the position list, as well as the corresponding data lists
				}
			}
			else if (pos > position.getLength())
			{
				std::cout << "Invalid Entry" << std::endl;
			}
			else
			{
				date.remove(position.getEntry(pos));
				name.remove(position.getEntry(pos));
				loc.remove(position.getEntry(pos));
				position.remove(pos);
				//this will run if the position is within the index and is nonzero, removing that index
			}
		}
		else if (command == "w")
		{
			myfile.open(fileIn, std::ios::in || std::ios::out);
			for(int i = 0; i < date.getLength(); i++)
			{
				myfile << date.getEntry(i) << "," << name.getEntry(i) << "," << loc.getEntry(i) << std::endl;
			}
			myfile.close();
			//writes the output to a file
		}
		else if (command == "^Z")
		{
			return 0;
		}
		else
		{
			std::cout << "Unknown Command\n";
		}
	}
	return 0;
}