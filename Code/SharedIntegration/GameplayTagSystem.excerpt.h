// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Tags/GameplayTagSystem.h
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 40-40] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Groggy);      // 그로기(행동 불가) 상태

// [원문 41-41 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 42-46] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Reviving);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Environment_Snow_Level1); // 얕은 눈
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Environment_Snow_Level2); // 깊은 눈
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Environment_Snow_Level3); // 극한 눈
UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Debuff_CannotSprint);     // 질주 불가 디버프

// [원문 47-117 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 118-118] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Movement_Sprint);

// [원문 119-156 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 157-158] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_HitReact);       // 약한 그로기
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_HitReact_Heavy); // 강한 그로기(넉백)

// [원문 159-159 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 160-161] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Revive);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Revive_ShowWeapon);

// [원문 162-218 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 219-222] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Type_DoT);         // 도트 데미지 전용 태그
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Type_Groggy);      // 약한 그로기 유발 데미지 태그
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Type_HeavyGroggy); // 강한 그로기(넉백) 유발 데미지 태그


// [원문 223-223 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 224-225] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Hit_FriendlyFire); // 팀킬
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Hit_Weakpoint);    // 약점 명중

// [원문 226-231 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 232-232] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cooldown_StaminaRegen);

// [원문 233-241 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 242-243] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_Multiplier_Weakpoint);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_Multiplier_FriendlyFire);

// [원문 244-245 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 246-246] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_ArmorPenetration);

// [원문 247-249 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 250-252] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Environment_SnowDebuff_L1);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Environment_SnowDebuff_L2);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Environment_SnowDebuff_L3);

// [원문 253-278 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 279-281] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Environment_Snow_Level1);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Environment_Snow_Level2);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Environment_Snow_Level3);
