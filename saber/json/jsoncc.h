#ifndef __SABER_JSONCC_H
#define __SABER_JSONCC_H
#include<iterator>
#include<stack>
#include<vector>
#include"../log.h"
#include<sstream>

/**
 *@brief json itertor class
 */
namespace jsoncc{
#define LOG_JSONCC\
		LOG_NEW("jsoncc")
		/**
		 *@brief class JsonType
		 */
		class JsonType{
				public:
						enum Type{
							NoType=0,
							Number=1,
							Object=2,
							Array=3
						};
		};


		/**
		 *@brief class JsonNode
		 */
		
		class JsonNode{
				public:
						////constrcutor and destructor
						JsonNode(){}
						JsonNode(const std::string &key,JsonType::Type type):m_key(key),m_type(type){}
						JsonNode(const std::string key,JsonType::Type type):m_key(key),m_type(type){}
						virtual  ~JsonNode(){}
						////getter and setter
						const JsonNode* getNext() const {return m_next;}
						const JsonNode* getPrev() const {return m_prev;}
						const JsonNode* getChild() const {return m_child;}
						void setNext(const JsonNode* next){m_next=next;}
						void setPrev(const JsonNode* prev){m_prev=prev;}
						void setChild(const JsonNode* child){m_child=child;
						}
						////virtual functions
						virtual std::string toString()=0;
						virtual void fromString(std::string str)=0;
						virtual void release()=0;
				protected:
					JsonNode* m_next=nullptr;
					JsonNode* m_prev=nullptr;
					JsonNode* m_child=nullptr;
					std::string m_key;
					JsonType::Type m_type=JsonType::Type::NoType;
		};

		/**
		 *@brief class JsonNumber
		 */
		template<class T>
		class JsonNumber:public JsonNode{
				public:
						typedef T value_type;
						////constructor
						JsonNumber(std::string &key,JsonType::Type type):JsonNode(key,type){}
						JsonNumber(std::string key,JsonType::Type type):JsonNode(key,type){}
						JsonNumber(std::string &key,JsonType::Type type,value_type val):JsonNode(key,type),m_value(val){}
						JsonNumber(std::string key,JsonType::Type type,value_type val):JsonNode(key,type),m_value(val){}
						////override
						std::string toString();
						void fromString(std::string str);
						void release()override{};
						////getter and setter
						const value_type getValue()const {return m_value;}
						void setValue(value_type val){m_value=val;}
				private:
						value_type m_value;

		};
	
		/**
		 *@brief class JsonArray
		 */
		template<class T>
		class JsonArray:public JsonNode{
				public:
						typedef T value_type;
						////constructor
						JsonArray(std::string &key,JsonType::Type type):JsonNode(key,type){}
						JsonArray(std::string key,JsonType::Type type):JsonNode(key,type){}
						void append(const value_type& x){m_value.push_back(x);}
						void remove(){m_value.pop_back();}
						////override
						std::string toString();
						void fromString(std::string str);
						void release()override{};

				private:
						std::vector<value_type> m_value;
		};	
		
		
		template<class T=JsonObject>
		class JsonArray:public JsonNode{
				public:
						typedef T value_type;
						////constructor
						JsonArray(std::string &key,JsonType::Type type):JsonNode(key,type){}
						JsonArray(std::string key,JsonType::Type type):JsonNode(key,type){}
						void append(const value_type& x){m_value.push_back(x);}
						void remove(){m_value.pop_back();}
						////override
						std::string toString();
						void fromString(std::string str);
						void release()override{};

				private:
						std::vector<value_type> m_value;
		};

	
		/**
		 *@brief class JsonObject
		 */
		class JsonObject:public JsonNode{
				public:
						typedef T value_type;		
						//// constructor
						JsonObject(std::string &key,JsonType::Type type):JsonNode(key,type){}
						JsonObject(std::string key,JsonType::Type type):JsonNode(key,type){}
						void append(JsonNode* node);
						void remove(std::string key);
						////overload functions
						std::string toString();
						void fromString(std::string str);
						void release()override{};
				private:
						JsonIter first=static_cast<JsonNode*>(this);
						JsonIter last=nullptr;

		};

	
		/**
		 *@brief class JsonIter
		 */
		template<class T=JsonNode>
		class JsonIter:public std::iterator<std::forward_iterator_tag,T>{		
		public:
				typedef T value_type;
				typedef T* node_ptr;
				typedef T self;
				////constrcutor
				JsonIter()=default;
				JsonIter(value_type* x);
				JsonIter(const JsonIter& x);
				JsonIter(JsonIter& x);
				////getter and setter
				const node_ptr getNode()const{return m_node;};
				void setNode(node_ptr ptr){m_node=ptr;};
				////overload operator
				self& operator=(const self& x);
				self& operator+(const int n);
				bool operator==(const self& x);
				bool operator!=(const self& x);
				self& operator++();
				self& operator++(int);
				self& operator--()=delete;
				self& operator--(int)=delete;
				self& operator*() const;
				node_ptr operator->()const;
		private:
				std::stack<node_ptr> m_stack;
				node_ptr m_node=nullptr;
		};
	/**
	 *@brief class JsonNumber functions
	 */
	template<class T>
	std::string JsonNumber::toString(){
		std::stringstream ss;
		ss<<"\""<<getKey()<<"\":";
		ss<<m_value;
		return ss.str();
	}

	template<class T>
	void fromString(std::string str){
		////"node":123 int
		////"node":3.14 double
		////"node":"hello world" string
		if(str[0]!='\"'){
			LOG_ERROR(LOG_JSONCC)<<"string format error!the head of string should be '\"' in string["<<str<<"]";
			throw std::invalid_argument(str);
		}
		int i;
		for(i=0;i<str.size();++i){
			if(str[i]=='\"'){
				pos=i;break;
			}
		}
		if(i+1<str.size()&&str[i+1]==':'){
			////get key value
			std::string key=str.substr(1,pos-1);
			m_key=key;
			std::stringstream ss;
			if(i+2<str.size()&&str[i+2]=='\"'){//string
				ss<<str.substr(i+3,str.size()-i-3);
				ss>>m_value;
			}else{//number
				ss<<str.substr(i+2,str.size()-i-2);
				ss>>m_value;
			}
		}else{
			LOG_ERROR(LOG_JSONCC)<<"string format error!;
			throw std::invalid_argument(str);
		}

	}

	/**
	 *@brief class JsonArray
	 */
	template<class T>
	std::string JsonArray::toString(){
		std::stringstream ss;
		ss<<"\""<<getKey()<<"\":[";
		for(int i=0;i<m_value.size();++i){
			ss<<m_value[i];
			if(i!=m_value.size()-1) ss<<",";
		}
		ss<<"]";
		return ss.str();
	}

	template<class T>
	void JsonArray::fromString(std::string str){
		if(str[0]!='\"'){
			LOG_ERROR(LOG_JSONCC)<<"string format error!the head of string should be '\"' in string["<<str<<"]";
			throw std::invalid_argument(str);
		}
		int i;
		for(i=0;i<str.size();++i){
			if(str[i]=='\"'){
				pos=i;break;
			}
		}
		if(i+2<str.size()&&str[i+1]==':'&&str[i+2]=='['){
			////get key value
			std::string key=str.substr(1,pos-1);
			m_key=key;
			std::string array=str.substr(i+3,str.size()-4-i);
			if(array[0]=='\"'){//string
				int lastpos=1;
				for(int j=1;j<array.size();++j){
					if(array[j]=='\"'){
						std::string temp=array.substr(lastpos,j-lastpos);
						m_value.push_back(temp);
						if(j+2<array.size()&&array[j+2]=='\"') 
								lastpos=j+2;
						else{
							LOG_ERROR(LOG_JSONCC)<<"string format error!;
							throw std::invalid_argument(str);
						}
					}
				}
			}else{//number
				int lastpos=1;
				for(int j=1;j<array.size();++j){
					if(array[j]==','){
						std::stringstream ss;
						std::string temp=array.substr(lastpos,j-lastpos);
						JsonArray::value_type num;
						ss<<temp;
						ss>>num;
						m_value.push_back(num);
						lastpos=j+1;
					}
				}
			}
		}else{
			LOG_ERROR(LOG_JSONCC)<<"string format error!;
			throw std::invalid_argument(str);
		}

	}
	/**
	 *@brief class JsonObject
	 */
		std::string JsonObject::toString(){
			std::stringstream ss;
			JsonNode* head=this->getChild();
			ss<<"{\n";
			while(head!=nullptr){
				ss<<head->toString();
				if(head->getNext()!=nullptr) ss<<",";
				head=head->getNext();
			}
			ss<<"\n}";
			return ss.str();
		}

		void JsonObject::fromString(std::string str){
				
		}

		void JsonObject::release()override{
			JsonNode* head=this->getChild();
			JsonNode* prev=head;
			while(head!=nullptr){
				head->release();
				LOG_INFO(LOG_JSONCC)<<"node "<<head->getKey()<<"released!";
				head=head->getNext();
				delete prev;
				prev=head;
			}
			delete prev;
		}

		void JsonObject::append(JsonNode* node){
			JsonNode* head=getChild();
			if(head==nullptr) setChild(node);
			else{
				while(head->getNext()!=nullptr) head=head->getNext();
				head->setNext(node);
			}
		}

		void JsonObject::remove(std::string key){

		}


	 /**
	  *@brief JsonIter constrcutor
	  */
	 template<class T=JsonNode>
	 JsonIter(value_type* x){
	 	m_node=x;
	 }

	 template<class T=JsonNode>
	 JsonIter(const JsonIter& x){
		m_node=x.m_node;
	 }

	 template<class T=JsonNode>
	 JsonIter(JsonIter& x){
	 	m_node=x.m_node;
	 }
	/**
	 *@brief JsonIter operator overload
	 */
	 template<class T=JsonNode>
	 typename JsonIter::self& operator=(const self& x){
		m_node=x.m_node;
		return *this;
	 } 

	 template<class T=JsonNode>
	 typename JsonIter::self& operator+(const int n){
	 	for(int i=0;i<n;++i) ++*this;
		return *this;
	 }
	
	 template<class T=JsonNode>
	 bool operator==(const self& x){
	 	return m_node->getKey()==x.m_node->getKey();
	 }

	 template<class T=JsonNode>
	 bool operator!=(const self& x){
	 	return m_node->getKey()!=x.m_node->getKey();
	 }

	 template<class T=JsonNode>
	 typename JsonIter::self& operator++(){
		if(m_node->getType()==JsonType::Type::Object){
			m_stack.push(m_node);
		}

		if(m_node->getType()==JsonType::Type::Array){
			
		}

		if(m_node->getNext()!=nullptr) m_node=m_node->getNext();
		else{
			node_ptr temp=m_stack.top();m_stack.pop();
			if(temp->getChild()!=nullptr) 
					m_node=temp->getChild();
		}
		return *this;
	 }	 
	 
	 template<class T=JsonNode>
	 typename JsonIter::self& operator++(int){
	 	JsonIter::self temp=*this;
		*this++;
		return temp;
	 }

	 template<class T=JsonNode>
	 typename JsonIter::self& operator*()const{
		 return &m_node;
	 }

	 template<class T=JsonNode>
	typename JsonIter::node_ptr operator->()const{
		return m_node;
	}

	 
};


#endif
