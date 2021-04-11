#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableItem.generated.h"

enum class EItemType : uint8;

UCLASS()
class PICKER_API APickableItem : public AActor
{
	GENERATED_BODY()

private:
	void OnStaticMeshLoaded(TSoftObjectPtr<UStaticMesh> StaticMeshPtr);

	void LoadStaticMesh();

public:	
	APickableItem();

	void SetItemType(EItemType InItemType);

	virtual void PostLoad() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	UPROPERTY(VisibleDefaultsOnly)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly)
	class USphereComponent* InteractCollision;

	UPROPERTY()
	class UItemsDataAsset* ItemsDataAsset;

public:	
	UPROPERTY(EditInstanceOnly)
	EItemType ItemType;
};
