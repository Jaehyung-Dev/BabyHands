// Fill out your copyright notice in the Description page of Project Settings.


#include "H_RequestActor.h"
#include "HttpModule.h"
#include "ImageUtils.h"

// Sets default values
AH_RequestActor::AH_RequestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AH_RequestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AH_RequestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AH_RequestActor::SendRequest(const FString url)
{
	// 모듈을 생성하고 request 인스턴스를 생성한다.
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	// 요청하기 위한 정보를 설정한다.
	req->SetURL(url);
	req->SetVerb(TEXT("GET"));
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	// 요청이 완료되었을 때 실행될 함수를 바인딩한다.
	//req->OnProcessRequestComplete().BindUFunction(this, FName("OnReceivedData"));
	req->OnProcessRequestComplete().BindUObject(this, &AH_RequestActor::OnReceivedData);

	// 서버에 요청을 보낸다.
	req->ProcessRequest();
}	

void AH_RequestActor::OnReceivedData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	
}

void AH_RequestActor::PostRequest(const FString url)
{
	TMap<FString, FString> studentData;
	studentData.Add("Hands Number", "0");
	

	FString myJsonData = UJsonParseLibrary::MakeJson(studentData);
	//gm->SetLogText(myJsonData);

	// 요청 설정
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
	req->SetURL(url);
	req->SetVerb(TEXT("POST"));
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	req->SetContentAsString(myJsonData);
	req->OnProcessRequestComplete().BindUObject(this, &AH_RequestActor::OnPostData);
	req->ProcessRequest();
}

void AH_RequestActor::OnPostData(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully)
{
	
}

