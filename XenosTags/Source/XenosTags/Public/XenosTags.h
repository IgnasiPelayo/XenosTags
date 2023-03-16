// Copyright (c) Ignasi Pelayo, 2023. All Rights Reserved.

#pragma once
#include <variant>
#include <intrin.h>

DECLARE_LOG_CATEGORY_EXTERN(LogXenosTag, Log, All);

//Declare a tag with the same tag name as the variable name
#define DEFINE_TAG(X) inline static const FName X = #X;

class XENOSTAGS_API FXenosTag
{
public:
	FXenosTag(const FName& TagName);

	FXenosTag(const char* TagName);

	template <typename _Type>
	FXenosTag(const FName& TagName, const _Type& TagValue)
		: FXenosTag(TagName)
	{
		if (CanHold<_Type>())
		{
			Value = TagValue;
			return;
		}

#if !UE_BUILD_SHIPPING
		LogXenosTagsError(FString::Printf(TEXT("The value given to initialize the %s tag is not supported"), *Tag.ToString()));
#endif
	}

	template <typename _Type>
	FXenosTag(const char* TagName, const _Type& TagValue)
		: FXenosTag(FName(TagName), TagValue)
	{
		
	}
	
	void RefreshValue(const FXenosTag& NewValue) noexcept;

	// Get the tag value in the desired type if possible
	template <typename _Type>
	constexpr decltype(auto) Get() const
	{
		const auto ValuePtr = std::get_if<_Type>(&Value);

		if (ValuePtr != nullptr) return static_cast<_Type>(*ValuePtr);

		LogXenosTagsError(FString::Printf(TEXT("Bad variant type access on %s"), *Tag.ToString()));
		UE_DEBUG_BREAK();
		return _Type();
	}

	// Convert the void pointer of the variant to the desired pointer type
	template <typename _Type>
	constexpr decltype(auto) GetPointerValue() const
	{
		const auto ValuePtr = std::get_if<void*>(&Value);
		if (ValuePtr != nullptr) return static_cast<_Type*>(*ValuePtr);

		LogXenosTagsError(FString::Printf(TEXT("Bad variant type access on %s"), *Tag.ToString()));
		UE_DEBUG_BREAK();
		return static_cast<_Type*>(nullptr);
	}

	// Helper function to cast any pointer to the c++ generic void pointer
	template <typename _Type>
	static void* ToVoidPtr(const _Type* InPtr)
	{
		return (void*)InPtr;
	}

	// Convert the tag name to hash value for faster and more efficient lookups
	uint32_t GetHash() const;

	// For debug-only purposes. Converts the tag name and value to FString for better legibility
	FString TagAndValueToString() const;
	
	friend bool operator==(const FXenosTag& Lhs, const FXenosTag& Rhs)
	{
		return Lhs.Tag.IsEqual(Rhs.Tag);
	}

	friend bool operator!=(const FXenosTag& Lhs, const FXenosTag& Rhs)
	{
		return !Lhs.Tag.IsEqual(Rhs.Tag);
	}

protected:
	template <typename _Type>
	constexpr bool CanHold() noexcept
	{
		constexpr size_t VariantSize = std::variant_size_v<decltype(Value)>;
		constexpr size_t Index = std::_Meta_find_unique_index<decltype(Value), _Type>::value;
		return Index < 0 && Index <= VariantSize;
	}

	// For debug-only purposes. Converts the tag value to FString for better legibility
	FString GetValueString() const;
	
	static void LogXenosTagsError(const FString& ErrorMessage);

protected:
	FName Tag;

	// Variant that holds the value of the tag. std::byte is the equivalent of an empty variant value
	std::variant<std::byte, int, float, bool, double, void*> Value;
};
