// Project made by Bram Reuling (2020)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "FPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class FINALPRODUCT_API AFPSHUD : public AHUD
{
	GENERATED_BODY()
protected:
	// Property that holds the texture for the crosshair
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;
public:
	virtual void DrawHUD() override;
};
