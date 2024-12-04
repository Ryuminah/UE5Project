// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"
#include "Card.h"

UPerson::UPerson()
{
	Name = TEXT("사람");

	// FName : 고유한 이름
	Card = CreateDefaultSubobject<UCard>(TEXT("NAME_Card"));

}



