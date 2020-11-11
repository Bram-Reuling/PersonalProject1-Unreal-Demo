// Project made by Bram Reuling (2020)


#include "FPSHUD.h"

void AFPSHUD::DrawHUD()
{
    Super::DrawHUD();

    if (CrosshairTexture)
    {
        // Find the center of our canvas.
        const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

        // Offset by half of the texture's dimensions so that the center of the texture aligns with the center of the Canvas.
        const FVector2D CrossHairPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

        // Draw the crosshair at the centerpoint of the screen.
        FCanvasTileItem TileItem(CrossHairPosition, CrosshairTexture->Resource, FLinearColor::White);
        TileItem.BlendMode = SE_BLEND_Translucent;
        Canvas->DrawItem(TileItem);
    }
}
