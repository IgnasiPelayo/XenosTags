// Copyright (c) Ignasi Pelayo, 2023. All Rights Reserved.


#include "XenosTags.h"

#include <sstream>

FXenosTag::FXenosTag(const FName& TagName)
	: Tag(TagName)
{
	
}

FXenosTag::FXenosTag(const char* TagName)
	: Tag(TagName)
{
	
}

void FXenosTag::RefreshValue(const FXenosTag& NewValue) noexcept
{
	Value = NewValue.Value;
}

uint32_t FXenosTag::GetHash() const
{
	uint32_t hash = 0x811C9DC5; // 2166136261
	constexpr uint32_t prime = 0x01000193; // 16777619

	const unsigned char* ptr = reinterpret_cast<const unsigned char*>(TCHAR_TO_UTF8(*Tag.ToString()));
	while (*ptr) hash = (*ptr++ ^ hash) * prime;

	return hash;
}

FString FXenosTag::TagAndValueToString() const
{
	return Tag.ToString() + ": " + GetValueString() + LINE_TERMINATOR;
}

FString FXenosTag::GetValueString() const
{
	// If a new type is added or removed from the variant the accessor must be created or removed
	static_assert(std::variant_size_v<decltype(Value)> == 6);
	
	const size_t CurrentIndex = Value.index();

	if (CurrentIndex == 0) return FString("-");
	if (CurrentIndex == 1) return FString::FromInt(Get<int>());
	if (CurrentIndex == 2) return FString::Printf(TEXT("%.3f"), Get<float>());
	if (CurrentIndex == 3) return Get<bool>() ? "true" : "false";
	if (CurrentIndex == 4) return FString::Printf(TEXT("%.3lf"), Get<double>());
	if (CurrentIndex == 5)
	{
		FString StringValue = "memory address ";
		std::ostringstream oss;
		oss << Get<void*>();
		StringValue += UTF8_TO_TCHAR(oss.str().c_str());
		return StringValue;
	}

	return FString("Invalid index. Something went wrong... Have you added the current index exception on \"FCustomTag::GetValueString()\" function?");
}

void FXenosTag::LogXenosTagsError(const FString& ErrorMessage)
{
	UE_LOG(LogClass, Error, TEXT("%s"), *ErrorMessage)
}