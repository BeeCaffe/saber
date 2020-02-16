#include"json.h"
void saber::JsonObject::pushBack(JsonNode::ptr node){
	JsonNode* cur=this->getChild();
	if(cur==nullptr){
			this->setChild(node);
			return;
	}
	while(cur->getNext()!=nullptr) cur=cur->getNext();
	cur->setNext(node);
}

void saber::JsonObject::popBack(){
	JsonNode::ptr cur=const_cast<JsonNode*>(this->getChild());
	while(cur=nullptr) cur=cur->getNext();
	if(cur->getPrev()==nullptr) 
	cur->getPrev()->setNext(nullptr);
	delete cur;
}

std::string saber::JsonIntArray::toString(){
	std::stringstream ss;
	ss<<"\""<<getKey()<<"\"";
	ss<<":";
	ss<<"[";
	for(int i=0;i<m_data.size();++i){
		ss<<m_data[i];
		if(i!=m_data.size()-1) ss<<",";
	}
	ss<<"]";
	return ss.str();
}

void saber::JsonIntArray::fromString(std::string &str){
	int sz=str.size();
	int last_pos=1;
	for(int i=0;i<sz;++i){
		if(str[i]==','||str[i]==']'){
			std::stringstream ss;
			ss<<str.substr(last_pos,i-last_pos);
			int tmp;
			ss>>tmp;
			m_data.push_back(tmp);
			last_pos=i+1;
		}
	}

}

std::string saber::JsonDoubleArray::toString(){
std::stringstream ss;
	ss<<"\""<<getKey()<<"\"";
	ss<<":";
	ss<<"[";
	for(int i=0;i<m_data.size();++i){
		ss<<m_data[i];
		if(i!=m_data.size()-1) ss<<",";
	}
	ss<<"]";
	return ss.str();

}

void saber::JsonDoubleArray::fromString(std::string &str){
	////"node":[121,223,312]
	int sz=str.size();
	int last_pos=1;
	for(int i=0;i<sz;++i){
		if(str[i]==','||str[i]==']'){
			std::stringstream ss;
			ss<<str.substr(last_pos,i-last_pos);
			double tmp;
			ss>>tmp;
			m_data.push_back(tmp);
			last_pos=i+1;
		}
	}
}

std::string saber::JsonStringArray::toString(){
std::stringstream ss;
	ss<<"\""<<getKey()<<"\"";
	ss<<":";
	ss<<"[";
	for(int i=0;i<m_data.size();++i){
		ss<<"\""<<m_data[i]<<"\"";
		if(i!=m_data.size()-1) ss<<",";
	}
	ss<<"]";
	return ss.str();

}

void saber::JsonStringArray::fromString(std::string &str){
	////"node":["hello","world"]
	int sz=str.size();
	for(int i=0;i<sz;++i){
		for(int j=i+1;j<sz;++j){
			if(str[i]=='\"'&&str[j]=='\"'){
				std::string tmp=str.substr(i+1,j-i-1);
				m_data.push_back(tmp);
				if(j+1<sz) i=j+1;
				else return;
			}
		}
	}
}

std::string saber::JsonObjectArray::toString(){
		std::stringstream ss;	
		ss<<"\""<<getKey()<<"\"";
		ss<<":";
		ss<<"[";
		for(int i=0;i<m_data.size();++i){
				std::string obj_str=m_data[i]->toString();
				int pos=0;
				for(int i=0;i<obj_str.size();++i){
					if(obj_str[i]==':'&&(i+1)<obj_str.size()&&obj_str[i+1]=='{'){
					pos=i+1;
					}
				}
				obj_str=obj_str.substr(pos+1);
				ss<<obj_str;
				if(i!=m_data.size()-1){ 
						ss<<",";
				}
		}
		ss<<"]";
		return ss.str();
}

void saber::JsonObjectArray::fromString(std::string &str){
	////"node":[{...},{...}]
	std::stack<std::pair<char,int>> S;////char int
	int sz=str.size();
	for(int i=0;i<sz;++i){
		if(str[i]=='{') S.push(std::make_pair('{',i));
		else if(str[i]=='}'){
			std::pair<char,int> last=S.top();S.pop();
			if(S.empty()){
				JsonObject* obj=new JsonObject();
				int last_pos=last.second;
				std::string obj_str=str.substr(last_pos,i+1-last_pos);
				obj->fromString(obj_str);
				m_data.push_back(obj);
			}
		}
	}
}

std::string saber::JsonDouble::toString(){
std::stringstream ss;
	ss<<"\""<<getKey()<<"\"";
	ss<<":";
	ss<<m_data;
	return ss.str();

}

void saber::JsonDouble::fromString(std::string &str){
	////"node":3.14 str=3.14
	std::stringstream ss;
	ss<<str;
	double tmp;
	ss>>tmp;
	m_data=tmp;
}

std::string saber::JsonInt::toString(){
	std::stringstream ss;
	ss<<"\""<<getKey()<<"\"";
	ss<<":";
	ss<<m_data;
	return ss.str();

}

void saber::JsonInt::fromString(std::string &str){
	//// "node":123
		std::stringstream ss;
		ss<<str;
		int32_t tmp;
		ss>>tmp;
		m_data=tmp;
}

std::string saber::JsonString::toString(){
std::stringstream ss;
	ss<<"\""<<getKey()<<"\"";
	ss<<":";
	ss<<"\"";
	ss<<m_data;
	ss<<"\"";
	return ss.str();


}

void saber::JsonString::fromString(std::string &str){
	//// "node":"hello"  str="hello"
		std::stringstream ss;
		ss<<str;
		m_data=ss.str();
}

std::string saber::JsonObject::toString(){
	std::stringstream ss;
	ss<<parseObject(this);
	return ss.str();
}

std::string saber::JsonObject::parseObject(JsonObject* obj){
	std::stringstream ss;
	if(!obj->getKey().empty())ss<<"\""<<obj->getKey()<<"\":";
	ss<<"\n{\n";
	JsonNode* cur=const_cast<JsonNode*>(obj->getChild());
	while(cur!=nullptr){
		if(cur->getType()!=JsonType::Type::Object){
				ss<<cur->toString();
		}else{ 
			ss<<parseObject(dynamic_cast<JsonObject*>(cur)); 
		}		
		////not last node
		if(cur->getNext()!=nullptr) ss<<",\n";
		cur=cur->getNext();
	}
	ss<<"\n}\n";
	return ss.str();
}

void saber::JsonObject::fromString(std::string &obj_str){
	////check json object string
	if(obj_str[0]=='{'&&obj_str[obj_str.size()-1]=='}'){
		//// json object string without "{}"
		obj_str=obj_str.substr(1,obj_str.size()-2);
	}else {
		LOG_ERROR(LOG_JSON)<<"Json Object String Format Uncorrect!";
	}
	////parse this string
	int last_pos=0;
	for(int i=0;i<obj_str.size();++i){
		////a node
		if(obj_str[i]==':'){
			std::string key=obj_str.substr(last_pos+1,i-last_pos-2);
			////an array
			if(i+1<obj_str.size()&&obj_str[i+1]=='['){
				int j=i+2;
				if(obj_str[j]=='{'){
					////an object array
					std::stack<std::pair<char,int>> S;////char, index
					S.push(std::make_pair('[',i+1));
					for(;j<obj_str.size();++j){
						if(obj_str[j]=='[') S.push(std::make_pair('[',j));
						else if(obj_str[j]==']'){
							S.pop();
							if(S.empty()) break;
						}
					}
					std::string array=obj_str.substr(i+1,j-i);
					JsonObjectArray* node=new JsonObjectArray(key);
					node->fromString(array);
					this->pushBack((JsonNode*)node);
					i=j;
					last_pos=i+2;
				}else if(obj_str[j]=='\"'){
					////string array
					while(j<obj_str.size()&&obj_str[j]!=']') ++j;
					std::string array=obj_str.substr(i+1,j-i);
					JsonStringArray* node=new JsonStringArray(key);
					node->fromString(array);
					this->pushBack((JsonNode*)node);
					i=j;
					last_pos=i+2;
				}
				else{
					while(j<obj_str.size()&&obj_str[j]!=']') ++j;
					std::string array=obj_str.substr(i+1,j-i);
					bool isInt=true;
					for(int k=0;k<array.size();++k){
						if(array[k]=='.'){
							isInt=false;break;
						}
					}
	
					if(isInt){////int  array
						JsonIntArray* node=new JsonIntArray(key);
						node->fromString(array);
						this->pushBack((JsonNode*)node);
					}else{////double array
						JsonDoubleArray* node=new JsonDoubleArray(key);
						node->fromString(array);
						this->pushBack((JsonNode*)node);
					}
					i=j;
					last_pos=i+2;
				}
			}
			else if(i+1<obj_str.size()&&obj_str[i+1]=='{'){
				//// an object
				int j=i+1;
				while(j<obj_str.size()&&obj_str[j]!='}') ++j;
				JsonObject* tmp=new JsonObject(key);
				std::string str=obj_str.substr(i+1,j-i);
				tmp->fromString(str);
				this->pushBack((JsonNode*)tmp);
				i=j;
				last_pos=i+2;
			}else{
				//// other types
				int j=i+1;
				while(j<obj_str.size()&&obj_str[j]!=',') ++j;
				std::string node_str=obj_str.substr(i+1,j-i-1);
				if(node_str[0]=='\"'){
					////string
					JsonString* node=new JsonString(key);
					std::string str=node_str.substr(1,node_str.size()-2);
					node->fromString(str);
					this->pushBack((JsonNode*)node);
				}else{
					bool isInt=true;
					for(int k=0;k<node_str.size();++k){
						if(node_str[k]=='.'){
							isInt=false;break;
						}
					}
					if(isInt){////int 
						JsonInt* node=new JsonInt(key);
						std::string str=node_str.substr(0,node_str.size());
						node->fromString(str);
						this->pushBack((JsonNode*)node);
					}else{////double 
						JsonDouble* node=new JsonDouble(key);
						std::string str=node_str.substr(0,node_str.size());
						node->fromString(str);
						this->pushBack((JsonNode*)node);
					}
			
				}
				i=j;
				last_pos=i+1;
			}
		}
	}
}

void saber::JsonObjectArray::setVisited(bool flag){
	for(auto item:m_data){
		item->setVisited(flag);
	}
}

saber::JsonNode* saber::JsonObject::getChild(){
	return m_child;
}
void saber::JsonObject::setChild(JsonNode* child){
	m_child=child;
}
/**
*class JsonTree functions
*/
void saber::JsonTree::fromString(std::string &json_str){
	checkString(json_str);
	JsonObject* root=new JsonObject();
	root->fromString(json_str);
	m_root=root;
	LOG_INFO(LOG_JSON)<<"JsonTree Build Done!";
}

std::string saber::JsonTree::toString(){
	std::stringstream ss;
	ss<<m_root->toString();
	std::string ans(ss.str());
	int pos=0;
	for(int i=0;i<ans.size();++i){
		if(ans[i]=='{'){ 
			pos=i;break;
		}
	}
	return ans.substr(pos);
}

void saber::JsonTree::release(){
		countKey();
		releaseObject(m_root);
		sharedRelease(m_root);
		LOG_INFO(LOG_JSON)<<"Json Tree Release Done!";
}

void saber::JsonTree::releaseObject(JsonObject* obj){
	JsonNode* cur=obj->getChild();
	while(cur!=nullptr){
		if(cur->getType()==JsonType::Object){
			releaseObject(dynamic_cast<JsonObject*>(cur));
		}else if(cur->getType()==JsonType::ObjectArray){
			std::vector<JsonObject*> vec=dynamic_cast<JsonObjectArray*>(cur)->getData();
			for(int i=0;i<vec.size();++i) {
					JsonObject* tmp=vec[i];
					releaseObject(tmp);
					sharedRelease(dynamic_cast<JsonNode*>(tmp));
			}
			vec.clear();
		}
		cur=cur->getNext();
	}
	cur=obj->getChild();
	while(cur!=nullptr){
		sharedRelease(dynamic_cast<JsonNode*>(cur));
		cur=cur->getNext();
	}
}

void saber::JsonTree::sharedRelease(JsonNode* node){
	if(--m_map[node->getKey()]==0){
		delete node;
	}
}


void saber::JsonTree::initTree(){
	if(m_root!=nullptr) return;
	JsonObject* root=new JsonObject("root object");
	m_root=root;
}

void saber::JsonTree::addNode(JsonNode* node){
	if(node==nullptr) LOG_DEBUG(LOG_JSON)<<"JsonNode Should Not Be nullptr";
	m_root->pushBack(node);
}

int saber::JsonTree::delNode(std::string key){
	return 0;
}

void saber::JsonTree::countKey(){
		std::queue<JsonNode*> que; 
		que.push(m_root);	////root is a JsonObject
		while(!que.empty()){
			for(int i=que.size()-1;i>=0;--i){
				JsonNode* cur=que.front();que.pop();
				m_map[cur->getKey()]++;
				cur=cur->getChild();
				while(cur!=nullptr){
						//// JsonObject push into queue
						if(cur->getType()==JsonType::Type::Object){
							que.push(cur);
						}else if(cur->getType()==JsonType::Type::ObjectArray){
							m_map[cur->getKey()]++;
							////JsonObjectArray push each items into queue
							std::vector<JsonObject*> vec(dynamic_cast<JsonObjectArray*>(cur)->getData());
							if(vec.empty()) LOG_DEBUG(LOG_NEW("JsonLog"))<<"JosnObjectArray data copy error";
							for(int i=0;i<vec.size();++i){
								que.push(vec[i]);
							}
						}else{
							m_map[cur->getKey()]++;
						}
						cur=cur->getNext();
				}
			}
		}
}

bool saber::JsonTree::checkString(std::string &str){
	clearSpace(str);
	std::stack<char> S;
	////check {} and [] error
	for(int i=0;i<str.size();++i){
		if(str[i]=='{'||str[i]=='[') S.push(str[i]);
		else if(str[i]=='}'){
			char cur=S.top();S.pop();
			if(cur!='{'){
				LOG_ERROR(LOG_JSON)<<"Json String Format Error -- Unpaired \"{}\" in Json String!";
				exit(0);
			} 
		} else if(str[i]==']'){
			char cur=S.top();S.pop();
			if(cur!='['){
				LOG_ERROR(LOG_JSON)<<"Json String Format Error -- Unpaired \"[]\" in Json String!";
				exit(0);
			} 

		}
	}
	//// with out key string error
	for(int i=0;i<str.size();++i){
		if(str[i]==':'&&i-1>=0&&str[i-1]!='\"'){
			LOG_ERROR(LOG_JSON)<<"Json String Format Error -- Absents Key String Before ':'"<<"in sub string : ["<<str.substr(i-5,10)<<"]";
			exit(0);
		}
	}
	return true;
}

void saber::JsonTree::clearSpace(std::string &str){
		int n=0;
		for(int i=0;i<str.size();++i){
			if(str[i]=='\"'){
				int j=i+1;
				while(j<str.size()&&str[j]!='\"') ++j;
				if(j==str.size()){ LOG_ERROR(LOG_JSON)<<"Json String Format Error! '\"' Unpaired In Json String ";
					exit(0);
				}
				else i=j;
				n+=2;
			}else{
				if(str[i]==' '){ 
					str.erase(i,1);
					--i;
				}
			}
		}
		if(n%2!=0){
			LOG_ERROR(LOG_JSON)<<"Json String Format Error! '\"' Unpaired In Json String "<<"'\"' number is : "<<n;
			exit(0);

		}
}

saber::JsonNode* saber::JsonTree::getNode(std::string &key){
		std::queue<JsonNode*> que; 
		que.push(m_root);	////root is a JsonObject
		while(!que.empty()){
			for(int i=que.size()-1;i>=0;--i){
				JsonNode* cur=que.front();que.pop();
				if(cur->getKey()==key) return cur;
				cur=cur->getChild();
				while(cur!=nullptr){
						//// JsonObject push into queue
						if(cur->getType()==JsonType::Type::Object){
							que.push(cur);
						}else if(cur->getType()==JsonType::Type::ObjectArray){
							if(cur->getKey()==key) return cur;
							////JsonObjectArray push each items into queue
							std::vector<JsonObject*> vec(dynamic_cast<JsonObjectArray*>(cur)->getData());
							if(vec.empty()) LOG_DEBUG(LOG_NEW("JsonLog"))<<"JosnObjectArray data copy error";
							for(int i=0;i<vec.size();++i){
								que.push(vec[i]);
							}
						}else{
							if(cur->getKey()==key) return cur;
						}
						cur=cur->getNext();
				}
			}
		}

		LOG_ERROR(LOG_JSON)<<"Node Not Found In JsonTree:["<<this->getName()<<"],Node Name Is:"<<"["<<key<<"]";
		throw "Node Not Found In JsonTree.\n";
		return nullptr;
}
