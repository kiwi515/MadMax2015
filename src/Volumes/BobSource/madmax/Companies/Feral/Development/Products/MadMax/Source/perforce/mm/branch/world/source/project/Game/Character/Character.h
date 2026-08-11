#ifndef PROJECT_GAME_CHARACTER_H
#define PROJECT_GAME_CHARACTER_H

#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/CharacterSystem/CharacterBase.h"
#include "project/Game/Interaction/InteractionUserProxy.h"
#include "project/Game/Health/HealthWrapper.h"
#include "libs/CoreLibs/main/include/ALib/HashTable.h"
#include "project/Game/Equipment/Item/Weapon/Explosive.h"
#include "project/Game/Inventory/Inventory.h"
#include "project/Game/Character/CharacterStats.h"
#include "build/Win64/Final/ctg/components/Physics/include/Physics/PfxCharacterInstance.h"
#include "project/Game/Character/BoneAttachment/BoneOffsetAlias.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/EffectSystem/Effects/AOVolume.h"
#include "project/Game/Character/AnimStateTransitionObserver.h"
#include "project/Game/AI/Pathfinding/AiPathfinderContext.h"
#include "project/fragments/ai/include/AiBehavior/ObjectBlackboard.h"
#include "project/Game/Character/ControlParameters.h"
#include "project/Game/Character/Helpers/AnimationAlignmentHelper.h"
#include "project/Game/Character/CharacterSounds.h"
#include "project/Game/Character/CharacterVocals.h"
#include "project/Game/AI/AiEntitiesGame.h"
#include "project/Game/Character/LookAtIKDirector.h"
#include "project/Game/GameObject/StateContainerDatas.h"
#include "project/Game/Character/TargetHandler.h"
#include "project/Game/Character/LocomotionGraph.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/GameObject/Effects/Outline.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/GameObject/AnimatedModel.h"
#include "project/Game/Character/CharacterIK.h"
#include "project/Game/Character/DeformerJointTwister.h"
#include "project/Game/Character/BoneAttachment/SecondaryMotionController.h"
#include "project/Game/Damage/DamageDecal.h"
#include "build/Win64/Final/ctg/components/Animation/include/Ragdoll/RagdollCollisionListener.h"
#include "build/Win64/Final/ctg/components/Animation/include/Ragdoll/Ragdoll.h"
#include "build/Win64/Final/ctg/components/Animation/include/Ragdoll/RagdollInstance.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/CharacterSystem/RagdollProxyPhantom.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/GameObject/Physics/DamageInflictor.h"
#include "project/Game/Character/FootstepFX.h"

struct SSpellHitInfo {

};

struct SExplosionHitData {

};

struct SBulletHitData {

};

class CSetTransformConstraint {

};

struct HThreadMutexName { // could not find where this is actually defined

};

class CCharacter : public CDamageable, public NCharacterSystem::CCharacterBase, public IPhysicsGameObjectListenable {
    struct SQueuedImpulsePair {
        public:
        CVector3f m_LinearImpulse;
        CVector3f m_AngularImpulse;
    };

    struct SAttachedEffectInfo {

    };

    struct SShapeImpulsePair {

    };

    struct SHitByFireData {

    };

    struct SHitByFireData {

    };

    struct SMeleeLoopEffect {

    };

    struct SMatrixSpring {

    };

    struct SSpellTargetCharacterInfo {

    };
    
    public: 
    THashTable<int,unsigned int,1,unsigned short> m_DecalTargetHashes;
    uint32_t m_CurrentDecalSlot;
    uint32_t m_DefaultControllerId;
    unsigned char m_IntervalOrder;
    bool m_IntervalUpdateFrame;
    float m_IntervalTimeSkipMultiplier;
    unsigned char m_IntervalFramesSkipped;

    private: 
    TArray<CCharacter::SQueuedImpulsePair> m_QueuedImpulses;

    public: 
    CExplosives* m_ActiveGrenade; // BOOST PTR
    uint32_t m_SpellCastSeed;
    uint32_t m_SpellCritSeed;
    float m_HeightOverGround;
    float m_HeightOverGroundExcludingWater;
    bool m_Visible : 1; /* BitPos=0 */
    bool m_Enabled : 1; /* BitPos=1 */
    bool m_StartEnabled : 1; /* BitPos=2 */
    bool m_GhostMode : 1; /* BitPos=3 */
    bool m_PendingGhostMode : 1; /* BitPos=4 */
    bool m_DontReactToHit : 1; /* BitPos=5 */
    bool m_DistanceCulledInVehicle : 1; /* BitPos=6 */
    bool m_InScoutingMode : 1; /* BitPos=7 */
    bool : 0; /* BitPos=8 */
    bool m_InPlayerUpgrade : 1; /* BitPos=0 */
    bool m_WasVisible : 1; /* BitPos=1 */
    bool m_AimingEnabled : 1; /* BitPos=2 */
    bool m_UpdatePhysics : 1; /* BitPos=3 */
    bool m_UseFinalTransparency : 1; /* BitPos=4 */
    bool m_IsPlayer : 1; /* BitPos=5 */
    bool m_PendingSetTransform : 1; /* BitPos=6 */
    bool m_UseScopeFresnelEffect : 1; /* BitPos=7 */
    bool : 0; /* BitPos=8 */
    bool m_SetPropertiesOK : 1; /* BitPos=0 */
    bool m_InSequence : 1; /* BitPos=1 */
    bool m_WasDestroyed : 1; /* BitPos=2 */
    bool m_Gibed : 1; /* BitPos=3 */
    bool m_SyncRagdollState : 1; /* BitPos=4 */
    bool m_SyncRagdollPartialEnable : 1; /* BitPos=5 */
    bool m_RagdollFullyEnabled : 1; /* BitPos=6 */
    bool m_SyncRagdollUsePoseBoneVelocities : 1; /* BitPos=7 */
    float m_ContinousRagdollPartialEnableTimer;
    CInventory* m_Inventory;
    CItemObject* m_WieldedItem; // BOOST PTR
    CCharacterStats m_Stats;
    CCharacterDaze m_Daze;
    std::vector<CItemObject*,std::allocator<CItemObject* > > m_InventoryAttachedItems; // BOOST PTR
    CPhysicsGameObjectListenerContainer m_Listeners;
    int32_t m_MaterialBelow;
    CVector3f m_SurfaceNormal;
    unsigned char m_SpawnTypeId;
    unsigned char m_SpawnTypeIdUnModified;
    uint32_t m_SpawnTeam;
    int32_t m_Faction;
    float m_CharacterLootTime;
    int32_t m_CharacterLevel;
    uint64_t m_InteractionContextId;
    uint64_t m_InteractionId;
    CPfxCharacterInstance::EProxyState m_PendingProxyState;
    bool m_PendingProxyStateCheckCollision;
    float m_CorpseCoolingTime;
    uint32_t m_TimeOfDeath;
    float m_AdvancedMoveToTimer;
    float m_CurrentAccuracy;
    float m_CurrentInternalAccuracy;
    float m_MinAccuracy;
    float m_MaxAccuracy;
    CVector3f m_AnimationTranslationScaling;
    CMatrix4f* m_DynamicAnimScalingGoal;
    CMatrix4f* m_DynamicAnimScalingStartOffset;
    CMatrix4f* m_DynamicAnimScalingGoalOffset;
    CVector3f m_CurrentScaledAnimationTranslation;
    std::vector<CCharacter::SAttachedEffectInfo,std::allocator<CCharacter::SAttachedEffectInfo> > m_AttachedCharacterEffects;
    std::vector<CEffectInstance *,std::allocator<CEffectInstance *> > m_IntensityEffects;
    float m_IntensityClamp;
    bool m_IntensityEffectRestart;

    protected: 
    std::vector<CBoneOffsetAlias::SBoneOffset,std::allocator<CBoneOffsetAlias::SBoneOffset> > m_BoneOffsets;

    public:
    float m_MaxHealth;
    CHashString m_RagdollCacheID;
    float m_HitReaction_ExplosionRagdollImpactThreshold;
    float m_HitReaction_MaxExplosionImpactForce;
    float m_HitReaction_MinorImpactMultiplier;
    float m_HitReaction_MajorImpactMultiplier;
    float m_HitReaction_ExtremeImpactMultiplier;
    float m_HitReaction_KillingBulletImpulseScale;
    float m_HitReaction_ImpactForceDecaySpeed;
    float m_HitReaction_ExplosionImpulseMultiplier;
    float m_HitReaction_ImpactMassThreshold;
    CEffectInstance* m_CollisionEffect;
    float m_ImpactDamageFactor;
    float m_ImpactDamageThreshold;
    float m_CurrentLean;
    CVector3f m_GrenadeTargetOffset;
    CVector3f m_LeftFootPosT0;
    CVector3f m_LeftFootPosT1;
    CVector3f m_RightFootPosT0;
    CVector3f m_RightFootPosT1;
    CAOVolumeInstance* m_AOVolumeInstance[2];
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_HideEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_ShowEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_DisableEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_DetachEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_DetachVehicleDeathEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_WieldRightSlotRightHandEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_WieldRightSlotLeftHandEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_RightSlotShowEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_RightSlotHideEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_DropItemBehindEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_UnequipWeaponEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_UnequipMeleeWeaponEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_AttachWieldedItemToBoneEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_ChangeWeaponEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_FireWeaponAtRangedWeaponTargetsEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_FireInteractionWeapon;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_SendActToInteractioAnimatedModel;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_SpawnItemEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_ThrowThunderStickEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_ThrowStoneEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_PlantLandMineEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_DisarmLinkTarget;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_LinkTargetGiveItemEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_LinkTargetStabShivEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_ReloadWeapon;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_ReloadWeaponPartial;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_ConsumeMagazineAmmo;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_EvadeLandEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_FootTouchEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_FootStrikeEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_InflictDamageEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_CastSpellEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_CastSpellBuffOnSelfEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_CastSpellBuffOnPlayerEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_InstantDeathEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_DetachFromInteractionContextEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_LinkTargetDoActEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_LinkSourcesDoActEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_SelfDoActEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_RotateTowardsLinkSourcesEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_CallPlayerAttentionEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_UserVMRegisterSetEvent[35];
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_UserVMRegisterAddEvent[35];
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_AcquireLinkTargetEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_ReleaseLinkTargetEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_AcquireMeleeTargetEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_SendFloatEventEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_InteractionGraphEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_DialogueIntentEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_DialogueIntentTriggerEvent;
    NEvent::CReceiveEvent<NAnimationSystem::STrackEventData,void,void,void,void> m_RunInteractionBehaviorEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_EnterScoutModeEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_ExitScoutModeEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_EnterSniperModeEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_ExitSniperModeEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_EnableCharacterEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_DisableCharacterEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_ShowCharacterEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_HideCharacterEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_FadeInCharacterEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_FadeOutCharacterEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_ClearAttachedEffectsEvent;
    NEvent::CReceiveEvent<void,void,void,void,void> m_EnterHighLodMode;
    NEvent::CReceiveEvent<void,void,void,void,void> m_ExitHighLodMode;
    NEvent::CSendEvent<void,void,void,void,void> m_OnCharacterDestroyedEvent;
    NEvent::CSendEvent<void,void,void,void,void> m_OnCharacterBuffAdded;
    THashTable<CHashString,unsigned int,1,unsigned short> m_AnimationTriggerEvents;
    std::vector<IAnimStateTransitionObserver *,std::allocator<IAnimStateTransitionObserver *> > m_StateTransitionObservers;

    private: 
    CAvatar* m_Avatar;
    IPfxGameObject::SHitReactInfo m_LatestHitReactInfo;
    SSpellHitInfo m_LastSpellHitInfo;
    SExplosionHitData m_LastExplosionHitData;
    CPhysicsGameObject::SHitByFireData m_LastFireHitData;
    SBulletHitData m_LastBulletHitData;
    bool m_LatestFireHitValid;
    float m_RecentFireDamageTimer;
    float m_LatestSuccesfullSPellGivenTime;
    float m_LatestSuccesfullSPellReceivedTime;
    int32_t m_AiBaseUpgradeLevel;
    bool m_IsHostileEvenIfAlliedFaction;
    uint64_t m_SavedTiltTowardsTargetId;
    bool m_IsNarrativeEncounterPerson;
    std::vector<CCharacter::SShapeImpulsePair,std::allocator<CCharacter::SShapeImpulsePair> > m_BulletImpulseStorage;
    CAiPathfinderContext* m_PathfinderContext;
    CAiPathfinderTarget m_PathfinderTargets[2];

    public: 
    volatile uint64_t m_BlackboardLock;
    SBlackboard m_Blackboard;
    float m_HeavyLanding_FallTime;
    CControlParameters* m_ControlParameters;
    bool m_FreezeFrameSafetyBool;
    CVector3f m_HipsPfxOffsetMS;
    float m_WaterLevel;
    CVector3f m_CustomUpStart;
    CVector3f m_CustomUpEnd;
    float m_CustomUpStartCursorPosition;
    float m_CustomUpEndCursorPosition;
    std::vector<std::pair<IPfxGameObject *,float>,std::allocator<std::pair<IPfxGameObject *,float> > > m_ImpactCooldowns;
    char m_CurrentMotionState;
    const char m_DefaultMotionState;
    CAnimationAlignmentHelper m_AlignmentHelper;
    CCharacterSounds* m_CharacterSounds;
    int32_t m_SoundGroup;
    int32_t m_SoundPresetID;
    CCharacterVocals* m_CharacterVocals;
    uint32_t m_VoiceOverId;
    int32_t m_VoiceOverResourceID;
    uint32_t m_DefaultContextBits;
    bool m_AiEntityEnabled;
    CAiCharacterEntity m_AiEntity;
    CLookAtIKDirector* m_LookAtDirector;
    float m_PenetrationTime;
    std::vector<CCharacter::SMeleeLoopEffect,std::allocator<CCharacter::SMeleeLoopEffect> > m_MeleeLoopEffects;

    private: 
    CHealthWrapper* m_HealthWrapper;

    protected: 
    std::vector<SObjectID,std::allocator<SObjectID> > m_GiveItems;
    SObjectID m_TargetInfo;
    CStateContainerDataTargetInfo* m_wpTargetInfo; // BOOST PTR
    CCharacterTargetHandler m_targetHandler;
    CLocomotionGraph m_LocomotionGraph;
    COutline* m_BerserkOutline; // BOOST PTR
    float m_DetectedByPlayerMaxRadius;
    float m_DetectedByPlayerCooldown;
    float m_TimeSinceDetectedByPlayer;
    int32_t m_DetectedByPlayerProgress;
    bool m_DetectedByPlayer;

    public: 
    bool m_RagdollPostSimMappingEnabled;
    CSetTransformConstraint m_SetTransformConstraint;
    CAnimatedModel m_AnimatedModel;
    CInteractionUserProxy m_InteractionUserProxy;
    CCharacterIK m_IK;
    bool m_DeformTwistsEnabled;
    CDeformerJointTwister m_DeformerJointTwister;
    std::vector<CSecondaryMotionController *,std::allocator<CSecondaryMotionController *> > m_SecondaryMotionControllers;
    CDamageDecal m_DamageDecal;
    CCharacter::SMatrixSpring m_MatSpring;
    int32_t m_HeadBoneHiIndex;
    int32_t m_HipsBoneHiIndex;
    CRagdollCollisionListener* m_RagdollCollisionListener;
    const NAnimationSystem::SRagdollParams* m_CurrentRagdollParams;
    CHashString m_CurrentRagdollParamsID;
    NAnimationSystem::CRagdollInstanceImpl* m_Ragdoll; // BOOST PTR
    CPfxRagdollProxyPhantom m_PfxRagdollProxyPhantom;
    float m_TimeBeforeSystemGroupReset;
    float m_TimeBeforeNoCollideIDReset;
    uint32_t m_OriginalSystemGroup;
    uint32_t m_CurrentSystemGroup;
    uint32_t m_PendingSystemGroup;
    uint32_t m_OriginalNoCollideID;
    uint32_t m_CurrentNoCollideID;
    uint32_t m_PendingNoCollideID;
    SGameEffectContainer* m_FireFlameEffectContainer;
    SGameEffectContainer* m_FireSoundEffectContainer;
    SGameEffectContainer* m_DazeEffectContainer;
    SGameEffectContainer* m_GibEffectContainer;
    std::vector<CCharacter::SSpellTargetCharacterInfo,std::allocator<CCharacter::SSpellTargetCharacterInfo> > m_SpellTargetCharacterInfo;

    private: 
    unsigned char m_FadeOut : 1; /* BitPos=0 */
    unsigned char m_FadeIn : 1; /* BitPos=1 */
    unsigned char m_FadeInResetOpacity : 1; /* BitPos=2 */
    float m_Opacity;
    uint32_t m_LastAnimStateChange;
    CDamageInflictor m_LastDamage;
    CHashString m_DestroyedDamageType;
    CFootstepFX m_FootstepFX;
    bool m_UsePostApplyRenderTransform : 1; /* BitPos=0 */
    CMatrix4f m_PostApplyRenderTransform;
    bool m_ModelMatrixInitialized;
    unsigned char m_SavedMinLod;
    unsigned char m_SavedOffsetLod;
    bool m_DynamicLODOverridden;
    float m_SavedScaleLod;

    // static variables
    public: 
    static CHashString FullBody;
    static CHashString UpperBody;
    static CHashString ALL_LAYERS;
    static CHashString RagdollRB_Head;
    static CHashString RagdollRB_Spine1;
    static CHashString RagdollRBGroup_Head;
    static CHashString RagdollRBGroup_Torso;
    static CHashString RagdollRBGroup_LeftArm;
    static CHashString RagdollRBGroup_RightArm;
    static CHashString RagdollRBGroup_LeftLeg;
    static CHashString RagdollRBGroup_RightLeg;
    static const uint32_t MAX_DECAL_TO_BONE_MAPPING_SLOTS;
    static uint32_t sIntervalCounter;
    static uint32_t sCreationID;
    static CHashString on_fire;
    static CHashString on_fire_light;
    static CHashString max_on_fire;
    static CHashString max_on_fire_light;
    static CHashString max_on_fire_buffed;
    static CHashString s_OnFireAct;
    static CHashString s_ForceOffFireAct;
    static bool sDebugBulletDamagesEnabled;
    static bool sDebugTrackMessagesEnabled;
    static float HeightC_FallNoDamage;
    static float VehicleDamageMin;
    static float VehicleDamageFactor;
    static float VehiclePainMin;
    static float VehiclePainFactor;
    static float VehicleDeathSpeed;
    static float VehicleReactSpeed;
    static float m_WeaponDespawnTime;
    static float m_ExplosiveDespawnTime;
    static float m_UpperDecalSpawnDmg;
    static float m_LowerDecalSpawnDmg;
    static float m_BloodDecalDistance;
    static bool m_BloodEnabled;
    static bool m_GibsEnabled;
    static bool m_DoIntervalUpdate;

    private: 
    static const float s_LodLimits[5];
    static const float s_LodScale[5];
    static float HeightD_Jump;
    static float HeightE_Ground;
    static int32_t NofCharacters;
    static const float m_MovementInputThreshold;
    static bool m_DebugHealth;

    public: 
    static HThreadMutexName* m_OnStateTransitionLock;

    protected: 
    static int32_t m_NofDetectedByPlayer;

    public: 
    static uint64_t m_PlayerDeaths;
    static uint64_t m_NPCDeaths;

    private: 
    static unsigned char m_PictureModeMinLod;
    static unsigned char m_PictureModeOffsetLod;
    static float m_PictureModeScaleLod;
    
    // methods
    public:
    static bool IsDead(float for_how_long);
    static float GetFloatRegister(int32_t index);
    int32_t GetFaction() const;
    virtual void SetTransform(const CMatrix4f& new_world_matrix);
    virtual CHealthWrapper* GetHealthWrapper() const; 
    void Revive();
    virtual void Enable(bool enable);
};

#endif