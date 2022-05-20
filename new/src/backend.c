#include <stdio.h>

#include "socket.h"
#include "handler.h"

int main(void)
{
	int backend;
	int user;
	
	backend = binding(80, 1, 1);
	if (backend != -1)
	{
		while (1)
		{
			user = accepting(backend);
			handling(user);
		}
	}
}
