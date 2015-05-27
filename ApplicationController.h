// Copyright (c) 2015 Samuel Barney

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

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
