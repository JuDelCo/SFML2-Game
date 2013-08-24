#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP


#include <map>
#include <vector>


template <typename ReturnT, typename ParamT1>
class EventHandlerBase1
{
	public:
		virtual ~EventHandlerBase1() {};
		virtual ReturnT notify(ParamT1 param1) = 0;
};


template <typename ListenerT, typename ReturnT, typename ParamT1>
class EventHandler1 : public EventHandlerBase1<ReturnT, ParamT1>
{
	private:
		typedef ReturnT(ListenerT::*MemberPtr)(ParamT1);

		ListenerT* m_object;
		MemberPtr m_member;

	public:
		EventHandler1(ListenerT* object, MemberPtr member) : m_object(object), m_member(member) {}

		ReturnT notify(ParamT1 param1)
		{
			return (m_object->*m_member)(param1);
		}
};


template <typename ReturnT, typename ParamT1>
class Event1
{
	private:
		typedef std::map<int, EventHandlerBase1<ReturnT, ParamT1>* > HandlersMap;
		HandlersMap m_handlers;
		int m_count;

	public:
		Event1() : m_count(0) {}

		virtual ~Event1()
		{
			for (typename HandlersMap::iterator it = m_handlers.begin(); it != m_handlers.end(); ++it)
			{
				delete it->second;
			}
		}

		template <typename ListenerT>
		int attach(ListenerT* object, ReturnT(ListenerT::*member)(ParamT1))
		{
			typedef ReturnT(ListenerT::*MemberPtr)(ParamT1);
			m_handlers[m_count] = (new EventHandler1<ListenerT, ReturnT, ParamT1>(object, member));
			++m_count;

			return m_count - 1;
		}

		bool detach(int id)
		{
			typename HandlersMap::iterator it = m_handlers.find(id);

			if (it == m_handlers.end())
			{
				return false;
			}

			delete it->second;
			m_handlers.erase(it);

			return true;
		}

		bool isAttached(int id)
		{
			return (m_handlers.find(id) != m_handlers.end());
		}

		void notify(ParamT1 param1)
		{
			for (typename HandlersMap::iterator it = m_handlers.begin(); it != m_handlers.end(); ++it)
			{
				it->second->notify(param1);
			}
		}

		template <typename CollectorT>
		typename CollectorT::return_type notify(ParamT1 param1, CollectorT& collect)
		{
			std::vector<ReturnT> results;

			for (typename HandlersMap::iterator it = m_handlers.begin(); it != m_handlers.end(); ++it)
			{
				results.push_back(it->second->notify(param1));
			}

			return collect(results.begin(), results.end());
		}
};


//--------------------


template <typename ReturnT, typename ParamT1, typename ParamT2>
class EventHandlerBase2
{
	public:
		virtual ~EventHandlerBase2() {};
		virtual ReturnT notify(ParamT1 param1, ParamT2 param2) = 0;
};


template <typename ListenerT, typename ReturnT, typename ParamT1, typename ParamT2>
class EventHandler2 : public EventHandlerBase2<ReturnT, ParamT1, ParamT2>
{
	private:
		typedef ReturnT(ListenerT::*MemberPtr)(ParamT1, ParamT2);

		ListenerT* m_object;
		MemberPtr m_member;

	public:
		EventHandler2(ListenerT* object, MemberPtr member) : m_object(object), m_member(member) {}

		ReturnT notify(ParamT1 param1, ParamT2 param2)
		{
			return (m_object->*m_member)(param1, param2);
		}
};


template <typename ReturnT, typename ParamT1, typename ParamT2>
class Event2
{
	private:
		typedef std::map<int, EventHandlerBase2<ReturnT, ParamT1, ParamT2>* > HandlersMap;
		HandlersMap m_handlers;
		int m_count;

	public:
		Event2() : m_count(0) {}

		virtual ~Event2()
		{
			for (typename HandlersMap::iterator it = m_handlers.begin(); it != m_handlers.end(); ++it)
			{
				delete it->second;
			}
		}

		template <typename ListenerT>
		int attach(ListenerT* object, ReturnT(ListenerT::*member)(ParamT1, ParamT2))
		{
			typedef ReturnT(ListenerT::*MemberPtr)(ParamT1, ParamT2);
			m_handlers[m_count] = (new EventHandler2<ListenerT, ReturnT, ParamT1, ParamT2>(object, member));
			++m_count;

			return m_count - 1;
		}

		bool detach(int id)
		{
			typename HandlersMap::iterator it = m_handlers.find(id);

			if (it == m_handlers.end())
			{
				return false;
			}

			delete it->second;
			m_handlers.erase(it);

			return true;
		}

		bool isAttached(int id)
		{
			return (m_handlers.find(id) != m_handlers.end());
		}

		void notify(ParamT1 param1, ParamT2 param2)
		{
			for (typename HandlersMap::iterator it = m_handlers.begin(); it != m_handlers.end(); ++it)
			{
				it->second->notify(param1, param2);
			}
		}

		template <typename CollectorT>
		typename CollectorT::return_type notify(ParamT1 param1, ParamT2 param2, CollectorT& collect)
		{
			std::vector<ReturnT> results;

			for (typename HandlersMap::iterator it = m_handlers.begin(); it != m_handlers.end(); ++it)
			{
				results.push_back(it->second->notify(param1, param2));
			}

			return collect(results.begin(), results.end());
		}
};


//--------------------


template <typename ReturnT, typename ParamT1, typename ParamT2, typename ParamT3>
class EventHandlerBase3
{
	public:
		virtual ~EventHandlerBase3() {};
		virtual ReturnT notify(ParamT1 param1, ParamT2 param2, ParamT3 param3) = 0;
};


template <typename ListenerT, typename ReturnT, typename ParamT1, typename ParamT2, typename ParamT3>
class EventHandler3 : public EventHandlerBase3<ReturnT, ParamT1, ParamT2, ParamT3>
{
	private:
		typedef ReturnT(ListenerT::*MemberPtr)(ParamT1, ParamT2, ParamT3);

		ListenerT* m_object;
		MemberPtr m_member;

	public:
		EventHandler3(ListenerT* object, MemberPtr member) : m_object(object), m_member(member) {}

		ReturnT notify(ParamT1 param1, ParamT2 param2, ParamT3 param3)
		{
			return (m_object->*m_member)(param1, param2, param3);
		}
};


template <typename ReturnT, typename ParamT1, typename ParamT2, typename ParamT3>
class Event3
{
	private:
		typedef std::map<int, EventHandlerBase3<ReturnT, ParamT1, ParamT2, ParamT3>* > HandlersMap;
		HandlersMap m_handlers;
		int m_count;

	public:
		Event3() : m_count(0) {}

		virtual ~Event3()
		{
			for (typename HandlersMap::iterator it = m_handlers.begin(); it != m_handlers.end(); ++it)
			{
				delete it->second;
			}
		}

		template <typename ListenerT>
		int attach(ListenerT* object, ReturnT(ListenerT::*member)(ParamT1, ParamT2, ParamT3))
		{
			typedef ReturnT(ListenerT::*MemberPtr)(ParamT1, ParamT2, ParamT3);
			m_handlers[m_count] = (new EventHandler3<ListenerT, ReturnT, ParamT1, ParamT2, ParamT3>(object, member));
			++m_count;

			return m_count - 1;
		}

		bool detach(int id)
		{
			typename HandlersMap::iterator it = m_handlers.find(id);

			if (it == m_handlers.end())
			{
				return false;
			}

			delete it->second;
			m_handlers.erase(it);

			return true;
		}

		bool isAttached(int id)
		{
			return (m_handlers.find(id) != m_handlers.end());
		}

		void notify(ParamT1 param1, ParamT2 param2, ParamT3 param3)
		{
			for (typename HandlersMap::iterator it = m_handlers.begin(); it != m_handlers.end(); ++it)
			{
				it->second->notify(param1, param2, param3);
			}
		}

		template <typename CollectorT>
		typename CollectorT::return_type notify(ParamT1 param1, ParamT2 param2, ParamT3 param3, CollectorT& collect)
		{
			std::vector<ReturnT> results;

			for (typename HandlersMap::iterator it = m_handlers.begin(); it != m_handlers.end(); ++it)
			{
				results.push_back(it->second->notify(param1, param2, param3));
			}

			return collect(results.begin(), results.end());
		}
};


#endif // EVENT_HANDLER_HPP
