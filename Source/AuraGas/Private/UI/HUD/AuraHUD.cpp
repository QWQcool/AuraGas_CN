// Copyright LCC Personal

#include "UI/HUD/AuraHUD.h"

// 实际的头文件包含（在源文件中进行）
#include "AbilitySystemComponent.h"           // 能力系统组件实现   
#include "AttributeSet.h"                     // 属性集实现
#include "UI/WidgetController/OverlayWidgetController.h"  // 覆盖层控件控制器实现
#include "UI/WidgetController/AuraWidgetController.h"     // 基础控件控制器实现
#include "UI/Widget/AuraUserWidget.h"         // Aura用户控件实现

// 获取或创建覆盖层控件控制器实例
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
    if (OverlayWidgetController == nullptr)
    {
        // 使用蓝图类创建新的控制器实例
        OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
        // 设置控制器参数
        OverlayWidgetController->SetWidgetControllerParams(WCParams);
        OverlayWidgetController->BindCallBacksToDependencies();
    }
    return OverlayWidgetController;
}

// 初始化整个覆盖层UI系统
void AAuraHUD::InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState,
    UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet)
{
    // 安全检查：确保蓝图类已设置
    checkf(OverlayWidgetClass, TEXT("Overlay Widget Class is nullptr. Please fill out Aura HUD Blueprint!"));
    checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class is nullptr. Please fill out Aura HUD Blueprint!"));
    
    // 创建控件实例
    UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
    OverlayWidget = Cast<UAuraUserWidget>(Widget);

    // 构建控件控制器参数
    const FWidgetControllerParams WidgetControllerParams{PlayerController, PlayerState, AbilitySystemComponent, AttributeSet};
    
    // 获取控件控制器
    UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
    
    // 设置控件与控制器的关联
    OverlayWidget->SetWidgetController(WidgetController);
    WidgetController->BroadcastInitialValues();
    
    // 将控件添加到视口
    Widget->AddToViewport();
}

void AAuraHUD::BeginPlay()
{
    Super::BeginPlay();  // 调用父类的BeginPlay
}
