#include"../saber/config.h"
#include"../saber/log.h"
#include<yaml-cpp/yaml.h>
#include<vector>

/*saber::ConfigVar<int>::ptr g_int_value_config=saber::Config::lookUp("system.port",(int)8080,"system_port");

//saber::ConfigVar<float>::ptr g_int_valuex_config=saber::Config::lookUp("system.port",(float)8080,"system_port");


saber::ConfigVar<float>::ptr g_float_value_config=saber::Config::lookUp("system.value",(float)10.2f,"system_value");

saber::ConfigVar<std::vector<int>>::ptr g_int_vec_value_config=saber::Config::lookUp("system.int_vec",std::vector<int>{1,2,3,4,5},"system.int_vec");

saber::ConfigVar<std::list<int>>::ptr g_int_list_value_config=saber::Config::lookUp("system.int_list",std::list<int>{7,8,9},"system.int_vec");

saber::ConfigVar<std::set<int>>::ptr g_int_set_value_config=saber::Config::lookUp("system.int_set",std::set<int>{0,1,2},"system.int_set");

saber::ConfigVar<std::unordered_set<int>>::ptr g_int_unordered_set_value_config=saber::Config::lookUp("system.int_unordered_set",std::unordered_set<int>{2,50,8},"system.int_unordered_set");

saber::ConfigVar<std::map<std::string,int>>::ptr g_int_map_value_config=saber::Config::lookUp("system.int_map",std::map<std::string,int>{{"k",23},{"f",28},{"s",81}},"system.int_map");

saber::ConfigVar<std::unordered_map<std::string,int>>::ptr g_int_umap_value_config=saber::Config::lookUp("system.int_umap",std::unordered_map<std::string,int>{{"uk",23},{"uf",28},{"us",81}},"system.int_umap");

class Person{
public:
	Person(){}
	std::string m_name;
	int m_age=0;
	bool m_sex=0;
	std::string toString() const{
		std::stringstream ss;
		ss<<"[Person name="<<m_name<<" age="<<m_age<<" sex="<<m_sex<<"]";
		return ss.str();
	}

	bool operator==(const Person& p) const {
		bool res=true;
		if(p.m_name!=m_name) res=false;
		if(p.m_age!=m_age) res=false;
		if(p.m_sex!=m_sex) res=false;
		return res;

	}

};

namespace saber{
	//vector
	template<>
	class LexicalCast<std::string,Person>{
	public:
		Person operator()(const std::string& v){
			YAML::Node node=YAML::Load(v);
			Person person;
			std::stringstream ss;
			person.m_name=node["name"].as<std::string>();
			person.m_age=node["age"].as<int>();
			person.m_sex=node["sex"].as<bool>();
			LOG_DEBUG(LOG_ROOT)<<person.toString();
			return person;
		}
	};

	template<>
	class LexicalCast<Person,std::string>{
	public:
		std::string operator()(const Person& p){
			YAML::Node node;
			node["name"] = p.m_name;
			node["age"] = p.m_age;
			node["sex"] = p.m_sex;
			std::stringstream ss;
			ss<<node;
			return ss.str();
		}
	};

};

saber::ConfigVar<Person>::ptr g_person = saber::Config::lookUp("class.person",Person(),"system person");

void test_class(){

	g_person->addListener(10,[](const Person& old_value,const Person& new_value ){
		LOG_INFO(LOG_ROOT)<<"old value="<<old_value.toString();
		LOG_INFO(LOG_ROOT)<<"new value="<<new_value.toString();
	});

	LOG_INFO(LOG_ROOT)<<"berfore: "<<g_person->getValue().toString()<<" - "<<g_person->toString();

	YAML::Node root=YAML::LoadFile("/home/beecaffe/src/saber/conf/test.yml");
	saber::Config::LoadFromYaml(root);

	LOG_INFO(LOG_ROOT)<<"after: "<<g_person->getValue().toString()<<" - "<<g_person->toString();
}

void print_yaml(const YAML::Node& node, int level){
	if(node.IsScalar()){
		LOG_INFO(LOG_ROOT)<<node.Scalar()<<"-"<<node.Tag()<<"-"<<level;
	}else if (node.IsNull()){
		LOG_INFO(LOG_ROOT)<<"NULL"<<"-"<<node.Tag()<<level;
	}else if (node.IsMap()){
		for(auto iter=node.begin();iter!=node.end();++iter){
			LOG_INFO(LOG_ROOT)<<iter->first<<"-"<<iter->second.Tag()<<level;
			print_yaml(iter->second,level+1);
		}
	}else  if(node.IsSequence()){
		for(size_t i=0;i<node.size();++i){
			LOG_INFO(LOG_ROOT)<<i<<"-"<<node[i].Tag()<<level;
			print_yaml(node[i],level);
		}
	}
}

void test_yaml(){
	//// load file from xx.yml file
	YAML::Node root=YAML::LoadFile("/home/beecaffe/src/saber/conf/test.yml");
	print_yaml(root,0);
	//LOG_INFO(LOG_ROOT)<<root;
}

void test_config(){

	LOG_INFO(LOG_ROOT)<<"before: "<<g_int_value_config->getValue();
	LOG_INFO(LOG_ROOT)<<"before: "<<g_float_value_config->toString();
#define XX(g_var, name, prefix) \
	{ \
			auto& v=g_var->getValue(); \
			for(auto& i:v){ \
				LOG_INFO(LOG_ROOT)<< #prefix" " #name ": "<<i; \
			} \
	}
	
	XX(g_int_vec_value_config,int_vec,before);
	XX(g_int_list_value_config, list_var,before);
	XX(g_int_set_value_config, int_set, before);
	XX(g_int_unordered_set_value_config,unordered_set,before);
	
	{
	auto& v=g_int_map_value_config->getValue();
	for(auto it=v.begin();it!=v.end();++it){
		LOG_INFO(LOG_ROOT)<<"int_map "<<"before: "<<"key: "<<it->first<<"value: "<<it->second;
	}
	}

	{
	auto& v=g_int_umap_value_config->getValue();
	for(auto it=v.begin();it!=v.end();++it){
		LOG_INFO(LOG_ROOT)<<"int_umap "<<"before: "<<"key: "<<it->first<<"value: "<<it->second;
	}}

	YAML::Node root=YAML::LoadFile("/home/beecaffe/src/saber/conf/log.yml");
	saber::Config::LoadFromYaml(root);

	LOG_INFO(LOG_ROOT)<<"after: "<<g_int_value_config->getValue();
	LOG_INFO(LOG_ROOT)<<"after: "<<g_float_value_config->toString();
	XX(g_int_vec_value_config,int_vec,after);
	XX(g_int_list_value_config, list_var,after);
	XX(g_int_set_value_config, int_set, after);
	XX(g_int_unordered_set_value_config,unordered_set,after);
	{
			auto& f = g_int_map_value_config->getValue();
			if(f.empty())	LOG_INFO(LOG_ROOT)<<"map is empty";
			for(auto it=f.begin();it!=f.end();++it){
				LOG_INFO(LOG_ROOT)<<"int_map "<<"after: "<<"key: "<<it->first
						<<"value:"<<it->second;
			}
	}

	{
			auto& v=g_int_umap_value_config->getValue();

			if(v.empty())	LOG_INFO(LOG_ROOT)<<"map is empty";
			for(auto it=v.begin();it!=v.end();++it){
				LOG_INFO(LOG_ROOT)<<"int_umap "<<"after: "<<"key: "<<it->first<<"value: "<<it->second;
			}
	}
}*/

void test_logger(){
	static saber::Logger::ptr system_log=FIND_LOG("system");
	LOG_INFO(system_log)<<"hello system"<<std::endl;
	std::cout<<saber::LogMng::Instance()->toYamlString()<<std::endl;
	YAML::Node root=YAML::LoadFile("/home/beecaffe/src/saber/conf/test.yml");
	
	saber::Config::LoadFromYaml(root);
	std::cout<<"====================================="<<std::endl;
	std::cout<<saber::LogMng::Instance()->toYamlString()<<std::endl;
	std::cout<<"====================================="<<std::endl;

	std::cout<<system_log->toYamlString()<<std::endl;
	LOG_INFO(LOG_ROOT)<<"hello system"<<std::endl;

	std::cout<<"====================================="<<std::endl;
	system_log->setFormatter("%d - %m%n");
	std::cout<<system_log->toYamlString()<<std::endl;
	LOG_INFO(LOG_ROOT)<<"hello system"<<std::endl;

}

int main(){
		//test_yaml();
		//test_config();
		//test_class();
		test_logger();
			saber::Config::Visit([](saber::ConfigVarBase::ptr var){
				LOG_INFO(LOG_ROOT)<<"name="<<var->getName()
								  <<" description="<<var->getDescription()
								  <<" typename="<<var->getName()
								  <<" value="<<var->toString();
			});

		return 0;
}






