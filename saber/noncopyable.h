#ifndef SABER_NONCOPYABLE_H
#define SABER_NONCOPYABLE_H
class Noncopyable{
protected:
		Noncopyable(){}
		~Noncopyable(){}
private:
		Noncopyable(const Noncopyable& instance);
		Noncopyable& operator=(const Noncopyable instance);
};
#endif
