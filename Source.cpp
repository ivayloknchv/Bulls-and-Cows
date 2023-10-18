#include <iostream>
#include <string>
#include <random>
#include <cmath>

int GetBulls(int num,int random)
{
	int bulls = 0;

	while (num != 0)
	{
		if ((num % 10) == (random % 10))
		{
			bulls++;
		}
		num /= 10;
		random /= 10;
	}
	return bulls;
}
int GetCows(int num,int random,int digits)
{
	int cows = 0;
	int dig = digits;
	int* numArr = new int[digits];
	int* ranArr = new int[digits];

	for (int i = 0; i < digits; i++)
	{
		numArr[i] = num % 10;
		ranArr[i] = random % 10;

		num /= 10;
		random /= 10;
	}

	for (int i = 0; i < digits; i++)
	{
		for (int j = 0; j < digits; j++)
		{
			if ((numArr[i] == ranArr[j]) && (i != j))
			{
				cows++;
			}
		}
	}
	return cows;
}
bool CheckDigitsCount(int number,int digits)
{
	if (abs(number) < pow(10, digits - 1)||abs(number)>=pow(10,digits))
	{
		return false;
	}
	return true;
}
bool CheckDifferentDigits(int num)
{
	int currentNum = 0;
	num = abs(num);
	int numbers[9] = { 1,2,3,4,5,6,7,8,9 };
	while (num != 0)
	{
		currentNum =num% 10;
		if (currentNum == 0)
		{
			return false;
		}

		for (int i = 0; i < 9; i++)
		{
			if ((currentNum == i + 1) && numbers[i] == 0)
			{
				return false;
			}
			if (currentNum == i + 1)
			{
				numbers[i] = 0;
				break;
			}
			
		}
		num /= 10;
	}
	return true;
}
int GetRandom(int digits)
{
	int random = 0;
	while (true)
	{
		std::random_device rd;
		std::uniform_int_distribution<int> dist(pow(10, digits - 1), pow(10, digits) - 1);
		random = dist(rd);
		if (CheckDifferentDigits(random))
		{
			break;
		}
	}
	return random;
}
bool ValidityCheck(int num,int digits)
{
	bool invalidNum = true;
	if (CheckDigitsCount(num, digits) == false)
	{
		std::cout << "Try another number! This one doesn't have " << digits << " digits!\n";
		invalidNum = false;
	}
	if (num < 0)
	{
		std::cout << "Try another number! This one is negative!\n";
		invalidNum = false;
	}
	if (CheckDifferentDigits(num) == false)
	{
		std::cout << "Try another number! This one has 0 or repeated digits!\n";
		invalidNum = false;
	}
	return invalidNum;
}
int main()
{
	int digits = 0, num = 0, random=0, bulls=0, cows=0;
	std::string name = " ";
	std::cout<< "Hey, what's your name? Type here: ";
	std::cin >> name;
	std::cout<<"Nice, "<<name<<"! Please enter the number of digits in the number you would like to play with : ";
	std::cin>>digits;
	std::cout<<"Great, let's play Bulls and Cows!\n";
	
	random = GetRandom(digits);

	while (true)
	{
		std::cout << "Please enter a " << digits << "-digit number: ";
		std::cin >> num;

		if (ValidityCheck(num,digits)==false)
		{
			continue;
		}
		int bulls = GetBulls(num, random);
		int cows = GetCows(num, random, digits);
		std::cout << "Bulls = " << bulls << " Cows = " << cows << '\n';

		if (bulls == digits)
		{
			std::cout << "Congratulations, " << name << "! You won this game! You guessed the number!";
		}
	}
	return 0;
}