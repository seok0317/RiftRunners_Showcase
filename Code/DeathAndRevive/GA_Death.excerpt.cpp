// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Ability/GA_Death.cpp
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 1-1] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
#include "GameCore/Ability/GA_Death.h"

// [원문 2-3 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 4-5] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
#include "GameCore/Interact/ReviveZoneActor.h"
#include "Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h"

// [원문 6-49 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 50-98] UGA_Death::ActivateAbility — 전체 함수임을 뜻하지 않습니다.
	// 넉백 수치가 0보다 클 때만 밀려나는 물리(Root Motion) 효과를 적용합니다.
	if (DeathKnockbackForce > 0.0f && DeathKnockbackDuration > 0.0f)
	{
		FVector PushDirection = FVector::ZeroVector;

		if (SectionName == SectionBack)
		{
			// Back 섹션: 앞으로 날아감
			PushDirection = Character->GetActorForwardVector();
		}
		else if (SectionName == SectionFront)
		{
			// Front 섹션: 뒤로 약간 왼쪽 대각선으로 날아감
			PushDirection = -Character->GetActorForwardVector() - (Character->GetActorRightVector() * 0.5f);
		}
		else if (SectionName == SectionLeft)
		{
			PushDirection = Character->GetActorRightVector();
		}
		else if (SectionName == SectionRight)
		{
			PushDirection = -Character->GetActorRightVector();
		}

		PushDirection.Z = 0.0f;
		if (!PushDirection.IsNearlyZero())
		{
			PushDirection.Normalize();

			UAbilityTask_ApplyRootMotionConstantForce* PushTask = UAbilityTask_ApplyRootMotionConstantForce::ApplyRootMotionConstantForce(
				this,
				FName("DeathKnockback"),
				PushDirection,
				DeathKnockbackForce,
				DeathKnockbackDuration,
				false,
				nullptr,
				ERootMotionFinishVelocityMode::SetVelocity,
				FVector::ZeroVector,
				0.0f,
				false
			);
			if (PushTask)
			{
				PushTask->ReadyForActivation();
			}
		}
	}


// [원문 99-120 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 121-138] UGA_Death::EndAbility — 전체 함수임을 뜻하지 않습니다.
	if (ABaseCharacter* Character = Cast<ABaseCharacter>(ActorInfo->AvatarActor.Get()))
	{
		Character->FinishDeath();

		if (Character->HasAuthority() && ReviveZoneClass)
		{
			FVector SpawnLocation = Character->GetActorLocation();
			FRotator SpawnRotation = Character->GetActorRotation();
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			if (AReviveZoneActor* SpawnedZone = GetWorld()->SpawnActor<AReviveZoneActor>(ReviveZoneClass, SpawnLocation, SpawnRotation, SpawnParams))
			{
				SpawnedZone->InitializeZone(Character);
			}
		}
	}


// [원문 139-207 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 208-222] UGA_Death::BeginDeath — 전체 함수임을 뜻하지 않습니다.
	if (DeathEffectClass)
	{
		FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
		Context.AddInstigator(Character, Character);
		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DeathEffectClass, 1.0f, Context);
		if (SpecHandle.IsValid())
		{
			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}

	if (Character->IsLocallyControlled())
	{
		// 이전에 사용하던 DeathScreen 위젯 팝업 호출 제거 (현재는 DamageOverlay로 대체됨)
	}
