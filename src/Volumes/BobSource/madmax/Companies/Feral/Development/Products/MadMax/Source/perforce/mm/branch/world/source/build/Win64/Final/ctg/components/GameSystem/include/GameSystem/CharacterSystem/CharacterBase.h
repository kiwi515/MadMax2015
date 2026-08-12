#ifndef COMPONENT_CHARACTER_BASE_H
#define COMPONENT_CHARACTER_BASE_H

#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Types/Rtti.h"
#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Math/Matrix.h"
#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Math/Vector.h"
#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Math/Quaternion.h"
#include "build/Win64/Final/ctg/components/Physics/include/Physics/PfxCharacter.h"
#include "build/Win64/Final/ctg/components/Animation/include/Animation/Skeleton.h"
#include "libs/ResourceCache/main/include/ResourceCache/ResourceCachePtr.h"
#include "build/Win64/Final/ctg/components/Physics/include/Physics/PfxRigidBodyCharacterInstance.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/Attachment/Attachable.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/CharacterSystem/CharacterController.h"
#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Types/HashString.h"
#include "project/Game/Vehicles/Vehicle.h"


namespace NCharacterSystem {

class CCharacterBase : public IPfxCharacter, public CRtti {
    public:
    struct AttachType {

    };

    protected:
    TResourceCachePtr<NAnimationSystem::CSkeletonImpl> m_Skeleton;
    CMatrix4f m_WorldMatrix;
    CMatrix4f m_PreviousTransform;
    CMatrix4f m_HipAdjustment;
    CQuaternion m_Q0;
    CQuaternion m_Q1;
    CVector3f m_T0;
    CVector3f m_T1;
    CQuaternion m_RotationGoal;
    CVector3f m_AngularVelocity;
    float m_MaxAngularSpeed;
    float m_MaxAngularAcceleration;
    std::shared_ptr<CPfxRigidBodyCharacterInstance> m_PfxCharacter; // BOOST PTR
    CAttachable m_Attachable;
    void* m_AttachedObject;
    CVector3f m_VelocityAnimation;
    CVector3f m_VelocitySteeringWS;
    CVector3f m_MeasuredLinearVelocity;
    float m_MeasuredWorldSpeed;
    CVector3f m_MeasuredAngularVelocity;
    std::weak_ptr<NCharacterSystem::CCharacterController> m_ActiveController; // BOOST PTR
    CHashString NullId;
    unsigned char m_Gender;
    unsigned char m_AttachType;
    bool m_VelocitySet : 1;
    bool m_GameEventActor : 1;
    bool m_Initialized : 1;
    bool m_RotationGoalActive : 1;
    bool m_RotationEnabled : 1;
    bool m_Paused : 1;

    public:
    virtual const CRttiTypeId& GetTypeId() const;
    virtual bool IsType(const CRttiTypeId&) const;
    CCharacterBase(const NCharacterSystem::CCharacterBase&);
    CCharacterBase();
    virtual ~CCharacterBase();
    bool IsInitialized() const;
    bool IsPaused() const;
    void SetPaused(bool);
    const std::weak_ptr<NCharacterSystem::CCharacterController>& GetController() const; // BOOST PTR
    void SetController(const std::weak_ptr<NCharacterSystem::CCharacterController>&); // BOOST PTR
    virtual void ResetController();
    virtual bool IsPlayerControlled() const;
    bool IsMale();

    protected: 
    const CMatrix4f* GetWorldMatrix() const;

    public: 
    const CMatrix4f& GetWorldMatrixRef() const {
        return this->m_WorldMatrix;
    };

    public: 
    void AdjustHip(const CMatrix4f&);
    const CMatrix4f GetHipAdjust() const;
    const CMatrix4f* GetAttachMatrix() const;
    void SetOrientation(const CMatrix4f&, bool);
    void SetPosition(const CVector3f&);
    virtual void AttachTo(const CMatrix4f*, void*, NCharacterSystem::CCharacterBase::AttachType, CMatrix4f*, uint32_t);
    virtual void Detach(float);
    bool IsAttachedTo(CMatrix4f*);
    void SetAttachOffset(const CMatrix4f&);
    const CMatrix4f* GetAttachOffset();
    void ResetAttachOffset();
    float GetMaxAngularSpeed() const;
    void SetMaxAngularSpeed(float);
    float GetMaxAngularAcceleration() const;
    void SetMaxAngularAcceleration(float);
    void RotateToward(const CQuaternion&);
    void RotateToward(float, float, float);
    void RotateToward(float);
    void RotateToward(const CVector3f&);
    void RotateInstantly(const CQuaternion&);
    void RotateInstantly(float);
    void RotateInstantly(const CVector3f&);
    virtual void DoRotateToward(float);
    void FinalizeRotation();
    void FinalizeRotationWithSync();
    bool HasRotationGoal() const;
    const CQuaternion& GetRotationGoal() const;
    void ResetRotationGoal();
    void LookAtPosition(const CVector3f&, const CVector3f&);
    void LookAtDirection(const CVector3f&, const CVector3f&);
    void UpdateMeasuredWorldVelocity(float);
    CVector3f GetVelocity() const;
    CVector3f GetSupportingSurfaceVelocity() const;
    const CVector3f& GetVelocityAnimationCharacterSpace() const;
    const CVector3f& GetMeasuredWorldVelocity() const;
    const CVector3f& GetMeasuredAngularVelocity() const;
    float GetMeasuredWorldSpeed() const;
    void SetVelocitySteering(const CVector3f&);
    void SetVelocitySteeringWS(const CVector3f&);
    void ClearVelocities();
    virtual bool DoAct(const CHashString&);
    virtual bool TryAct(const CHashString&);
    virtual bool SetState(const CHashString&);
    virtual const CHashString& GetState() const;
    virtual const CHashString& GetPreviousState() const;
    CPfxCharacterInstance* GetPfxCharacter();
    IPfxInstance* GetIPfxInstance();
    CPfxCharacterInstance::CharacterInput& GetPhysicsInputState();
    virtual std::shared_ptr<CVehicle> GetVehicle() const; // BOOST PTR
    const TResourceCachePtr<NAnimationSystem::CSkeletonImpl>& GetSkeleton();
    const CMatrix4f& GetPreviousTransform();
    CAttachable& GetAttachable();
    virtual void UpdateGraphicsMatrix();
    virtual void SyncGraphicsMatricesToWorld();
    void SetRotationEnabled(bool);

    protected: 
    void WriteWorldMatrix(const CMatrix4f&);
    void WriteWorldMatrixTranslation(const CVector3f&);
    void GetLocalSpaceSteeringVelocity(CVector3f&) const;
    void InitWorldMatrix(const CMatrix4f&);
    virtual void OnAttached(uint32_t);
    virtual void OnDetached(float);

    public: 
    NCharacterSystem::CCharacterBase& operator=(const NCharacterSystem::CCharacterBase&);
    void __local_vftable_ctor_closure();
    virtual void* __vecDelDtor(uint32_t);
    
    static const CRttiTypeId& TYPE_ID();
};

}

#endif