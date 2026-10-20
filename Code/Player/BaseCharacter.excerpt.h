// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Character/BaseCharacter.h
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 7-7] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
#include "GameplayTagContainer.h"

// [원문 8-13 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 14-19] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedDelegate, float, CurrentHealth, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChangedDelegate, float, CurrentStamina, float, MaxStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSnowDebuffChangedDelegate, bool, bIsActive);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageTakenDelegate, float, DamageAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthCapMultiplierChangedDelegate, float, Multiplier);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaCapMultiplierChangedDelegate, float, Multiplier);

// [원문 20-20 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 21-23] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.

#define ECC_TraceAttack  ECC_GameTraceChannel2
#define ECC_Hitbox       ECC_GameTraceChannel3

// [원문 24-54 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 55-75] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	// 부활 시 상태 및 물리 초기화
	virtual void Revive();

	UPROPERTY(BlueprintAssignable, Category = "GAS|Events")
	FOnHealthChangedDelegate OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Events")
	FOnStaminaChangedDelegate OnStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Events")
	FOnSnowDebuffChangedDelegate OnSnowDebuffChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Events")
	FOnDamageTakenDelegate OnDamageTaken;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Events")
	FOnHealthCapMultiplierChangedDelegate OnHealthCapMultiplierChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Events")
	FOnStaminaCapMultiplierChangedDelegate OnStaminaCapMultiplierChanged;


// [원문 76-81 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 82-84] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	UFUNCTION()
	void OnDeadTagChanged(const FGameplayTag CallbackTag, int32 NewCount);


// [원문 85-87 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 88-93] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Effects")
	TArray<TSubclassOf<class UGameplayEffect>> DefaultEffects;


// [원문 94-97 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 98-100] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Tags")
	FGameplayTag CharacterRoleTag;


// [원문 101-114 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 115-117] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Death")
	bool bDisableMovementOnDeathStart = false;


// [원문 118-154 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 155-159] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	void OnHealthChangedCallback(const FOnAttributeChangeData& Data);
	void OnStaminaChangedCallback(const FOnAttributeChangeData& Data);
	void OnHealthCapMultiplierChangedCallback(const FOnAttributeChangeData& Data);
	void OnStaminaCapMultiplierChangedCallback(const FOnAttributeChangeData& Data);
	void OnSnowDebuffTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
