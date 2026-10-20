// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Character/PlayerCharacter.h
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 1-6] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"

// [원문 7-7 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 8-14] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

// [원문 15-17 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 18-19] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
class UProjectInputSettingsSubsystem;
class AWeaponBase;

// [원문 20-23 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 24-41] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
enum class EProjectInputAction : uint8;
enum class EProjectInputMode : uint8;

/**
 * 3인칭 조작 및 Enhanced Input을 지원하는 플레이어 캐릭터 클래스
 */
UCLASS()
class TEAMPROJECT_FIN_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	friend class FProjectInputSettingsTest;

public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;


// [원문 42-44 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 45-47] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	virtual void PawnClientRestart() override;
	virtual void UnPossessed() override;
	virtual void Tick(float DeltaTime) override;

// [원문 48-48 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 49-75] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.

	/** 메뉴 진입·포커스 상실 시 유지 입력을 해제하며 스마트 트래킹 사격은 실행하지 않는다. */
	void ResetPersistentInput();

	/** 카메라 붐 컴포넌트 반환 */
	FORCEINLINE USpringArmComponent *GetCameraBoom() const { return CameraBoom; }

	/** 팔로우 카메라 컴포넌트 반환 */
	FORCEINLINE UCameraComponent *GetFollowCamera() const { return FollowCamera; }

	/** Returns SnowDeformationComponentV2 subobject **/
	FORCEINLINE class USnowDeformationComponentV2* GetSnowDeformationComponentV2() const { return SnowDeformationComponentV2; }

	/** Snow deformation continuous sweep component (V2) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Snow Deformation", meta = (AllowPrivateAccess = "true"))
	class USnowDeformationComponentV2* SnowDeformationComponentV2;

	// --- Checkpoint System ---
	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void SetCheckpoint(FVector NewLocation);

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void RespawnAtCheckpoint();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Checkpoint")
	FVector LastCheckpointLocation;


// [원문 76-77 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 78-81] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	/** 서버가 확정한 실제 피해를 소유 클라이언트의 화면 연출에 전달한다. */
	UFUNCTION(Client, Unreliable)
	void ClientNotifyDamageTaken(float DamageAmount);


// [원문 82-84 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 85-106] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	/** Enhanced Input 바인딩 액션 핸들러 */
	void Move(const FInputActionValue &Value);
	void StopMove();
	void Look(const FInputActionValue &Value);
	void HandlePersistentInputStarted(EProjectInputAction Action);
	void HandlePersistentInputCompleted(EProjectInputAction Action);
	void HandlePersistentInputCanceled(EProjectInputAction Action);
	EProjectInputMode GetPersistentInputMode(EProjectInputAction Action) const;
	void CancelAimInput();
	void StartSprint();
	void StopSprint();
	void CancelSprintAbility();
	void StartCrouch();
	void StopCrouch();
	void StartAim();
	void StopAim();

// [원문 107-109 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 110-129] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.

public:
	/** 화면 중앙(크로스헤어)을 정확히 바라보는 보정된 AimOffset 각도를 계산합니다. */
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void GetAimOffsetAngles(float &OutPitch, float &OutYaw) const;

	/** 크로스헤어 레이저의 최대 사거리 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AimOffset|Calibration")
	float AimTraceDistance = 10000.0f;

	/** 시선 각도를 계산할 기준 뼈(본) 이름 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AimOffset|Calibration")
	FName AimSocketName = FName("head");

	/** 서버로 구르기 방향을 확실하게 전달하기 위한 변수 및 RPC */
	FVector ReplicatedDodgeDirection;

	UFUNCTION(Server, Reliable)
	void ServerSetDodgeDirection(FVector InDirection);


// [원문 130-132 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 133-175] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	/** [네트워크] Simulated Proxy에게 ControlRotation.Yaw를 복제하기 위한 변수 (에임 오프셋 좌우 동기화용) */
	UPROPERTY(Replicated)
	float ReplicatedControlYaw = 0.0f;

	/** [네트워크] 멀티플레이어 환경에서 가짜 로프 시뮬레이션을 동기화하기 위한 앵커 참조 */
	UPROPERTY(ReplicatedUsing=OnRep_SwingingAnchor)
	class ARopeAnchorActor* CurrentSwingingAnchor;

	// AnimBP에서 앵커에 쉽게 접근할 수 있도록 노출
	UFUNCTION(BlueprintPure, Category = "Rope")
	class ARopeAnchorActor* GetCurrentSwingingAnchor() const { return CurrentSwingingAnchor; }

	/** [네트워크 로컬] 클라이언트에서 밧줄을 놓았을 때(Current가 null이 될 때) 어떤 앵커를 해제할지 기억해두는 변수 */
	UPROPERTY()
	class ARopeAnchorActor* PreviousSwingingAnchor;

	UFUNCTION()
	void OnRep_SwingingAnchor();

protected:
	/** 정밀 조준 보정(IK)을 위한 내부 상태 변수 */
	mutable float CurrentAimPitch = 0.0f;
	mutable float CurrentAimYaw = 0.0f;
	/** 몸 기준 상대각과 분리한 좌우 총구 정밀 보정값 */
	mutable float CurrentAimYawCorrection = 0.0f;
	mutable uint64 AimYawCorrectionFrame = MAX_uint64;

protected:
	/** 구르기 시작 */
	void StartDodge();

	/** 이벤트 기반 회전 모드 동적 갱신 */
	void UpdateRotationMode();

	/** 카메라 줌 인/아웃(FOV) 보간용 타이머 함수 */
	void UpdateCameraZoom();

	/** 앉기 카메라 보간용 타이머 함수 */
	void UpdateCrouchCameraOffset();

	/** GAS 태그 변화 이벤트 콜백 (조준 동기화) */
	void OnAimingTagChanged(const struct FGameplayTag Tag, int32 NewCount);


// [원문 176-193 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 194-203] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	void EvaluateInputQueue();
	void QueueInputEvaluation();
	void BindInputSettings();
	void UnbindInputSettings();
	void OnInputModeChanged(EProjectInputAction Action, EProjectInputMode Mode);
	void OnInputStaminaChanged(const struct FOnAttributeChangeData& Data);

	UFUNCTION()
	void OnInputWeaponEquipped(AWeaponBase* NewWeapon);


// [원문 204-209 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 210-211] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	/** 매핑 컨텍스트를 로컬 플레이어 서브시스템에 등록 */
	void RegisterInputMappingContext();

// [원문 212-220 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 221-273] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
protected:
	/** 현재 조준 중인지 여부 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
	bool bIsAiming = false;

	/** 현재 사격 중인지 여부 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
	bool bIsFiring = false;

	/** 홀드·토글의 유지 의도는 어빌리티의 실제 활성 상태와 별도로 보존한다. */
	bool bWantsToSprint = false;
	/** 방향 입력이 있을 때만 달리기 어빌리티를 활성화한다. */
	bool bHasMovementInput = false;
	bool bWantsToAim = false;
	bool bWantsToCrouch = false;
	bool bAimInputUsesSmartTracking = false;

	TWeakObjectPtr<UProjectInputSettingsSubsystem> InputSettings;
	TWeakObjectPtr<UAbilitySystemComponent> InputAbilitySystem;
	FDelegateHandle InputModeChangedHandle;
	FDelegateHandle InputStaminaChangedHandle;
	FTimerHandle InputQueueTimerHandle;

	/** 기본 시야각 (평상시) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom")
	float DefaultFOV = 90.0f;

	/** 조준 시 시야각 (줌 인) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom")
	float AimFOV = 60.0f;

	/** 카메라 줌 인/아웃 전환 속도 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Zoom")
	float ZoomInterpSpeed = 15.0f;

	/** 평상시 카메라 스프링암 길이 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Rope")
	float DefaultTargetArmLength = 140.0f;

	/** 로프 스윙 시 카메라 스프링암 길이 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Rope")
	float RopeTargetArmLength = 300.0f;

	/** 스프링암 길이 전환 속도 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Rope")
	float ArmLengthInterpSpeed = 5.0f;

	/** 현재 목표로 하는 카메라 시야각(FOV) 내부 변수 */
	float TargetFOV = 90.0f;

	/** 카메라 줌 업데이트용 타이머 핸들 */
	FTimerHandle ZoomTimerHandle;


// [원문 274-286 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 287-341] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	/** 앉을 때 카메라가 밑으로 얼마나 부드럽게 내려갈지 (원하는 만큼 설정) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Crouch")
	float CrouchCameraDropAmount = 45.0f;

	/** 앉기/일어서기 시 카메라 보간 속도 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Crouch")
	float CrouchCameraInterpSpeed = 12.0f;

	/** 카메라 높이 조절 타이머 핸들 */
	FTimerHandle CrouchCameraTimerHandle;

	/** 현재 목표로 하는 카메라 Z축 오프셋 */
	float TargetCameraZOffset = 0.0f;

protected:
	/** 3인칭 카메라 붐 (스프링암) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** 플레이어를 추적하는 3인칭 카메라 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	/** 기본 인풋 매핑 컨텍스트 (IMC) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|MappingContext")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** 기본 매핑 컨텍스트 우선순위 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|MappingContext")
	int32 DefaultMappingPriority = 0;

	/** 이동 입력 액션 (IA_Move, 2D Axis) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> MoveAction;

	/** 시점 회전 입력 액션 (IA_Look, 2D Axis) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> LookAction;

	/** 구르기 입력 액션 (IA_Dodge, Digital) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> DodgeAction;

	/** 달리기 입력 액션 (IA_Sprint, Digital) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> SprintAction;

	/** 앉기 입력 액션 (IA_Crouch, Digital) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> CrouchAction;

	/** 조준 입력 액션 (IA_Aim, Digital) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Action")
	TObjectPtr<UInputAction> AimAction;


// [원문 342-364 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 365-376] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	/** 달리기 키 입력 시 활성화할 어빌리티 클래스 참조 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TSubclassOf<class UGameplayAbility> SprintAbilityClass;

	/** 앉기 키 입력 시 활성화할 어빌리티 클래스 참조 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TSubclassOf<class UGameplayAbility> CrouchAbilityClass;

	/** 조준 키 입력 시 활성화할 어빌리티 클래스 참조 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TSubclassOf<class UGameplayAbility> AimAbilityClass;


// [원문 377-384 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 385-387] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	/** 구르기 키 입력 시 활성화할 어빌리티 클래스 참조 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TSubclassOf<class UGameplayAbility> DodgeAbilityClass;

// [원문 388-408 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 409-430] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.

	/** 부활 시 캐릭터 처리 */
	virtual void Revive() override;

protected:
	/** 사망 시 카메라 서서히 멀어지게 하는 타이머 핸들 */
	FTimerHandle TH_CameraZoom;

	void UpdateCameraFadeSettings();

public:
	/** 로프 탑승 상태에 따라 카메라 줌 타이머를 켜는 이벤트 함수 */
	void SetRopeCameraMode(bool bIsSwinging);

	/** 로프 탑승 중 무기를 숨기기 위한 함수 */
	void SetWeaponHidden(bool bHideWeapon);

protected:
	FTimerHandle RopeCameraTimerHandle;
	float TargetRopeArmLength = 140.0f;
	void UpdateRopeCameraOffset();
};
