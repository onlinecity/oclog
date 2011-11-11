/*
 * Copy/pasted from:
 * http://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html
 */

#ifndef SINKQUEUE_H_
#define SINKQUEUE_H_

#include <queue>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

namespace oc {
namespace log {

/**
 * SinkQueue is a threadsafe queue. It encapsulates the std::queue with mutex locks.
 */
template<typename T>
class SinkQueue
{
private:
	std::queue<T> the_queue;
	mutable boost::mutex the_mutex;
	boost::condition_variable the_condition_variable;

public:
	/**
	 * Push an element to the queue.
	 * @param data
	 */
	void push(T const& data)
	{
		boost::mutex::scoped_lock lock(the_mutex);
		the_queue.push(data);
		lock.unlock();
		the_condition_variable.notify_one();
	}

	/**
	 * @return true if the queue is empty
	 */
	bool empty() const
	{
		boost::mutex::scoped_lock lock(the_mutex);
		return the_queue.empty();
	}

	/**
	 * Tries to pop the front of the queue. If successful the front is popped and true is returned.
	 * @param popped_value
	 * @return
	 */
	bool try_pop(T& popped_value)
	{
		boost::mutex::scoped_lock lock(the_mutex);
		if (the_queue.empty()) {
			return false;
		}

		popped_value = the_queue.front();
		the_queue.pop();
		return true;
	}

	/**
	 * Blocks until the front element for the queue can be popped.
	 * @param popped_value
	 */
	void wait_and_pop(T& popped_value)
	{
		boost::mutex::scoped_lock lock(the_mutex);
		while (the_queue.empty()) {
			the_condition_variable.wait(lock);
		}

		popped_value = the_queue.front();
		the_queue.pop();
	}

};
} // log
} // oc

#endif /* SINKQUEUE_H_ */
