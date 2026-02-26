// Copyright LCC Personal


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"


AAuraCharacter::AAuraCharacter()
{
	// 设置角色移动朝向：让角色自动朝向移动方向
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	// 设置角色旋转速率：Y轴（水平旋转）每秒400度
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	
	// 限制角色在平面上移动：防止角色在Z轴上移动
	GetCharacterMovement()->bConstrainToPlane = true;
	
	// 角色开始时自动对齐到平面
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// 禁用控制器对角色旋转的控制
	// 这样角色旋转完全由移动方向决定，而不是控制器输入
	bUseControllerRotationPitch = false;  // 禁用俯仰角控制
	bUseControllerRotationYaw = false;    // 禁用偏航角控制
	bUseControllerRotationRoll = false;    // 禁用滚转角控制
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 设置玩家状态的AbilitySystemComponent 在服务器上
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// 设置玩家状态的AbilitySystemComponent 在客户端上
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
}
