// Copyright LCC Personal


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AuraGas/AuraGas.h"

AAuraEnemy::AAuraEnemy()
{
	// 设置网格体的碰撞响应，使其对可见性通道（通常用于射线检测）产生阻挡
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// 创建并设置Gameplay Ability System组件
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	// 设置组件需要网络复制
	AbilitySystemComponent->SetIsReplicated(true);
	// 设置复制模式为最小复制（只复制必要的数据）
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	// 创建属性集组件，用于管理角色的各种属性（如生命值、魔法值等）
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::BeginPlay()
{
	// 调用父类的BeginPlay函数
	Super::BeginPlay();
	
	// 检查AbilitySystemComponent是否有效（防止空指针）
	check(AbilitySystemComponent);
	
	// 初始化AbilitySystemComponent，设置拥有者和化身（都是this，表示敌人自己）
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AAuraEnemy::HighlightActor()
{
	// 启用网格体的自定义深度渲染（用于高亮效果）
	GetMesh()->SetRenderCustomDepth(true);
	// 设置自定义深度模板值为红色（CUSTOM_DEPTH_RED是自定义的枚举值）
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
	// 同样启用武器的高亮效果
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighlightActor()
{
	// 关闭网格体的自定义深度渲染（取消高亮）
	GetMesh()->SetRenderCustomDepth(false);
	
	// 关闭武器的高亮效果
	Weapon->SetRenderCustomDepth(false);
}
