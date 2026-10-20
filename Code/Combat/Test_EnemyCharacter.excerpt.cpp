// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Character/Test_EnemyCharacter.cpp
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 1-20] ATest_EnemyCharacter::ATest_EnemyCharacter, ATest_EnemyCharacter::BeginPlay — 전체 함수임을 뜻하지 않습니다.
// Copyright Epic Games, Inc. All Rights Reserved.

#include "Test_EnemyCharacter.h"
#include "Components/SkeletalMeshComponent.h"

ATest_EnemyCharacter::ATest_EnemyCharacter()
{
	// 스켈레탈 메시 피격 판정 세팅 (적군용)
	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		// 적군은 플레이어 총알(PlayerAttack)에만 Block 판정을 냄
		MeshComp->SetCollisionResponseToChannel(ECC_TraceAttack, ECR_Block);
		// 몬스터끼리의 공격(EnemyAttack)은 완전히 관통(Ignore)시켜 팀킬 길막 방지
	}
}

void ATest_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}
