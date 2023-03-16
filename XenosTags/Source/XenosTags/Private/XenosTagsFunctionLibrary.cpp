// Copyright (c) Ignasi Pelayo, 2023. All Rights Reserved.

#include "XenosTagsFunctionLibrary.h"

void UXenosTagsFunctionLibrary::AddTag(const TScriptInterface<IXenosTagsContainer> TagsContainer, FName Tag,
	bool bIsPermanent)
{
	TagsContainer->AddTag(Tag, bIsPermanent);
}

void UXenosTagsFunctionLibrary::AddTagWithPointerValue(const TScriptInterface<IXenosTagsContainer> TagsContainer,
	FName Tag, UObject* Value, bool bIsPermanent)
{
	TagsContainer->AddTag(FXenosTag(Tag, static_cast<void*>(Value)), bIsPermanent);
}

void UXenosTagsFunctionLibrary::AddTagWithIntValue(const TScriptInterface<IXenosTagsContainer> TagsContainer,
	FName Tag, int32 Value, bool bIsPermanent)
{
	TagsContainer->AddTag(FXenosTag(Tag, Value), bIsPermanent);
}

void UXenosTagsFunctionLibrary::AddTagWithFloatValue(const TScriptInterface<IXenosTagsContainer> TagsContainer,
	FName Tag, float Value, bool bIsPermanent)
{
	TagsContainer->AddTag(FXenosTag(Tag, Value), bIsPermanent);
}

void UXenosTagsFunctionLibrary::AddTagWithBoolValue(const TScriptInterface<IXenosTagsContainer> TagsContainer,
	FName Tag, bool Value, bool bIsPermanent)
{
	TagsContainer->AddTag(FXenosTag(Tag, Value), bIsPermanent);
}

bool UXenosTagsFunctionLibrary::HasTag(const TScriptInterface<IXenosTagsContainer> TagsContainer, FName Tag,
	bool bConsumeTag)
{
	return TagsContainer->HasTag(Tag, bConsumeTag);
}

void UXenosTagsFunctionLibrary::RemoveTag(const TScriptInterface<IXenosTagsContainer> TagsContainer, FName Tag)
{
	TagsContainer->RemoveTag(Tag);
}

bool UXenosTagsFunctionLibrary::GetTagPointerValue(const TScriptInterface<IXenosTagsContainer> TagsContainer,
	FName Tag, UObject*& PointerValue)
{
	return TagsContainer->GetTagValuePointerAs<UObject>(Tag, PointerValue);
}

bool UXenosTagsFunctionLibrary::GetTagIntValue(const TScriptInterface<IXenosTagsContainer> TagsContainer, FName Tag,
	int32& IntValue)
{
	return TagsContainer->GetTagValue<int>(Tag, IntValue);
}

bool UXenosTagsFunctionLibrary::GetTagFloatValue(const TScriptInterface<IXenosTagsContainer> TagsContainer, FName Tag,
	float& FloatValue)
{
	return TagsContainer->GetTagValue<float>(Tag, FloatValue);
}

bool UXenosTagsFunctionLibrary::GetTagBoolValue(const TScriptInterface<IXenosTagsContainer> TagsContainer, FName Tag,
	bool& BoolValue)
{
	return TagsContainer->GetTagValue<bool>(Tag, BoolValue);
}

void UXenosTagsFunctionLibrary::LogActiveTagsFromContainer(const TScriptInterface<IXenosTagsContainer> TagsContainer)
{
	TagsContainer->LogActiveTags();
}