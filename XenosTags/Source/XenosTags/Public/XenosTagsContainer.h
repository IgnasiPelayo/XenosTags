// Copyright (c) Ignasi Pelayo, 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "XenosTags.h"

#include "XenosTagsContainer.generated.h"

UINTERFACE(MinimalAPI)
class UXenosTagsContainer : public UInterface
{
	GENERATED_BODY()
};

// This interface allows to store and manage multiple tags that can be temporal (at the end of the frame should be cleared)
// or permanent
class XENOSTAGS_API IXenosTagsContainer
{
	GENERATED_BODY()

public:
	// Resize the array that contains the current tags for this tags container to avoid "unnecessary" copies in runtime
	void ReserveTagsContainerSize(const int& NewSize);

	// Add tags from the start. Very useful on permanent tags
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Tags")
	void AddTagsOnInitialize();

	void AddTag(const FXenosTag& Tag, const bool& bIsPermanent = false);

	void RemoveTag(const FXenosTag& Tag);

	bool HasTag(const FXenosTag& Tag, const bool& bConsumeTag = false);

	template<typename T>
	bool GetTagValue(const FXenosTag& Tag, T& OutValue) const
	{
		const uint32 Hash = Tag.GetHash();

		if (Get<T>(Hash, Tag, TagsHash, OutValue))
		{
			return true;
		}
	
		if (Get<T>(Hash, Tag, PermanentTagsHash, OutValue))
		{
			return true;
		}
	
		return false;
	}

	template<typename T>
	bool GetTagValuePointerAs(const FXenosTag& Tag, T*& OutValue) const
	{
		const uint32 Hash = Tag.GetHash();

		if (GetPointerValue<T>(Hash, Tag, TagsHash, OutValue))
		{
			return true;
		}
	
		if (GetPointerValue<T>(Hash, Tag, PermanentTagsHash, OutValue))
		{
			return true;
		}
	
		return false;
	}
	
	void ClearTags();

	void ClearPermanentTags();

	void LogActiveTags();

protected:
	void AddUniqueTag(const FXenosTag& Tag, uint32& OutIndex);
	
	void AddTag(const FXenosTag& Tag, FHashTable& HashTable);

	bool HasTag(const uint32& Hash, const FXenosTag& Tag, const FHashTable& HashTable) const;

	template<typename T>
	bool Get(const uint32& Hash, const FXenosTag& Tag, const FHashTable& HashTable, T& OutValue) const
	{
		for (uint32 i = HashTable.First(Hash); HashTable.IsValid(i); i = HashTable.Next(i))
		{
			if (Tags[i] == Tag)
			{
				OutValue = Tags[i].Get<T>();
				return true;
			}
		}

		return false;
	}

	template<typename T>
	bool GetPointerValue(const uint32& Hash, const FXenosTag& Tag, const FHashTable& HashTable, T*& OutValue) const
	{
		for (uint32 i = HashTable.First(Hash); HashTable.IsValid(i); i = HashTable.Next(i))
		{
			if (Tags[i] == Tag)
			{
				OutValue = Tags[i].GetPointerValue<T>();
				return true;
			}
		}

		return false;
	}
	
	bool GetIndexByHash(const uint32& Hash, const FXenosTag& Tag, const FHashTable& HashTable, uint32& OutIndex);

protected:
	TArray<FXenosTag> Tags;

	// Tags that should be cleared at the end of every tick
	FHashTable TagsHash;

	// Tags that will only be removed when the user wants to
	FHashTable PermanentTagsHash;
};