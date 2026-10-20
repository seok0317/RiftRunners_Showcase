// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/PCGMap/MapBuild/WorldGenSubSystem.h
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 8-8] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
#include "TimerManager.h"

// [원문 9-11 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 12-13] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
class AJumpMapLayoutController;
class ABasePlayerController;

// [원문 14-69 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 70-73] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	// PC의 준비 보고/완료 통보를 현재 점프맵 인스턴스에만 연결한다.
	void ReportJumpMapReady(ABasePlayerController* Player, AJumpMapLayoutController* LayoutController, bool bSuccess);
	void CompleteJumpMapTransition(AJumpMapLayoutController* LayoutController);


// [원문 74-121 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 122-134] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	bool bPendingJumpMap = false;
	bool bJumpMapTransitionFailed = false;
	TWeakObjectPtr<AJumpMapLayoutController> AwaitedJumpMapController;
	TWeakObjectPtr<UWorld> JumpMapWorld;
	FTransform JumpMapEntry = FTransform::Identity;
	FTimerHandle JumpMapTimeoutHandle;

	bool IsJumpMap(const TSoftObjectPtr<UWorld>& Level) const;
	void OnJumpMapLayoutFinished(AJumpMapLayoutController* LayoutController, bool bSuccess);
	void OnJumpMapParticipantsReady(AJumpMapLayoutController* LayoutController, bool bSuccess);
	void FailJumpMapTransition(const FString& Reason);
	void ClearJumpMapPreparation();

