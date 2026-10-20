// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Ability/DamageSystemLibrary.h
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 2-11] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.

	#pragma once

	#include "CoreMinimal.h"
	#include "Kismet/BlueprintFunctionLibrary.h"
	#include "GameplayTagContainer.h"
	#include "Engine/HitResult.h"
	#include "DamageSystemLibrary.generated.h"

	class UGameplayEffect;

// [원문 12-12 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 13-31] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	class AActor;

	UENUM(BlueprintType)
	enum class EDamageGroggyType : uint8
	{
		None			UMETA(DisplayName = "없음 (일반 데미지)"),
		LightGroggy		UMETA(DisplayName = "약한 그로기 (제자리 피격)"),
		HeavyGroggy		UMETA(DisplayName = "강한 그로기 (넉백 피격)")
	};

	USTRUCT(BlueprintType)
	struct FDamagePayload
	{
		GENERATED_BODY()

	public:
		FDamagePayload()
			: BaseDamage(0.0f)
			, ArmorPenetration(0.0f)

// [원문 32-32 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 33-38] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
			, WeakpointMultiplier(1.5f)
			, FriendlyFireMultiplier(0.25f)
			, DoTDuration(0.0f)
			, DoTPeriod(0.0f)
			, GroggyType(EDamageGroggyType::None)
			, DamageEffectClass(nullptr)

// [원문 39-39 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 40-49] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
		{}

		// 기본 데미지
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float BaseDamage;

		// 방어구 관통력 (적의 방어력을 깎고 데미지 계산)
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float ArmorPenetration;


// [원문 50-53 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 54-78] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
		// 약점 명중 시 배수
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float WeakpointMultiplier;

		// 아군(자폭 포함) 피격 시 배수
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float FriendlyFireMultiplier;

		// 단일 타격 대상 정보 (AoE가 아닐 때 필수)
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		FHitResult HitResult;


		// 도트 딜(DoT) 총 지속 시간 (0이면 즉발 데미지)
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage|DoT")
		float DoTDuration;

		// 도트 딜 타격 간격 (예: 1.0이면 1초마다 타격)
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage|DoT")
		float DoTPeriod;

		// 그로기 유발 타입 (일반 / 약한 그로기 / 강한 넉백 그로기)
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage|Effect")
		EDamageGroggyType GroggyType;


// [원문 79-79 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 80-81] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage|Advanced")
		TSubclassOf<UGameplayEffect> DamageEffectClass;

// [원문 82-87 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 88-101] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	};

	/**
	 * 모든 공격 및 기믹에서 공통으로 호출하는 통합 데미지 파이프라인
	 */
	UCLASS()
	class TEAMPROJECT_FIN_API UDamageSystemLibrary : public UBlueprintFunctionLibrary
	{
		GENERATED_BODY()

	public:
		// 공격자가 피격자(들)에게 데미지를 가합니다. (반드시 서버에서만 호출)
		UFUNCTION(BlueprintCallable, Category = "DamageSystem", meta = (WorldContext = "WorldContextObject"))
		static void ApplyGameDamage(const UObject* WorldContextObject, AActor* InstigatorActor, const FDamagePayload& Payload);
