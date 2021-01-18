#include "MyObject.h"
#include <Windows.h>
#include <ManiaModLoader.h>
#include <SonicMania.h>

using namespace SonicMania;

enum Animations {
    Idle,
    Firing,
    Projectile
};

struct ObjectMyObject : SonicMania::Object {
    SonicMania::Hitbox hitbox;
    WORD spriteIndex;
    WORD sfxId;
};

struct EntityMyObject : SonicMania::Entity {
    SonicMania::EntityAnimationData animData;
    short sfxTimer;
};

ObjectMyObject *OBJ_MyObject = NULL;

void MyObject_Create()
{
    SonicMania::CreateObject(
        SonicMania::CreateSlot_Replace,
        &OBJ_MyObject,
        "Ring",
        sizeof(EntityMyObject),     // Local structure of an entity
        sizeof(ObjectMyObject),     // Global structure of the object
        MyObject_Update,            // Updates an entity
        MyObject_LateUpdate,        // Same as Update, but after a Draw
        MyObject_StageUpdate,       // Updates the global object
        MyObject_Draw,              // Draw an entity
        MyObject_Setup,             // Set-up an entity
        MyObject_StageLoad,         // Set-up an object
        MyObject_EditorLoad,
        MyObject_EditorDraw,
        MyObject_GetAttributes      // Get the properties of an entity from the Scene file
    );
}

void MyObject_Update()
{
    auto entity = (EntityMyObject *)EntityInfo.CurrentEntity;
    ProcessAnimation(&entity->animData);
    GetHitbox(&entity->animData, 0);

    EntityPlayer* player = nullptr;
    auto playerObjectId  = OBJ_Player->ObjectID;
    while (GetActiveObjects(playerObjectId, (Entity **)&player) == 1)
    {
        if (Player_CheckBadnikHit(player, entity, &OBJ_MyObject->hitbox) == 1)
            Player_BadnikBreak(entity, player, true);
    }

    if (--entity->sfxTimer == 0) {
        entity->sfxTimer = 100;
        SonicMania::PlaySoundFX(OBJ_MyObject->sfxId, 0, 255);
    }
}

void MyObject_LateUpdate() { printf("LateUpdate\n"); }
void MyObject_StageUpdate() { printf("StageUpdate\n"); }

void MyObject_Draw()
{
    auto entity = (EntityMyObject*)EntityInfo.CurrentEntity;
    DrawSprite(&entity->animData, 0, 0);
}

void MyObject_Setup(void *subtype)
{
    auto entity        = (EntityMyObject *)EntityInfo.CurrentEntity;
    entity->Visible    = true;
    entity->DrawOrder  = OBJ_ZONE->DrawOrderLow;
    entity->Priority   = ACTIVE_BOUNDS;
    entity->DrawFX     = DrawingFX_Flip;
    entity->Direction  = FLIP_NONE;
    entity->UpdateRange.SetFullX(0x80 << 16);
    entity->UpdateRange.SetFullY(0x80 << 16);
    entity->sfxTimer         = 100;

    SetSpriteAnimation(OBJ_MyObject->spriteIndex, 1, &entity->animData, true, 0);
}
void MyObject_StageLoad()
{
    OBJ_MyObject->spriteIndex   = LoadAnimation("AIZ/Bloominator.bin", Scope_Stage);
    OBJ_MyObject->hitbox.Left   = -12;
    OBJ_MyObject->hitbox.Top    = -18;
    OBJ_MyObject->hitbox.Right  = 12;
    OBJ_MyObject->hitbox.Bottom = 18;

    OBJ_MyObject->sfxId = TryLoadSoundFX("Stage/Shot.wav", Scope_Stage);

    if (OBJ_DebugMode->DebugItemCount < 256) {
        OBJ_DebugMode->Sprites[OBJ_DebugMode->DebugItemCount]   = OBJ_MyObject->ObjectID;
        OBJ_DebugMode->SpawnPtrs[OBJ_DebugMode->DebugItemCount] = []() -> Entity * {
            auto entity = (EntityMyObject*)SpawnObject(OBJ_MyObject->ObjectID, 0,
                EntityInfo.CurrentEntity->Base.Position.X,
                EntityInfo.CurrentEntity->Base.Position.Y);

            return entity;
        };
        OBJ_DebugMode->DrawPtrs[OBJ_DebugMode->DebugItemCount]  = []() -> int
        {
            auto entity = &EntityInfo.CurrentEntity->Base;
            SetSpriteAnimation(OBJ_MyObject->spriteIndex, Animations::Idle, &OBJ_DebugMode->DebugData, true, 0);

            return DrawSprite(&OBJ_DebugMode->DebugData, 0, 0);
        };
        OBJ_DebugMode->DebugItemCount++;
    }
}

void MyObject_EditorLoad() { }
void MyObject_EditorDraw() { }
void MyObject_GetAttributes() { }
