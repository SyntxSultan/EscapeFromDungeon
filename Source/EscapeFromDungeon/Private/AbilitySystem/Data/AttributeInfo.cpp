// Copyright SyntaxSultan


#include "AbilitySystem/Data/AttributeInfo.h"

FEFDAttributeInfo UAttributeInfo::FindAttributeInfoWithTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FEFDAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag == AttributeTag)
		{
			return Info;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant find Info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}
	return FEFDAttributeInfo();
}
