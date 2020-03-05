#include"config.h"
namespace saber{
	
	saber::Config::ConfigVarMap Config::s_datas;

	/**
	 *@brief ListAllMember
	 */
	static void ListAllMember(const std::string& prefix,
							  const YAML::Node& node,
							  std::list<std::pair<std::string,const YAML::Node>>& output){
		if(prefix.find_first_not_of("aqwertyuiopasdfghjklzxcvbnm._0123456789")!=std::string::npos){
			LOG_ERROR(LOG_ROOT)<<"Config invalid name: "<<prefix<<" : "<<node;
			return;
		}
		output.push_back(std::make_pair(prefix,node));
		if(node.IsMap()){
			for(auto it=node.begin();
					 it!=node.end();
					 ++it){
				ListAllMember(prefix.empty() ? it->first.Scalar() : prefix+"."+it->first.Scalar(),it->second,output);
			}
		}
	}

	/**
	 *@brief LookupBase
	 */
	ConfigVarBase::ptr Config::LookupBase(const std::string& name){
		auto it=s_datas.find(name);
		return it==s_datas.end() ? nullptr : it->second;

	}

	/**
	 *@brief LoadFromYaml
	 */
	void saber::Config::LoadFromYaml(const YAML::Node& root){
			std::list<std::pair<std::string, const YAML::Node>> all_nodes;
			ListAllMember("",root,all_nodes);

			for(auto& i:all_nodes){
					std::string key= i.first;
					if(key.empty()) continue;
					std::transform(key.begin(),key.end(),key.begin(),::tolower);
					ConfigVarBase::ptr var = LookupBase(key);
					//LOG_DEBUG(LOG_ROOT)<<"1: "<<key;
					if(var){
						if(i.second.IsScalar()){
					//LOG_DEBUG(LOG_ROOT)<<"2: "<<i.second.Scalar();
							var->fromString(i.second.Scalar());
						}else{
							std::stringstream ss;
							ss<<i.second;
					//LOG_DEBUG(LOG_ROOT)<<"3: "<<ss.str();
							var->fromString(ss.str()); 
						}
					}
			}
	}
};


