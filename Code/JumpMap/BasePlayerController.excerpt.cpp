// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/BasePlayerController.cpp
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 7-7] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
#include "Environment/JumpMapLayoutController.h"

// [원문 8-12 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 13-13] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
#include "GameCore/Character/PlayerCharacter.h"

// [원문 14-31 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 32-41] ABasePlayerController::FlushPressedKeys — 전체 함수임을 뜻하지 않습니다.
void ABasePlayerController::FlushPressedKeys()
{
	// 키 해제 이벤트보다 먼저 정리해야 스마트 트래킹이 메뉴에서 사격하지 않는다.
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn()))
	{
		PlayerCharacter->ResetPersistentInput();
	}
	Super::FlushPressedKeys();
}


// [원문 42-409 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 410-425] ABasePlayerController::Server_ReportJumpMapReady_Implementation, ABasePlayerController::Client_FinishJumpMapLoading_Implementation — 전체 함수임을 뜻하지 않습니다.
void ABasePlayerController::Server_ReportJumpMapReady_Implementation(AJumpMapLayoutController* LayoutController, bool bSuccess)
{
	if (UWorldGenSubSystem* Sys = GetGameInstance()->GetSubsystem<UWorldGenSubSystem>())
	{
		Sys->ReportJumpMapReady(this, LayoutController, bSuccess);
	}
}

void ABasePlayerController::Client_FinishJumpMapLoading_Implementation(AJumpMapLayoutController* LayoutController)
{
	if (UWorldGenSubSystem* Sys = GetGameInstance()->GetSubsystem<UWorldGenSubSystem>())
	{
		Sys->CompleteJumpMapTransition(LayoutController);
	}
}

