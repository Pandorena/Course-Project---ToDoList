#include "functions.h"
#include "prints.h"
#include "fort.hpp"


void printMenu()
{
	const std::string redTextColor = "\x1B[31m";
	fort::char_table table;
	/* Set table border style */
	table.set_border_style(FT_BASIC_STYLE);

	// Fill table with data                                                  
	table << fort::header
		<< "A" << "Add new users, tasks or projects" << fort::endr
		<< fort::separator
		<< "P" << "Print desired information" << fort::endr
		<< fort::separator
		<< "C" << "Count tasks or projects" << fort::endr
		<< fort::separator
		<< "R" << "Read data in" << fort::endr
		<< fort::separator
		<< "W" << "Write data out" << fort::endr
		<< fort::separator
		<< "D" << "Delete data" << fort::endr
		<< fort::separator
		<< "Q" << "Quit" << fort::endr
		<< fort::endr;

	table.column(0).set_cell_text_align(fort::text_align::center);
	table.column(1).set_cell_text_align(fort::text_align::left);

	std::cout << table.to_string() << std::endl;
}




void printAdding()
{
	fort::char_table table;
	/* Set table border style */
	table.set_border_style(FT_BASIC_STYLE);

	// Fill table with data                                                  
	table << fort::header
		<< "1" << "Add Users" << fort::endr
		<< fort::separator
		<< "2" << "Add Tasks" << fort::endr
		<< fort::separator
		<< "3" << "Add Projects" << fort::endr
		<< fort::separator
		<< "4" << "Return to the menu" << fort::endr
		<< fort::endr;

	table.column(0).set_cell_text_align(fort::text_align::center);
	table.column(1).set_cell_text_align(fort::text_align::left);

	std::cout << table.to_string() << std::endl;
}



void printPrinting()
{
	fort::char_table table;
	/* Set table border style */
	table.set_border_style(FT_BASIC_STYLE);

	// Fill table with data                                                  
	table << fort::header
		<< "1" << "I want to select username and..." << fort::endr
		<< fort::separator
		<< "2" << "I want to sort..." << fort::endr
		<< fort::separator
		<< "3" << "Return to the menu" << fort::endr
		<< fort::endr;

	table.column(0).set_cell_text_align(fort::text_align::center);
	table.column(1).set_cell_text_align(fort::text_align::left);

	std::cout << table.to_string() << std::endl;
}



void printPrintingByUsername()
{
	cout << "Select username and..." << endl;
	fort::char_table table;
	/* Set table border style */
	table.set_border_style(FT_BASIC_STYLE);

	// Fill table with data                                                  
	table << fort::header
		<< "1" << "print all his tasks" << fort::endr
		<< fort::separator
		<< "2" << "print all his projects" << fort::endr
		<< fort::separator
		<< "3" << "print all the tasks that end before or after some date" << fort::endr
		<< fort::separator
		<< "4" << "print projects that end before or after some date" << fort::endr
		<< fort::separator
		<< "5" << "Return to the menu" << fort::endr
		<< fort::endr;

	table.column(0).set_cell_text_align(fort::text_align::center);
	table.column(1).set_cell_text_align(fort::text_align::left);

	std::cout << table.to_string() << std::endl;
}



void printPrintingBySorting()
{
	cout << "Enter username and sort..." << endl;
	fort::char_table table;
	/* Set table border style */
	table.set_border_style(FT_BASIC_STYLE);

	// Fill table with data                                                  
	table << fort::header
		<< "1" << "all his tasks by date" << fort::endr
		<< fort::separator
		<< "2" << "all his tasks by date in reverse order" << fort::endr
		<< fort::separator
		<< "3" << "all his tasks by name" << fort::endr
		<< fort::separator
		<< "4" << "all his tasks by priority" << fort::endr
		<< fort::separator
		<< "5" << "Return to the menu" << fort::endr
		<< fort::endr;

	table.column(0).set_cell_text_align(fort::text_align::center);
	table.column(1).set_cell_text_align(fort::text_align::left);

	std::cout << table.to_string() << std::endl;
}


void printDeleting()
{
	fort::char_table table;
	/* Set table border style */
	table.set_border_style(FT_BASIC_STYLE);

	// Fill table with data                                                  
	table << fort::header
		<< "1" << "Delete user (also deletes tasks and projects related to the user)" << fort::endr
		<< fort::separator
		<< "2" << "Delete task from user" << fort::endr
		<< fort::separator
		<< "3" << "Delete project from user (also deletes tasks related to the project)" << fort::endr
		<< fort::separator
		<< "4" << "Delete tasks by date" << fort::endr
		<< fort::separator
		<< "5" << "Delete projects by date" << fort::endr
		<< fort::separator
		<< "6" << "Return to the menu" << fort::endr
		<< fort::endr;

	table.column(0).set_cell_text_align(fort::text_align::center);
	table.column(1).set_cell_text_align(fort::text_align::left);

	std::cout << table.to_string() << std::endl;
}


void printCounting()
{
	cout << "Enter username and count..." << endl;
	fort::char_table table;
	/* Set table border style */
	table.set_border_style(FT_BASIC_STYLE);

	// Fill table with data                                                  
	table << fort::header
		<< "1" << "all his tasks" << fort::endr
		<< fort::separator
		<< "2" << "all his projects" << fort::endr
		<< fort::separator
		<< "3" << "all his tasks by priority" << fort::endr
		<< fort::separator
		<< "4" << "Return to the menu" << fort::endr
		<< fort::endr;

	table.column(0).set_cell_text_align(fort::text_align::center);
	table.column(1).set_cell_text_align(fort::text_align::left);

	std::cout << table.to_string() << std::endl;
}




void printProjects()
{
	fort::char_table table;
	/* Set table border style */
	table.set_border_style(FT_BASIC_STYLE);
	for (const Project& project : projects)
	{
		table << fort::header
			<< "Name: " << project.project_name << fort::endr
			<< fort::separator
			<< "Due Date: " << std::put_time(&project.due_date, "%Y-%m-%d") << fort::endr
			<< fort::endr;
		table.column(0).set_cell_text_align(fort::text_align::left);
		table.column(1).set_cell_text_align(fort::text_align::left);

		std::cout << table.to_string() << std::endl;
	}
}




void printUsers()
{
	fort::char_table table;
	/* Set table border style */
	table.set_border_style(FT_BASIC_STYLE);
	for (const User& user : users)
	{
		table << fort::header
			<< "Username: " << user.username << fort::endr
			<< fort::separator
			<< "Name: " << user.name << fort::endr
			<< fort::endr;
		table.column(0).set_cell_text_align(fort::text_align::left);
		table.column(1).set_cell_text_align(fort::text_align::left);


	}
	std::cout << table.to_string() << std::endl;

}

void printTask(const Task& task)
{
	fort::char_table table;
	/* Set table border style */
	table.set_border_style(FT_BASIC_STYLE);

	table << fort::header
		<< "Name: " << task.task_name << fort::endr
		<< fort::separator
		<< "ID: " << task.task_id << fort::endr
		<< fort::separator
		<< "Due Date: " << std::put_time(&task.due_date, "%Y-%m-%d") << fort::endr
		<< fort::separator
		<< "Status: " << StatusNames[task.status] << fort::endr
		<< fort::separator
		<< "Priority Level: " << PriorityNames[task.priority_level] << fort::endr
		<< fort::endr;
	table.column(0).set_cell_text_align(fort::text_align::left);
	table.column(1).set_cell_text_align(fort::text_align::left);

	std::cout << table.to_string() << std::endl;
}

void printProject(const Project& project)
{
	fort::char_table table;
	/* Set table border style */
	table.set_border_style(FT_BASIC_STYLE);

	table << fort::header
		<< "Name: " << project.project_name << fort::endr
		<< fort::separator
		<< "ID: " << project.project_id << fort::endr
		<< fort::separator
		<< "Due Date: " << std::put_time(&project.due_date, "%Y-%m-%d") << fort::endr
		<< fort::endr;

	table.column(0).set_cell_text_align(fort::text_align::left);
	table.column(1).set_cell_text_align(fort::text_align::left);

	std::cout << table.to_string() << std::endl;

}

void printTasks()
{
	fort::char_table table;
	/* Set table border style */
	table.set_border_style(FT_BASIC_STYLE);
	for (const Task& task : tasks)
	{
		printTask(task);
	}
}


bool printProjectsForUser(string userName)
{
	int counter{ 0 };
	fort::char_table table;
	/* Set table border style */
	table.set_border_style(FT_BASIC_STYLE);
	int userid = GetUserId(userName);
	if (userid == -1)
	{
		cout << "User not found." << endl;
		return false;
	}
	for (const Project& project : projects)
	{
		if (project.user_id == userid)
		{
			printProject(project);
			counter++;
		}
	}
	if (counter == 0) {
		cout << "User has no projects" << endl;
		return false;
	}
	return true;
}

bool printTasksForUser(string userName, PriorityLevel prio)
{
	int counter{0};
	fort::char_table table;
	/* Set table border style */
	table.set_border_style(FT_BASIC_STYLE);
	int userid = GetUserId(userName);
	if (userid == -1)
	{
		cout << "User not found." << endl;
		return false;
	}
	for (const Task& task : tasks)
	{
		if (task.user_id == userid && (prio == 0 || prio == task.priority_level))
		{
			printTask(task);
			counter++;
		}
	}
	if (counter == 0) {
		cout << "User has no tasks" << endl;
		return false;
	}
	return true;
}

