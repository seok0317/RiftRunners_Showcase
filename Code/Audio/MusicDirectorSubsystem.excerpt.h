// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Audio/MusicDirectorSubsystem.h
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 1-8] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
#pragma once

#include "CoreMinimal.h"
#include "Containers/Ticker.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MusicDirectorSubsystem.generated.h"

class UFMODEvent;

// [원문 9-9 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 10-16] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
struct FStreamableHandle;
struct FWorldContext;
namespace FMOD::Studio
{
	class EventDescription;
	class EventInstance;
}

// [원문 17-21 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 22-37] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.

UCLASS()
class TEAMPROJECT_FIN_API UMusicDirectorSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// 네트워크 전달 후 각 머신에서 로컬 음악 상태를 적용한다.
	UFUNCTION(BlueprintCallable, Category = "Audio|Music")
	void SetMusicState(float Value);

	UFUNCTION(BlueprintCallable, Category = "Audio|Music")
	void StopMusic();

// [원문 38-38 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 39-69] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.

private:
	enum class EApplyResult : uint8
	{
		Success,
		NotReady,
		Failed
	};

	// FMOD 타입을 헤더에 노출하지 않고 파라미터의 값 데이터만 보관한다.
	struct FParameterCache
	{
		uint32 IdData1 = 0;
		uint32 IdData2 = 0;
		float Minimum = 0.0f;
		float Maximum = 0.0f;
		bool bRequiresInteger = false;
		bool bValid = false;

		bool IsValueAllowed(float Value) const
		{
			return bValid && FMath::IsFinite(Value) && Value >= Minimum && Value <= Maximum &&
				(!bRequiresInteger || Value == FMath::RoundToFloat(Value));
		}
	};

	friend class FProjectMusicOptimizationTest;

	void LoadMainEvent(TSoftObjectPtr<UFMODEvent> Event);
	void OnEventLoaded(uint32 ExpectedGeneration, TSoftObjectPtr<UFMODEvent> Event);
	EApplyResult ApplyState();

// [원문 70-71 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 72-78] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	bool CacheParameter(FMOD::Studio::EventDescription* Description);
	bool RefreshCurrentInstance();
	void ReleaseCurrentInstance();
	void ApplyOrRetry();
	bool RetryPlayback(float DeltaTime);
	void CancelRetry();
	void OnPreLoadMap(const FWorldContext& WorldContext, const FString& MapName);

// [원문 79-80 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 81-86] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.

	UPROPERTY(Transient)
	TObjectPtr<UFMODEvent> MainEvent;

	// 인스턴스의 stop/release는 ReleaseCurrentInstance에서만 수행한다.
	FMOD::Studio::EventInstance* CurrentInstance = nullptr;

// [원문 87-89 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 90-92] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	TSharedPtr<FStreamableHandle> LoadHandle;
	FTSTicker::FDelegateHandle RetryHandle;
	FDelegateHandle PreLoadMapHandle;

// [원문 93-94 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 95-104] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	FName ParameterName;
	FParameterCache ParameterCache;
	float DesiredValue = 0.0f;
	float AppliedValue = 0.0f;
	bool bHasDesiredState = false;
	bool bHasAppliedState = false;
	bool bLoading = false;
	uint32 Generation = 0;
	double RetryDeadline = 0.0;
};
