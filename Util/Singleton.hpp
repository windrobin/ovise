/*
 * singleton.hpp
 *
 *  Created on: 06.12.2010
 *      Author: gindele
 */

#ifndef SINGLETON_HPP_
#define SINGLETON_HPP_

#include <boost/utility.hpp>
#include <boost/thread/once.hpp>
#include <boost/scoped_ptr.hpp>


template<class T>
class Singleton : private boost::noncopyable {
public:

	static T& instance() {
		boost::call_once(init, flag);
		return *t;
	}

	static void init() {
		t.reset(new T());
	}

private:
	 static boost::scoped_ptr<T> t;
	 static boost::once_flag flag;
};

template<class T> boost::scoped_ptr<T> Singleton<T>::t(0);
template<class T> boost::once_flag Singleton<T>::flag = BOOST_ONCE_INIT;

#endif /* SINGLETON_HPP_ */
