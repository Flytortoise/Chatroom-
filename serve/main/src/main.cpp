#include <iostream>
#include "Abstract.h"
#include "my_stock.h"
#include "Start.h"
#include "Init.h"

using namespace std;

void * Start (void *p);

Serve_Stock* Serve_Stock::serve = NULL;
//Client_Stock::client = NULL;
start* start::my_start_ = NULL;
Online_data* Online_data::data = NULL;
Pass* Pass::pass_ = NULL;
Select* Select::select_ = NULL;

int main(int argc, char *argv[])
{
	pthread_t client_tidp;
	int client_stock;
	
	Init::init();

	AB_Action * my_serve = Serve_Stock::GetStock();
	while(1)
	{
		client_stock = my_serve->Action();
		cout << "client_stock = " << client_stock << endl; 
		if(pthread_create(&client_tidp,NULL,Start,static_cast<void *>(&client_stock)) != 0)	//创建线程，单独为客户端工作
		{
		    perror("Pthread_create error!");
			exit(-1);
		}
	
	}
	Serve_Stock::FreeStock();
	return 0;
}

void * Start (void *p)
{
	AB_Director * my_start = start::CreateStart();
	my_start->Direct(*(static_cast<int *>(p)));
	start::FreeStart();
}
