// #include <cstdint>
// #include <array>
// #include <list>
// #include <map>
// #include <memory>
// #include <string>
// #include <unordered_map>
// #include <utility>
// #include <vector>

// class CGameObject : public CRtti {
//     public:
//     virtual unsigned long long GetObjectID() const;
//     virtual void PostInit();

//     CGameObject();
//     virtual ~CGameObject();
// };

// class CEventHandler {
//     public:
//     CEventHandler();
//     virtual ~CEventHandler();
// };

// class CSaveInfo {
//     public:
//     std::uint32_t m_WorldSaveIndex;

//     CSaveInfo();
//     virtual ~CSaveInfo();
// };

// class CMatrix4f {
//     public:
//     char padding[64];

//     static CMatrix4f IDENTITY;
// };

// class CDataSaveHandler {
//     public:
//     void* AllocateRAWData(unsigned long long objectID, unsigned long size);
//     void* GetAllocatedRAWDataPtr(unsigned long long objectID) const;
// };

// class CSaveBitStorage {
//     std::uint64_t* m_Hashes;
//     std::uint64_t* m_Bits;
//     std::uint32_t m_Size;
//     std::uint32_t m_AmountStoredHash;
// };

// class CSaveContext {
//     public:
//     CDataSaveHandler m_DataHandler;
//     CSaveBitStorage m_BitStorage;
//     std::uint32_t m_Version;
// };

// struct SUpgradeableValue {

// };

// class CBonusDataContainer {

// };

// struct TEventHandle {
//     uint64_t dummy;
// };

// namespace NEvent {
//     struct CEventData {
//         uint64_t m_Type;
//         const void* m_Pointers[5];
//     };

//     class CEventBase {
//         public:
//         TEventHandle* m_EventImpl;
//         CEventBase();
//         virtual ~CEventBase();
//     };

//     class CBaseSendEvent {
//         public:
//         CEventBase* m_Impl;

//         CBaseSendEvent();
//         virtual ~CBaseSendEvent();

//         void Send(const CEventData& data) const;
//     };

//     class CEventHandler {

//     };

//     class CEventImpl {
//         public:
//     };
// };

// template <typename... Args>
// class CEventWithArguments {
//     public:

// };

// template <typename... Args>
// class CReceiveEvent : public CEventWithArguments<Args...> {
//     public:
//     static const uint64_t s_Type;
//     NEvent::CEventBase m_Impl;
// };

// template <typename... Args>
// class CSendEvent : public NEvent::CBaseSendEvent {
//     public:
//     static const uint64_t s_Type = 0xFFFFFFFFFF;

//     void Send() {
//         NEvent::CEventData data;

//         data.m_Type = s_Type;
//         data.m_Pointers[0] = nullptr;
//         data.m_Pointers[1] = nullptr;
//         data.m_Pointers[2] = nullptr;
//         data.m_Pointers[3] = nullptr;

//         NEvent::CBaseSendEvent::Send(data);
//     };
// };

// struct SObjectID {
//     std::uint64_t id;
// };

// class CHashString {
//     public:
//     uint32_t m_Hash;
// };

// static CHashString item_name_hash[4];
// static int32_t OBJECT_IDS_KEY;

// class CRuntimeContainer {

// };

// class SGameObjectSetPropertiesContext {

// };

// class Base {
//     public:
//     class IAppSystem {

//     };
// };

// template <typename T>
// class CAvaSingle {
//     public:
//     static T* Instance;
// };

// class CUpgradeableValuesManager : public CAvaSingle<CUpgradeableValuesManager>, public Base::IAppSystem, public NEvent::CEventHandler {
//     private:
//     std::vector<SUpgradeableValue, std::allocator<SUpgradeableValue>> m_Values;
//     CHashString m_SegmentHealth;
//     CBonusDataContainer m_BonusContainer;
//     CReceiveEvent<void, void, void, void, void> m_GuiCheckBonusEvent;
//     CReceiveEvent<void, void, void, void, void> m_GriffaDespawnedEvent;
//     CReceiveEvent<void, void, void, void, void> m_GriffaWeaponPickupEvent;

//     public:
//     float GetFloat(CHashString name_id);
// };



// class CLootBag : public CGameObject, public CEventHandler {
//     public:
//         char padding[0xd0];

//         CMatrix4f m_WorldMatrix;

//         CSaveInfo m_SaveInfo;

//         SObjectID m_EconomyResourceId;

//         CReceiveEvent<void, void, void, void, void> m_CheckLootEvent;
//         CReceiveEvent<void, void, void, void, void> m_CollectLootEvent;
//         CReceiveEvent<void, void, void, void, void> m_EnableEvent;
//         CReceiveEvent<void, void, void, void, void> m_DisableEvent;

//         CSendEvent<void, void, void, void, void> m_HasLootEvent;
//         CSendEvent<void, void, void, void, void> m_HasZeroLootEvent;
//         CSendEvent<void, void, void, void, void> m_IsEmptyEvent;
//         CSendEvent<void, void, void, void, void> m_ExtraItemCollectedEvent;

//         std::uint32_t m_TotalItemCount;

//         float m_BonusPointsAccumulated;

//         std::uint32_t m_DefaultLootItems[4];
        
//         float m_SlotMultiplier[4];

//         bool m_Enabled;
//         bool m_DynamicContent;
//         bool m_HasBeenGenerated;
//         bool m_HasScrap;
//         bool m_BonusCollected;

//         CLootBag();
//         virtual ~CLootBag();

//         virtual CSaveInfo& GetSaveInfo();
//         virtual bool HasLocalTransform();
//         virtual bool GetRequiredUpdates();
//         virtual bool CheckHasLoot() const;
//         virtual CMatrix4f& GetLocalTransform();
//         virtual bool GetTransform(CMatrix4f* outMatrix);
//         virtual void SetTransform(const CMatrix4f& inMatrix);
//         virtual const char* GetKlassName() const;
//         virtual void SetLocalTransform(const CMatrix4f& mat);
//         virtual void Save(CSaveContext& ctx);
//         virtual void Load(const CSaveContext& ctx);
//         virtual unsigned long long GetObjectID() const;
//         virtual void PostInit();
//         virtual int GetTotalDefaultQuantity() const;
//         virtual void CalculateBonusLootPoints(float f);
//         virtual bool GenerateLootUsingDefaultValues(std::vector<unsigned int, std::allocator<unsigned int> >& dummy);
//         virtual void GetQuantityValues(CHashString const& hash, unsigned int& a, unsigned int& b);

//         protected: 
//         bool CheckHasInventorySpace();

//         public:
//         virtual void CalculateWeightValuesForAmmoTypes(std::vector<float, std::allocator<float> >& a, std::vector<float, std::allocator<float> >& b);
//         virtual void AddToPlayerInventory(CHashString const& hash, int b);
//         virtual void CollectBonusItemsIfAny();
//         virtual void CollectLoot(std::vector<unsigned int, std::allocator<unsigned int> > const& a);
//         virtual bool GenerateLootDynamically(std::vector<unsigned int, std::allocator<unsigned int> >& a);
//         virtual bool GenerateLoot(std::vector<unsigned int, std::allocator<unsigned int> >& a);
//         virtual void HandleEvent(NEvent::CEventImpl const*, NEvent::CEventData const&);
//         virtual void SetProperties(CRuntimeContainer const&, SGameObjectSetPropertiesContext*);
// };

// CSaveInfo& CLootBag::GetSaveInfo()
// {
//     return this->m_SaveInfo;
// }

// bool CLootBag::HasLocalTransform()
// {
//     return false;
// }

// bool CLootBag::GetRequiredUpdates()
// {
//     return false;
// }

// bool CLootBag::CheckHasLoot() const
// {
//     return this->m_TotalItemCount != 0;
// }

// CMatrix4f& CLootBag::GetLocalTransform()
// {
//     return CMatrix4f::IDENTITY;
// }

// bool CLootBag::GetTransform(CMatrix4f* outMatrix) 
// {
//     *outMatrix = this->m_WorldMatrix;
//     return true;
// };

// void CLootBag::SetTransform(const CMatrix4f& inMatrix)
// {
//     this->m_WorldMatrix = inMatrix;
//     return;
// }

// const char* CLootBag::GetKlassName() const
// {
//     return "CLootBag";
// }

// void CLootBag::SetLocalTransform(const CMatrix4f& mat)
// {
//     return;
// }

// void CLootBag::Save(CSaveContext& ctx)
// {
//     unsigned long long objectID = CGameObject::GetObjectID();
//     void* buff = ctx.m_DataHandler.AllocateRAWData(objectID, sizeof(std::uint32_t));

//     *static_cast<std::uint32_t*>(buff) = this->m_TotalItemCount;
// }

// void CLootBag::Load(const CSaveContext& ctx)
// {
//     unsigned long long objectID = CGameObject::GetObjectID();
//     const std::uint32_t* buff = static_cast<const std::uint32_t*>(ctx.m_DataHandler.GetAllocatedRAWDataPtr(objectID));

//     if(buff) {
//         this->m_TotalItemCount = *buff;
//     }
// }

// void CLootBag::PostInit()
// {
//     CGameObject::PostInit();

//     if(this->m_TotalItemCount == 0) {
//         this->m_HasZeroLootEvent.Send();
//     } else {
//         this->m_HasLootEvent.Send();
//     }
// }

// uint32_t HashString(const char *str) {

// };

// CLootBag::CLootBag() : CGameObject(), CEventHandler()
// {
//     this->m_TotalItemCount = 0;

//     this->m_DefaultLootItems[0] = 0;
//     this->m_DefaultLootItems[1] = 0;
//     this->m_DefaultLootItems[2] = 0;
//     this->m_DefaultLootItems[3] = 0;

//     this->m_Enabled = true;
//     this->m_DynamicContent = false;
//     this->m_HasBeenGenerated = false;
//     this->m_HasScrap = false;
//     this->m_BonusCollected = false;
// }

// CLootBag::~CLootBag()
// {
    
// }

// int CLootBag::GetTotalDefaultQuantity() const
// {
//     return this->m_DefaultLootItems[0] + this->m_DefaultLootItems[1] +
//         this->m_DefaultLootItems[2] + this->m_DefaultLootItems[3];
// }

// void CLootBag::CalculateBonusLootPoints(float f)
// {

// }

// bool CLootBag::GenerateLootUsingDefaultValues(std::vector<unsigned int, std::allocator<unsigned int> >& dummy)
// {

// }

// bool CLootBag::CheckHasInventorySpace() 
// {
//     int totalSpace = 0;
//     CHashString* pHash = item_name_hash;

//     do
//     {
//         unsigned int max_quantity;
//         unsigned int cur_quantity;
//         GetQuantityValues(*pHash, max_quantity, cur_quantity);
//         int num = 0;

//         if(cur_quantity < max_quantity)
//         {
//             num = max_quantity - cur_quantity;
//         }
//         totalSpace += num;
//         pHash++;
//     } while (pHash != (CHashString*)OBJECT_IDS_KEY);

//     return totalSpace != 0;
// }

// void CLootBag::CalculateWeightValuesForAmmoTypes(std::vector<float, std::allocator<float> >& a, std::vector<float, std::allocator<float> >& b)
// {
//     if(this->m_BonusCollected != false)
//     {
//         return;
//     }

//     CHashString ammo_hash;
//     ammo_hash.m_Hash = HashString("ammo_collector");

//     float f = CAvaSingle<CUpgradeableValuesManager>::Instance->GetFloat(ammo_hash);
//     this->m_BonusPointsAccumulated = (f - 1.0) * b[0] + m_BonusPointsAccumulated;

//     return;
// }

// void CLootBag::CollectBonusItemsIfAny()
// {

// }

// void CLootBag::CollectLoot(std::vector<unsigned int, std::allocator<unsigned int> > const& a)
// {

// }

// bool CLootBag::GenerateLootDynamically(std::vector<unsigned int, std::allocator<unsigned int> >& a)
// {
//     return false;
// }

// bool CLootBag::GenerateLoot(std::vector<unsigned int, std::allocator<unsigned int> >& loot)
// {
//     bool hasLoot = false;
//     uint32_t* pData = loot.data();

//     if(this->m_DynamicContent)
//     {
//         hasLoot = GenerateLootDynamically(loot);
//     } 
//     else 
//     {
//         pData[0] = this->m_DefaultLootItems[0];
//         pData[1] = this->m_DefaultLootItems[1];
//         pData[2] = this->m_DefaultLootItems[2];
//         pData[3] = this->m_DefaultLootItems[3];

//         if (pData[0] != 0 || pData[1] != 0 || pData[2] != 0 || pData[3] != 0)
//         {
//             hasLoot = true;
//         }
//     }

//     if(hasLoot)
//     {
//         if(!this->m_BonusCollected)
//         {
//             uint32_t itemCount = this->m_TotalItemCount;

//             CHashString ammo_hash;
//             ammo_hash.m_Hash = HashString("ammo_collector");

//             CUpgradeableValuesManager* pMgr = CAvaSingle<CUpgradeableValuesManager>::Instance;
//             float f = pMgr->GetFloat(ammo_hash);

//             float total = static_cast<float>(itemCount) * (f - 1.0f);

//             this->m_BonusPointsAccumulated = total;
//         }
//     }
    
//     this->m_HasBeenGenerated = true;
//     return hasLoot;
// }

// void CLootBag::HandleEvent(NEvent::CEventImpl const*, NEvent::CEventData const&)
// {

// }

// void CLootBag::SetProperties(CRuntimeContainer const&, SGameObjectSetPropertiesContext*)
// {

// }