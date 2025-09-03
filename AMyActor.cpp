#include "AMyActor.h"


AAMyActor::AAMyActor()
{
 	PrimaryActorTick.bCanEverTick = false;
    CurrentLocation = FVector2D(0, 0);

}

void AAMyActor::BeginPlay()
{
	Super::BeginPlay();
	move(10); // -> 무브로 이동
    // 총 이벤트 발생 횟수 출력
    // LogTemp: Error: TotalEvent: [evCnt]
    UE_LOG(LogTemp, Error, TEXT("TotalEvent: %d"), evCnt);

}

void AAMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//커스텀 하지 않고, FVector2D::Distance(a,b)로 대체 가능
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
        //이전 x, y값을 저장
        float prevX = CurrentLocation.X;
        float prevY = CurrentLocation.Y;

        // 0 또는 1 만큼 이동
        CurrentLocation.X += step();
        CurrentLocation.Y += step();

        //float dis = FVector2D::Distance(FVector2D(prevX,prevY), FVector2D(CurrentLocation.X,CurrentLocation.Y))
        float dis = distance(FVector2D(prevX, prevY), FVector2D(CurrentLocation.X, CurrentLocation.Y)); //이동 거리 계산
        totDist += dis; // 총 이동 거리에 더해준다

        // 출력 예상 
        // -> LogTemp: Warning: Step  [i] : X = [prevX], Y = [prevY] -> X = [CurrentLocation.X], Y = [CurrentLocation.Y] | distance : [dis]
        // %2d  -> 출력결과 자리수를 2자리로 설정하고 빈곳은 공백으로 채운다  ex) [ 1]
        // %02d -> 출력결과 자리수를 2자리로 설정하고 빈곳은 0으로 채운다     ex) [01]
        // %0.2f -> 출력결과 소수점 2자리까지 나오게 한다. ex) [0.00]
        UE_LOG(LogTemp, Warning, 
            TEXT("Step %2d : X = %0.2f, Y = %0.2f -> X = %0.2f, Y = %0.2f | distance : %0.2f "),
                        i, prevX, prevY, CurrentLocation.X, CurrentLocation.Y, dis);

        // 이벤트가 발생했는지 리턴값으로 확인 후 출력
        // ->LogTemp: Warning: Event!
        if (creatEvent() == 1) {
            UE_LOG(LogTemp, Warning, TEXT("Event!"));
        }
    }
    // 총 이동 거리 출력
    // LogTemp: Error: totDist : [totDist]
    UE_LOG(LogTemp, Error, TEXT("totDist : %0.2f"), totDist);
}


int32 AAMyActor::step() {
    // 랜덤 0 ~ 1 리턴
	return FMath::RandRange(0, 1);
}

int32 AAMyActor::creatEvent() {
    // 랜덤 0 ~ 1
	int event = FMath::RandRange(0, 1);

    // 이벤트가 발생하면 총 이벤트가 1증가하고 1로 리턴한다
	if (event == 1) {
		++evCnt;
        return 1;
	}
    // 발생하지 않았다면 0을 리턴한다
    return 0;
}