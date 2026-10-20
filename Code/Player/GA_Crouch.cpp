// Copyright Epic Games, Inc. All Rights Reserved.

#include "GA_Crouch.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"

UGA_Crouch::UGA_Crouch()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Crouch::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// ?∏Î¶¨???îÏßÑ Í∏∞Î≥∏ ?âÍ∏∞(Ï∫°Ïäê ?¨Í∏∞ Î≥ÄÍ≤?Î∞?Î¨ºÎ¶¨ ?ÅÌÉú ?ÑÌôò) ?∏Ï∂ú
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (Character)
	{
		Character->Crouch();
	}

	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	if (ASC && CrouchEffectClass)
	{
		// ?¥ÏÜç Í∞êÏÜå??GE(Gameplay Effect) ?ÅÏö©
		FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
		ContextHandle.AddInstigator(ActorInfo->AvatarActor.Get(), ActorInfo->AvatarActor.Get());
		
		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(CrouchEffectClass, GetAbilityLevel(), ContextHandle);
		if (SpecHandle.IsValid())
		{
			ActiveCrouchEffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void UGA_Crouch::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// ?∏Î¶¨???îÏßÑ Í∏∞Î≥∏ ?âÍ∏∞ ?¥Ï†ú
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (Character)
	{
		Character->UnCrouch();
	}

	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	if (ASC && ActiveCrouchEffectHandle.IsValid())
	{
		// ?¥ÎπåÎ¶¨Ìã∞ Ï¢ÖÎ£å ???âÍ∏∞ ?®Í≥º(GE) ?úÍ±∞
		ASC->RemoveActiveGameplayEffect(ActiveCrouchEffectHandle);
		ActiveCrouchEffectHandle.Invalidate();
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
