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
    ProcessGuess(Input);
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (bGameOver)
    {
        ClearScreen();
        InitGame();
        return;
    }

    if (Guess == HiddenWord)
    {
        ClearScreen();
        PrintLine(TEXT("Correct! You have won!"));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("I told you to guess a %i letter word... \ncan't you count?"), HiddenWord.Len());
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("There can be no repeating letters."));
        return;
    }

    if (--Lives > 0)
    {
        PrintLine(TEXT("Incorrect. You have %i more guesses."), Lives);
        return;
    }

    ClearScreen();
    PrintLine(TEXT("Incorrect. You have lost."));
    PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
    EndGame();
}

void UBullCowCartridge::InitGame()
{
    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Welcome to Bull Cow!"));
    PrintLine(TEXT("Please guess the %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("You have %i guesses..."), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    TCHAR letter;

    for (int32 i = 0; i < Word.Len(); i++)
    {
        letter = Word[i];
        for (int32 j = 0; j < Word.Len(); j++)
        {
            if (j == i) continue;
            if (Word[j] == letter) return false;
        }
    }
    return true;
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press ENTER to play again..."));
}

