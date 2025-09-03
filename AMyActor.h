#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AMyActor.generated.h"

UCLASS()
class HOMEWORK_API AAMyActor : public AActor
{
	GENERATED_BODY()
	int32 evCnt = 0; // �� �̺�Ʈ �߻� Ƚ��
	float totDist = 0; // �� �̵� �Ÿ� 
	FVector2D CurrentLocation; // ���� ��ġ�� ��� ��ǥ
	
public:	
	AAMyActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	float distance(FVector2D first, FVector2D second); //distance Ŀ���� �Լ�
	void move(int32 MoveCount); // �̵�
	int32 step(); // �̵��Ÿ�
	int32 creatEvent(); // �̺�Ʈ
};
