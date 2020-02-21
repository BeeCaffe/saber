#include"../saber/config.h"
#include"../saber/log.h"
saber::ConfigVar<int>::ptr g_int_value_config=saber::Config::Lookup("system port",(int)8080,"system port");
using namespace saber;

int main(){
		LOG_INFO(LOG_ROOT)<<g_int_value_config->getValue();
		LOG_INFO(LOG_ROOT)<<g_int_value_config->toString();
	return 0;
}
