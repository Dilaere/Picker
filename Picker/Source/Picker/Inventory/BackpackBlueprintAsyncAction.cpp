#include "BackpackBlueprintAsyncAction.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

#include "BackpackComponent.h"
#include "ItemsDataAsset.h"

UBackpackBlueprintAsyncAction* UBackpackBlueprintAsyncAction::GetItemIcon(const UObject* WorldContextObject)
{
	return NewObject<UBackpackBlueprintAsyncAction>(WorldContextObject->GetWorld());
}

void UBackpackBlueprintAsyncAction::Activate()
{
	auto* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto* BackpackComponent = PlayerCharacter != nullptr ? PlayerCharacter->FindComponentByClass<UBackpackComponent>() : nullptr;
	if (BackpackComponent == nullptr)
	{
		return;
	}

	auto Icon = BackpackComponent->BackpackData.StoredItem->Icon;
	auto OnLoaded = [this, Icon]()
	{
		if (Icon.IsValid())
		{
			OnIconLoaded.Broadcast(Icon.Get());
		}
	};

	if (UAssetManager::IsValid())
	{
		FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
		StreamableManager.RequestAsyncLoad(Icon.ToSoftObjectPath(), OnLoaded);
	}
	else
	{
		OnIconLoaded.Broadcast(Icon.LoadSynchronous());
	}
}