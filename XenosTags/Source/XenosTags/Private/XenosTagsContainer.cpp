// Copyright (c) Ignasi Pelayo, 2023. All Rights Reserved.

#include "XenosTagsContainer.h"

void IXenosTagsContainer::ReserveTagsContainerSize(const int& NewSize)
{
	Tags.Reserve(NewSize);
}

void IXenosTagsContainer::AddTag(const FXenosTag& Tag, const bool& bIsPermanent)
{
	AddTag(Tag, bIsPermanent ? PermanentTagsHash : TagsHash);
}

void IXenosTagsContainer::RemoveTag(const FXenosTag& Tag)
{
	const uint32 Hash = Tag.GetHash();
	uint32 Index = 0;

	if (GetIndexByHash(Hash, Tag, TagsHash, Index))
	{
		TagsHash.Remove(Hash, Index);
	}

	if (GetIndexByHash(Hash, Tag, PermanentTagsHash, Index))
	{
		PermanentTagsHash.Remove(Hash, Index);
	}
}

bool IXenosTagsContainer::HasTag(const FXenosTag& Tag, const bool& bConsumeTag)
{
	const uint32 Hash = Tag.GetHash();
	const bool HasTagCheck = HasTag(Hash, Tag, TagsHash) || HasTag(Hash, Tag, PermanentTagsHash);

	if (HasTagCheck && bConsumeTag)
	{
		RemoveTag(Tag);
	}

	return HasTagCheck;
}

void IXenosTagsContainer::ClearTags()
{
	TagsHash.Clear();
}

void IXenosTagsContainer::ClearPermanentTags()
{
	PermanentTagsHash.Clear();
}

void IXenosTagsContainer::LogActiveTags()
{
	FString Message = "Tags: ";
	for (int i = 0; i < Tags.Num(); i++)
	{
		if (HasTag(Tags[i]))
		{
			Message.Append(LINE_TERMINATOR).Append(Tags[i].TagAndValueToString());
		}
	}

	UE_LOG(LogClass, Display, TEXT("----- %s"), *Message)
}

void IXenosTagsContainer::AddUniqueTag(const FXenosTag& Tag, uint32& OutIndex)
{
	TArray<FXenosTag>::SizeType Index;
	if (Tags.Num() > 0 && Tags.Find(Tag, Index))
	{
		OutIndex = Index;
		Tags[Index].RefreshValue(Tag);

		return;
	}

	OutIndex = Tags.Add(Tag);
}

void IXenosTagsContainer::AddTag(const FXenosTag& Tag, FHashTable& HashTable)
{
	const uint32 Hash = Tag.GetHash();

	uint32 TagIndex = 0;
	AddUniqueTag(Tag, TagIndex);

	if (HasTag(Hash, Tag, HashTable) == false)
	{
		HashTable.Add(Hash, TagIndex);
	}
}

bool IXenosTagsContainer::HasTag(const uint32& Hash, const FXenosTag& Tag, const FHashTable& HashTable) const
{
	for (uint32 i = HashTable.First(Hash); HashTable.IsValid(i); i = HashTable.Next(i))
	{
		if (Tags[i] == Tag)
		{
			return true;
		}
	}

	return false;
}

bool IXenosTagsContainer::GetIndexByHash(const uint32& Hash, const FXenosTag& Tag, const FHashTable& HashTable,
	uint32& OutIndex)
{
	/** To remove a Tag from a HashTable we need it's hash value and the position or index inside the Tags array.
 	*	In order to get this index and not iterate all the tags inside Tags array, we can convert the tag to hash
 	*	and only iterate all the tags that have the same hash value, decreasing vastly the execution time. */

	for (uint32 i = HashTable.First(Hash); HashTable.IsValid(i); i = HashTable.Next(i))
	{
		if (Tags[i] == Tag)
		{
			OutIndex = i;
			return true;
		}
	}

	return false;
}