// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Animation/PlayerAnimInstance.h
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 2-5] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.

#pragma once

#include "CoreMinimal.h"

// [원문 6-7 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 8-20] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
#include "PlayerAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EPivotDirection : uint8
{
	Forward UMETA(DisplayName = "Forward"),
	Backward UMETA(DisplayName = "Backward"),
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right")
};

class ABaseCharacter;
class UCharacterMovementComponent;

// [원문 21-21 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 22-27] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.

/**
 * 플레이어 캐릭터의 애니메이션 블루프린트용 C++ 베이스 클래스
 * 모든 계산은 C++에서 수행하며, 애님 블루프린트(ABP)에서는 변수를 읽기만(Read-Only) 합니다.
 */
UCLASS()

// [원문 28-28 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 29-36] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
{
	GENERATED_BODY()

public:
	UPlayerAnimInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

// [원문 37-37 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 38-48] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.

protected:
	/** 내부 연산 헬퍼 함수 */
	void UpdateLocomotionValues(float DeltaSeconds);
	void UpdateAimOffsetValues(float DeltaSeconds);

	/** GAS 태그 변화 이벤트 콜백 */
	void OnSprintingTagChanged(const FGameplayTag Tag, int32 NewCount);
	void OnAimingTagChanged(const FGameplayTag Tag, int32 NewCount);
	void OnDeadTagChanged(const FGameplayTag Tag, int32 NewCount);


// [원문 49-54 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 55-64] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
protected:
	/* -------------------------------------------------------------------------
	 * 캐싱된 참조 포인터
	 * ------------------------------------------------------------------------- */
	UPROPERTY(BlueprintReadOnly, Category = "References")
	TWeakObjectPtr<ABaseCharacter> OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	TWeakObjectPtr<UCharacterMovementComponent> MovementComponent;


// [원문 65-67 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 68-155] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	/* -------------------------------------------------------------------------
	 * 기본 이동 및 속도 변수 (Locomotion)
	 * ------------------------------------------------------------------------- */
	 /** 수평 이동 속력 (Size2D) - BlendSpace 축 값으로 사용 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	float GroundSpeed = 0.0f;

	/** 이동 속도 벡터 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	FVector Velocity = FVector::ZeroVector;

	/** 입력 가속도 벡터 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	FVector Acceleration = FVector::ZeroVector;

	/** 캐릭터 기준 이동 방향 각도 (-180 ~ +180도) - 스트레이프 BlendSpace 축 값으로 사용 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	float Direction = 0.0f;

	/** 지상 속도가 일정 임계값(3.0) 이상인지 여부 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	bool bIsMoving = false;

	/** 가속도 입력이 존재하는지 여부 (Size2D > 0) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	bool bHasAcceleration = false;

	/** 가속도 입력이 있고 실제로 이동 중인지 여부 (Start / Stop 상태 전이의 핵심 조건) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	bool bShouldMove = false;

	/** 정지 상태에 진입할 때 뛰고 있었는지 걷고 있었는지 판별용 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	bool bWasSprinting = false;



	/** 현재 조준(Aiming) 중인지 여부 - GAS 태그로만 업데이트 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	bool bIsAiming = false;

	/** 현재 사망(Dead) 상태인지 여부 - GAS 태그 델리게이트로 업데이트 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Posture")
	bool bIsDead = false;

	/* -------------------------------------------------------------------------
	 * Aim Offset (상체 회전) 관련 변수
	 * ------------------------------------------------------------------------- */
	 /** 이동 중 급격하게 반대/측면 방향으로 전환하는 순간 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	bool bIsPivot = false;

	/** 피벗/정지 시 사용할 확정된 방향 상태 (블렌드 스페이스 튐 방지용 Enum) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	EPivotDirection CurrentPivotDirection = EPivotDirection::Forward;

	/** 정지 시 애니메이션 튐 방지를 위해, 마지막으로 안정적이던 이동(관성) 방향을 기록 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	float SavedMovementDirection = 0.0f;


	/** 피벗 시 속도 방향과 가속도 방향 사이의 각도 차이 (0 ~ 180도) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion")
	float PivotAngle = 0.0f;

	/* -------------------------------------------------------------------------
	 * 상태 및 자세 변수 (States & Posture)
	 * ------------------------------------------------------------------------- */
	 /** 스프린팅(달리기) 상태 여부 (GAS 태그 델리게이트로 업데이트되어 틱 낭비 없음) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Posture")
	bool bIsSprinting = false;

	/** 앉기(크라우치) 상태 여부 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Posture")
	bool bIsCrouching = false;

	/** 공중 낙하 상태 여부 (점프 없음, 지형 추락/낙하 감지) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Posture")
	bool bIsFalling = false;

	/** 지면에 닿아있는 상태인지 여부 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Posture")
	bool bIsGrounded = true;

	/* -------------------------------------------------------------------------
	 * 에임 오프셋 변수 (Aim Offset)
	 * ------------------------------------------------------------------------- */
	 /** 현재 적용 중인 최종 조준 상하 각도 */

// [원문 156-157 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 158-160] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	float AimPitch = 0.0f;

	/** 현재 적용 중인 최종 조준 좌우 각도 */

// [원문 161-162 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 163-163] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	float AimYaw = 0.0f;
