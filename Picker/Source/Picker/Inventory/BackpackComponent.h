#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BackpackComponent.generated.h"

class APickableItem;
struct FItemSettings;
enum class EItemType : uint8;

USTRUCT(BlueprintType)
struct FBackpackData
{
	GENERATED_BODY()

	EItemType ItemType;

	FItemSettings* StoredItem = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSimpleDynamicMulticastDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PICKER_API UBackpackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBackpackComponent();

	UFUNCTION(BlueprintPure)
	bool HasItem() const;

	void PickItem(APickableItem* Item);
	void DropItem(FVector Destination);

private:
	UPROPERTY()
	class UItemsDataAsset* ItemsDataAsset;

public:
	FBackpackData BackpackData;

	UPROPERTY(BlueprintAssignable)
	FSimpleDynamicMulticastDelegate OnBackpackChanged;
};