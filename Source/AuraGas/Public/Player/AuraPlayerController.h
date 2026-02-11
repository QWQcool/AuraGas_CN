// Copyright LCC Personal

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

// 前置声明：避免头文件循环包含，提高编译效率
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * AuraPlayerController - 玩家控制器类
 * 
 * 玩家控制器是UE中控制玩家角色的核心类，负责：
 * 1. 处理玩家输入（键盘、鼠标、手柄等）
 * 2. 管理玩家视角和摄像机
 * 3. 处理网络复制（多人游戏）
 * 4. 管理UI和HUD交互
 */
UCLASS()
class AURAGAS_API AAuraPlayerController : public APlayerController
{
	// UE宏：生成反射代码，支持序列化、蓝图访问等
	GENERATED_BODY()
	
public:
	// 构造函数
	AAuraPlayerController();
	
protected:
	// 重写BeginPlay：在Actor开始游戏时调用，用于初始化逻辑
	virtual void BeginPlay() override;

	// 重写SetupInputComponent：设置输入组件
	virtual void SetupInputComponent() override;
	
private:
	// UPROPERTY宏：使变量在编辑器中可见，支持序列化和垃圾回收
	// EditAnywhere：可在编辑器的任何地方编辑此属性
	// Category = "Input"：在编辑器中将此属性归类到"Input"分类下
	UPROPERTY(EditAnywhere, Category = "Input")
	// TObjectPtr：UE5引入的智能指针，自动管理UObject的生命周期
	// UInputMappingContext：Enhanced Input系统的输入映射上下文
	// 用于定义按键与游戏动作的映射关系
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	void Move(const FInputActionValue& InputActionValue);

	
};