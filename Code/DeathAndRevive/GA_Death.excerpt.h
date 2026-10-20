// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Ability/GA_Death.h
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 53-64] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Death|Knockback")
	float DeathKnockbackForce = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Death|Knockback")
	float DeathKnockbackDuration = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Death|Revive")
	TSubclassOf<class AReviveZoneActor> ReviveZoneClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Death|Effect")
	TSubclassOf<class UGameplayEffect> DeathEffectClass;

