#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AMyActor.generated.h"

UCLASS()
class HOMEWORK_API AAMyActor : public AActor
{
	GENERATED_BODY()
	int32 evCnt = 0; // 총 이벤트 발생 횟수
	float totDist = 0; // 총 이동 거리 
	FVector2D CurrentLocation; // 현재 위치를 담는 좌표
	
public:	
	AAMyActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	float distance(FVector2D first, FVector2D second); //distance 커스텀 함수
	void move(int32 MoveCount); // 이동
	int32 step(); // 이동거리
	int32 creatEvent(); // 이벤트
};
