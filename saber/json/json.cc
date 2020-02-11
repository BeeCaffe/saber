#include"json.h"
template<class T>
void saber::JsonNode<T>::pushBack(JsonNode<T>::ptr node){
	JsonNode::ptr cur=this;
	while(cur->getNext()!=nullptr) cur=cur->getNext();
	cur->setNext(node);
}

template<class T>
void saber::JsonNode<T>::pushFront(JsonNode<T>::ptr node){
	JsonNode::ptr cur=this;
	while(cur->getPrev()!=nullptr) cur=cur->getPrev();
	cur->setPrev(node);
}

template<class T>
void saber::JsonNode<T>::popBack(){
	JsonNode::ptr cur=this;
	while(cur->getNext()!=nullptr) cur=cur->getNext();
	cur->getPrev()->setNext(nullptr);
	delete cur;
}

template<class T>
void saber::JsonNode<T>::popFront(){
	JsonNode::ptr cur=this;
	while(cur->getPrev()!=nullptr) cur=cur->getPrev();
	cur->getNext()->setPrev(nullptr);
	delete cur;
}
/**
 *class JsonObject functions
 */
/*template<class T>
std::stringstream saber::JsonObject<T>::toSString(){
		std::stringstream ss;
		ss<<"{\n";
		ss<<parseNode(this->getChild());
		ss<<"}\n";
		return ss;
}*/

/*template<class T>
std::string saber::JsonObject<T>::parseNode(JsonNode<T>* cur){
		std::stringstream ss;
		if(cur==nullptr) return "";
		JsonType::Type type=cur->getType();
		////parse one node
		switch(type){
				case JsonType::Type::Int:
				ss<<"\""<<cur->getKey()<<"\"";
				ss<<":";
				ss<<dynamic_cast<typename JsonInt<T>::ptr>(cur)->getData();
				ss<<",\n";
				break;
				
				case JsonType::Type::Double:
				ss<<"\""<<cur->getKey()<<"\"";
				ss<<":";
				ss<<dynamic_cast<typename JsonDouble<T>::ptr >(cur)->getData();
				ss<<",\n";
				break;

				case JsonType::Type::String:
				ss<<"\""<<cur->getKey()<<"\"";
				ss<<":";
				ss<<"\""<<dynamic_cast<typename JsonString<T>::ptr>(cur)->getData()<<"\"";
				ss<<",\n";
				break;
				
				case JsonType::Type::Array:{
					ss<<"\""<<cur->getKey()<<"\"";
					ss<<":";
					auto array=dynamic_cast<typename JsonArray<T>::ptr>(cur)->getData();
					ss<<"[";
					for(auto item:array){
					ss<<item<<",";
				} 
					ss<<"]";
					ss<<",\n";
										   }
					break;

				case JsonType::Type::Object:
					ss<<"\""<<cur->getKey()<<"\"";
					ss<<":{\n";
					ss<<parseNode(dynamic_cast<typename JsonObject<T>::ptr >(cur)->getData());
					ss<<"},\n";
					break;

				default:
					{SABER_LOG_DEBUG(SABER_LOG_ROOT)<<"Json Node should not be unknown type";}
					break;
		}

		////parse child
		ss<<parseNode(cur->getChild());
		////parse brother
		while(cur->getNext()!=nullptr){ 
				cur=cur->getNext();
				ss<<parseNode(cur);
		}
		return ss.str();
}*/

