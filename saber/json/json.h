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

	protected:

		JsonNode::ptr m_prev=nullptr;

		JsonNode::ptr m_next=nullptr;

		JsonNode::ptr m_child=nullptr;

		JsonType::Type m_type=JsonType::Type::Unknow;

		std::string m_key="root";

	};

	template<class T>
	class JsonInt:public JsonNode<T>{
	public:
			
			typedef JsonInt<T>* ptr;
			
			JsonInt(std::string key,int32_t val):JsonNode<int>(key,JsonType::Type::Int),m_data(val){}


			~JsonInt(){}
			
			////getter and setter

			const int32_t getData()const {return m_data;}

			void setData(int32_t val){m_data=val;}

	private:

			int32_t m_data=0;
	};	
	
	template<class T>
	class JsonDouble:public JsonNode<T>{
	public:

			typedef JsonDouble<T>* ptr;

			JsonDouble(std::string key,double val):JsonNode<T>(key,JsonType::Type::Double),m_data(val){}

			~JsonDouble(){}

			////getter and setter
			const double getData() const {return m_data;}

			void setData(double val){m_data=val;}


	private:

			double m_data;
	};

	template<class T>
	class JsonString:public JsonNode<T>{
	public:

			typedef JsonString<T>* ptr;

			JsonString(std::string key,std::string val):JsonNode<T>(key,JsonType::Type::String),m_data(val){}


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
	
	template<class T>
	class JsonObject:public JsonNode<T>{
	public:

			typedef JsonObject<T>* ptr;

			JsonObject(std::string key,JsonNode<T>* root):JsonNode<T>(key,JsonType::Type::Object),m_root(root){
			}
			
			////getter and setter
			const JsonNode<T>* getData() const {return m_root;}

			void setData(JsonNode<T>* val){m_root=val;}

			std::stringstream toSString(){
				std::stringstream ss;
				ss<<"{\n";
				ss<<parseNode(this->getChild());
				ss<<"}\n";
				return ss;
			}

			std::string parseNode(JsonNode<T>* node);

	private:

			JsonNode<T>* m_root;

	};


};
#endif
