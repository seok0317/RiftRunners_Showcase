// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Ability/ExecCalc_Damage.cpp
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 2-11] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.

#include "ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "../Attribute/CharacterAttributeSet.h"
#include "../Tags/GameplayTagSystem.h"

// 캡처를 위한 매크로 세팅
struct FDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);

// [원문 12-12 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 13-19] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

	FDamageStatics()
	{
		// 피격자의 방어력 캡처
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSet, Armor, Target, false);

// [원문 20-21 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 22-37] UExecCalc_Damage::UExecCalc_Damage — 전체 함수임을 뜻하지 않습니다.
		// 공격자의 공격력 캡처
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSet, AttackPower, Source, false);
		// 피격자의 데미지 메타 어트리뷰트 캡처
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSet, Damage, Target, false);
	}
};

static const FDamageStatics& DamageStatics()
{
	static FDamageStatics Statics;
	return Statics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);

// [원문 38-38 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 39-56] UExecCalc_Damage::UExecCalc_Damage, UExecCalc_Damage::Execute_Implementation — 전체 함수임을 뜻하지 않습니다.
	RelevantAttributesToCapture.Add(DamageStatics().AttackPowerDef);
	RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();

	if (!TargetASC || !SourceASC)
	{
		return;
	}

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	// DoT 태그 확인 (도트 딜은 무적 상태를 무시하고 들어감)

// [원문 57-57 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 58-108] UExecCalc_Damage::Execute_Implementation — 전체 함수임을 뜻하지 않습니다.

	// 1. 무적(Invincible) 판별 로직
	if (TargetTags && TargetTags->HasTag(GameplayTagSystem::State_Invincible) && !bIsDoT)
	{
		// 도트가 아닌 즉발 데미지는 무적일 때 완전히 무효화
		return;
	}

	FAggregatorEvaluateParameters EvalParams;
	EvalParams.TargetTags = TargetTags;
	EvalParams.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();

	// 2. 공격자의 공격력(AttackPower) 캡처
	float AttackPower = 1.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AttackPowerDef, EvalParams, AttackPower);
	AttackPower = FMath::Max(AttackPower, 0.0f);

	// 3. 피격자의 방어력(Armor) 캡처
	float Armor = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvalParams, Armor);
	Armor = FMath::Max(Armor, 0.0f);

	// 4. Base Damage 가져오기 (BP 노드에서 SetByCaller로 넘긴 값)
	float BaseDamage = Spec.GetSetByCallerMagnitude(GameplayTagSystem::Data_Damage, false, 0.0f);

	// 5. 증폭 배수 캡처 (BP 노드에서 SetByCaller로 넘긴 값, 기본값 세팅)
	float WeakpointMultiplier = Spec.GetSetByCallerMagnitude(GameplayTagSystem::Data_Multiplier_Weakpoint, false, 1.5f);
	float FriendlyFireMultiplier = Spec.GetSetByCallerMagnitude(GameplayTagSystem::Data_Multiplier_FriendlyFire, false, 0.5f);

	// 공격력 스탯 반영
	float FinalDamage = BaseDamage * AttackPower;

	// 태그 기반 배수 적용
	if (Spec.GetDynamicAssetTags().HasTag(GameplayTagSystem::Hit_Weakpoint))
	{
		FinalDamage *= WeakpointMultiplier;
	}
	
	if (Spec.GetDynamicAssetTags().HasTag(GameplayTagSystem::Hit_FriendlyFire))
	{
		FinalDamage *= FriendlyFireMultiplier;
	}

	// 6. 방어력(Armor) 공식 적용 (스탠다드 경감 공식: 100 / (100 + 방어력))
	// 무기 고유의 방어구 관통력(ArmorPenetration)을 가져와 상대 방어력을 깎음
	float ArmorPenetration = Spec.GetSetByCallerMagnitude(GameplayTagSystem::Data_ArmorPenetration, false, 0.0f);
	float EffectiveArmor = FMath::Max(Armor - ArmorPenetration, 0.0f); // 방어력은 0 이하로 떨어지지 않음

	float DamageMitigation = 100.0f / (100.0f + EffectiveArmor);
	FinalDamage *= DamageMitigation;


// [원문 109-152 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 153-158] UExecCalc_Damage::Execute_Implementation — 전체 함수임을 뜻하지 않습니다.
	// 7. 최종 산출 데미지 적용
	if (FinalDamage > 0.0f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().DamageProperty, EGameplayModOp::Additive, FinalDamage));
	}
}
