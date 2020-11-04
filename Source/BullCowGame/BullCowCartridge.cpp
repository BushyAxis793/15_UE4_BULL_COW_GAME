// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
//#include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();

	Isograms = GetValidWords(Words);

	SetupGame(); //Set up game
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

	HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
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

void UBullCowCartridge::ProcessGuess(const FString &Guess)
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
	FBullCowCount Score = GetBullCows(Guess);

	PrintLine(TEXT("Guess  again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString &Word) const
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

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString> &WordList) const
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

FBullCowCount UBullCowCartridge::GetBullCows(const FString &Guess) const
{
	FBullCowCount Count;

	for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
	{
		if (Guess[GuessIndex] == HiddenWord[GuessIndex])
		{
			Count.Bulls++;
			continue;
		}
		for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
		{
			if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
			{
				Count.Cows++;
				break;
			}
		}
	}
	return Count;
}
