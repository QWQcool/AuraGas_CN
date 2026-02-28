// Copyright LCC Personal

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURAGAS_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UObject> WidgetController;
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
