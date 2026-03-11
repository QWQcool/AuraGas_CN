// Copyright LCC Personal

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Interaction/EnemyInterface.h"

// 构造函数：在对象创建时调用
AAuraPlayerController::AAuraPlayerController()
{
	// 在多人游戏中，这个设置确保玩家控制器可以在客户端之间同步
	// 服务器上的变化会自动复制到所有客户端
	bReplicates = true;
	
	LastActor = nullptr;
	ThisActor = nullptr;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit)return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	IEnemyInterface* LastEnemyInterface = Cast<IEnemyInterface>(LastActor);
	IEnemyInterface* ThisEnemyInterface = Cast<IEnemyInterface>(ThisActor);

	/**
	 * Line trace from cursor. There are several scanarios:
	 * A. LastActor is nullptr && ThisActor is nullptr
	 *    - Do nothing
	 * B. LastActor is nullptr && ThisActor is not nullptr
	 *    - Highlight ThisActor
	 * C. LastActor is not nullptr && ThisActor is nullptr
	 *    - Remove highlight from LastActor
	 * D. LastActor is not nullptr && ThisActor is not nullptr, but LastActor != ThisActor
	 *    - Remove highlight from LastActor
	 *    - Highlight ThisActor
	 * E. LastActor is not nullptr && ThisActor is not nullptr, and LastActor == ThisActor
	 *    - Do nothing
	 */

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr && ThisEnemyInterface != nullptr)
		{
			//Case B
			ThisEnemyInterface->HighlightActor();
		}
		else
		{
			//Case A
			//Do nothing
		}
	}
	else
	{
		if (ThisActor == nullptr)
		{
			//Case C
			if (LastEnemyInterface != nullptr)
			{
				LastEnemyInterface->UnHighlightActor();
			}
		}
		else if (LastActor != ThisActor)
		{
			//Case D
			if (LastEnemyInterface != nullptr)
			{
				LastEnemyInterface->UnHighlightActor();
			}
			if (ThisEnemyInterface != nullptr)
			{
				ThisEnemyInterface->HighlightActor();
			}
		}
		else if (LastActor == ThisActor)
		{
			//Case E
			//Do nothing
		}
	}
}

// BeginPlay：在Actor开始游戏时调用，用于初始化逻辑
void AAuraPlayerController::BeginPlay()
{
	// 调用父类的BeginPlay，确保基础功能正常初始化
	Super::BeginPlay();
	
	// 只在有本地玩家的情况下设置Enhanced Input系统（避免服务器端断言失败）
	if (GetLocalPlayer())
	{
		// check宏：调试断言，如果AuraContext为nullptr则崩溃
		// 确保在编辑器中设置了Input Mapping Context资源
		check(AuraContext);
		
		// Enhanced Input System：UE5的新输入系统，比传统输入系统更强大
		// 获取本地玩家的Enhanced Input子系统（单例模式）
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		
		// 再次检查子系统是否有效
		check(Subsystem);
		
		// 添加输入映射上下文到子系统
		// AuraContext：包含按键到游戏动作的映射定义
		// 0：优先级，数值越小优先级越高（0为最高优先级）
		Subsystem->AddMappingContext(AuraContext, 0);
		
		// 显示鼠标光标
		bShowMouseCursor = true;
		// 设置默认鼠标光标样式
		DefaultMouseCursor = EMouseCursor::Default;
		
		// 创建游戏和UI混合输入模式
		FInputModeGameAndUI InputModeData;
		
		// 设置鼠标锁定行为：不锁定鼠标到视口
		// 这样鼠标就可以在游戏窗口外自由移动
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		
		// 设置鼠标捕获时不隐藏光标
		InputModeData.SetHideCursorDuringCapture(false);
		
		// 应用输入模式设置
		SetInputMode(InputModeData);
	}
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// 获取输入向量（WASD或手柄摇杆输入）
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
    
	// 获取控制器旋转（只使用Yaw轴，忽略俯仰和滚转）
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
    
	// 计算前后方向和左右方向向量
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    
	// 合成最终移动方向向量
	const FVector Direction = ForwardDirection * InputAxisVector.Y + RightDirection * InputAxisVector.X;

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(Direction);

		// 如果需要对前后移动和左右移动应用不同的缩放系数
		// 需要分别调试前后和左右移动的输入值
		// 游戏逻辑要求前后和左右移动有不同的行为（如不同的加速度、摩擦系数等）
		// ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		// ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}