#ifndef __SABER_CONFIG_H
#define __SABER_CONFIG_H
#include<memory>
#include<sstream>
#include<string>
#include<boost/lexical_cast.hpp>
#include"log.h"
#include<map>

namespace saber{
	#define LOG_CONF\
			LOG_NEW("ConfigLog")

	class ConfigVarBase{
	public:
		typedef std::shared_ptr<ConfigVarBase> ptr;
		ConfigVarBase(const std::string &name,const std::string &description=""):m_name(name),
	  m_description(description){
	  }

		virtual ~ConfigVarBase(){}

		const std::string getName()const {return m_name;}

		const std::string getDescription() const {return m_description;}

		void setName(const std::string& name){m_name=name;}

		void setDescription(const std::string& des){m_description=des;}

		virtual std::string toString()=0;

		virtual bool fromString(const std::string& val)=0;
	protected:
		std::string m_name;
		std::string m_description;

	};

	template<class T>
	class ConfigVar:public ConfigVarBase{
	public:
			typedef std::shared_ptr<ConfigVar> ptr;
			
			/**
			 *@brief constructor
			 */
			ConfigVar(const std::string &name,
					  const T& default_val,
					  const std::string &description=""):
					ConfigVarBase(name,description),
					m_val(default_val){}

			/**
			 *@brief to string
			 */
			std::string toString() override {
				try{
					return boost::lexical_cast<std::string>(m_val);	
				}catch(std::exception &e){
					LOG_ERROR(LOG_CONF)<<"ConfigVar::toString exception"
							<<e.what()<<"convert:"<<typeid(m_val).name()
							<<"to string";
				}
				return "";
			}

			/**
			 *@brief from string
			 */
			bool fromString(const std::string& val){
				try{
					m_val=boost::lexical_cast<T>(val);
				}catch(std::exception &e){
					LOG_ERROR(LOG_CONF)<<"ConfigVar::toString exception"
							<<e.what()<<"convert string to "
							<<typeid(m_val).name();
				}
				return false;
			}

			/**
			 *@brief getter and setter
			 */
			const T getValue() const {return m_val;}
			void setValue(const T& val){m_val=val;}
	private:
		 T m_val;
	};

	/**
	 *@brief class Config , the manage class of configure
	 */
	class Config{
	public:
			typedef std::shared_ptr<Config> ptr;

			typedef std::map<std::string,ConfigVarBase::ptr> ConfigVarMap;

	private:

			static std::map<std::string,ConfigVarBase::ptr> s_datas;

	public:
			/**
			 *@brief LookUp 
			 */
			template<class T>
			static typename ConfigVar<T>::ptr Lookup(const std::string& name,
							const T& default_value,const std::string &description=""){
				auto temp=Lookup<T>(name);
				if(temp){
					LOG_ERROR(LOG_CONF)<<"lookup name="<<name<<"exists";
					return temp;
				}
				if(name.find_first_not_of("aqwertyuiopasdfghjklzxcvbnmaQWERTYUIOPASDFGHJKLZXCVBNM._0123456789")!=std::string::npos){
					LOG_ERROR(LOG_CONF)<<"Look up name invalid"<<name;
					throw std::invalid_argument(name);
				}
				typename ConfigVar<T>::ptr v(new ConfigVar<T>(name,default_value,description));
				s_datas[name]=v;
			}
			
			/**
			 *@brief LookUp
			 */
			template<class T>
			static typename ConfigVar<T>::ptr Lookup(const std::string &name){
				auto iter=s_datas.find(name);
				if(iter==s_datas.end()) return nullptr;
				return std::dynamic_pointer_cast<ConfigVar<T>>(iter->second);
			}
	};
	
};
#endif
