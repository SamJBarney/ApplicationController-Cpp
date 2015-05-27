//
//  Created by Barney, Samuel on 5/22/15.
//  Copyright (c) 2015 Barney, Samuel. All rights reserved.
//

#ifndef __ApplicationController__
#define __ApplicationController__

#include <string>
#include <map>

template <class ... Args>
class ApplicationController
{
public:
	class Handler
	{
	public:
		virtual ~Handler(){}
		virtual void handle(Args ... arguments) = 0;
	};
	
	typedef std::map<std::string, Handler*> Map;
	
	ApplicationController(): mDefaultHandler(NULL){}
	ApplicationController(Handler * aDefault): mDefaultHandler(aDefault){}
	~ApplicationController()
	{
		for (typename Map::iterator it = mCommands.begin(); it != mCommands.end(); ++it)
			delete it->second;
		if (mDefaultHandler)
			delete mDefaultHandler;
	}
	
	bool registerHandler(const std::string & aCommand, Handler * aHandler)
	{
		if (mCommands.find(aCommand) == mCommands.end())
		{
			mCommands[aCommand] = aHandler;
		}
		return false;
	}
	void execute(const std::string & aCommand, Args ... arguments)
	{
		typename Map::iterator it = mCommands.find(aCommand);
		if (it != mCommands.end())
		{
			it->second->handle(arguments ...);
		}
		else if (mDefaultHandler)
		{
			mDefaultHandler->handle(arguments ...);
		}
	}
	
	
private:
	Map mCommands;
	Handler * mDefaultHandler;
};

#endif /* defined(__ApplicationController__) */
