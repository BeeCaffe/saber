#ifndef __SABER_JSON_H
#define __SABER_JSON_H
#include<string>
#include<vector>
#include"../log.h"
#include<sstream>
#include<iostream>
namespace saber{
	class JsonType{
	public:
			enum Type{
				Unknow=0,
				Int=1,
				Double=2,
				String=3,
				Array=4,
				Object=5,
			};
	};	
	
	template<class T>
	class JsonNode{
	public:

		typedef	JsonNode<T>* ptr;

		typedef T ValueType;

		////constructor and destructor

		JsonNode(){}

		JsonNode(std::string key,JsonType::Type type):m_key(key),m_type(type){}

		virtual ~JsonNode(){};

		////getter and setter

		const JsonNode::ptr getNext() const {return m_next;}

		const JsonNode::ptr getPrev() const {return m_prev;}

		const JsonNode::ptr getChild() const {return m_child;}

		const JsonType::Type getType() const {return m_type;}

		void setNext(JsonNode::ptr next) {m_next=next;}

		void setPrev(JsonNode::ptr prev) {m_prev=prev;}

		void setChild(JsonNode::ptr child) {m_child=child;}

		void setType(JsonType::Type type) {m_type=type;}
		
		std::string getKey(){return m_key;}

		void setKey(std::string key){m_key=key;}
		////push and pop
		
		void pushBack(JsonNode<T>::ptr node);

		void pushFront(JsonNode<T>::ptr node);

		void popBack();

		void popFront();

		const bool isVisited(){return m_flag;}

		void setVisited(bool flag){m_flag=flag;}

	protected:

		JsonNode::ptr m_prev=nullptr;

		JsonNode::ptr m_next=nullptr;

		JsonNode::ptr m_child=nullptr;

		JsonType::Type m_type=JsonType::Type::Unknow;

		std::string m_key="root";

		bool m_flag=false;

	};

	class JsonInt:public JsonNode<int>{
	public:
			
			typedef JsonInt* ptr;
			
			JsonInt(std::string key,int32_t val):JsonNode<int>(key,JsonType::Type::Int),m_data(val){}


			~JsonInt(){}
			
			////getter and setter

			const int32_t getData()const {return m_data;}

			void setData(int32_t val){m_data=val;}

	private:

			int32_t m_data=0;
	};	
	
	class JsonDouble:public JsonNode<int>{
	public:

			typedef JsonDouble* ptr;

			JsonDouble(std::string key,double val):JsonNode<int>(key,JsonType::Type::Double),m_data(val){}

			~JsonDouble(){}

			////getter and setter
			const double getData() const {return m_data;}

			void setData(double val){m_data=val;}


	private:

			double m_data;
	};

	class JsonString:public JsonNode<int>{
	public:

			typedef JsonString* ptr;

			JsonString(std::string key,std::string val):JsonNode<int>(key,JsonType::Type::String),m_data(val){}


			////getter and setter
			const std::string getData() const {return m_data;}

			void setData(std::string val){m_data=val;}

	private:
			std::string m_data;
	};

	template<class T>
	class JsonArray:public JsonNode<T>{
	public:
			typedef JsonArray<T>* ptr;

			JsonArray(std::string key,std::vector<T> val):JsonNode<T>(key,JsonType::Type::Array),m_data(val){}

			~JsonArray(){}
			////getter and setter
			const std::vector<T>& getData() const {return m_data;}

			void setData(std::vector<T> val){m_data=val;}
	
	private:
			std::vector<T> m_data;
	};
	
	class JsonObject:public JsonNode<int>{
	public:

			typedef JsonObject* ptr;

			JsonObject(std::string key,JsonNode<int>* root):JsonNode<int>(key,JsonType::Type::Object),m_root(root){
			}
			
			////getter and setter
			JsonNode<int>* getData() {return m_root;}

			void setData(JsonNode<int>* val){m_root=val;}

			std::stringstream toSString(){
				std::stringstream ss;
				ss<<"{\n";
				ss<<parseNode(this->getData());
				ss<<"}\n";
				return ss;
			}

			std::string parseNode(JsonNode<int>* cur);
			
			void InitTree();
		
	private:

			JsonNode<int>* m_root;

	};


	/**
	 *class JsonObject functions
	 */
	std::string JsonObject::parseNode(JsonNode<int>* cur){
				std::stringstream ss;
				if(cur==nullptr) return "";
				JsonType::Type type=cur->getType();
				////parse one node
				switch(type){
						case JsonType::Type::Int:
						ss<<"\""<<cur->getKey()<<"\"";
						ss<<":";
						ss<<dynamic_cast<JsonInt::ptr>(cur)->getData();
						ss<<",\n";
						break;
						
						case JsonType::Type::Double:
						ss<<"\""<<cur->getKey()<<"\"";
						ss<<":";
						ss<<dynamic_cast<JsonDouble::ptr >(cur)->getData();
						ss<<",\n";
						break;

						case JsonType::Type::String:
						ss<<"\""<<cur->getKey()<<"\"";
						ss<<":";
						ss<<"\""<<dynamic_cast<JsonString::ptr>(cur)->getData()<<"\"";
						ss<<",\n";
						break;
						
						case JsonType::Type::Array:{
							ss<<"\""<<cur->getKey()<<"\"";
							ss<<":";
							auto array=dynamic_cast<typename JsonArray<JsonNode::ValueType >::ptr>(cur)->getData();
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
							ss<<":\n{\n";
							ss<<parseNode(dynamic_cast<JsonObject::ptr >(cur)->getData());
							ss<<"},\n";
							break;

						default:
							{SABER_LOG_DEBUG(SABER_LOG_ROOT)<<"Json Node should not be unknown type";}
							break;
				}

				////parse child
				if(!cur->getChild()->isVisited()) ss<<parseNode(cur->getChild());
				////parse brother
				while(cur->getNext()!=nullptr){ 
						if(!cur->isVisited()){
							cur=cur->getNext();
							ss<<parseNode(cur);
							cur->setVisited(true);
						}
				}
				return ss.str();

			}


};

void saber::JsonObject::InitTree(){
	
}

#endif
