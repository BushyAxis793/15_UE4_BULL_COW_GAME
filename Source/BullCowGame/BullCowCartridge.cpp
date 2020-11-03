// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();
	GetValidWords(Words);
	SetupGame(); //Set up game

	PrintLine(TEXT("The number of possible words is %i"), Words.Num());
	PrintLine(TEXT("Number of valid words is: %i."), GetValidWords(Words).Num());
	PrintLine(TEXT("The Hidden Word is: %s."), *HiddenWord); // Debug Line
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{

	if (bGameOver)
	{
		ClearScreen();
		SetupGame();
	}
	else
	{
		ProcessGuess(Input);
	}
}

void UBullCowCartridge::SetupGame()
{
	//Welcomeing the player
	PrintLine(TEXT("Welcome to game!"));

	HiddenWord = TEXT("cakes"); //Set the HiddenWord
	Lives = HiddenWord.Len();
	bGameOver = false;

	PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
	PrintLine(TEXT("You have %i Lives"), Lives);
	PrintLine(TEXT("Type in your guess and press enter to continue..."));

	// const TCHAR HW[] = TEXT("cakes");

	IsIsogram(HiddenWord);
}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;
	ClearScreen();
	PrintLine(TEXT("You have no lives left!"));
	PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
	PrintLine(TEXT("\nPrsess enter to play again"));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
	if (Guess == HiddenWord)
	{
		PrintLine(TEXT("You have won!"));
		EndGame();
		return;
	}

	// Check right number of characters
	if (Guess.Len() != HiddenWord.Len())
	{
		PrintLine(TEXT("Sorry, try guessing again, you have %i lives reamining"), Lives);
		PrintLine(TEXT("The hidden word is %i letter long"), HiddenWord.Len());
		return;
	}

	// Check if Isogram
	if (!IsIsogram(Guess))
	{

		PrintLine(TEXT("Noe repeating letters guesss again"));
		return;
	}

	//Remove lives
	PrintLine(TEXT("Lost a life!"));
	--Lives;

	if (Lives <= 0)
	{

		EndGame();
		return;
	}
	//Show the player Bulls and Cows
	PrintLine(TEXT("Guess  again, you have %i lives left"), Lives);
	//Check if lives >0
	//If yes play again
	//Show lives left
	//if not show gameover and HiddenWord?
	//Prompt play again, Press Enter to play again
	// Check user input
	// Play again or quit
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
	for (int32 Index = 0; Index < Word.Len(); Index++)
	{
		for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
		{
			if (Word[Index] == Word[Comparison])
			{
				return false;
			}
		}
	}
	return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const
{

	TArray<FString> ValidWords;

	for (FString Word : WordList)
	{
		if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
		{

			ValidWords.Emplace(Word);
		}
	}
	return ValidWords;
}
