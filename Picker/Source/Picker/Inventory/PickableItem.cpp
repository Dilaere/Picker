#include "PickableItem.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

#include "ItemsDataAsset.h"

APickableItem::APickableItem()
{
	static ConstructorHelpers::FObjectFinder<UItemsDataAsset> ItemsDataAssetFinder(TEXT("ItemsDataAsset'/Game/Inventory/ItemsDataAsset.ItemsDataAsset'"));
	ItemsDataAsset = ItemsDataAssetFinder.Object;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	InteractCollision = CreateDefaultSubobject<USphereComponent>(TEXT("InteractCollision"));
	InteractCollision->SetSphereRadius(100.f);
	InteractCollision->SetupAttachment(RootComponent);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetWorldScale3D(FVector(0.3f));

	LoadStaticMesh();
}

void APickableItem::SetItemType(EItemType InItemType)
{
	if (ItemType != InItemType)
	{
		ItemType = InItemType;
		LoadStaticMesh();
	}
}

void APickableItem::PostLoad()
{
	Super::PostLoad();

	LoadStaticMesh();
}

#if WITH_EDITOR
void APickableItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ?
		PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(APickableItem, ItemType))
	{
		LoadStaticMesh();
	}
}
#endif

void APickableItem::LoadStaticMesh()
{
	if (FItemSettings* ItemSettings = ItemsDataAsset->ItemsData.Find(ItemType))
	{
		if (UAssetManager::IsValid())
		{
			FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
			StreamableManager.RequestAsyncLoad(ItemSettings->StaticMesh.ToSoftObjectPath(),
				FStreamableDelegate::CreateUObject(this, &APickableItem::OnStaticMeshLoaded, ItemSettings->StaticMesh));
		}
		else
		{
			StaticMesh->SetStaticMesh(ItemSettings->StaticMesh.LoadSynchronous());
		}
	}
}

void APickableItem::OnStaticMeshLoaded(TSoftObjectPtr<UStaticMesh> StaticMeshPtr)
{
	if (IsValidLowLevel() && StaticMeshPtr.IsValid())
	{
		StaticMesh->SetStaticMesh(StaticMeshPtr.Get());
	}
}
