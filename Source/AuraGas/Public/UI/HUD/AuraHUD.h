// Copyright LCC Personal

#pragma once

#include "CoreMinimal.h"           // UE基础头文件，包含基本类型和宏定义
#include "GameFramework/HUD.h"    // HUD基类头文件，AAuraHUD继承自AHUD
#include "AuraHUD.generated.h"    // UE反射系统生成的头文件，支持蓝图和反射

// Forward declarations - 前向声明（优化关键）
class UAbilitySystemComponent;    // 前向声明能力系统组件类
class UAttributeSet;             // 前向声明属性集类
class UOverlayWidgetController;   // 前向声明覆盖层控件控制器类
class UAuraUserWidget;           // 前向声明Aura用户控件类
struct FWidgetControllerParams;   // 前向声明控件控制器参数结构体

/**
 * Aura游戏的主要HUD类，负责管理UI控件的显示和交互
 */
UCLASS()
class AURAGAS_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:
	// 当前显示的覆盖层控件实例（蓝图可读）
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	// 获取或创建覆盖层控件控制器
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	// 初始化覆盖层UI系统
	void InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState, 
					 UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet);
    
protected:
	virtual void BeginPlay() override;  // 游戏开始时调用
private:
	// 覆盖层控件的蓝图类引用（可在编辑器中设置）
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	// 覆盖层控件控制器实例
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	// 覆盖层控件控制器的蓝图类引用
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
