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
	// ����� �����ϰ� request �ν��Ͻ��� �����Ѵ�.
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedPtr<IHttpRequest> req = httpModule.CreateRequest();

	// ��û�ϱ� ���� ������ �����Ѵ�.
	req->SetURL(url);
	req->SetVerb(TEXT("GET"));
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	// ��û�� �Ϸ�Ǿ��� �� ����� �Լ��� ���ε��Ѵ�.
	//req->OnProcessRequestComplete().BindUFunction(this, FName("OnReceivedData"));
	req->OnProcessRequestComplete().BindUObject(this, &AH_RequestActor::OnReceivedData);

	// ������ ��û�� ������.
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

	// ��û ����
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

