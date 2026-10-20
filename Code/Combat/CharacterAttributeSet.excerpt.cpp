// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Attribute/CharacterAttributeSet.cpp
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 7-7] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
#include "GameCore/Character/PlayerCharacter.h"

// [원문 8-10 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 11-11] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
#include "GameFramework/Actor.h"

// [원문 12-19 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 20-23] UCharacterAttributeSet::UCharacterAttributeSet — 전체 함수임을 뜻하지 않습니다.
	InitStaminaRegenRate(20.0f);
	InitMovementSpeed(300.0f);
	InitArmor(0.0f);
	InitAttackPower(1.0f); // 공격력 배수 (기본 1.0 = 100%)

// [원문 24-25 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 26-29] UCharacterAttributeSet::UCharacterAttributeSet — 전체 함수임을 뜻하지 않습니다.
	InitStaminaCostMultiplier(1.0f);
	InitDamage(0.0f);
	InitHealthCapMultiplier(1.0f);
	InitStaminaCapMultiplier(1.0f);

// [원문 30-39 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 40-41] UCharacterAttributeSet::GetLifetimeReplicatedProps — 전체 함수임을 뜻하지 않습니다.
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, StaminaRegenRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, StaminaCostMultiplier, COND_None, REPNOTIFY_Always);

// [원문 42-42 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 43-44] UCharacterAttributeSet::GetLifetimeReplicatedProps — 전체 함수임을 뜻하지 않습니다.
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);

// [원문 45-46 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 47-48] UCharacterAttributeSet::GetLifetimeReplicatedProps — 전체 함수임을 뜻하지 않습니다.
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, HealthCapMultiplier, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, StaminaCapMultiplier, COND_None, REPNOTIFY_Always);

// [원문 49-64 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 65-75] UCharacterAttributeSet::PreAttributeChange — 전체 함수임을 뜻하지 않습니다.
	else if (Attribute == GetHealthCapMultiplierAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.75f, 1.0f);
	}
	else if (Attribute == GetStaminaCapMultiplierAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.75f, 1.0f);
	}
	else if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth() * GetHealthCapMultiplier());

// [원문 76-78 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 79-79] UCharacterAttributeSet::PreAttributeChange — 전체 함수임을 뜻하지 않습니다.
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina() * GetStaminaCapMultiplier());

// [원문 80-84 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 85-88] UCharacterAttributeSet::PreAttributeChange — 전체 함수임을 뜻하지 않습니다.
	else if (Attribute == GetStaminaRegenRateAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}

// [원문 89-103 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 104-104] UCharacterAttributeSet::PostGameplayEffectExecute — 전체 함수임을 뜻하지 않습니다.
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth() * GetHealthCapMultiplier()));

// [원문 105-107 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 108-108] UCharacterAttributeSet::PostGameplayEffectExecute — 전체 함수임을 뜻하지 않습니다.
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina() * GetStaminaCapMultiplier()));

// [원문 109-109 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 110-110] UCharacterAttributeSet::PostGameplayEffectExecute — 전체 함수임을 뜻하지 않습니다.
	else if (ModifiedAttribute == GetMaxHealthAttribute() || ModifiedAttribute == GetHealthCapMultiplierAttribute())

// [원문 111-111 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 112-115] UCharacterAttributeSet::PostGameplayEffectExecute — 전체 함수임을 뜻하지 않습니다.
		if (ModifiedAttribute == GetHealthCapMultiplierAttribute())
		{
			SetHealthCapMultiplier(FMath::Clamp(GetHealthCapMultiplier(), 0.75f, 1.0f));
		}

// [원문 116-116 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 117-117] UCharacterAttributeSet::PostGameplayEffectExecute — 전체 함수임을 뜻하지 않습니다.
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth() * GetHealthCapMultiplier()));

// [원문 118-118 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 119-119] UCharacterAttributeSet::PostGameplayEffectExecute — 전체 함수임을 뜻하지 않습니다.
	else if (ModifiedAttribute == GetMaxStaminaAttribute() || ModifiedAttribute == GetStaminaCapMultiplierAttribute())

// [원문 120-120 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 121-124] UCharacterAttributeSet::PostGameplayEffectExecute — 전체 함수임을 뜻하지 않습니다.
		if (ModifiedAttribute == GetStaminaCapMultiplierAttribute())
		{
			SetStaminaCapMultiplier(FMath::Clamp(GetStaminaCapMultiplier(), 0.75f, 1.0f));
		}

// [원문 125-125 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 126-126] UCharacterAttributeSet::PostGameplayEffectExecute — 전체 함수임을 뜻하지 않습니다.
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina() * GetStaminaCapMultiplier()));

// [원문 127-131 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 132-139] UCharacterAttributeSet::PostGameplayEffectExecute — 전체 함수임을 뜻하지 않습니다.
	else if (ModifiedAttribute == GetDamageAttribute())
	{
		// 메타 어트리뷰트: 누적된 데미지를 Health에서 깎고 즉시 0으로 초기화
		const float LocalDamageDone = GetDamage();
		SetDamage(0.0f);

		if (LocalDamageDone > 0.0f)
		{

// [원문 140-151 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 152-156] UCharacterAttributeSet::PostGameplayEffectExecute — 전체 함수임을 뜻하지 않습니다.
			{
				PlayerCharacter->ClientNotifyDamageTaken(AppliedDamage);
			}

			const FGameplayTagContainer& DynamicTags = Data.EffectSpec.GetDynamicAssetTags();

// [원문 157-214 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 215-234] UCharacterAttributeSet::OnRep_HealthCapMultiplier 외 3개 함수 구간 — 전체 함수임을 뜻하지 않습니다.
void UCharacterAttributeSet::OnRep_HealthCapMultiplier(const FGameplayAttributeData& OldHealthCapMultiplier) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, HealthCapMultiplier, OldHealthCapMultiplier);
}

void UCharacterAttributeSet::OnRep_StaminaCapMultiplier(const FGameplayAttributeData& OldStaminaCapMultiplier) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, StaminaCapMultiplier, OldStaminaCapMultiplier);
}

void UCharacterAttributeSet::OnRep_StaminaRegenRate(const FGameplayAttributeData& OldStaminaRegenRate) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, StaminaRegenRate, OldStaminaRegenRate);
}

void UCharacterAttributeSet::OnRep_StaminaCostMultiplier(const FGameplayAttributeData& OldStaminaCostMultiplier) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, StaminaCostMultiplier, OldStaminaCostMultiplier);
}


// [원문 235-239 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 240-249] UCharacterAttributeSet::OnRep_Armor, UCharacterAttributeSet::OnRep_AttackPower — 전체 함수임을 뜻하지 않습니다.
void UCharacterAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, Armor, OldArmor);
}

void UCharacterAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, AttackPower, OldAttackPower);
}

