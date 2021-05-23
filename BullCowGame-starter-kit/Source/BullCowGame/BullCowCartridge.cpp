// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    InitGame();
    
    //PrintLine(TEXT("The HiddenWord is %s"), *HiddenWord);
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        InitGame();
    }
    else
    {
        if (Input.Len() == HiddenWord.Len())
        {
            if (Input == HiddenWord)
            {
                PrintLine(TEXT("Correct!"));
                EndGame();
            }
            else
            {
                PrintLine(TEXT("Incorrect."));
                EndGame();
            }
        }
        else
        {
            PrintLine(TEXT("I told you to guess a %i letter word... \ncan't you count?"), HiddenWord.Len());
        }
    }

    
}

void UBullCowCartridge::InitGame()
{
    HiddenWord = TEXT("cake");
    Lives = 4;
    bGameOver = false;

    PrintLine(TEXT("Welcome to Bull Cow!"));
    PrintLine(TEXT("Please guess the %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("You have %i guesses..."), Lives);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press ENTER to play again..."));
}