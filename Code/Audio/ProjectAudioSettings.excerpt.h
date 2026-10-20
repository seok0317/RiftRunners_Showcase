// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Audio/ProjectAudioSettings.h
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 1-7] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ProjectAudioSettings.generated.h"

class UFMODEvent;

// [원문 8-8 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 9-23] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
class USoundControlBus;
class USoundControlBusMix;

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Project Audio"))
class TEAMPROJECT_FIN_API UProjectAudioSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Config, Category = "Music")
	TSoftObjectPtr<UFMODEvent> MainMusicEvent;

	UPROPERTY(EditAnywhere, Config, Category = "Music")
	FName MusicStateParameterName = TEXT("MusicState");


// [원문 24-27 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 28-42] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	UPROPERTY(EditAnywhere, Config, Category = "Volume")
	TSoftObjectPtr<USoundControlBusMix> UserMix;

	UPROPERTY(EditAnywhere, Config, Category = "Volume")
	TSoftObjectPtr<USoundControlBus> MasterBus;

	UPROPERTY(EditAnywhere, Config, Category = "Volume")
	TSoftObjectPtr<USoundControlBus> MusicBus;

	UPROPERTY(EditAnywhere, Config, Category = "Volume")
	TSoftObjectPtr<USoundControlBus> SFXBus;

	UPROPERTY(EditAnywhere, Config, Category = "Volume")
	TSoftObjectPtr<USoundControlBus> UIBus;
};
