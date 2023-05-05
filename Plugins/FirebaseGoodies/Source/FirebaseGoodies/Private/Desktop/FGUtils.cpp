#include "FGUtils.h"

TArray<char*> StringCopies;

char* FGUtils::GetStringCopy(const FString& Value)
{
	const auto Str = StringCast<ANSICHAR>(*Value);
	char* Destination = new char[Str.Length() + 1];

	snprintf(Destination, Str.Length() + 1, "%s", Str.Get());

	StringCopies.Add(Destination);

	return Destination;
}

void FGUtils::ClearStringCopies()
{
	for (const auto Str : StringCopies)
	{
		delete[]Str;
	}

	StringCopies.Empty();
}
