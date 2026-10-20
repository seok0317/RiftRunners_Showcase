// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/PCGMap/MapBuild/WorldGenSubSystem.cpp
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 13-14] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
#include "GameCore/BaseGameMode.h"
#include "Environment/JumpMapLayoutController.h"

// [원문 15-15 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 16-16] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
#include "GameCore/Character/PlayerCharacter.h"

// [원문 17-22 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 23-24] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
DEFINE_LOG_CATEGORY_STATIC(LogJumpMapTransition, Log, All);


// [원문 25-65 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 66-66] UWorldGenSubSystem::OnPreLoadMap — 전체 함수임을 뜻하지 않습니다.
	ClearJumpMapPreparation();

// [원문 67-115 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 116-116] UWorldGenSubSystem::Deinitialize — 전체 함수임을 뜻하지 않습니다.
	ClearJumpMapPreparation();

// [원문 117-296 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 297-298] UWorldGenSubSystem::RetryCurrentSector — 전체 함수임을 뜻하지 않습니다.
	if (!IsJumpMap(LastSectorLevel))
	{

// [원문 299-338 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 339-339] UWorldGenSubSystem::ResetRunForLobby — 전체 함수임을 뜻하지 않습니다.
	ClearJumpMapPreparation();

// [원문 340-471 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 472-485] UWorldGenSubSystem::ApplySector — 전체 함수임을 뜻하지 않습니다.
	ClearJumpMapPreparation();
	bPendingJumpMap = IsJumpMap(Level);
	if (bPendingJumpMap)
	{
		bSectorChanging = true;
		JumpMapWorld = World;
		// 레벨 표시 자체가 끝나지 않는 경우도 기존 파티 복귀로 처리한다.
		World->GetTimerManager().SetTimer(JumpMapTimeoutHandle,
			FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				FailJumpMapTransition(TEXT("점프맵 로드/배치 준비가 30초 안에 끝나지 않았습니다."));
			}), 30.f, false);
	}


// [원문 486-486 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 487-487] UWorldGenSubSystem::ApplySector — 전체 함수임을 뜻하지 않습니다.
	if (UGameInstance *GI = GetGameInstance(); GI && !bPendingJumpMap)

// [원문 488-512 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 513-516] UWorldGenSubSystem::ApplySector — 전체 함수임을 뜻하지 않습니다.
			if (bPendingJumpMap)
			{
				FailJumpMapTransition(TEXT("점프맵 레벨 스트리밍에 실패했습니다."));
			}

// [원문 517-522 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 523-526] UWorldGenSubSystem::ApplySector — 전체 함수임을 뜻하지 않습니다.
		if (bPendingJumpMap)
		{
			FailJumpMapTransition(TEXT("점프맵 스트리밍 객체가 없습니다."));
		}

// [원문 527-529 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 530-533] UWorldGenSubSystem::ApplySector — 전체 함수임을 뜻하지 않습니다.
	if (PendingSector)
	{
		PendingSector->OnLevelShown.RemoveDynamic(this, &UWorldGenSubSystem::OnSectorShown);
	}

// [원문 534-549 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 550-588] UWorldGenSubSystem::OnSectorShown — 전체 함수임을 뜻하지 않습니다.
	const ULevel *Level = PendingSector->GetLoadedLevel();
	if (bPendingJumpMap)
	{
		APlayerStart* JumpStart = nullptr;
		AJumpMapLayoutController* LayoutController = nullptr;
		int32 ControllerCount = 0;
		if (Level)
		{
			for (AActor* Actor : Level->Actors)
			{
				if (!IsValid(Actor))
				{
					continue;
				}
				if (!JumpStart)
				{
					JumpStart = Cast<APlayerStart>(Actor);
				}
				if (AJumpMapLayoutController* Candidate = Cast<AJumpMapLayoutController>(Actor))
				{
					LayoutController = Candidate;
					++ControllerCount;
				}
			}
		}
		if (!JumpStart || ControllerCount != 1)
		{
			FailJumpMapTransition(FString::Printf(TEXT("PlayerStart 또는 점프맵 컨트롤러 설정 오류: 시작점=%d 컨트롤러=%d"),
				JumpStart != nullptr, ControllerCount));
			return;
		}
		JumpMapEntry = JumpStart->GetActorTransform();
		AwaitedJumpMapController = LayoutController;
		LayoutController->OnLayoutFinished.AddUObject(this, &ThisClass::OnJumpMapLayoutFinished);
		LayoutController->OnParticipantsReady.AddUObject(this, &ThisClass::OnJumpMapParticipantsReady);
		LayoutController->BeginLayout();
		return;
	}


// [원문 589-620 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 621-624] UWorldGenSubSystem::FinishTransition — 전체 함수임을 뜻하지 않습니다.
	AJumpMapLayoutController* JumpController = AwaitedJumpMapController.Get();
	const bool bFinishJumpMap = JumpController && JumpMapWorld.Get() == World;
	if (!bFinishJumpMap)
	{

// [원문 625-628 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 629-630] UWorldGenSubSystem::FinishTransition — 전체 함수임을 뜻하지 않습니다.
	if (!bFinishJumpMap)
	{

// [원문 631-642 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 643-644] UWorldGenSubSystem::FinishTransition — 전체 함수임을 뜻하지 않습니다.
	if (!bFinishJumpMap)
	{

// [원문 645-653 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 654-660] UWorldGenSubSystem::FinishTransition — 전체 함수임을 뜻하지 않습니다.
			const APlayerState* PlayerState = It->IsValid() ? It->Get()->PlayerState.Get() : nullptr;
			if (bFinishJumpMap && IsValid(PlayerState) && !PlayerState->IsInactive()
				&& !PlayerState->IsOnlyASpectator() && !PlayerState->IsABot())
			{
				FailJumpMapTransition(TEXT("점프맵 참가자의 Pawn이 없어 시작 위치로 이동할 수 없습니다."));
				return;
			}

// [원문 661-678 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 679-683] UWorldGenSubSystem::FinishTransition — 전체 함수임을 뜻하지 않습니다.
			if (bFinishJumpMap)
			{
				FailJumpMapTransition(TEXT("점프맵 시작 위치로 이동하지 못했습니다."));
				return;
			}

// [원문 684-684 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 685-689] UWorldGenSubSystem::FinishTransition — 전체 함수임을 뜻하지 않습니다.
		else if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Pawn))
		{
			// 이전 맵의 체크포인트를 새 맵의 실제 입장 위치로 교체한다.
			PlayerCharacter->SetCheckpoint(PlayerCharacter->GetActorLocation());
		}

// [원문 690-690 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 691-859] UWorldGenSubSystem::FinishTransition 외 7개 함수 구간 — 전체 함수임을 뜻하지 않습니다.

	if (bFinishJumpMap)
	{
		PreloadReachableSectors();
		for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		{
			if (ABasePlayerController* PC = Cast<ABasePlayerController>(It->Get()))
			{
				// 같은 PC의 Reliable RPC 순서로 위치를 먼저 맞춘 뒤 로딩을 종료한다.
				if (APawn* Pawn = PC->GetPawn())
				{
					PC->ClientSetLocation(Pawn->GetActorLocation(), Pawn->GetActorRotation());
				}
				PC->Client_FinishJumpMapLoading(JumpController);
			}
		}
		bSectorChanging = false;
		ClearJumpMapPreparation();
	}
}

bool UWorldGenSubSystem::IsJumpMap(const TSoftObjectPtr<UWorld>& Level) const
{
	if (Level.IsNull())
	{
		return false;
	}
	const FSoftObjectPath Path = Level.ToSoftObjectPath();
	for (const TSoftObjectPtr<UWorld>& JumpMap : GetDefault<UWorldGenSettings>()->JumpMapLevels)
	{
		if (!JumpMap.IsNull() && JumpMap.ToSoftObjectPath() == Path)
		{
			return true;
		}
	}
	return false;
}

void UWorldGenSubSystem::OnJumpMapLayoutFinished(AJumpMapLayoutController* LayoutController, bool bSuccess)
{
	UWorld* World = GetWorld();
	if (!World || !IsValid(LayoutController) || AwaitedJumpMapController.Get() != LayoutController
		|| JumpMapWorld.Get() != World || bJumpMapTransitionFailed)
	{
		return;
	}
	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		if (ABasePlayerController* PC = Cast<ABasePlayerController>(It->Get()); PC && PC->IsLocalController())
		{
			PC->Server_ReportJumpMapReady(LayoutController, bSuccess && IsValid(PC->GetPawn()));
		}
	}
}

void UWorldGenSubSystem::ReportJumpMapReady(ABasePlayerController* Player, AJumpMapLayoutController* LayoutController, bool bSuccess)
{
	UWorld* World = GetWorld();
	if (!World || World->GetNetMode() == NM_Client || !IsValid(Player) || !IsValid(LayoutController)
		|| AwaitedJumpMapController.Get() != LayoutController || JumpMapWorld.Get() != World
		|| bJumpMapTransitionFailed)
	{
		return;
	}
	LayoutController->ReportParticipantReady(Player, bSuccess);
}

void UWorldGenSubSystem::OnJumpMapParticipantsReady(AJumpMapLayoutController* LayoutController, bool bSuccess)
{
	UWorld* World = GetWorld();
	if (!World || World->GetNetMode() == NM_Client || !IsValid(LayoutController)
		|| AwaitedJumpMapController.Get() != LayoutController || JumpMapWorld.Get() != World
		|| bJumpMapTransitionFailed)
	{
		return;
	}
	if (!bSuccess)
	{
		FailJumpMapTransition(LayoutController->GetPreparationFailure());
		return;
	}
	// 기다리는 동안 이전 발판을 유지하고, 전원 준비 완료 뒤 기존 정리를 수행한다.
	GetGameInstance()->GetSubsystem<USectorSubsystem>()->ClearSpawned();
	UnloadLastSubLevel();
	CurrentSector = PendingSector;
	isLastSubLevel = true;
	PendingSector = nullptr;
	FinishTransition(JumpMapEntry);
}

void UWorldGenSubSystem::CompleteJumpMapTransition(AJumpMapLayoutController* LayoutController)
{
	UWorld* World = GetWorld();
	if (!World || !IsValid(LayoutController) || AwaitedJumpMapController.Get() != LayoutController
		|| JumpMapWorld.Get() != World || !LayoutController->IsLocalLayoutReady() || bJumpMapTransitionFailed)
	{
		return;
	}
	bSectorChanging = false;
	if (World->GetNetMode() == NM_Client)
	{
		GetGameInstance()->GetSubsystem<USectorSubsystem>()->ClearSpawned();
		UnloadLastSubLevel();
		CurrentSector = PendingSector;
		isLastSubLevel = true;
		PendingSector = nullptr;
	}
	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		if (ABasePlayerController* PC = Cast<ABasePlayerController>(It->Get()); PC && PC->IsLocalController())
		{
			PC->EndLevelTransition();
		}
	}
	ClearJumpMapPreparation();
}

void UWorldGenSubSystem::FailJumpMapTransition(const FString& Reason)
{
	UWorld* World = GetWorld();
	if (!World || JumpMapWorld.Get() != World || bJumpMapTransitionFailed)
	{
		return;
	}
	bJumpMapTransitionFailed = true;
	UE_LOG(LogJumpMapTransition, Error, TEXT("점프맵 준비 실패: %s"), *Reason);
	World->GetTimerManager().ClearTimer(JumpMapTimeoutHandle);
	if (World->GetNetMode() == NM_Client)
	{
		if (AJumpMapLayoutController* LayoutController = AwaitedJumpMapController.Get())
		{
			for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
			{
				if (ABasePlayerController* PC = Cast<ABasePlayerController>(It->Get()); PC && PC->IsLocalController())
				{
					PC->Server_ReportJumpMapReady(LayoutController, false);
				}
			}
		}
		return;
	}
	ABaseGameMode* GameMode = World->GetAuthGameMode<ABaseGameMode>();
	if (!GameMode || !GameMode->ReturnPartyToRoom())
	{
		UE_LOG(LogJumpMapTransition, Error, TEXT("점프맵 실패 후 대기실 복귀를 시작하지 못했습니다."));
	}
}

void UWorldGenSubSystem::ClearJumpMapPreparation()
{
	if (PendingSector)
	{
		PendingSector->OnLevelShown.RemoveDynamic(this, &UWorldGenSubSystem::OnSectorShown);
	}
	if (UWorld* World = JumpMapWorld.Get())
	{
		World->GetTimerManager().ClearTimer(JumpMapTimeoutHandle);
	}
	if (AJumpMapLayoutController* LayoutController = AwaitedJumpMapController.Get())
	{
		LayoutController->OnLayoutFinished.RemoveAll(this);
		LayoutController->OnParticipantsReady.RemoveAll(this);
		LayoutController->CancelPreparation();
	}
	AwaitedJumpMapController.Reset();
	JumpMapWorld.Reset();
	bPendingJumpMap = false;
	bJumpMapTransitionFailed = false;
}
