// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Character/BaseCharacter.cpp
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 13-14] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

// [원문 15-16 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 17-17] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
#include "../../Environment/EnvironmentCharacterMovementComponent.h"

// [원문 18-28 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 29-39] ABaseCharacter::ABaseCharacter — 전체 함수임을 뜻하지 않습니다.

	if (UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->SetCollisionResponseToChannel(ECC_TraceAttack, ECR_Ignore);
		Capsule->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	}

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetCollisionProfileName(TEXT("CharacterHitbox"));
	}

// [원문 40-72 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 73-82] ABaseCharacter::InitializeAbilitySystem — 전체 함수임을 뜻하지 않습니다.
		AbilitySystemComponent->RegisterGameplayTagEvent(GameplayTagSystem::State_Dead, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ABaseCharacter::OnDeadTagChanged);

		// 서버와 클라이언트 모두 자신의 역할 태그(피아식별용)를 부착해야 합니다.
		if (CharacterRoleTag.IsValid())
		{
			AbilitySystemComponent->AddLooseGameplayTag(CharacterRoleTag);
		}

		if (HasAuthority())
		{

// [원문 83-120 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 121-122] ABaseCharacter::GrantCharacterRoleTag — 전체 함수임을 뜻하지 않습니다.
		AbilitySystemComponent->AddLooseGameplayTag(CharacterRoleTag);
	}

// [원문 123-140 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 141-142] ABaseCharacter::GrantDefaultAbilities — 전체 함수임을 뜻하지 않습니다.
		{
			FGameplayAbilitySpec AbilitySpec(AbilityClass, 1, INDEX_NONE, this);

// [원문 143-153 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 154-170] ABaseCharacter::ApplyDefaultEffects — 전체 함수임을 뜻하지 않습니다.

	// 시작 시 기본 이펙트(패시브, 스태미나 자동 회복 등) 적용
	for (const TSubclassOf<UGameplayEffect>& EffectClass : DefaultEffects)
	{
		if (EffectClass)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			EffectContext.AddInstigator(this, this);

			FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, 1.0f, EffectContext);
			if (SpecHandle.IsValid())
			{
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}
}

// [원문 171-180 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 181-182] ABaseCharacter::BroadcastInitialAttributes — 전체 함수임을 뜻하지 않습니다.
		OnHealthCapMultiplierChanged.Broadcast(CharacterAttributeSet->GetHealthCapMultiplier());
		OnStaminaCapMultiplierChanged.Broadcast(CharacterAttributeSet->GetStaminaCapMultiplier());

// [원문 183-195 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 196-216] ABaseCharacter::BindAttributeDelegates — 전체 함수임을 뜻하지 않습니다.

	AbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetHealthAttribute())
		.AddUObject(this, &ABaseCharacter::OnHealthChangedCallback);

	AbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetStaminaAttribute())
		.AddUObject(this, &ABaseCharacter::OnStaminaChangedCallback);

	AbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetHealthCapMultiplierAttribute())
		.AddUObject(this, &ABaseCharacter::OnHealthCapMultiplierChangedCallback);

	AbilitySystemComponent
		->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetStaminaCapMultiplierAttribute())
		.AddUObject(this, &ABaseCharacter::OnStaminaCapMultiplierChangedCallback);

	AbilitySystemComponent->RegisterGameplayTagEvent(
		FGameplayTag::RequestGameplayTag(FName("State.environment.snow.Level3")), 
		EGameplayTagEventType::NewOrRemoved)
		.AddUObject(this, &ABaseCharacter::OnSnowDebuffTagChanged);

// [원문 217-223 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 224-224] ABaseCharacter::ApplyMovementSpeed — 전체 함수임을 뜻하지 않습니다.
		MovementComponent->MaxWalkSpeedCrouched = FMath::Max(NewMovementSpeed, 0.0f);

// [원문 225-231 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 232-247] ABaseCharacter::OnHealthChangedCallback, ABaseCharacter::OnStaminaChangedCallback — 전체 함수임을 뜻하지 않습니다.

void ABaseCharacter::OnHealthChangedCallback(const FOnAttributeChangeData& Data)
{
	if (CharacterAttributeSet)
	{
		OnHealthChanged.Broadcast(Data.NewValue, CharacterAttributeSet->GetMaxHealth());
	}
}

void ABaseCharacter::OnStaminaChangedCallback(const FOnAttributeChangeData& Data)
{
	if (CharacterAttributeSet)
	{
		OnStaminaChanged.Broadcast(Data.NewValue, CharacterAttributeSet->GetMaxStamina());
	}
}

// [원문 248-248 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 249-263] ABaseCharacter::OnHealthCapMultiplierChangedCallback, ABaseCharacter::OnStaminaCapMultiplierChangedCallback, ABaseCharacter::OnSnowDebuffTagChanged — 전체 함수임을 뜻하지 않습니다.
void ABaseCharacter::OnHealthCapMultiplierChangedCallback(const FOnAttributeChangeData& Data)
{
	OnHealthCapMultiplierChanged.Broadcast(Data.NewValue);
}

void ABaseCharacter::OnStaminaCapMultiplierChangedCallback(const FOnAttributeChangeData& Data)
{
	OnStaminaCapMultiplierChanged.Broadcast(Data.NewValue);
}

void ABaseCharacter::OnSnowDebuffTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	OnSnowDebuffChanged.Broadcast(NewCount > 0);
}


// [원문 264-278 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 279-281] ABaseCharacter::BeginDeath — 전체 함수임을 뜻하지 않습니다.

		if (bDisableMovementOnDeathStart)
		{

// [원문 282-287 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 288-290] ABaseCharacter::BeginDeath — 전체 함수임을 뜻하지 않습니다.
		Capsule->SetCollisionResponseToChannel(ECC_TraceAttack, ECR_Ignore);
		Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		Capsule->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

// [원문 291-294 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 295-297] ABaseCharacter::BeginDeath — 전체 함수임을 뜻하지 않습니다.
		MeshComponent->SetCollisionResponseToChannel(ECC_TraceAttack, ECR_Ignore);
		MeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		MeshComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

// [원문 298-314 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 315-318] ABaseCharacter::FinishDeath — 전체 함수임을 뜻하지 않습니다.
	if (UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->DisableMovement();
	}

// [원문 319-319 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 320-322] ABaseCharacter::Revive — 전체 함수임을 뜻하지 않습니다.

void ABaseCharacter::Revive()
{

// [원문 323-323 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 324-334] ABaseCharacter::Revive — 전체 함수임을 뜻하지 않습니다.
	bDeathFinished = false;

	if (UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	}

	if (USkeletalMeshComponent* MeshComponent = GetMesh())
	{
		MeshComponent->SetCollisionResponseToChannel(ECC_TraceAttack, ECR_Block);

// [원문 335-335 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 336-336] ABaseCharacter::Revive — 전체 함수임을 뜻하지 않습니다.
		MeshComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

// [원문 337-342 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 343-349] ABaseCharacter::Revive — 전체 함수임을 뜻하지 않습니다.
	}

	if (UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->SetMovementMode(MOVE_Walking);
	}
}

// [원문 350-350 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 351-361] ABaseCharacter::OnDeadTagChanged — 전체 함수임을 뜻하지 않습니다.
void ABaseCharacter::OnDeadTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		BeginDeath();
	}
	else
	{
		Revive();
	}
}
