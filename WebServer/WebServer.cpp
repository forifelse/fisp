// WebServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../AuxiSys/include/useAuxiSys.h"
#include "mainlgc.h"

int main(int argc, char** argv)
{
	WebLgc webLgc;
	webLgc.dbPath()->fromPath(String(argv[0]), 2);
	WebServer svr(&webLgc);
	svr.create();
	svr.run(81);
    return 0;
}

