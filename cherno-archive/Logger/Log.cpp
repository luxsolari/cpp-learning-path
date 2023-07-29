#include <iostream>
//int g_Variable = 10; // It is initialized to 10. It is not static so it will be linked inside all files that include this header file.
//extern int s_Variable; // This is an externally linked variable, it is declared in another file.
extern int ss_Variable;

class Log
{
public:	
	enum Level : unsigned short // This is an enum. It is a way to create a custom data type that can only have a limited number of values.
	{ 
		LEVEL_ERROR = 0, LEVEL_WARNING, LEVEL_INFO 
	};

private:
	Level m_LogLevel = LEVEL_INFO; // this is a class member variable (field) and it is private so it can only be accessed by the class itself.
	static int instanceCount;  // This is a static variable. It is shared between all objects of this class. It is private so it can only be accessed by the class itself.
							   // It is initialized to 0. It is a good practice to initialize static variables in the class definition.
	static int messagesLogged; 
	
public:
	Log() = delete; // This default constructor is deleted so it can't be used. This is a way to prevent the creation of an object without parameters.
				    // It is a good practice to delete the default constructor if you are going to create a custom constructor.
	
	Log(Level level)
	{
		std::cout << "Log created with level " << level << std::endl;
		m_LogLevel = level;
		instanceCount++;
	}

	void SetLevel(Level level)
	{
		m_LogLevel = level;
	}
	
	void Error(const char* message)
	{
		if (m_LogLevel >= LEVEL_ERROR) {
			std::cout << "[ERROR]: " << message << std::endl;
			messagesLogged++;
		}
	}

	void Warn(const char* message)
	{
		if (m_LogLevel >= LEVEL_WARNING) {
			std::cout << "[WARNING]: " << message << std::endl;
			messagesLogged++;
		}
	}

	void Info(const char* message)
	{
		if (m_LogLevel >= LEVEL_INFO) {
			std::cout << "[INFO]: " << message << std::endl;
			messagesLogged++;
		}
	}

	int static GetInstanceCount() // This is a static method. It is shared between all objects of this class. It is public so it can be accessed from outside the class.
	{
		return instanceCount;
	}

	int static GetMessagesLogged() // This is a static method. It is shared between all objects of this class. It is public so it can be accessed from outside the class.
	{
		return messagesLogged;
	}

	~Log() // This is the destructor. It is called when the object is destroyed. It is a good practice to use it to free memory. 
	{
		std::cout << "Log destroyed" << std::endl;
		instanceCount--;
	}
};

int Log::instanceCount = 0;  // This is the definition of the static variable. It is initialized to 0. It is shared between all objects of this class. 
							 // It is public so it can be accessed from outside the class.
int Log::messagesLogged;

//int main()
//{
//	register int number = 5;
//	std::cout << "Logger instances: " << Log::GetInstanceCount() << std::endl;
//	Log logger = { Log::LEVEL_WARNING }; // The scope of this variable is limited to this block. It is created on the stack.
//	logger.Info("Created logger intance ! \n");
//	logger.Warn("This instance was created without using new, so it is located on the stack. ");
//	std::cout << "Logger instances: " << Log::GetInstanceCount() << std::endl;
//	logger.Info("The value of the extern variable is: " + ss_Variable);	
//}
