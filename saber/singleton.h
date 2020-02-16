#ifndef __SABER__SINGLETION_H
#define __SABER__SINGLETION_H
namespace saber{

template<class T,class X=void,int N=0>

class Singleton{
	public:
			static T* Instance(){
				static T v;
				return &v;
			}
	private:

};

template<class T,class X=void,int N=0>
class SingletonPtr{
public:
		
		static std::shared_ptr<T> Instance(){
				static std::shared_ptr<T> v(new T);
				return v;
		}
private:
};
};
#endif
