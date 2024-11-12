#include "Audience.h"

Audience::Audience()
{
	printf("観客 : ");
	printf("(拍手)\n");
}

Audience::~Audience()
{
	printf("観客 : ");
	printf("全員が立ち上がり、拍手が鳴りやまなかった\n");
}

void Audience::Recital()
{
	printf("観客 : ");
	printf("美しい音色に鳥肌が止まらない..!\n");
}
