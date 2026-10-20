// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/BaseGameState.cpp
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 9-11] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "GameCore/Audio/MusicDirectorSubsystem.h"

// [원문 12-196 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 197-241] ABaseGameState::BeginPlay 외 3개 함수 구간 — 전체 함수임을 뜻하지 않습니다.
void ABaseGameState::BeginPlay()
{
	Super::BeginPlay();
	// 초기 복제가 BeginPlay보다 먼저 도착했어도 최신 상태를 적용한다.
	ApplyMusicState();
}

void ABaseGameState::SetMusicState(float Value)
{
	if (!HasAuthority())
	{
		return;
	}
	if (!FMath::IsFinite(Value))
	{
		UE_LOG(LogProjectMusicState, Warning, TEXT("유효하지 않은 음악 상태 값."));
		return;
	}
	MusicState.bHasState = true;
	MusicState.ParameterValue = Value;
	++MusicState.Revision;
	ForceNetUpdate();
	ApplyMusicState();
}

void ABaseGameState::OnRep_MusicState()
{
	ApplyMusicState();
}

void ABaseGameState::ApplyMusicState()
{
	if (!MusicState.bHasState || GetNetMode() == NM_DedicatedServer)
	{
		return;
	}
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (UMusicDirectorSubsystem* Director = GameInstance->GetSubsystem<UMusicDirectorSubsystem>())
		{
			Director->SetMusicState(MusicState.ParameterValue);
		}
	}
}


// [원문 242-516 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 517-517] ABaseGameState::GetLifetimeReplicatedProps — 전체 함수임을 뜻하지 않습니다.
	DOREPLIFETIME(ABaseGameState, MusicState);
