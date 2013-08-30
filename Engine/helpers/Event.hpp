#pragma once
#ifndef EVENT_HPP
#define EVENT_HPP


#include "EventHandler.hpp"
#include <cstddef>


/*
	(In MotherShip Class)
		EventManager1<int,int> shootHandler;

	(In Ships Classes)
		EventListener1<Ship_Type1,int,int> shootListener;
	(... and ...)
		Ship_Type1() : shootListener(this, &Ship_Type1::onShootCommand) {}

	(Later in Code...)
		MotherShipClass motherShip;
		Ship_Type1 ship1;
		Ship_Type2* ship2 = new Ship_Type2();

		motherShip.shootHandler.add(&ship1.shootListener);
		motherShip.shootHandler.add(&ship2->shootListener);
		motherShip.shootHandler.trigger(50);
		delete ship2; // Ka-boom !
		motherShip.shootHandler.trigger(100);
*/


template <typename ReturnT, typename ParamT1>
class EventListenerBase1
{
	public:
		virtual int add(Event1<ReturnT, ParamT1>* cppEvent) = 0;
		virtual bool remove() = 0;
};


template <typename ListenerT, typename ReturnT, typename ParamT1>
class EventListener1 : public EventListenerBase1<ReturnT, ParamT1>
{
	public:
		typedef ReturnT(ListenerT::*MemberPtr)(ParamT1);

		EventListener1(ListenerT* object, MemberPtr member) : m_object(object), m_member(member), m_cppEvent(nullptr) {}

		virtual ~EventListener1()
		{
			if (m_cppEvent != nullptr)
			{
				m_cppEvent->Detach(m_handle);
			}
		}

		int add(Event1<ReturnT, ParamT1>* cppEvent)
		{
			m_cppEvent = cppEvent;
			m_handle = m_cppEvent->Attach(m_object, m_member);

			return m_handle;
		}

		bool remove()
		{
			m_cppEvent = nullptr;

			return true;
		}

	private:
		ListenerT* m_object;
		MemberPtr m_member;
		int m_handle;
		Event1<ReturnT, ParamT1>* m_cppEvent;
};


template <typename ReturnT, typename ParamT1>
class EventManager1 : private Event1<ReturnT, ParamT1>
{
	public:
		typedef std::map<int, EventListenerBase1<ReturnT, ParamT1>*> SlotHandlersMap;

		virtual ~EventManager1()
		{
			for (auto it : m_slots)
			{
				if (this->isAttached(it.first))
				{
					it.second->remove();
				}
			}
		}

		bool add(EventListenerBase1<ReturnT, ParamT1>* slot)
		{
			int handle = slot->add(this);
			m_slots[handle] = slot;

			return true;
		}

		bool trigger(ParamT1 param1)
		{
			this->notify(param1);

			return true;
		}

		template <class CollectorT>
		typename CollectorT::return_type Trigger(ParamT1 param1, CollectorT& collect)
		{
			return notify(param1, collect);
		}

	private:
		SlotHandlersMap m_slots;
};


//--------------------


template <typename ReturnT, typename ParamT1, typename ParamT2>
class EventListenerBase2
{
	public:
		virtual int add(Event2<ReturnT, ParamT1, ParamT2>* cppEvent) = 0;
		virtual bool remove() = 0;
};


template <typename ListenerT, typename ReturnT, typename ParamT1, typename ParamT2>
class EventListener2 : public EventListenerBase2<ReturnT, ParamT1, ParamT2>
{
	public:
		typedef ReturnT(ListenerT::*MemberPtr)(ParamT1, ParamT2);

		EventListener2(ListenerT* object, MemberPtr member) : m_object(object), m_member(member), m_cppEvent(nullptr) {}

		virtual ~EventListener2()
		{
			if (m_cppEvent != nullptr)
			{
				m_cppEvent->detach(m_handle);
			}
		}

		int add(Event2<ReturnT, ParamT1, ParamT2>* cppEvent)
		{
			m_cppEvent = cppEvent;
			m_handle = m_cppEvent->attach(m_object, m_member);

			return m_handle;
		}

		bool remove()
		{
			m_cppEvent = nullptr;

			return true;
		}

	private:
		ListenerT* m_object;
		MemberPtr m_member;
		int m_handle;
		Event2<ReturnT, ParamT1, ParamT2>* m_cppEvent;
};


template <typename ReturnT, typename ParamT1, typename ParamT2>
class EventManager2 : private Event2<ReturnT, ParamT1, ParamT2>
{
	public:
		typedef std::map<int, EventListenerBase2<ReturnT, ParamT1, ParamT2>*> SlotHandlersMap;

		virtual ~EventManager2()
		{
			for (auto it : m_slots)
			{
				if (this->isAttached(it.first))
				{
					it.second->remove();
				}
			}
		}

		bool add(EventListenerBase2<ReturnT, ParamT1, ParamT2>* slot)
		{
			int handle = slot->add(this);
			m_slots[handle] = slot;

			return true;
		}

		bool trigger(ParamT1 param1, ParamT2 param2)
		{
			this->notify(param1, param2);

			return true;
		}

		template <class CollectorT>
		typename CollectorT::return_type Trigger(ParamT1 param1, ParamT2 param2, CollectorT& collect)
		{
			return notify(param1, param2, collect);
		}

	private:
		SlotHandlersMap m_slots;
};


//--------------------


template <typename ReturnT, typename ParamT1, typename ParamT2, typename ParamT3>
class EventListenerBase3
{
	public:
		virtual int add(Event3<ReturnT, ParamT1, ParamT2, ParamT3>* cppEvent) = 0;
		virtual bool remove() = 0;
};


template <typename ListenerT, typename ReturnT, typename ParamT1, typename ParamT2, typename ParamT3>
class EventListener3 : public EventListenerBase3<ReturnT, ParamT1, ParamT2, ParamT3>
{
	public:
		typedef ReturnT(ListenerT::*MemberPtr)(ParamT1, ParamT2, ParamT3);

		EventListener3(ListenerT* object, MemberPtr member) : m_object(object), m_member(member), m_cppEvent(nullptr) {}

		virtual ~EventListener3()
		{
			if (m_cppEvent != nullptr)
			{
				m_cppEvent->detach(m_handle);
			}
		}

		int add(Event3<ReturnT, ParamT1, ParamT2, ParamT3>* cppEvent)
		{
			m_cppEvent = cppEvent;
			m_handle = m_cppEvent->attach(m_object, m_member);

			return m_handle;
		}

		bool remove()
		{
			m_cppEvent = nullptr;

			return true;
		}

	private:
		ListenerT* m_object;
		MemberPtr m_member;
		int m_handle;
		Event3<ReturnT, ParamT1, ParamT2, ParamT3>* m_cppEvent;
};


template <typename ReturnT, typename ParamT1, typename ParamT2, typename ParamT3>
class EventManager3 : private Event3<ReturnT, ParamT1, ParamT2, ParamT3>
{
	public:
		typedef std::map<int, EventListenerBase3<ReturnT, ParamT1, ParamT2, ParamT3>*> SlotHandlersMap;

		virtual ~EventManager3()
		{
			for (auto it : m_slots)
			{
				if (this->isAttached(it.first))
				{
					it.second->remove();
				}
			}
		}

		bool add(EventListenerBase3<ReturnT, ParamT1, ParamT2, ParamT3>* slot)
		{
			int handle = slot->add(this);
			m_slots[handle] = slot;

			return true;
		}

		bool trigger(ParamT1 param1, ParamT2 param2, ParamT3 param3)
		{
			this->notify(param1, param2, param3);

			return true;
		}

		template <class CollectorT>
		typename CollectorT::return_type Trigger(ParamT1 param1, ParamT2 param2, ParamT3 param3, CollectorT& collect)
		{
			return notify(param1, param2, param3, collect);
		}

	private:
		SlotHandlersMap m_slots;
};


#endif // EVENT_HPP
