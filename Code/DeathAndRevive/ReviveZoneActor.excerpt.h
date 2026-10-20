// 코드 및 설계 전시용 원문 발췌. 빌드 대상이 아닙니다.
// 생략된 함수·선언·외부 타입은 원본 프로젝트에 의존합니다.
// 각 조각 사이의 원본 코드와 제어 흐름은 생략되어 있으며, 이를 새 코드로 연결하지 않았습니다.

// 원본 파일: Source/TeamProject_Fin/GameCore/Interact/ReviveZoneActor.h
// 기준 커밋: 265059d8a3305a45c8f6c890590f4074069a3a88
// [원문 1-88] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReviveZoneActor.generated.h"

class UCapsuleComponent;
class UNiagaraComponent;
class UAudioComponent;
class ABaseCharacter;
class UDefaultWidgetLayer;

UENUM(BlueprintType)
enum class EReviveZoneState : uint8
{
	Idle,
	Reviving,
	GracePeriod,
	Decaying
};

/**
 * 부활 구역 액터 (서버 주도 동기화)
 */
UCLASS()
class TEAMPROJECT_FIN_API AReviveZoneActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AReviveZoneActor();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	/* 컴포넌트 (블루프린트에서 애셋 세팅 할당 가능) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCapsuleComponent> ReviveZoneCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UNiagaraComponent> ReviveEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UAudioComponent> ReviveAudio;

protected:
	/* 블루프린트 설정 변수 (기획자/디자이너 조절용) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Revive Settings")
	float MaxReviveTime = 15.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Revive Settings")
	float GracePeriodTime = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Revive Settings")
	float DecayRate = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Revive Settings")
	float ZoneRadius = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Revive Settings")
	float ZoneHalfHeight = 150.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Revive Settings|Audio")
	float MinPitch = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Revive Settings|Audio")
	float MaxPitch = 1.5f;

	/* 상태 네트워크 동기화 (서버 -> 클라) */
	UPROPERTY(ReplicatedUsing = OnRep_CurrentState)
	EReviveZoneState CurrentState;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentProgress)
	float CurrentProgress;

	/* 로컬 클라이언트 전용 UI 클래스 캐싱 (블루프린트 할당용) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Revive Settings|UI")
	TSubclassOf<class UReviveGaugeWidget> ReviveGaugeClass;

	UFUNCTION()
	void OnRep_CurrentState();

	UFUNCTION()
	void OnRep_CurrentProgress();

private:

// [원문 89-90 생략: 이 사이의 제어 흐름은 재구성하지 않음]
// [원문 91-127] 선언·설정 조각 — 전체 함수임을 뜻하지 않습니다.
	/* 클라이언트 UI 부드러운 보간을 위한 시각적 게이지 */
	float VisualProgress;

	/* 로직 제어용 내부 변수 (서버 전용) */
	float GraceTimer;

	UPROPERTY(Replicated)
	TObjectPtr<ABaseCharacter> DeadPlayer;

	UPROPERTY()
	TArray<TObjectPtr<ABaseCharacter>> ActiveRescuers;

	/* 런타임에 한 번만 생성해서 쥐고 있을 위젯 포인터 (서버는 null) */
	UPROPERTY()
	TObjectPtr<class UReviveGaugeWidget> LocalReviveWidget;

	FTimerHandle TH_UpdateLoop;

	/* 충돌 오버랩 이벤트 함수 */
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void UpdateLoop();
	void UpdateAudioAndVisuals(float DeltaTime);
	void UpdateClientUI();
	void FinishRevive();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OnReviveFinished();

public:
	/** 사망한 플레이어가 Zone에 스폰된 직후 호출하여 사망자 정보를 등록합니다. */
	void InitializeZone(ABaseCharacter* InDeadPlayer);
};
