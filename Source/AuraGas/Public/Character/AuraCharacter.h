// Copyright LCC Personal

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURAGAS_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** ComBatInterface */
	 virtual int32 GetPlayerLevel() override;
	/** end ComBatInterface */
private:
	virtual void InitAbilityActorInfo() override;
};
