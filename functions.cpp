#pragma once

#include "functions.h"
#include "prints.h"


using namespace std;

int GetUserId(string username)
{
	for (const auto& user : users)
	{
		if (user.username == username)
		{
			return static_cast<int>(user.user_id);
		}
	}
	return -1;
}

int GetProjectId(string project_name)
{
	for (const auto& project : projects)
	{
		if (project.project_name == project_name)
		{

			return static_cast<int>(project.project_id);
		}
	}
	return -1;
}

void read_txs(const string fname)
{
	ifstream file{ fname, ios::binary };
	if (!file)
	{
		cout << "Wrong name of the file." << endl;
		return;
	}

	int usersCount;
	file.read(reinterpret_cast<char*>(&usersCount), sizeof(int));
	cout << "Users count: " << usersCount << endl;
	for (int i = 0; i < usersCount; ++i)
	{
		User user;
		file.read(reinterpret_cast<char*>(&user.user_id), sizeof(user.user_id));
		std::size_t usernameSize;
		file.read(reinterpret_cast<char*>(&usernameSize), sizeof(usernameSize));
		std::string username(usernameSize, '\0');
		file.read(&username[0], usernameSize);
		user.username = std::move(username);
		std::size_t nameSize;
		file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
		std::string name(nameSize, '\0');
		file.read(&name[0], nameSize);
		user.name = std::move(name);
		users.push_back(user);
	}

	int tasksCount;
	file.read(reinterpret_cast<char*>(&tasksCount), sizeof(int));
	cout << "Tasks count: " << tasksCount << endl;
	for (int i = 0; i < tasksCount; ++i)
	{
		Task task;
		file.read(reinterpret_cast<char*>(&task.user_id), sizeof(task.user_id));
		file.read(reinterpret_cast<char*>(&task.project_id), sizeof(task.project_id));
		file.read(reinterpret_cast<char*>(&task.task_id), sizeof(task.task_id));
		std::size_t taskNameSize;
		file.read(reinterpret_cast<char*>(&taskNameSize), sizeof(taskNameSize));
		std::string taskName(taskNameSize, '\0');
		file.read(&taskName[0], taskNameSize);
		task.task_name = std::move(taskName);
		tm dueDate;
		file.read(reinterpret_cast<char*>(&dueDate), sizeof(dueDate));
		task.due_date = std::move(dueDate);

		file.read(reinterpret_cast<char*>(&task.status), 1);
		file.read(reinterpret_cast<char*>(&task.priority_level), 1);
		tasks.push_back(task);
	}

	int projectsCount;
	file.read(reinterpret_cast<char*>(&projectsCount), sizeof(int));
	cout << "Projects count: " << projectsCount << endl;
	for (int i = 0; i < projectsCount; ++i)
	{
		Project project;
		file.read(reinterpret_cast<char*>(&project.user_id), sizeof(project.user_id));
		file.read(reinterpret_cast<char*>(&project.project_id), sizeof(project.project_id));
		std::size_t projectNameSize;
		file.read(reinterpret_cast<char*>(&projectNameSize), sizeof(projectNameSize));
		std::string projectName(projectNameSize, '\0');
		file.read(&projectName[0], projectNameSize);
		project.project_name = std::move(projectName);
		tm dueDate;
		file.read(reinterpret_cast<char*>(&dueDate), sizeof(dueDate));
		project.due_date = std::move(dueDate);
		projects.push_back(project);
	}
	file.close();
}

void write_txs(const string fname)
{
	ofstream file{ fname, ios::binary };
	if (!file)
		throw BadFileName();

	uint64_t usersCount = users.size();
	file.write(reinterpret_cast<char*>(&usersCount), sizeof(int));
	for (const auto& user : users)
	{
		file.write(reinterpret_cast<const char*>(&user.user_id), sizeof(user.user_id));
		std::size_t usernameSize = user.username.size();
		file.write(reinterpret_cast<const char*>(&usernameSize), sizeof(usernameSize));
		file.write(user.username.c_str(), usernameSize);
		std::size_t nameSize = user.name.size();
		file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
		file.write(user.name.c_str(), nameSize);
	}
	uint64_t tasksCount = tasks.size();
	file.write(reinterpret_cast<char*>(&tasksCount), sizeof(int));
	for (const auto& task : tasks)
	{
		file.write(reinterpret_cast<const char*>(&task.user_id), sizeof(task.user_id));
		file.write(reinterpret_cast<const char*>(&task.project_id), sizeof(task.project_id));
		file.write(reinterpret_cast<const char*>(&task.task_id), sizeof(task.task_id));
		std::size_t taskNameSize = task.task_name.size();
		file.write(reinterpret_cast<const char*>(&taskNameSize), sizeof(taskNameSize));
		file.write(task.task_name.c_str(), taskNameSize);

		file.write(reinterpret_cast<const char*>(&task.due_date), sizeof(task.due_date));

		file.write(reinterpret_cast<const char*>(&task.status), 1);
		file.write(reinterpret_cast<const char*>(&task.priority_level), 1);
	}
	uint64_t projectsCount = projects.size();
	file.write(reinterpret_cast<char*>(&projectsCount), sizeof(int));
	for (const auto& project : projects)
	{
		file.write(reinterpret_cast<const char*>(&project.user_id), sizeof(project.user_id));
		file.write(reinterpret_cast<const char*>(&project.project_id), sizeof(project.project_id));
		std::size_t projectNameSize = project.project_name.size();
		file.write(reinterpret_cast<const char*>(&projectNameSize), sizeof(projectNameSize));
		file.write(project.project_name.c_str(), projectNameSize);
		file.write(reinterpret_cast<const char*>(&project.due_date), sizeof(project.due_date));
	}

	file.close();
}

// Adding users, tasks and projects

bool isValidtask_id(int task_id)
{
	for (const auto& task : tasks)
	{
		if (task.task_id == task_id)
		{
			return true;
		}
	}
	return false;
}

void addUser()
{
	User user;
	user.user_id = users.size() + 1;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (true) {
		cout << "Enter username: ";
		getline(cin, user.username);

		if (user.username.empty()) {
			cout << "Username cannot be empty. Please try again." << endl;
		}
		else if (GetUserId(user.username) != -1) {
			cout << "This username already exists. Choose another one." << endl;
		}
		else {
			break;
		}
	}

	while (true) {
		cout << "Enter name: ";
		getline(cin, user.name);

		if (user.name.empty()) {
			cout << "Name cannot be empty. Please try again." << endl;
		}
		else {
			break;
		}
	}

	users.push_back(user);
	cout << "New user added successfully" << endl;
}

void addTask()
{
	Task task;
	string userName;
	string project_name;

	cout << "Available usernames: " << endl;
	for (const User& user : users)
	{
		cout << user.username << endl;
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (true) {
		cout << "User username: ";
		getline(cin, userName);

		if (userName.empty()) {
			cout << "Username cannot be empty. Please try again." << endl;
		}
		else {
			task.user_id = GetUserId(userName);

			if (task.user_id == -1) {
				cout << "User not found." << endl;
				return;
			}

			break;
		}
	}

	cout << "Available projects for your user: " << endl;
	printProjectsForUser(userName);

	while (true) {
		cout << "Enter project name: ";
		getline(cin, project_name);

		if (project_name.empty()) {
			cout << "Project name cannot be empty. Please try again." << endl;
		}
		else {
			task.project_id = GetProjectId(project_name);

			if (task.project_id == -1) {
				cout << "Project not found." << endl;
				return;
			}

			break;
		}
	}

	task.task_id = tasks.size() + 1;

	while (true) {
		cout << "Enter task name: ";
		getline(cin, task.task_name);

		if (task.task_name.empty()) {
			cout << "Task name cannot be empty. Please try again." << endl;
		}
		else {
			break;
		}
	}

	string userString;
	while (true) {
		cout << "Enter a datetime string (format: YYYY-MM-DD): ";
		getline(cin, userString);
		std::tm tm = {};
		std::istringstream iss(userString);
		iss >> std::get_time(&tm, "%Y-%m-%d");
		if (!iss.fail()) {
			task.due_date = tm;
			break;
		}
		else {
			cout << "Invalid datetime format. Please try again." << endl;
		}
	}
	
	while (true) {
		cout << "Enter status (1 = Preparation, 2 = InProgress, 3 = Done): ";
		string status_string;
		int status{ 0 };
		getline(cin, status_string);
		if (status_string.empty()) {
			cout << "Status cannot be empty. Please try again." << endl;
			continue;
		}
		try { status = stoi(status_string); }
		catch (std::exception)
		{
			cout << "Invalid status. Please try again.";
			continue;
		}
		if (status > 3 || status < 1) {
			cout << "Invalid status. Please try again." << endl;
		}
		else {
			task.status = static_cast<EStatus>(status);
			break;
		}
	}

	while (true) {
		cout << "Enter priority level (1 = Low, 2 = Medium, 3 = High): ";
		int priorityLevel;
		cin >> priorityLevel;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (priorityLevel > 3 || priorityLevel < 1) {
			cout << "Invalid priority level. Please try again." << endl;
		}
		else {
			task.priority_level = static_cast<PriorityLevel>(priorityLevel);
			break;
		}
	}

	tasks.push_back(task);
	cout << "New task added successfully!" << endl;
}


void addProject()
{
	Project newProject;
	string userName;

	cout << "Enter the following details for the new project:" << endl;
	cout << "Available usernames: " << endl;
	for (const User& user : users)
	{
		cout << user.username << endl;
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (true) {
		cout << "User username: ";

		getline(cin, userName);

		if (userName.empty()) {
			cout << "Username cannot be empty. Please try again." << endl;
		}
		else {
			newProject.user_id = GetUserId(userName);

			if (newProject.user_id == -1) {
				cout << "User not found." << endl;
				return;
			}

			break;
		}
	}

	newProject.project_id = projects.size() + 1;

	while (true) {
		cout << "Project name: ";
		getline(cin, newProject.project_name);

		if (newProject.project_name.empty()) {
			cout << "Project name cannot be empty. Please try again." << endl;
		}
		else {
			break;
		}
	}

	string userString;
	while (true) {
		cout << "Enter a datetime string (format: YYYY-MM-DD): ";
		getline(cin, userString);
		std::tm tm = {};
		std::istringstream iss(userString);
		iss >> std::get_time(&tm, "%Y-%m-%d");
		if (!iss.fail()) {
			newProject.due_date = tm;
			break;
		}
		else {
			cout << "Invalid datetime format. Please try again." << endl;
		}
	}

	projects.push_back(newProject);

	cout << "New project added successfully!" << endl;
}



void printTasksSorted(string username, SortBy type)
{
	int userid = GetUserId(username);
	if (userid == -1)
	{
		cout << "User not found." << endl;
		return;
	}

	vector<Task> userTasks;
	for (const Task& task : tasks)
	{
		if (task.user_id == userid)
		{
			userTasks.push_back(task);
		}
	}

	switch (type)
	{
	case SortBy::Date:
		std::sort(userTasks.begin(), userTasks.end(), [](const Task& a, const Task& b)
			{
				tm aTime = a.due_date;
		tm bTime = b.due_date;
		if (aTime.tm_year != bTime.tm_year) {
			return aTime.tm_year < bTime.tm_year;
		}
		if (aTime.tm_mon != bTime.tm_mon) {
			return aTime.tm_mon < bTime.tm_mon;
		}
		if (aTime.tm_mday != bTime.tm_mday) {
			return aTime.tm_mday < bTime.tm_mday;
		}
		return false; });
		break;
	case SortBy::DateReverse:
		std::sort(userTasks.begin(), userTasks.end(), [](const Task& a, const Task& b)
			{
				tm aTime = a.due_date;
		tm bTime = b.due_date;
		if (aTime.tm_year != bTime.tm_year) {
			return aTime.tm_year > bTime.tm_year;
		}
		if (aTime.tm_mon != bTime.tm_mon) {
			return aTime.tm_mon > bTime.tm_mon;
		}
		if (aTime.tm_mday != bTime.tm_mday) {
			return aTime.tm_mday > bTime.tm_mday;
		}
		return false; });
		break;
	case SortBy::Username:
		std::sort(userTasks.begin(), userTasks.end(), [](const Task& a, const Task& b)
			{ return a.user_id < b.user_id; });
		break;
	case SortBy::Priority:
		std::sort(userTasks.begin(), userTasks.end(), [](const Task& a, const Task& b)
			{ return a.priority_level > b.priority_level; });
		break;
	case SortBy::Status:
		std::sort(userTasks.begin(), userTasks.end(), [](const Task& a, const Task& b)
			{ return a.status > b.status; });
		break;
	}




	for (const Task& task : userTasks)
	{
		printTask(task);
	}
}

void deleteUser()
{
	int countertasks{ 0 };
	int counterprojects{ 0 };
	string userName;
	cout << "Enter the username of the user whose tasks you want to delete: ";
	cin >> userName;
	cout << endl;
	int user_id = GetUserId(userName);
	if (user_id == -1)
	{
		cout << "User not found." << endl;
		return;
	}

	for (int i = 0; i < tasks.size(); i++)
	{
		if (tasks[i].user_id == user_id)
		{
			tasks.erase(tasks.begin() + i);
			countertasks++;
			--i;
		}
	}
	for (int i = 0; i < projects.size(); i++)
	{
		if (projects[i].user_id == user_id)
		{
			projects.erase(projects.begin() + i);
			counterprojects++;
			--i;
		}
	}
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].user_id == user_id)
		{
			users.erase(users.begin() + i);

			cout << "User deleted successfully!" << endl;
			cout << "Total projects removed: " << counterprojects << endl;
			cout << "Total tasks removed: " << countertasks << endl;
			return;
		}
	}

	cout << "User not found." << endl;

}

void deleteTask()
{
	string userName;
	cout << "Enter the username of the user whose tasks you want to delete: ";
	cin >> userName;
	int userid = GetUserId(userName);
	if (userid == -1)
	{
		cout << "User not found." << endl;
		return;
	}

	string task_id_string;
	int task_id{ 0 };
	cout << "Enter the task ID of the task you want to delete: ";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, task_id_string);
	if (task_id_string.empty()) {
		cout << "Task ID cannot be empty. Please try again." << endl;
		return;
	}
	try { task_id = stoi(task_id_string); }
	catch (std::exception)
	{
		cout << "Invalid task id. Please try again." << endl;
		return;
	}
	if (!isValidtask_id(task_id))
	{
		cout << "Invalid task ID" << endl;
		return;
	}

	
	for (int i = 0; i < tasks.size(); ++i)
	{
		if (tasks[i].task_id == task_id && tasks[i].user_id == userid)
		{
			tasks.erase(tasks.begin() + i);

			cout << "Task deleted successfully!" << endl;
			return;
		}
	}
	cout << "Task not found." << endl;
}

void deleteProject()
{
	int taskscounter{ 0 };
	string userName;
	cout << "Enter the username of the user whose projects you want to delete: ";
	cin >> userName;
	cout << endl;
	int userid = GetUserId(userName);
	if (userid == -1)
	{
		cout << "User not found." << endl;
		return;
	}
	int project_id;
	cout << "Enter the project ID of the project you want to delete: ";
	cin >> project_id;
	cout << endl;
	for (int i = 0; i < projects.size(); ++i)
	{
		if (projects[i].project_id == project_id && projects[i].user_id == userid)
		{
			deleteAllProjectTasks(projects[i].project_name, taskscounter);
			projects.erase(projects.begin() + i);
			cout << "Project deleted successfully!" << endl;
			return;
		}
	}
	cout << "Project not found." << endl;
}


enum RemoveType : unsigned char
{
	Before = 1,
	After = 2
};




void deleteAllProjectTasks(string projectName, int& counter)
{
	int projectID = GetProjectId(projectName);
	if (projectID == -1)
	{
		cout << "Project not found" << endl;
		return;
	}
	for (int i = 0; i < tasks.size(); ++i)
	{
		if (tasks[i].project_id == projectID)
		{
			tasks.erase(tasks.begin() + i);
			counter++;
			--i;
		}
	}
}

void printTasksByDate(RemoveType type)
{
	int counter{ 0 };

	std::tm tm = {};
	while (true)
	{
		string userString;
		cout << "Enter the date: ";
		cin >> userString;
		cout << endl;
		std::istringstream iss(userString);
		iss >> std::get_time(&tm, "%Y-%m-%d");
		if (!iss.fail())
		{
			break;
		}
	}
	std::time_t userDate = std::mktime(&tm);
	for (int i = 0; i < tasks.size(); ++i)
	{
		std::time_t taskDate = std::mktime(&tasks[i].due_date);
		double aux = std::difftime(userDate, taskDate);
		if (aux > 0 && type == Before)
		{
			printTask(tasks[i]);
			counter++;
		}
		else if (aux < 0 && type == After)
		{
			printTask(tasks[i]);
			counter++;
		}
	}
	if (counter == 0 && type == Before) {
		cout << "You don't have any tasks before date: " << std::put_time(&tm, "%Y-%m-%d") << endl;
	}
	else if (counter == 0 && type == After) {
		cout << "You don't have any tasks after date: " << std::put_time(&tm, "%Y-%m-%d") << endl;
	}
}


void printProjectsByDate(RemoveType type)
{
	int counter{ 0 };
	std::tm tm = {};
	while (true)
	{
		string userString;
		cout << "Enter the date: ";
		cin >> userString;
		cout << endl;
		std::istringstream iss(userString);
		iss >> std::get_time(&tm, "%Y-%m-%d");
		if (!iss.fail())
		{
			break;
		}
	}
	std::time_t userDate = std::mktime(&tm);
	for (int i = 0; i < projects.size(); ++i)
	{
		std::time_t taskDate = std::mktime(&tasks[i].due_date);
		double aux = std::difftime(userDate, taskDate);
		if (aux > 0 && type == Before)
		{
			printProject(projects[i]);
			counter++;
		}
		else if (aux < 0 && type == After)
		{
			printProject(projects[i]);
			counter++;
		}
	}
	if (counter == 0 && type == Before) {
		cout << "You don't have any projects before date: " << std::put_time(&tm, "%Y-%m-%d") << endl;
	}
	else if (counter == 0 && type == After) {
		cout << "You don't have any projects after date: " << std::put_time(&tm, "%Y-%m-%d") << endl;
	}
}


void deleteProjectsByDate(RemoveType type)
{
	int counter{ 0 };
	int taskscounter{ 0 };
	std::tm tm = {};
	while (true)
	{
		string userString;
		cout << "Enter the date: ";
		cin >> userString;
		cout << endl;
		std::istringstream iss(userString);
		iss >> std::get_time(&tm, "%Y-%m-%d");
		if (!iss.fail())
		{
			break;
		}
	}
	std::time_t userDate = std::mktime(&tm);
	for (int i = 0; i < projects.size(); ++i)
	{
		std::time_t projectDate = std::mktime(&projects[i].due_date);
		double aux = std::difftime(userDate, projectDate);
		if (aux < 0 && type == After)
		{
			deleteAllProjectTasks(projects[i].project_name, taskscounter);
			projects.erase(projects.begin() + i);
			counter++;
			--i;
		}
		else if (aux > 0 && type == Before)
		{
			deleteAllProjectTasks(projects[i].project_name, taskscounter);
			projects.erase(projects.begin() + i);
			counter++;
			--i;
		}
	}
	cout << "Total projects removed: " << counter << endl;
	cout << "Total tasks removed: " << taskscounter << endl;
}

void deleteTasksByDate(RemoveType type)
{
	int counter{ 0 };
	std::tm tm = {};
	while (true)
	{
		string userString;
		cout << "Enter the date: ";
		cin >> userString;
		cout << endl;
		std::istringstream iss(userString);
		iss >> std::get_time(&tm, "%Y-%m-%d");
		if (!iss.fail())
		{
			break;
		}
	}
	std::time_t userDate = std::mktime(&tm);
	for (int i = 0; i < tasks.size(); ++i)
	{
		std::time_t taskDate = std::mktime(&tasks[i].due_date);
		double aux = std::difftime(userDate, taskDate);
		if (aux < 0 && type == Before)
		{
			tasks.erase(tasks.begin() + i);
			--i;
			counter++;
		}
		else if (aux > 0 && type == After)
		{
			tasks.erase(tasks.begin() + i);
			--i;
			counter++;
		}
	}
	cout << "Total tasks removed: " << counter << endl;
}




void deleteTab()
{
	char choice;
	do
	{
		cout << "What do you want to delete?" << endl;
		printDeleting();
		cin >> choice;
		int date;
		switch (choice)
		{
		case '1':
			deleteUser();
			break;
		case '2':
			deleteTask();
			break;
		case '3':
			deleteProject();
			break;
		case '4':
			cout << "You want to delete tasks before or after some date?" << endl << "(Enter 1 for before and 2 for after)";
			cin >> date;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (date <= 0 || date >= 3)
			{
				cout << "Invalid choice, try again." << endl;
				continue;
			}
			deleteTasksByDate((RemoveType)date);
			break;
		case '5':
			while (true)
			{
				cout << "You want to delete project before or after some date?" << endl << "(Enter 1 for before and 2 for after)";
				cin >> date;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (date <= 0 || date >= 3)
				{
					cout << "Invalid choice, try again." << endl;
					continue;
				}
				deleteProjectsByDate((RemoveType)date);
				break;
			}
		case '6':
			cout << "Returning to the menu." << endl;
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
			break;
		}
	} while (choice != '6');
}

void choiceA()
{
	char choiceA;
	do
	{
		cout << "Do you want to add users, tasks or projects?" << endl;
		printAdding();
		cin >> choiceA;

		switch (choiceA)
		{
		case '1':
			addUser();
			break;
		case '2':
			addTask();
			break;
		case '3':
			addProject();
			break;

		case '4':
			cout << "Returning to the menu." << endl;
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
			break;
		}
	} while (choiceA != '4');
}

void choiceP()
{
	char choiceP;
	do
	{
		cout << "Select what you want to print" << endl;
		printPrinting();
		
		cin >> choiceP;
		string userName;
		int date;
		switch (choiceP)
		{
		case '1':           //I want to select username and
			char choicePU;
			do
			{
				printPrintingByUsername();

				cin >> choicePU;
				switch (choicePU)
				{
				case '1':   //print all his tasks
					cout << "Available usernames: " << endl;
					for (const User& user : users)
					{
						cout << user.username << endl;
					}
					cout << "Enter user's username: ";
					cin.ignore();
					getline(cin, userName);
					printTasksForUser(userName);
					break;
				case '2':   //print all his projects
					cout << "Available usernames: " << endl;
					for (const User& user : users)
					{
						cout << user.username << endl;
					}
					cout << "Enter user's username: ";
					cin.ignore();
					getline(cin, userName);
					printProjectsForUser(userName);
					break;
				case '3':   //print all the tasks that end before or after some date
					cout << "You want to print tasks before or after some date?" << endl << "(Enter 1 for Before and 2 for After)";
					
					cin >> date;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					if (date <= 0 || date >= 3)
					{
						cout << "Invalid choice, try again." << endl;
						continue;
					}
					printTasksByDate((RemoveType)date);
					break;
				case '4':   //print projects that end before or after some date
					cout << "You want to print projects before or after some date?" << endl << "(Enter 1 for Before and 2 for After)";
					
					cin >> date;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					if (date <= 0 || date >= 3)
					{
						cout << "Invalid choice, try again." << endl;
						continue;
					}
					printProjectsByDate((RemoveType)date);
					break;
				case '5':
					cout << "Returning to the menu." << endl;
					break;
				default:
					cout << "Invalid choice. Please try again." << endl;
					break;
				}
			} while (choicePU != '5');
			break;

		case '2':   //I want to sort...
			char choicePS;
			do
			{
				printPrintingBySorting();

				cin >> choicePS;
				switch (choicePS)
				{
				case '1':   //sort all his tasks by date
					cout << "Available usernames: " << endl;
					for (const User& user : users)
					{
						cout << user.username << endl;
					}
					cout << "Enter user's username: ";
					cin.ignore();
					getline(cin, userName);
					printTasksSorted(userName, Date);
					break;
				case '2':   //sort all his tasks by date in reverse order
					cout << "Available usernames: " << endl;
					for (const User& user : users)
					{
						cout << user.username << endl;
					}
					cout << "Enter user's username: ";
					cin.ignore();
					getline(cin, userName);
					printTasksSorted(userName, DateReverse);
					break;
				case '3':   //sort all his tasks by username
					cout << "Available usernames: " << endl;
					for (const User& user : users)
					{
						cout << user.username << endl;
					}
					cout << "Enter user's username: ";
					cin.ignore();
					getline(cin, userName);
					printTasksSorted(userName, Username);
					break;
				case '4':   //sort all his tasks by priority
					cout << "Available usernames: " << endl;
					for (const User& user : users)
					{
						cout << user.username << endl;
					}
					cout << "Enter user's username: ";
					cin.ignore();
					getline(cin, userName);
					printTasksSorted(userName, Priority);
					break;
				case '5':
					cout << "Returning to the menu." << endl;
					break;
				default:
					cout << "Invalid choice. Please try again." << endl;
					break;
				}
			} while (choicePS != '5');
			break;

		case '3':   //print everything
			printUsers();
			printTasks();
			printProjects();
			break;

		case '4':
			cout << "Returning to the menu." << endl;
			break;

		default:
			cout << "Invalid choice. Please try again." << endl;
			break;
		}
	} while (choiceP != '4');
}



