#include "BackpackComponent.h"

#include "PickableItem.h"
#include "ItemsDataAsset.h"

UBackpackComponent::UBackpackComponent()
{
	static ConstructorHelpers::FObjectFinder<UItemsDataAsset> ItemsDataAssetFinder(TEXT("ItemsDataAsset'/Game/Inventory/ItemsDataAsset.ItemsDataAsset'"));
	ItemsDataAsset = ItemsDataAssetFinder.Object;
}

bool UBackpackComponent::HasItem() const
{
	return BackpackData.StoredItem != nullptr;
}

void UBackpackComponent::PickItem(APickableItem* Item)
{
	if (FItemSettings* ItemSettings = ItemsDataAsset->ItemsData.Find(Item->ItemType))
	{
		BackpackData.ItemType = Item->ItemType;
		BackpackData.StoredItem = ItemSettings;

		Item->Destroy();
		OnBackpackChanged.Broadcast();
	}
}

void UBackpackComponent::DropItem(FVector Destination)
{
	if (APickableItem* Spawned = StaticCast<APickableItem*>(GetWorld()->SpawnActor(APickableItem::StaticClass())))
	{
		Spawned->SetActorLocation(Destination);
		Spawned->SetItemType(BackpackData.ItemType);

		BackpackData.StoredItem = nullptr;
		OnBackpackChanged.Broadcast();
	}
}