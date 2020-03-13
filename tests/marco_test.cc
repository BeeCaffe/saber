#include"../saber/saber.h"
#include<assert.h>
saber::Logger::ptr g_logger=LOG_NEW("system");
void test_assert(){
	//ASSERT(0);
	ASSERT2(0==1,"abcdefg")
}

int main(){
	test_assert();
	return 0;
}


