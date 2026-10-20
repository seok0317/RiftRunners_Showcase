// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/BaseGameState.h
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 34-50] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
// 늦게 접속해도 최신 음악 상태를 받도록 단발 알림 대신 상태를 복제한다.
USTRUCT()
struct FReplicatedMusicState
{
	GENERATED_BODY()


	UPROPERTY()
	bool bHasState = false;

	UPROPERTY()
	float ParameterValue = 0.0f;

	UPROPERTY()
	uint32 Revision = 0;
};


// [원문 51-81 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 82-82] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	virtual void BeginPlay() override;

// [원문 83-100 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 101-104] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	// 서버에서 상태를 설정하고 각 머신의 음악 Director에 전달한다.
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Audio|Music")
	void SetMusicState(float Value);


// [원문 105-239 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 240-247] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	UPROPERTY(ReplicatedUsing = OnRep_MusicState)
	FReplicatedMusicState MusicState;

	UFUNCTION()
	void OnRep_MusicState();

	void ApplyMusicState();

