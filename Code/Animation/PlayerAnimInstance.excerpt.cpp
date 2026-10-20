// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Animation/PlayerAnimInstance.cpp
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 1-11] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlayerAnimInstance.h"

#include "../Character/BaseCharacter.h"
#include "../Character/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "../Tags/GameplayTagSystem.h"

// [원문 12-14 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 15-28] UPlayerAnimInstance::UPlayerAnimInstance, UPlayerAnimInstance::NativeInitializeAnimation — 전체 함수임을 뜻하지 않습니다.
#include "Components/SkeletalMeshComponent.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	if (OwnerCharacter.IsValid())
	{
		MovementComponent = OwnerCharacter->GetCharacterMovement();

// [원문 29-29 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 30-50] UPlayerAnimInstance::NativeInitializeAnimation, UPlayerAnimInstance::NativeUpdateAnimation — 전체 함수임을 뜻하지 않습니다.
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!OwnerCharacter.IsValid())
	{
		OwnerCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
		if (OwnerCharacter.IsValid())
		{
			MovementComponent = OwnerCharacter->GetCharacterMovement();
		}
	}

	if (!OwnerCharacter.IsValid() || !MovementComponent.IsValid())
	{
		return;
	}


// [원문 51-51 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 52-53] UPlayerAnimInstance::NativeUpdateAnimation — 전체 함수임을 뜻하지 않습니다.
	UpdateLocomotionValues(DeltaSeconds);
	UpdateAimOffsetValues(DeltaSeconds);

// [원문 54-77 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 78-78] UPlayerAnimInstance::BindAbilitySystemEvents — 전체 함수임을 뜻하지 않습니다.
		UnbindGameplayTagEvent(PreviousASC, GameplayTagSystem::State_Movement_Sprinting);

// [원문 79-79 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 80-80] UPlayerAnimInstance::BindAbilitySystemEvents — 전체 함수임을 뜻하지 않습니다.
		UnbindGameplayTagEvent(PreviousASC, GameplayTagSystem::State_Dead);

// [원문 81-84 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 85-85] UPlayerAnimInstance::BindAbilitySystemEvents — 전체 함수임을 뜻하지 않습니다.
	BindGameplayTagEvent(ASC, GameplayTagSystem::State_Movement_Sprinting, &UPlayerAnimInstance::OnSprintingTagChanged);

// [원문 86-86 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 87-87] UPlayerAnimInstance::BindAbilitySystemEvents — 전체 함수임을 뜻하지 않습니다.
	BindGameplayTagEvent(ASC, GameplayTagSystem::State_Dead, &UPlayerAnimInstance::OnDeadTagChanged);

// [원문 88-110 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 111-272] UPlayerAnimInstance::UpdateLocomotionValues 외 4개 함수 구간 — 전체 함수임을 뜻하지 않습니다.
void UPlayerAnimInstance::UpdateLocomotionValues(float DeltaSeconds)
{
	Velocity = MovementComponent->Velocity;
	GroundSpeed = Velocity.Size2D();
	Acceleration = MovementComponent->GetCurrentAcceleration();

	bHasAcceleration = Acceleration.SizeSquared2D() > 0.0f;
	bIsMoving = GroundSpeed > 3.0f;
	
	bShouldMove = bHasAcceleration && bIsMoving;

	// 이동 중일 때만 걷기/뛰기 상태를 업데이트하여 Stop 진입 시 마지막 속도 상태 유지
	if (bShouldMove)
	{
		bWasSprinting = (GroundSpeed > 250.0f);
	}

	// 캐릭터 정면 회전 대비 이동 방향 각도 계산 (-180 ~ +180도)
	// [다리 부들거림 픽스] 속도가 거의 0일 때 Velocity 벡터는 미세한 마찰/물리로 인해 사방으로 튀기 때문에 Direction이 홱홱 바뀝니다.
	// 따라서 의미 있는 속도(GroundSpeed > 3.0f)일 때만 Direction을 업데이트하여 출발(Start) 시 다리 블렌드스페이스가 요동치는 것을 막습니다.
	if (bIsMoving)
	{
		Direction = CalculateDirection(Velocity, OwnerCharacter->GetActorRotation());
	}

	// [핵심 로직] 속도(관성)와 가속도(입력)의 방향이 얼추 일치할 때(정상 주행 중)만 방향을 저장합니다 (Stop 노드용).
	if (bHasAcceleration && GroundSpeed > 50.0f)
	{
		const FVector NormVel = Velocity.GetSafeNormal2D();
		const FVector NormAcc = Acceleration.GetSafeNormal2D();

		// 내적이 0.5 이상(약 60도 이내)일 때만 업데이트
		if (FVector::DotProduct(NormVel, NormAcc) > 0.5f)
		{
			SavedMovementDirection = Direction;
		}
	}

	// 자세 및 상태 업데이트
	bIsCrouching = MovementComponent->IsCrouching();
	bIsFalling = MovementComponent->IsFalling();
	bIsGrounded = !bIsFalling;

	// 피벗(급격한 방향 전환) 감지: 일정 속도 이상 이동 중 가속도와 속도의 내적이 음수일 때
	if (bHasAcceleration && GroundSpeed > 150.0f)
	{
		const FVector NormalizedVelocity = Velocity.GetSafeNormal2D();
		const FVector NormalizedAcceleration = Acceleration.GetSafeNormal2D();
		const float DotProduct = FVector::DotProduct(NormalizedVelocity, NormalizedAcceleration);

		if (DotProduct < -0.2f)
		{
			// [수정됨] 언리얼 내장 함수 대신, 수학적으로 100% 정확한 로컬 요(Yaw) 각도를 직접 계산합니다.
			// 1. 월드 공간의 가속도(입력)를 캐릭터가 바라보는 기준(로컬 공간)으로 역변환합니다.
			const FVector LocalAccel = OwnerCharacter->GetActorRotation().UnrotateVector(Acceleration);
			
			// 2. Atan2를 사용하여 정확한 방향 각도(-180 ~ 180)를 추출합니다.
			const float PivotAngleRaw = FMath::RadiansToDegrees(FMath::Atan2(LocalAccel.Y, LocalAccel.X));

			// [수정됨] if (!bIsPivot) 잠금을 해제하여, 피벗 중 입력이 바뀌어도 즉각적으로 올바른 상태를 찾도록 합니다.
			if (PivotAngleRaw >= -45.0f && PivotAngleRaw <= 45.0f)
			{
				CurrentPivotDirection = EPivotDirection::Forward;
			}
			else if (PivotAngleRaw > 45.0f && PivotAngleRaw <= 135.0f)
			{
				CurrentPivotDirection = EPivotDirection::Right;
			}
			else if (PivotAngleRaw >= -135.0f && PivotAngleRaw < -45.0f)
			{
				CurrentPivotDirection = EPivotDirection::Left;
			}
			else
			{
				CurrentPivotDirection = EPivotDirection::Backward;
			}

			bIsPivot = true;
			PivotAngle = FMath::RadiansToDegrees(FMath::Acos(FMath::Clamp(DotProduct, -1.0f, 1.0f)));
		}
		else
		{
			bIsPivot = false;
			PivotAngle = 0.0f;
		}
	}
	else
	{
		bIsPivot = false;
		PivotAngle = 0.0f;
	}
}

void UPlayerAnimInstance::OnSprintingTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	// 태그 델리게이트 이벤트가 발생했을 때만 단 1번 호출됨
	bIsSprinting = (NewCount > 0);
}

void UPlayerAnimInstance::OnAimingTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	bIsAiming = (NewCount > 0);
}

void UPlayerAnimInstance::OnDeadTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	bIsDead = (NewCount > 0);
	if (!bIsDead)
	{
		bUseDeathPose = false;
	}
}

void UPlayerAnimInstance::UpdateAimOffsetValues(float DeltaSeconds)
{
	float TargetPitch = 0.0f;
	float TargetYaw = 0.0f;

	// [크로스헤어 보정] 로컬 플레이어는 카메라 중심선(크로스헤어)을 쳐다보도록 정밀 계산된 각도를 사용합니다.
	if (OwnerCharacter->IsLocallyControlled())
	{
		if (APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(OwnerCharacter))
		{
			PlayerChar->GetAimOffsetAngles(TargetPitch, TargetYaw);
			TargetPitch = FMath::Clamp(TargetPitch, -90.0f, 90.0f);
			
			if (TargetYaw > 90.0f) TargetYaw = 180.0f - TargetYaw;
			else if (TargetYaw < -90.0f) TargetYaw = -180.0f - TargetYaw;
		}
	}
	else
	{
		// [네트워크 동기화] 원격 클라이언트(Simulated Proxy)는 카메라가 없으므로 서버가 복제해준 회전값을 사용합니다.
		const FRotator AimRotation = OwnerCharacter->GetBaseAimRotation();
		const FRotator ActorRotation = OwnerCharacter->GetActorRotation();

		const float NormalizedPitch = FRotator::NormalizeAxis(AimRotation.Pitch);
		TargetPitch = FMath::Clamp(NormalizedPitch, -90.0f, 90.0f);

		float RealAimYaw = AimRotation.Yaw;
		if (OwnerCharacter->GetLocalRole() == ROLE_SimulatedProxy)
		{
			if (APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(OwnerCharacter))
			{
				RealAimYaw = PlayerChar->ReplicatedControlYaw;
			}
		}

		const FRotator RealAimRot(AimRotation.Pitch, RealAimYaw, 0.0f);
		const FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(RealAimRot, ActorRotation);
		TargetYaw = DeltaRot.Yaw;

		if (TargetYaw > 90.0f) TargetYaw = 180.0f - TargetYaw;
		else if (TargetYaw < -90.0f) TargetYaw = -180.0f - TargetYaw;
	}

	// 로컬 좌우 상대각은 즉시 적용해 몸이 돌아간 뒤 이전 오프셋이 남지 않도록 한다.
	// 상하 보정, 달리기 복귀, 원격 플레이어의 기존 보간은 유지한다.
	const bool bUseRelativeAimYaw = OwnerCharacter->IsLocallyControlled() && !bIsSprinting;
	AimPitch = FMath::FInterpTo(AimPitch, TargetPitch, DeltaSeconds, 15.0f);
	AimYaw = bUseRelativeAimYaw ? TargetYaw : FMath::FInterpTo(AimYaw, TargetYaw, DeltaSeconds, 15.0f);
}

// [원문 273-366 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 367-367] UPlayerAnimInstance::UpdateLeftHandIKAlpha — 전체 함수임을 뜻하지 않습니다.
	bool bIsReviving = false;

// [원문 368-368 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 369-369] UPlayerAnimInstance::UpdateLeftHandIKAlpha — 전체 함수임을 뜻하지 않습니다.
	if (UAbilitySystemComponent* ASC = OwnerCharacter->GetAbilitySystemComponent())

// [원문 370-370 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 371-380] UPlayerAnimInstance::UpdateLeftHandIKAlpha — 전체 함수임을 뜻하지 않습니다.
		bIsReloading = ASC->HasMatchingGameplayTag(GameplayTagSystem::State_Weapon_Reloading);
		bIsReviving = ASC->HasMatchingGameplayTag(GameplayTagSystem::State_Reviving);
	}

	if (bIsDead || bIsReviving)
	{
		// 사망 또는 부활 시 손이 꺾이는 것을 방지하기 위해 IK 즉시 해제
		TargetLeftHandIKAlpha = 0.0f;
		LeftHandIKAlpha = 0.0f; // 즉각적으로 풀리게 Interp 생략 가능
		return;
