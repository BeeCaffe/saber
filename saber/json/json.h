#ifndef __SABER_JSON_H
#define __SABER_JSON_H
#include<string>
#include<vector>
#include"../log.h"
#include<sstream>
#include<iostream>
#include<queue>
#include<stack>
#include<set>
#include<fstream>
namespace saber{
	#define LOG_JSON\
		LOG_NEW("JsonLog")
    class JsonObject;
	class JsonType{
	public:
			enum Type{
				Unknow=0,
				Int=1,
				Double=2,
				String=3,
				IntArray=4,
				StringArray=5,
				DoubleArray=6,
				ObjectArray=7,
				Object=8,
			};
	};	

	class JsonNode{
	public:

		typedef	JsonNode* ptr;

		////constructor and destructor

		JsonNode(){}

		JsonNode(std::string key,JsonType::Type type):m_key(key),m_type(type){}

		virtual ~JsonNode(){};

		////getter and setter

		const JsonNode::ptr getNext() const {return m_next;}

		const JsonNode::ptr getPrev() const {return m_prev;}

		const JsonType::Type getType() const {return m_type;}

		void setNext(JsonNode::ptr next) {m_next=next;}

		void setPrev(JsonNode::ptr prev) {m_prev=prev;}

		void setType(JsonType::Type type) {m_type=type;}
		
		std::string getKey(){return m_key;}

		void setKey(std::string key){m_key=key;}
		////push and pop
		
		virtual void pushBack(JsonNode::ptr node){};

		virtual void pushFront(JsonNode::ptr node){};

		virtual void popBack(){};

		virtual  void popFront(){};

		const bool isVisited() const {return m_flag;}

		virtual void setVisited(bool flag){m_flag=flag;}

		virtual std::string toString()=0;

		virtual void fromString(std::string &str)=0;

		virtual JsonNode* getChild(){};

		virtual void setChild(){};
	protected:

		JsonNode::ptr m_prev=nullptr;

		JsonNode::ptr m_next=nullptr;

		JsonNode* m_child=nullptr;

		JsonType::Type m_type=JsonType::Type::Unknow;

		std::string m_key="root";

		bool m_flag=false;

	};

	class JsonInt:public JsonNode{
	public:
			
			typedef JsonInt* ptr;
			
			JsonInt(std::string key,int32_t val):JsonNode(key,JsonType::Type::Int),m_data(val){}

			JsonInt(std::string key):JsonNode(key,JsonType::Type::Int){}

			~JsonInt(){}
			
			////getter and setter

			const int32_t getData()const {return m_data;}

			void setData(int32_t val){m_data=val;}

			std::string toString() override;

			void fromString(std::string &str) override;

	private:

			int32_t m_data=0;
	};	
	
	class JsonDouble:public JsonNode{
	public:

			typedef JsonDouble* ptr;

			JsonDouble(std::string key,double val):JsonNode(key,JsonType::Type::Double),m_data(val){}

			JsonDouble(std::string key):JsonNode(key,JsonType::Type::Double){}

			~JsonDouble(){}

			////getter and setter
			const double getData() const {return m_data;}

			void setData(double val){m_data=val;}

			std::string toString() override;

			void fromString(std::string &str) override;


	private:

			double m_data;
	};

	class JsonString:public JsonNode{
	public:

			typedef JsonString* ptr;

			JsonString(std::string key,std::string val):JsonNode(key,JsonType::Type::String),m_data(val){}

			JsonString(std::string key):JsonNode(key,JsonType::Type::String){}
			////getter and setter
			const std::string getData() const {return m_data;}

			void setData(std::string val){m_data=val;}
			std::string toString() override;

			void fromString(std::string &str) override;


	private:
			std::string m_data;
	};

	class JsonIntArray:public JsonNode{
	public:
			typedef JsonIntArray* ptr;

			JsonIntArray(std::string key,std::vector<int> array):JsonNode(key,JsonType::Type::IntArray),m_data(array)
			{}

			JsonIntArray(std::string key):JsonNode(key,JsonType::Type::IntArray){}

			~JsonIntArray(){}
			////getter and setter

			std::vector<int32_t>& getData(){return m_data;}

			void setData(std::vector<int32_t>& array){m_data=array;}

			std::string toString();

			void fromString(std::string &str);

    private:

	    std::vector<int32_t> m_data;
	};

    class JsonDoubleArray:public JsonNode{
    public:
        typedef JsonDoubleArray* ptr;

        JsonDoubleArray(std::string key,std::vector<double> array):JsonNode(key,JsonType::Type::DoubleArray),m_data(array)
        {}

		JsonDoubleArray(std::string key):JsonNode(key,JsonType::Type::DoubleArray){}

        ~JsonDoubleArray(){}
        ////getter and setter

        std::vector<double >& getData(){return m_data;}

        void setData(std::vector<double >& array){m_data=array;}			
		std::string toString();

		void fromString(std::string &str);

    private:

        std::vector<double > m_data;
    };

    class JsonStringArray:public JsonNode{
    public:
        typedef JsonStringArray* ptr;

        JsonStringArray(std::string key,std::vector<std::string> array):JsonNode(key,JsonType::Type::StringArray),m_data(array)
        {}

		JsonStringArray(std::string key):JsonNode(key,JsonType::Type::StringArray){}

        ~JsonStringArray(){}
        ////getter and setter

        std::vector<std::string>& getData(){return m_data;}

        void setData(std::vector<std::string>& array){m_data=array;}
    			
		std::string toString();

			
		void fromString(std::string &str);

	private:

        std::vector<std::string> m_data;
    };

    class JsonObjectArray:public JsonNode{
    public:
        typedef JsonObjectArray* ptr;

        JsonObjectArray(std::string key,std::vector<JsonObject*> array):JsonNode(key,JsonType::Type::ObjectArray),m_data(array)
        {}

		JsonObjectArray(std::string key):JsonNode(key,JsonType::ObjectArray){}

        ~JsonObjectArray(){}
        ////getter and setter

        std::vector<JsonObject*>& getData(){return m_data;}

        void setData(std::vector<JsonObject*>& array){m_data=array;}	

		void add(JsonObject* data){m_data.push_back(data);}

		void del(){m_data.pop_back();}
		
		std::string toString();

		void fromString(std::string &str);

		void setVisited(bool flag) override;

	public:
		friend class JsonTree;
    private:

        std::vector<JsonObject*> m_data;
    };

	class JsonObject:public JsonNode{
	public:
			typedef JsonObject* ptr;

			JsonObject(std::string key):JsonNode(key,JsonType::Type::Object){}
			JsonObject():JsonNode("",JsonType::Type::Object){}

			std::string toString() override;

			void fromString(std::string &str) override;

			std::string parseObject(JsonObject* cur);

			JsonNode* getChild();

			void setChild(JsonNode* child);
			
			void pushBack(JsonNode::ptr node) override;

			void popBack() override;
	};

	/**
	 *@brief class JsonTree
	 */
	class JsonTree{
		public:
				typedef JsonTree* ptr;
				/**
				 *@brief constructor
				 *@param [root] the root JsonObejct
				 */
				JsonTree(JsonObject::ptr root):m_root(root){
				}
				
				JsonTree(){}

				void initTree();

				~JsonTree(){};

				const JsonObject::ptr getRoot() const {return m_root;}

				void setRoot(JsonObject::ptr root) {m_root=root;}

				std::string toString();

				void fromString(std::string &str);

				void fromFile(const std::string &file);
				
				bool checkString(std::string &str);

				void clearSpace(std::string &str);

				JsonNode* getNode(std::string &key);
				/**
				 *@brief an assist function for toString(),used to travel
				 *Json Tree.
				 */
				static std::string parse(JsonNode::ptr root);
				
				/**
				 *@brief release the whole json tree,delete the pointer
				 */
				void release();

				void releaseObject(JsonObject* root);

				void sharedRelease(JsonNode*);

				void addNode(JsonNode* node);

				int delNode(std::string key);

				void countKey();

				const std::string getName() const {return m_name;}

				void setName(std::string name){m_name=name;}

		private:

			JsonObject::ptr m_root=nullptr;

			std::map<std::string,int> m_map;

			std::string m_name;
	};
};


#endif
