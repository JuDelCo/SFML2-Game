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
        MotherShipClass MotherShip;
        Ship_Type1 Ship_1;
        Ship_Type2* Ship_2 = new Ship_Type2();

        MotherShip.shootHandler.add(&Ship_1.shootListener);
        MotherShip.shootHandler.add(&Ship_2->shootListener);
        MotherShip.shootHandler.trigger(50);
        delete Ship_2; // Ka-boom !
        MotherShip.shootHandler.trigger(100);

    //--------------------------------------

    #include <algorithm>

    class ResponseAccumulator
    {
    public:
        typedef int return_type;

        template <typename iterator>
        int operator () (iterator begin, iterator end)
        {
            int sum = 0;
            for(iterator it=begin; it!=end; ++it)
            {
                sum+=*it;
            }

            return sum;
        }
    };
*/


template <typename ReturnT, typename ParamT1>
class EventListenerBase1
{
	public:
		virtual int Add(Event1<ReturnT, ParamT1>* cpp_event) = 0;
		virtual bool Remove() = 0;
};


template <typename ListenerT, typename ReturnT, typename ParamT1>
class EventListener1 : public EventListenerBase1<ReturnT, ParamT1>
{
	public:
		typedef ReturnT(ListenerT::*PtrMember)(ParamT1);

		EventListener1(ListenerT* object, PtrMember member) : m_object(object), m_member(member), m_cpp_event(NULL) {}

		virtual ~EventListener1()
		{
			if(m_cpp_event != NULL)
			{
				m_cpp_event->Detach(m_handle);
			}
		}

		int Add(Event1<ReturnT, ParamT1>* cpp_event)
		{
			m_cpp_event = cpp_event;
			m_handle = m_cpp_event->Attach(m_object, m_member);

			return m_handle;
		}

		bool Remove()
		{
			m_cpp_event = NULL;

			return true;
		}

	private:
		ListenerT* m_object;
		PtrMember m_member;
		int m_handle;
		Event1<ReturnT, ParamT1>* m_cpp_event;
};


template <typename ReturnT, typename ParamT1>
class EventManager1 : private Event1<ReturnT, ParamT1>
{
	public:
		typedef std::map<int, EventListenerBase1<ReturnT, ParamT1>* > SlotHandlersMap;

		virtual ~EventManager1()
		{
			typename SlotHandlersMap::iterator it = m_slots.begin();

			for(; it != m_slots.end(); ++it)
			{
				if(this->is_attached(it->first))
				{
					it->second->Remove();
				}
			}
		}

		bool Add(EventListenerBase1<ReturnT, ParamT1>* slot)
		{
			int handle = slot->Add(this);
			m_slots[handle] = slot;

			return true;
		}

		bool Trigger(ParamT1 param1)
		{
			this->Notify(param1);

			return true;
		}

		template <class CollectorT>
		typename CollectorT::return_type Trigger(ParamT1 param1, CollectorT& collect)
		{
			return Notify(param1, collect);
		}

	private:
		SlotHandlersMap m_slots;
};


//--------------------


template <typename ReturnT, typename ParamT1, typename ParamT2>
class EventListenerBase2
{
	public:
		virtual int Add(Event2<ReturnT, ParamT1, ParamT2>* cpp_event) = 0;
		virtual bool Remove() = 0;
};


template <typename ListenerT, typename ReturnT, typename ParamT1, typename ParamT2>
class EventListener2 : public EventListenerBase2<ReturnT, ParamT1, ParamT2>
{
	public:
		typedef ReturnT(ListenerT::*PtrMember)(ParamT1, ParamT2);

		EventListener2(ListenerT* object, PtrMember member) : m_object(object), m_member(member), m_cpp_event(NULL) {}

		virtual ~EventListener2()
		{
			if(m_cpp_event != NULL)
			{
				m_cpp_event->Detach(m_handle);
			}
		}

		int Add(Event2<ReturnT, ParamT1, ParamT2>* cpp_event)
		{
			m_cpp_event = cpp_event;
			m_handle = m_cpp_event->Attach(m_object, m_member);

			return m_handle;
		}

		bool Remove()
		{
			m_cpp_event = NULL;

			return true;
		}

	private:
		ListenerT* m_object;
		PtrMember m_member;
		int m_handle;
		Event2<ReturnT, ParamT1, ParamT2>* m_cpp_event;
};


template <typename ReturnT, typename ParamT1, typename ParamT2>
class EventManager2 : private Event2<ReturnT, ParamT1, ParamT2>
{
	public:
		typedef std::map<int, EventListenerBase2<ReturnT, ParamT1, ParamT2>* > SlotHandlersMap;

		virtual ~EventManager2()
		{
			typename SlotHandlersMap::iterator it = m_slots.begin();

			for(; it != m_slots.end(); ++it)
			{
				if(this->is_attached(it->first))
				{
					it->second->Remove();
				}
			}
		}

		bool Add(EventListenerBase2<ReturnT, ParamT1, ParamT2>* slot)
		{
			int handle = slot->Add(this);
			m_slots[handle] = slot;

			return true;
		}

		bool Trigger(ParamT1 param1, ParamT2 param2)
		{
			this->Notify(param1, param2);

			return true;
		}

		template <class CollectorT>
		typename CollectorT::return_type Trigger(ParamT1 param1, ParamT2 param2, CollectorT& collect)
		{
			return Notify(param1, param2, collect);
		}

	private:
		SlotHandlersMap m_slots;
};


//--------------------


template <typename ReturnT, typename ParamT1, typename ParamT2, typename ParamT3>
class EventListenerBase3
{
	public:
		virtual int Add(Event3<ReturnT, ParamT1, ParamT2, ParamT3>* cpp_event) = 0;
		virtual bool Remove() = 0;
};


template <typename ListenerT, typename ReturnT, typename ParamT1, typename ParamT2, typename ParamT3>
class EventListener3 : public EventListenerBase3<ReturnT, ParamT1, ParamT2, ParamT3>
{
	public:
		typedef ReturnT(ListenerT::*PtrMember)(ParamT1, ParamT2, ParamT3);

		EventListener3(ListenerT* object, PtrMember member) : m_object(object), m_member(member), m_cpp_event(NULL) {}

		virtual ~EventListener3()
		{
			if(m_cpp_event != NULL)
			{
				m_cpp_event->Detach(m_handle);
			}
		}

		int Add(Event3<ReturnT, ParamT1, ParamT2, ParamT3>* cpp_event)
		{
			m_cpp_event = cpp_event;
			m_handle = m_cpp_event->Attach(m_object, m_member);

			return m_handle;
		}

		bool Remove()
		{
			m_cpp_event = NULL;

			return true;
		}

	private:
		ListenerT* m_object;
		PtrMember m_member;
		int m_handle;
		Event3<ReturnT, ParamT1, ParamT2, ParamT3>* m_cpp_event;
};


template <typename ReturnT, typename ParamT1, typename ParamT2, typename ParamT3>
class EventManager3 : private Event3<ReturnT, ParamT1, ParamT2, ParamT3>
{
	public:
		typedef std::map<int, EventListenerBase3<ReturnT, ParamT1, ParamT2, ParamT3>* > SlotHandlersMap;

		virtual ~EventManager3()
		{
			typename SlotHandlersMap::iterator it = m_slots.begin();

			for(; it != m_slots.end(); ++it)
			{
				if(this->is_attached(it->first))
				{
					it->second->Remove();
				}
			}
		}

		bool Add(EventListenerBase3<ReturnT, ParamT1, ParamT2, ParamT3>* slot)
		{
			int handle = slot->Add(this);
			m_slots[handle] = slot;

			return true;
		}

		bool Trigger(ParamT1 param1, ParamT2 param2, ParamT3 param3)
		{
			this->Notify(param1, param2, param3);

			return true;
		}

		template <class CollectorT>
		typename CollectorT::return_type Trigger(ParamT1 param1, ParamT2 param2, ParamT3 param3, CollectorT& collect)
		{
			return Notify(param1, param2, param3, collect);
		}

	private:
		SlotHandlersMap m_slots;
};


#endif // EVENT_HPP
