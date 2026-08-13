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
    public: 
    virtual ~CRtti();
    virtual const CRttiTypeId& GetTypeId() const;
    virtual bool IsType(const CRttiTypeId&) const;

    CRtti(const CRtti&);
    CRtti();
    CRtti& operator=(const CRtti&);
    
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
    
    public: 
    static const CRttiTypeId& TYPE_ID();
};

#endif