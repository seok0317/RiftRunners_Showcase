// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Attribute/CharacterAttributeSet.h
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 44-59] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthCapMultiplier, Category = "Attributes|Health")
	FGameplayAttributeData HealthCapMultiplier;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, HealthCapMultiplier)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaCapMultiplier, Category = "Attributes|Stamina")
	FGameplayAttributeData StaminaCapMultiplier;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, StaminaCapMultiplier)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRegenRate, Category = "Attributes|Stamina")
	FGameplayAttributeData StaminaRegenRate;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, StaminaRegenRate)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaCostMultiplier, Category = "Attributes|Stamina")
	FGameplayAttributeData StaminaCostMultiplier;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, StaminaCostMultiplier)


// [원문 60-63 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 64-71] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Attributes|Defense")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Armor)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackPower, Category = "Attributes|Offense")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, AttackPower)


// [원문 72-79 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 80-84] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	// 메타 어트리뷰트 (복제되지 않음, 데미지 계산 및 체력 차감용 임시 변수)
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Meta")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Damage)


// [원문 85-97 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 98-109] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	UFUNCTION()
	void OnRep_HealthCapMultiplier(const FGameplayAttributeData& OldHealthCapMultiplier) const;

	UFUNCTION()
	void OnRep_StaminaCapMultiplier(const FGameplayAttributeData& OldStaminaCapMultiplier) const;

	UFUNCTION()
	void OnRep_StaminaRegenRate(const FGameplayAttributeData& OldStaminaRegenRate) const;

	UFUNCTION()
	void OnRep_StaminaCostMultiplier(const FGameplayAttributeData& OldStaminaCostMultiplier) const;


// [원문 110-112 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 113-118] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UFUNCTION()
	void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower) const;

