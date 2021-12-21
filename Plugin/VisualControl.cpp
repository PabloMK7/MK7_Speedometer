#include "VisualControl.hpp"
#include "MarioKartFramework.hpp"
#include "str16utils.hpp"
#include "ExtraResource.hpp"

namespace CTRPluginFramework {

    VisualControl::MessageString::MessageString(const u16* src, bool makeCopy) {
        usesLocalData = true;
        if (makeCopy)
        {
            u32 sizeBytes = (strsize16(src) + 1) * 2;
            if (sizeBytes > sizeof(localData)) {
                usesLocalData = false;
                data = (u16*)::operator new(sizeBytes);
            } else {
                data = localData;
            }
            strcpy16((u16*)data, src);
        }
        else data = src;
    }

    VisualControl::MessageString::MessageString(const char* src) {
        usesLocalData = true;
        u32 size = utf8len(src);
        u32 sizeBytes = (size + 1) * 2;
        if (sizeBytes > sizeof(localData)) {
            usesLocalData = false;
            data = (u16*)::operator new(sizeBytes);
        } else {
            data = localData;
        }
        int units = utf8_to_utf16((u16*)data, (u8*)src, size);
        if (units >= 0)
            ((u16*)data)[units] = 0;
    }

    void VisualControl::AnimationFamily::SetAnimation(u32 subAnimationID, float frame) {
        ((void(*)(AnimationFamily*, int, float))VisualControl::GameFuncs::animFamilySetAnimation)(this, subAnimationID, frame);
    }
    void VisualControl::AnimationFamily::ChangeAnimation(u32 subAnimationID, float frame) {
        ((void(*)(AnimationFamily*, int, float))VisualControl::GameFuncs::animFamilyChangeAnimation)(this, subAnimationID, frame);
    }
    void VisualControl::AnimationFamily::ChangeAnimationByRate(u32 subAnimationID, float frame) {
        ((void(*)(AnimationFamily*, int, float))VisualControl::GameFuncs::animFamilyChangeAnimationByRate)(this, subAnimationID, frame);
    }

    void VisualControl::AnimationDefine::InitAnimationFamilyList(int animationCount) {
        ((void(*)(AnimationDefine*, int))VisualControl::GameFuncs::initAnimationFamilyList)(this, animationCount);
    }
    void VisualControl::AnimationDefine::InitAnimationFamily(int animationID, const char* affectedGroup, int unknwownCount) {
        ((void(*)(AnimationDefine*, int, const MarioKartFramework::SafeStringBase&, int))VisualControl::GameFuncs::initAnimationFamily)(this, animationID, MarioKartFramework::SafeStringBase(affectedGroup), unknwownCount);
    }
    void VisualControl::AnimationDefine::InitAnimation(int subAnimationID, const char* animationName, AnimationKind kind) {
        ((void(*)(AnimationDefine*, int, const MarioKartFramework::SafeStringBase&, AnimationKind))VisualControl::GameFuncs::initAnimation)(this, subAnimationID, MarioKartFramework::SafeStringBase(animationName), kind);
    }
    void VisualControl::AnimationDefine::InitAnimationStopByRate(int subAnimationID, const char* animationName, float rate) {
        ((void(*)(AnimationDefine*, int, const MarioKartFramework::SafeStringBase&, float))VisualControl::GameFuncs::initAnimation)(this, subAnimationID, MarioKartFramework::SafeStringBase(animationName), rate);
    }
    void VisualControl::AnimationDefine::InitAnimationReverse(int subAnimationID, const char* animationName, AnimationKind kind) {
        ((void(*)(AnimationDefine*, int, const MarioKartFramework::SafeStringBase&, AnimationKind))VisualControl::GameFuncs::initAnimation)(this, subAnimationID, MarioKartFramework::SafeStringBase(animationName), kind);
    }

    void* VisualControl::GameFuncs::PointControlVtable = nullptr; // (void*)0x61A0F0;
    u32 VisualControl::GameFuncs::CreateArgCons = 0; // 0x00157998;
    u32 VisualControl::GameFuncs::ControlAnimCons = 0; // 0x0015B42C;
    u32 VisualControl::GameFuncs::VisualControlCons = 0; // 0x001579F0;
    u32 VisualControl::GameFuncs::InitCreateArgFunc = 0; // 0x00167BD8;
    u32 VisualControl::GameFuncs::EndSetupControlFunc = 0; // 0x00167EF8;

    u32 VisualControl::GameFuncs::BaseFastControlAnimOff = 0; // 0x0015ABA0;
    u32 VisualControl::GameFuncs::BaseFastControlCalcAnimEl = 0; // 0x0015AC8C;

    u32 VisualControl::GameFuncs::initAnimationFamilyList = 0; // 0x0015B2B0;
    u32 VisualControl::GameFuncs::initAnimationFamily = 0; // 0x0015B1D8;
    u32 VisualControl::GameFuncs::initAnimation = 0; // 0x0015B150;
    u32 VisualControl::GameFuncs::initAnimationStopByRate = 0; // 0x00142358;
    u32 VisualControl::GameFuncs::initAnimationReverse = 0; // 0x0015B34C;

    u32 VisualControl::GameFuncs::animFamilySetAnimation = 0; // 0x0015B480;
    u32 VisualControl::GameFuncs::animFamilyChangeAnimation = 0; // 0x0015B51C;
    u32 VisualControl::GameFuncs::animFamilyChangeAnimationByRate = 0; // 0x0015B5B8;

    VisualControl* VisualControl::lastLoadVisualControl = nullptr;

    void VisualControl::nullFunc() {
        // Do nothing
        return;
    }

    VisualControl::AnimationDefine* VisualControl::getAnimationDefine(CreateArg* createArgs) {
        return (AnimationDefine*)((u32)createArgs + 0x78);
    }

    void VisualControl::OnReset(GameVisualControl* visualControl) {
        visualControl->AnimOff();
    }

    void VisualControl::OnDeallocate(GameVisualControl* visualControl) {
        VisualControl* v = visualControl->vtable->visualControl;
        if (v->deallocateCallback)
            v->deallocateCallback(v);
        else
            v->Deallocate();
    }

    VisualControl::VisualControl(const char* cName) {
        this->controlName = cName;

        // Setup createArgVtable
        createArgVtable.userDataDefine = (void(*)(CreateArg*))nullFunc;
        createArgVtable.getAnimationDefine = getAnimationDefine;

        // Setup animationDefineVtable
        animationDefineVtable.defineAnimation = (void(*)(AnimationDefine*))nullFunc;

        // Setup VisualControlVtable
        memcpy(&gameVisualControlVtable, GameFuncs::PointControlVtable, sizeof(gameVisualControlVtable));
        originalDeallocate = gameVisualControlVtable._deallocating;
        gameVisualControlVtable._deallocating = OnDeallocate;
        gameVisualControlVtable.onCreate = (void(*)(GameVisualControl*, void*))nullFunc; // OnCreate
        gameVisualControlVtable.onReset = OnReset; // OnReset
        gameVisualControlVtable.onCalc = (void(*)(GameVisualControl*))nullFunc; // OnCalc
        gameVisualControlVtable.animMenuIn = (void(*)(GameVisualControl*))nullFunc; // OnMenuIn
        gameVisualControlVtable.animMenuOut = (void(*)(GameVisualControl*))nullFunc; // OnMenuOut

        gameVisualControlVtable.visualControl = this;
        gameVisualControlVtable.userData = nullptr;

        deallocateCallback = nullptr;
    }

    VisualControl::~VisualControl() {}

    void VisualControl::Load() {
        u8 visualControlCreateArg[0x90];
		u8* controlAnimator = visualControlCreateArg + 0x78;
		u32* racePage = (u32*)MarioKartFramework::getBaseRacePage();
		u32* controlInitializer = (u32*)(racePage[0x6C/4]);
        MarioKartFramework::SafeStringBase cName(controlName);
        MarioKartFramework::SafeStringBase elName("Point");

        lastLoadVisualControl = this;

		// Construct visualcontrolcreatearg
		((u8*(*)(u8*))(GameFuncs::CreateArgCons))(visualControlCreateArg);
		*((u32*)visualControlCreateArg) = (u32)&createArgVtable;

		// Construct controlanimator
		((u8*(*)(u8*))(GameFuncs::ControlAnimCons))(controlAnimator);
		*((u32*)controlAnimator) = (u32)&animationDefineVtable;

		// Construct visualcontrol
		u32* visualControl = (u32*)ExtraResource::GameAlloc::game_operator_new_autoheap(0x94); // 0x001097C8
		memset(visualControl, 0, 0x94);
		((u32*(*)(u32*))(GameFuncs::VisualControlCons))(visualControl);
		*visualControl = (u32)&gameVisualControlVtable;

		// Setup visualcontrol
		visualControl[0x7C/4] = 0;
		visualControl[0x80/4] = 0;
		visualControl[0x84/4] = 0;
		if (!visualControl[0x10/4]) {
			visualControl[0x10/4] = (u32)visualControl; // ??? Okay game
		}
		u32* something = (u32*)(visualControl[0x10/4]);
		something[0x4/4] = controlInitializer[0];
		((void(*)(u32, u32*))((u32***)controlInitializer)[0][0x14/4][0])(controlInitializer[0] + 0x14, visualControl + 0x8/4);

		// Initialize visualcontrol
		controlInitializer[0x4/4] = (u32)visualControl;
		((void(*)(u32*, u8*, MarioKartFramework::SafeStringBase*, MarioKartFramework::SafeStringBase*))GameFuncs::InitCreateArgFunc)(controlInitializer, visualControlCreateArg, &cName, &elName);

		// Finish initializing visualcontrol
		controlInitializer[0x8/4] = (u32)visualControlCreateArg;
		((u32(*)(u32*, u8*))GameFuncs::EndSetupControlFunc)(controlInitializer, visualControlCreateArg);

		// Append visualcontrol to the race page
		MarioKartFramework::BasePageAppendVisualControl((u32)racePage, (u32)visualControl);

		// Return created visual control
		gameVisualControl = (GameVisualControl*)visualControl;
    }

    u32 VisualControl::GetLayoutElementHandle(const char* paneName) {
        NwlytControlSight* layout = gameVisualControl->GetNwlytControl();
        MarioKartFramework::SafeStringBase pName(paneName);
        return layout->vtable->getConstElementHandle(layout, pName, 0);
    }
}