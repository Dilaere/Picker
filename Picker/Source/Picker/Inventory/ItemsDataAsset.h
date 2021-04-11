#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemsDataAsset.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Bottle,
	Stone
};

USTRUCT(BlueprintType)
struct FItemSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UStaticMesh> StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;
};

UCLASS()
class PICKER_API UItemsDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EItemType, FItemSettings> ItemsData;
};
