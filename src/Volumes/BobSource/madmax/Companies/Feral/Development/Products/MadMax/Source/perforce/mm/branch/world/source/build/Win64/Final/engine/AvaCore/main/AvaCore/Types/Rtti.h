#ifndef ENGINE_RTTI_H
#define ENGINE_RTTI_H

class CRttiTypeId {
    uint32_t m_Hash;

    public:
    CRttiTypeId(const char*);
    CRttiTypeId(uint32_t hash) : m_Hash(hash) {};
    bool operator==(const CRttiTypeId&) const;
    bool operator!=(const CRttiTypeId&) const;
    bool operator<(const CRttiTypeId&) const;
    uint32_t id() const;
};

class CRtti {
    public: virtual ~CRtti();
    public: virtual const CRttiTypeId& GetTypeId() const;
    public: virtual bool IsType(const CRttiTypeId&) const;
    public: CRtti(const CRtti&);
    public: CRtti();
    public: CRtti& operator=(const CRtti&);
    public: void __local_vftable_ctor_closure();
    public: virtual void* __vecDelDtor(uint32_t);
    
    public: static const CRttiTypeId& TYPE_ID();
};

#endif