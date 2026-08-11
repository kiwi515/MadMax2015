#ifndef COMPONENT_EVENT_H
#define COMPONENT_EVENT_H

#include <cstdint>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct TEventHandle {
    uint64_t dummy;
};

namespace NEvent {
    struct CEventData {
        uint64_t m_Type;
        const void* m_Pointers[5];
    };

    class CEventBase {
        public:
        TEventHandle* m_EventImpl;
        CEventBase();
        ~CEventBase();
    };

    class CBaseSendEvent {
        public:
        CEventBase* m_Impl;

        CBaseSendEvent();
        virtual ~CBaseSendEvent();

        void Send(const CEventData& data) const;
    };

    class CEventImpl {
        public:
    };

    class CEventHandler {
        private:
        uint16_t* m_SubscribedTo;

        public: virtual ~CEventHandler();
        private: CEventHandler(const NEvent::CEventHandler&);
        protected: CEventHandler();
        private: virtual void HandleEvent(const NEvent::CEventImpl*, const NEvent::CEventData&);
        private: void PushBack(int32_t, const uint16_t*);
        private: int32_t Find(const uint16_t&);
        private: bool Remove(const uint16_t&);
        private: const NEvent::CEventHandler& operator=(NEvent::CEventHandler&);
        public: void __local_vftable_ctor_closure();
        public: virtual void* __vecDelDtor(uint32_t);
    };

    template <typename... Args>
    class CEventWithArguments {
        public:

    };

    template <typename... Args>
    class CReceiveEvent : public CEventWithArguments<Args...> {
        public:
        static const uint64_t s_Type;
        NEvent::CEventBase m_Impl;
    };

    template <typename... Args>
    class CSendEvent : public NEvent::CBaseSendEvent {
        public:
        static const uint64_t s_Type = 0xFFFFFFFFFF;

        void Send() {
            NEvent::CEventData data;

            data.m_Type = s_Type;
            data.m_Pointers[0] = nullptr;
            data.m_Pointers[1] = nullptr;
            data.m_Pointers[2] = nullptr;
            data.m_Pointers[3] = nullptr;

            NEvent::CBaseSendEvent::Send(data);
        };
    };
};

#endif