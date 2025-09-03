#include "AMyActor.h"


AAMyActor::AAMyActor()
{
 	PrimaryActorTick.bCanEverTick = false;
    CurrentLocation = FVector2D(0, 0);

}

void AAMyActor::BeginPlay()
{
	Super::BeginPlay();
	move(10); // -> ����� �̵�
    // �� �̺�Ʈ �߻� Ƚ�� ���
    // LogTemp: Error: TotalEvent: [evCnt]
    UE_LOG(LogTemp, Error, TEXT("TotalEvent: %d"), evCnt);

}

void AAMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Ŀ���� ���� �ʰ�, FVector2D::Distance(a,b)�� ��ü ����
float AAMyActor::distance(FVector2D first, FVector2D second)
{
	float dx = first.X - second.X;
	float dy = first.Y - second.Y;
	return FMath::Sqrt(dx * dx + dy * dy);
}

void AAMyActor::move(int32 MoveCount) {

    UE_LOG(LogTemp, Error, TEXT("Step 0 : X = %0.2f, Y = %0.2f"), CurrentLocation.X, CurrentLocation.Y);
    for (int32 i = 1; i <= MoveCount; i++)
    {
        //���� x, y���� ����
        float prevX = CurrentLocation.X;
        float prevY = CurrentLocation.Y;

        // 0 �Ǵ� 1 ��ŭ �̵�
        CurrentLocation.X += step();
        CurrentLocation.Y += step();

        //float dis = FVector2D::Distance(FVector2D(prevX,prevY), FVector2D(CurrentLocation.X,CurrentLocation.Y))
        float dis = distance(FVector2D(prevX, prevY), FVector2D(CurrentLocation.X, CurrentLocation.Y)); //�̵� �Ÿ� ���
        totDist += dis; // �� �̵� �Ÿ��� �����ش�

        // ��� ���� 
        // -> LogTemp: Warning: Step  [i] : X = [prevX], Y = [prevY] -> X = [CurrentLocation.X], Y = [CurrentLocation.Y] | distance : [dis]
        // %2d  -> ��°�� �ڸ����� 2�ڸ��� �����ϰ� ����� �������� ä���  ex) [ 1]
        // %02d -> ��°�� �ڸ����� 2�ڸ��� �����ϰ� ����� 0���� ä���     ex) [01]
        // %0.2f -> ��°�� �Ҽ��� 2�ڸ����� ������ �Ѵ�. ex) [0.00]
        UE_LOG(LogTemp, Warning, 
            TEXT("Step %2d : X = %0.2f, Y = %0.2f -> X = %0.2f, Y = %0.2f | distance : %0.2f "),
                        i, prevX, prevY, CurrentLocation.X, CurrentLocation.Y, dis);

        // �̺�Ʈ�� �߻��ߴ��� ���ϰ����� Ȯ�� �� ���
        // ->LogTemp: Warning: Event!
        if (creatEvent() == 1) {
            UE_LOG(LogTemp, Warning, TEXT("Event!"));
        }
    }
    // �� �̵� �Ÿ� ���
    // LogTemp: Error: totDist : [totDist]
    UE_LOG(LogTemp, Error, TEXT("totDist : %0.2f"), totDist);
}


int32 AAMyActor::step() {
    // ���� 0 ~ 1 ����
	return FMath::RandRange(0, 1);
}

int32 AAMyActor::creatEvent() {
    // ���� 0 ~ 1
	int event = FMath::RandRange(0, 1);

    // �̺�Ʈ�� �߻��ϸ� �� �̺�Ʈ�� 1�����ϰ� 1�� �����Ѵ�
	if (event == 1) {
		++evCnt;
        return 1;
	}
    // �߻����� �ʾҴٸ� 0�� �����Ѵ�
    return 0;
}