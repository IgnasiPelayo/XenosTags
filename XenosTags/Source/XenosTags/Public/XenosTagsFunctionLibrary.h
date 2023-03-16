// Copyright (c) Ignasi Pelayo, 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "XenosTagsContainer.h"

#include "XenosTagsFunctionLibrary.generated.h"

UCLASS()
class XENOSTAGS_API UXenosTagsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Tags")
	static void AddTag(const TScriptInterface<IXenosTagsContainer> TagsContainer, FName Tag, bool bIsPermanent = false);

	UFUNCTION(BlueprintCallable, Category = "Tags")
	static void AddTagWithPointerValue(const TScriptInterface<IXenosTagsContainer> TagsContainer, FName Tag, UObject* Value, bool bIsPermanent = false);
	
	UFUNCTION(BlueprintCallable, Category = "Tags")
	static void AddTagWithIntValue(const TScriptInterface<IXenosTagsContainer> TagsContainer, FName Tag, int32 Value, bool bIsPermanent = false);

	UFUNCTION(BlueprintCallable, Category = "Tags")
	static void AddTagWithFloatValue(const TScriptInterface<IXenosTagsContainer> TagsContainer, FName Tag, float Value, bool bIsPermanent = false);

	UFUNCTION(BlueprintCallable, Category = "Tags")
	static void AddTagWithBoolValue(const TScriptInterface<IXenosTagsContainer> TagsContainer, FName Tag, bool Value, bool bIsPermanent = false);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tags")
	static bool HasTag(const TScriptInterface<IXenosTagsContainer> TagsContainer, FName Tag, bool bConsumeTag = false);

	UFUNCTION(BlueprintCallable, Category = "Tags")
	static void RemoveTag(const TScriptInterface<IXenosTagsContainer> TagsContainer, FName Tag);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tags")
	static bool GetTagPointerValue(const TScriptInterface<IXenosTagsContainer> TagsContainer, FName Tag, UObject*& PointerValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tags")
	static bool GetTagIntValue(const TScriptInterface<IXenosTagsContainer> TagsContainer, FName Tag, int32& IntValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tags")
	static bool GetTagFloatValue(const TScriptInterface<IXenosTagsContainer> TagsContainer, FName Tag, float& FloatValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tags")
	static bool GetTagBoolValue(const TScriptInterface<IXenosTagsContainer> TagsContainer, FName Tag, bool& BoolValue);

	UFUNCTION(BlueprintCallable, Category = "Tags")
	static void LogActiveTagsFromContainer(const TScriptInterface<IXenosTagsContainer> TagsContainer);
};