#include "Database.h"

#include "UserClass.h"
#include "ProjectClass.h"

void Database::createUser(std::string name, std::string password, int free_time, std::string prerequisites, std::string StudyFields)
{
	users.emplace(std::pair<std::string, User*>(name, new User(name, password, free_time, prerequisites, StudyFields)));
}

void Database::createProject(User* initiator, std::string name, std::string objective, std::string tasks, std::string subjectField, std::string client, std::string deadline, std::string prerequisites)
{
	projects.emplace(std::pair<std::string, Project*>(name, new Project(initiator, name, objective, tasks, subjectField, client, deadline, prerequisites)));
}

User* Database::getUser(std::string name)
{
	return users[name];
}

bool Database::checkUser(std::string name) 
{
	if (users.count(name) == 0)
		return true;
	else
		return false;
}

bool Database::checkProject(std::string name) 
{
	if (projects.count(name) == 0)
		return true;
	else
		return false;
}

Project* Database::getProject(std::string name)
{
	return projects[name];
}

void Database::deleteUser(std::string userName)
{
	delete users[userName];
	users.erase(userName);
}

void Database::deleteProject(std::string projectName)
{
	delete projects[projectName];
	projects.erase(projectName);
}

void Database::finishProject(std::string projectName)
{
	finishedProjects.insert(std::pair<std::string, Project*>(projectName, projects[projectName]));
	projects.erase(projectName);
}

std::vector<Project*> Database::findProjects(std::vector<std::string> prer)
{
	std::vector<Project*> found;
	bool flag = false;
	std::vector<std::string> projectPrer;
	for (const std::pair<std::string, Project*>& p : projects)
	{
		projectPrer = p.second->getPrerequisites();
		for (int i = 0; i < projectPrer.size(); i++)
		{
			flag = false;
			for (int j = 0; j < prer.size(); j++)
			{
				if (prer[j] == projectPrer[i])
				{
					flag = true;
					break;
				}
			}
			if (flag == false)
			{
				break;
			}
		}
		if (flag == true)
		{
			found.push_back(p.second);
		}
	}
	return found;
}

std::vector<User*> Database::findParticipants(std::vector<std::string> prer)
{
	std::vector<User*> found;
	bool flag = false;
	std::vector<std::string> userPrer;
	for (const std::pair<std::string, User*>& p : users)
	{
		userPrer = p.second->getPrerequisites();
		for (int i = 0; i < prer.size(); i++)
		{
			flag = false;
			for (int j = 0; j < userPrer.size(); j++)
			{
				if (prer[i] == userPrer[j])
				{
					flag = true;
					break;
				}
			}
			if (flag == false)
			{
				break;
			}
		}
		if (flag == true)
		{
			found.push_back(p.second);
		}
	}
	return found;
}

Database::~Database()
{
	{
		for (std::map<std::string, User*>::iterator itr = users.begin(); itr != users.end(); itr++)
		{
			delete (itr->second);
		}
		users.clear();
		for (std::map<std::string, Project*>::iterator itr = projects.begin(); itr != projects.end(); itr++)
		{
			delete (itr->second);
		}
		projects.clear();
		for (std::map<std::string, Project*>::iterator itr = finishedProjects.begin(); itr != finishedProjects.end(); itr++)
		{
			delete (itr->second);
		}
		finishedProjects.clear();
	}
}