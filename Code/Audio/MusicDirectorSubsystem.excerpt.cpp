// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Audio/MusicDirectorSubsystem.cpp
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 1-9] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
#include "GameCore/Audio/MusicDirectorSubsystem.h"

#include "Containers/Ticker.h"
#include "Engine/AssetManager.h"
#include "Engine/Engine.h"
#include "Engine/StreamableManager.h"
#include "Engine/World.h"
#include "FMODEvent.h"
#include "FMODStudioModule.h"

// [원문 10-10 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 11-16] 원본 파일의 일부 구간 — 전체 함수임을 뜻하지 않습니다.
#include "GameCore/Audio/ProjectAudioSettings.h"
#include "HAL/PlatformTime.h"
#include "ProfilingDebugging/CpuProfilerTrace.h"
#include "UObject/UObjectGlobals.h"
#include "fmod_errors.h"
#include "fmod_studio.hpp"

// [원문 17-17 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 18-30] UMusicDirectorSubsystem::Initialize — 전체 함수임을 뜻하지 않습니다.

DEFINE_LOG_CATEGORY_STATIC(LogProjectMusic, Log, All);

namespace
{
	constexpr float MusicRetryInterval = 0.1f;
	constexpr double MusicRetryDuration = 10.0;
}

void UMusicDirectorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	PreLoadMapHandle = FCoreUObjectDelegates::PreLoadMapWithContext.AddUObject(this, &ThisClass::OnPreLoadMap);

// [원문 31-35 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 36-40] UMusicDirectorSubsystem::Initialize, UMusicDirectorSubsystem::Deinitialize — 전체 함수임을 뜻하지 않습니다.
}

void UMusicDirectorSubsystem::Deinitialize()
{
	FCoreUObjectDelegates::PreLoadMapWithContext.Remove(PreLoadMapHandle);

// [원문 41-42 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 43-158] UMusicDirectorSubsystem::Deinitialize 외 4개 함수 구간 — 전체 함수임을 뜻하지 않습니다.
	StopMusic();
	Super::Deinitialize();
}

void UMusicDirectorSubsystem::SetMusicState(float Value)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(ProjectMusic_SetMusicState);
	const UWorld* World = GetWorld();
	if (IsRunningDedicatedServer() || (World && World->GetNetMode() == NM_DedicatedServer))
	{
		return;
	}
	if (!FMath::IsFinite(Value))
	{
		UE_LOG(LogProjectMusic, Warning, TEXT("음악 상태 값은 유한한 숫자여야 합니다."));
		return;
	}
	DesiredValue = Value;
	bHasDesiredState = true;
	// 진행 중인 작업은 유지하고 마지막 요청값만 갱신한다. 대기 제한도 연장하지 않는다.
	if (bLoading || RetryHandle.IsValid())
	{
		return;
	}
	const UProjectAudioSettings* Settings = GetDefault<UProjectAudioSettings>();
	if (ParameterName != Settings->MusicStateParameterName)
	{
		ParameterCache = FParameterCache();
		bHasAppliedState = false;
	}
	ParameterName = Settings->MusicStateParameterName;
	if (Settings->MainMusicEvent.IsNull() || ParameterName.IsNone())
	{
		UE_LOG(LogProjectMusic, Warning, TEXT("MainMusicEvent 또는 MusicStateParameterName이 설정되지 않았습니다."));
		return;
	}
	if (!MainEvent)
	{
		LoadMainEvent(Settings->MainMusicEvent);
		return;
	}
	ApplyOrRetry();
}

void UMusicDirectorSubsystem::LoadMainEvent(TSoftObjectPtr<UFMODEvent> Event)
{
	bLoading = true;
	const uint32 ExpectedGeneration = Generation;
	// 완료 시 설정을 다시 조회하지 않고 실제로 요청한 에셋을 사용한다.
	LoadHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(
		Event.ToSoftObjectPath(),
		FStreamableDelegate::CreateWeakLambda(this, [this, ExpectedGeneration, Event]()
		{
			OnEventLoaded(ExpectedGeneration, Event);
		}));
	if (!LoadHandle)
	{
		bLoading = false;
		UE_LOG(LogProjectMusic, Warning, TEXT("메인 FMOD Event 로딩 요청 실패."));
	}
}

void UMusicDirectorSubsystem::OnEventLoaded(uint32 ExpectedGeneration, TSoftObjectPtr<UFMODEvent> Event)
{
	if (ExpectedGeneration != Generation || !bHasDesiredState)
	{
		return;
	}
	bLoading = false;
	MainEvent = Event.Get();
	LoadHandle.Reset();
	if (!MainEvent)
	{
		UE_LOG(LogProjectMusic, Warning, TEXT("메인 FMOD Event 로딩 실패."));
		return;
	}
	ApplyOrRetry();
}

UMusicDirectorSubsystem::EApplyResult UMusicDirectorSubsystem::ApplyState()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(ProjectMusic_ApplyState);
	if (!IFMODStudioModule::IsAvailable() ||
		!IFMODStudioModule::Get().GetStudioSystem(EFMODSystemContext::Runtime))
	{
		return EApplyResult::NotReady;
	}
	if (!RefreshCurrentInstance())
	{
		return EApplyResult::Failed;
	}

	// 정상 인스턴스의 후속 요청은 Event 조회 및 문자열 변환 없이 처리한다.
	FMOD::Studio::EventDescription* Description = nullptr;
	if (!CurrentInstance || !ParameterCache.bValid)
	{
		Description = IFMODStudioModule::Get().GetEventDescription(MainEvent, EFMODSystemContext::Runtime);
		if (!Description)
		{
			return EApplyResult::NotReady;
		}
		if (!ParameterCache.bValid && !CacheParameter(Description))
		{
			return EApplyResult::Failed;
		}
	}
	if (!ParameterCache.IsValueAllowed(DesiredValue))
	{
		UE_LOG(LogProjectMusic, Warning, TEXT("음악 파라미터 값이 잘못되었습니다: %s = %f (범위 %f~%f)"),
			*ParameterName.ToString(), DesiredValue, ParameterCache.Minimum, ParameterCache.Maximum);
		return EApplyResult::Failed;
	}

	const bool bNewInstance = CurrentInstance == nullptr;
	if (!bNewInstance && bHasAppliedState && AppliedValue == DesiredValue)
	{

// [원문 159-159 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 160-193] UMusicDirectorSubsystem::ApplyState — 전체 함수임을 뜻하지 않습니다.
	}

	if (bNewInstance)
	{
		const FMOD_RESULT Result = Description->createInstance(&CurrentInstance);
		if (Result != FMOD_OK)
		{
			CurrentInstance = nullptr;
			UE_LOG(LogProjectMusic, Warning, TEXT("음악 인스턴스 생성 실패: %s"), UTF8_TO_TCHAR(FMOD_ErrorString(Result)));
			return EApplyResult::Failed;
		}
	}

	// 최초 재생만 Seek Speed를 건너뛰고, 이후 전환은 FMOD 설정을 따른다.
	const FMOD_STUDIO_PARAMETER_ID ParameterId{ ParameterCache.IdData1, ParameterCache.IdData2 };
	FMOD_RESULT Result = CurrentInstance->setParameterByID(ParameterId, DesiredValue, bNewInstance);
	if (Result == FMOD_OK && bNewInstance)
	{
		Result = CurrentInstance->start();
	}
	if (Result != FMOD_OK)
	{
		UE_LOG(LogProjectMusic, Warning, TEXT("음악 상태 적용/재생 실패: %s"), UTF8_TO_TCHAR(FMOD_ErrorString(Result)));
		// Bank 재로드 등으로 ID가 무효화된 경우 다음 요청에서 다시 조회한다.
		ParameterCache = FParameterCache();
		bHasAppliedState = false;
		if (bNewInstance)
		{
			ReleaseCurrentInstance();
		}
		return EApplyResult::Failed;
	}
	AppliedValue = DesiredValue;
	bHasAppliedState = true;

// [원문 194-271 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 272-303] UMusicDirectorSubsystem::CacheParameter, UMusicDirectorSubsystem::RefreshCurrentInstance — 전체 함수임을 뜻하지 않습니다.
bool UMusicDirectorSubsystem::CacheParameter(FMOD::Studio::EventDescription* Description)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(ProjectMusic_CacheParameter);
	const FTCHARToUTF8 Name(*ParameterName.ToString());
	FMOD_STUDIO_PARAMETER_DESCRIPTION Parameter{};
	const FMOD_RESULT Result = Description->getParameterDescriptionByName(Name.Get(), &Parameter);
	if (Result != FMOD_OK)
	{
		UE_LOG(LogProjectMusic, Warning, TEXT("음악 파라미터 조회 실패 (%s): %s"),
			*ParameterName.ToString(), UTF8_TO_TCHAR(FMOD_ErrorString(Result)));
		return false;
	}
	if (Parameter.type != FMOD_STUDIO_PARAMETER_GAME_CONTROLLED ||
		(Parameter.flags & (FMOD_STUDIO_PARAMETER_GLOBAL | FMOD_STUDIO_PARAMETER_READONLY)))
	{
		UE_LOG(LogProjectMusic, Warning, TEXT("쓰기 가능한 로컬 음악 파라미터가 아닙니다: %s"), *ParameterName.ToString());
		return false;
	}
	ParameterCache.IdData1 = Parameter.id.data1;
	ParameterCache.IdData2 = Parameter.id.data2;
	ParameterCache.Minimum = Parameter.minimum;
	ParameterCache.Maximum = Parameter.maximum;
	ParameterCache.bRequiresInteger =
		(Parameter.flags & (FMOD_STUDIO_PARAMETER_DISCRETE | FMOD_STUDIO_PARAMETER_LABELED)) != 0;
	ParameterCache.bValid = true;
	return true;
}

bool UMusicDirectorSubsystem::RefreshCurrentInstance()
{
	if (CurrentInstance && !CurrentInstance->isValid())
	{

// [원문 304-304 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 305-327] UMusicDirectorSubsystem::RefreshCurrentInstance, UMusicDirectorSubsystem::ReleaseCurrentInstance — 전체 함수임을 뜻하지 않습니다.
		CurrentInstance = nullptr;
		ParameterCache = FParameterCache();
		bHasAppliedState = false;
	}
	if (CurrentInstance)
	{
		FMOD_STUDIO_PLAYBACK_STATE State = FMOD_STUDIO_PLAYBACK_STOPPED;
		const FMOD_RESULT Result = CurrentInstance->getPlaybackState(&State);
		if (Result != FMOD_OK)
		{
			UE_LOG(LogProjectMusic, Warning, TEXT("음악 재생 상태 조회 실패: %s"), UTF8_TO_TCHAR(FMOD_ErrorString(Result)));
			return false;
		}
		if (State == FMOD_STUDIO_PLAYBACK_STOPPED)
		{
			ReleaseCurrentInstance();
		}
	}
	return true;
}

void UMusicDirectorSubsystem::ReleaseCurrentInstance()
{

// [원문 328-328 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 329-399] UMusicDirectorSubsystem::ReleaseCurrentInstance 외 5개 함수 구간 — 전체 함수임을 뜻하지 않습니다.
	if (CurrentInstance && IFMODStudioModule::IsAvailable() && CurrentInstance->isValid())
	{
		CurrentInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE);
		CurrentInstance->release();
	}
	CurrentInstance = nullptr;
	ParameterCache = FParameterCache();
	bHasAppliedState = false;
}

void UMusicDirectorSubsystem::ApplyOrRetry()
{
	if (ApplyState() != EApplyResult::NotReady)
	{
		CancelRetry();
		return;
	}
	if (RetryHandle.IsValid())
	{
		return;
	}
	RetryDeadline = FPlatformTime::Seconds() + MusicRetryDuration;
	RetryHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateUObject(this, &ThisClass::RetryPlayback), MusicRetryInterval);
}

bool UMusicDirectorSubsystem::RetryPlayback(float DeltaTime)
{
	const EApplyResult Result = ApplyState();
	if (Result != EApplyResult::NotReady)
	{
		RetryHandle.Reset();
		return false;
	}
	if (FPlatformTime::Seconds() >= RetryDeadline)
	{
		UE_LOG(LogProjectMusic, Warning, TEXT("FMOD 시스템/Bank 준비 대기 시간 초과. 다음 음악 이벤트에서 재시도합니다."));
		RetryHandle.Reset();
		return false;
	}
	return true;
}

void UMusicDirectorSubsystem::CancelRetry()
{
	if (RetryHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(RetryHandle);
	}
	RetryHandle.Reset();
	RetryDeadline = 0.0;
}

void UMusicDirectorSubsystem::StopMusic()
{
	++Generation;
	CancelRetry();
	if (LoadHandle)
	{
		LoadHandle->CancelHandle();
	}
	LoadHandle.Reset();
	bLoading = false;
	bHasDesiredState = false;
	ReleaseCurrentInstance();
	MainEvent = nullptr;
}

void UMusicDirectorSubsystem::OnPreLoadMap(const FWorldContext& WorldContext, const FString& MapName)
{
	if (WorldContext.OwningGameInstance == GetGameInstance())

// [원문 400-439 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 440-494] FProjectMusicOptimizationTest::RunTest — 전체 함수임을 뜻하지 않습니다.
#if WITH_DEV_AUTOMATION_TESTS
#include "Engine/GameInstance.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FProjectMusicOptimizationTest,
	"TeamProject.Audio.MusicOptimization",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FProjectMusicOptimizationTest::RunTest(const FString& Parameters)
{
	// 값 검증이 FMOD 호출 없이 동작하고 기존 Discrete/Continuous 규칙을 보존하는지 검사한다.
	UMusicDirectorSubsystem::FParameterCache Cache;
	TestFalse(TEXT("조회 전 캐시는 사용할 수 없음"), Cache.IsValueAllowed(0.0f));
	Cache.bValid = true;
	Cache.Minimum = 0.0f;
	Cache.Maximum = 10.0f;
	Cache.bRequiresInteger = true;
	TestTrue(TEXT("최솟값 허용"), Cache.IsValueAllowed(0.0f));
	TestTrue(TEXT("최댓값 허용"), Cache.IsValueAllowed(10.0f));
	TestFalse(TEXT("범위 미만 거부"), Cache.IsValueAllowed(-1.0f));
	TestFalse(TEXT("범위 초과 거부"), Cache.IsValueAllowed(11.0f));
	TestFalse(TEXT("Discrete 소수 거부"), Cache.IsValueAllowed(1.5f));
	Cache.bRequiresInteger = false;
	TestTrue(TEXT("Continuous 소수 허용"), Cache.IsValueAllowed(1.5f));

	UGameInstance* GameInstance = NewObject<UGameInstance>();
	UMusicDirectorSubsystem* Director = NewObject<UMusicDirectorSubsystem>(GameInstance);
	Director->bLoading = true;
	Director->SetMusicState(1.0f);
	Director->SetMusicState(9.0f);
	TestEqual(TEXT("로딩 중 최신 값 유지"), Director->DesiredValue, 9.0f);
	TestTrue(TEXT("로딩 중 중복 로딩 요청 없음"), Director->bLoading && !Director->LoadHandle);
	Director->StopMusic();

	// 아직 준비되지 않은 시스템을 흉내 내되 실제 FMOD 및 오디오 장치에는 접근하지 않는다.
	Director->RetryDeadline = FPlatformTime::Seconds() + MusicRetryDuration;
	const double OriginalDeadline = Director->RetryDeadline;
	Director->RetryHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateLambda([](float) { return false; }), 3600.0f);
	const auto OriginalRetryHandle = Director->RetryHandle.Pin();
	Director->SetMusicState(2.0f);
	Director->SetMusicState(8.0f);
	TestTrue(TEXT("대기 중 재시도 예약 재사용"), Director->RetryHandle.Pin() == OriginalRetryHandle);
	TestEqual(TEXT("반복 요청이 대기 제한을 연장하지 않음"), Director->RetryDeadline, OriginalDeadline);
	TestEqual(TEXT("대기 중 최신 값 유지"), Director->DesiredValue, 8.0f);

	Director->ParameterCache = Cache;
	Director->bHasAppliedState = true;
	const uint32 PreviousGeneration = Director->Generation;
	Director->StopMusic();
	TestFalse(TEXT("정지 시 재시도 예약 해제"), Director->RetryHandle.IsValid());
	TestFalse(TEXT("정지 시 파라미터 캐시 해제"), Director->ParameterCache.bValid);
	TestFalse(TEXT("정지 시 적용 상태 해제"), Director->bHasAppliedState);
	TestFalse(TEXT("정지 시 요청 상태 해제"), Director->bHasDesiredState);

// [원문 495-499 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 500-503] FProjectMusicOptimizationTest::RunTest — 전체 함수임을 뜻하지 않습니다.
	TestEqual(TEXT("정지 시 이전 비동기 세대 무효화"), Director->Generation, PreviousGeneration + 1);
	return true;
}
#endif
