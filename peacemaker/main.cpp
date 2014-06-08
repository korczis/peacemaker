//
//  main.cpp
//  peacemaker
//
//  Created by Tomas Korcak on 6/8/14.
//  Copyright (c) 2014 Tomas Korcak. All rights reserved.
//

// core c++ includes
#include <cstdio>
#include <cstdlib>

#include "Application/Application.h"

int main(const int argc, const char *argv[])
{
   // Create peacemaker application
	auto app = new pm::Application(argc, argv);
   
   auto res = app->Run();
   
   // Delete application
   delete app;
   app = 0;
   
   return res;
}
