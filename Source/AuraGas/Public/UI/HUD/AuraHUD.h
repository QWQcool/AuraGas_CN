// Copyright LCC Personal

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;

/**
 * 
 */
UCLASS()
class AURAGAS_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
	TObjectPtr<UAuraUserWidget> OverlayWidget;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
};
