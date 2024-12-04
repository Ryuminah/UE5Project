// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.generated.h"

// 언리얼 C++ 방식의 Enum
UENUM()
enum class ECardType : uint8
{
	Student = 1 UMETA(DisplayName = "ForStudent"),
	Teacher UMETA(DisplayName = "ForTeacher"),
	Staff UMETA(DisplayName = "ForStaff"),
	Invalid
};

/**
 * 
 */
UCLASS()
class UE5PART1_API UCard : public UObject
{
	GENERATED_BODY()
	
public:
	UCard();
	ECardType GetCardType() const { return CardType; }
	void SetCardType(ECardType InCard) { CardType = InCard; }

private:
	UPROPERTY()
	ECardType CardType;

	UPROPERTY()
	uint32 Id;
};
