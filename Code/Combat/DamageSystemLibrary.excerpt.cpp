// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Ability/DamageSystemLibrary.cpp
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 2-3] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.

#include "DamageSystemLibrary.h"

// [원문 4-4 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 5-6] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

// [원문 7-8 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 9-13] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
#include "../Tags/GameplayTagSystem.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "PhysicalMaterials/PhysicalMaterial.h"


// [원문 14-45 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 46-68] UDamageSystemLibrary::ApplyGameDamage — 전체 함수임을 뜻하지 않습니다.
void UDamageSystemLibrary::ApplyGameDamage(const UObject* WorldContextObject, AActor* InstigatorActor, const FDamagePayload& Payload)
{
	if (!InstigatorActor || !InstigatorActor->HasAuthority())
	{
		// 이 노드는 무조건 서버(Authority)에서만 실행되어야 합니다.
		return;
	}

	if (!Payload.DamageEffectClass)
	{
		UE_LOG(LogTemp, Error, TEXT("ApplyGameDamage: DamageEffectClass is missing! Please assign GE_Damage_Base in the payload."));
		return;
	}

	UAbilitySystemComponent* SourceASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(InstigatorActor);
	if (!SourceASC) return;

	AActor* TargetActor = Payload.HitResult.GetActor();
	if (!TargetActor) return;

	UAbilitySystemComponent* TargetASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);
	if (!TargetASC) return;


// [원문 69-85 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 86-87] UDamageSystemLibrary::ApplyDamageToTarget — 전체 함수임을 뜻하지 않습니다.
	// GE 생성
	FGameplayEffectContextHandle ContextHandle = SourceASC->MakeEffectContext();

// [원문 88-98 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 99-113] UDamageSystemLibrary::ApplyDamageToTarget — 전체 함수임을 뜻하지 않습니다.

	FGameplayEffectSpec* Spec = SpecHandle.Data.Get();

	// DoT 세팅 (주의: 원본 GE가 HasDuration 또는 Infinite일 때만 안전하게 적용 가능)
	if (Payload.DoTDuration > 0.0f && Payload.DoTPeriod > 0.0f)
	{
		// 만약 실수로 Instant(즉발) GE를 넣고 DoT를 켜면 엔진이 크래시납니다. 이를 방지하는 안전장치.
		if (Spec->Def && Spec->Def->DurationPolicy == EGameplayEffectDurationType::Instant)
		{
			UE_LOG(LogTemp, Error, TEXT("ApplyGameDamage: DoT를 적용하려면 Payload의 DamageEffectClass가 'Has Duration' 정책을 가진 GE여야 합니다! 현재 Instant GE가 들어가 있어 즉발 데미지로 강제 전환됩니다."));
		}
		else
		{
			Spec->SetDuration(Payload.DoTDuration, true);
			Spec->Period = Payload.DoTPeriod;

// [원문 114-114 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 115-128] UDamageSystemLibrary::ApplyDamageToTarget — 전체 함수임을 뜻하지 않습니다.
		}
	}

	// 그로기 유발 판별 (디자이너가 Payload에서 선택한 경우)
	if (Payload.GroggyType == EDamageGroggyType::HeavyGroggy)
	{
		Spec->AddDynamicAssetTag(GameplayTagSystem::Damage_Type_HeavyGroggy);
	}
	else if (Payload.GroggyType == EDamageGroggyType::LightGroggy)
	{
		Spec->AddDynamicAssetTag(GameplayTagSystem::Damage_Type_Groggy);
	}

	// 자폭 및 팀킬 판별 (GAS 태그 기반)

// [원문 129-130 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 131-137] UDamageSystemLibrary::ApplyDamageToTarget — 전체 함수임을 뜻하지 않습니다.

	if (bIsSelf || bIsTeammate)
	{
		Spec->AddDynamicAssetTag(GameplayTagSystem::Hit_FriendlyFire);
	}

	// 약점 판별

// [원문 138-138 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 139-143] UDamageSystemLibrary::ApplyDamageToTarget — 전체 함수임을 뜻하지 않습니다.
	{
		Spec->AddDynamicAssetTag(GameplayTagSystem::Hit_Weakpoint);
	}

	// SetByCaller 데이터 전송 (방어구 관통력 및 각종 배수)

// [원문 144-144 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 145-145] UDamageSystemLibrary::ApplyDamageToTarget — 전체 함수임을 뜻하지 않습니다.
	Spec->SetSetByCallerMagnitude(GameplayTagSystem::Data_ArmorPenetration, Payload.ArmorPenetration);

// [원문 146-146 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 147-151] UDamageSystemLibrary::ApplyDamageToTarget — 전체 함수임을 뜻하지 않습니다.
	Spec->SetSetByCallerMagnitude(GameplayTagSystem::Data_Multiplier_Weakpoint, Payload.WeakpointMultiplier);
	Spec->SetSetByCallerMagnitude(GameplayTagSystem::Data_Multiplier_FriendlyFire, Payload.FriendlyFireMultiplier);

	// 서버에서 피격자에게 적용
	SourceASC->ApplyGameplayEffectSpecToTarget(*Spec, TargetASC);
