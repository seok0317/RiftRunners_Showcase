// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/BasePlayerController.h
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 19-19] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
class AJumpMapLayoutController;

// [원문 20-29 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 30-30] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	virtual void FlushPressedKeys() override;

// [원문 31-67 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 68-74] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	// 배치 처리는 점프맵 컨트롤러가 맡고, 소유된 PC는 준비 완료 통신만 전달한다.
	UFUNCTION(Server, Reliable)
	void Server_ReportJumpMapReady(AJumpMapLayoutController* LayoutController, bool bSuccess);

	UFUNCTION(Client, Reliable)
	void Client_FinishJumpMapLoading(AJumpMapLayoutController* LayoutController);

