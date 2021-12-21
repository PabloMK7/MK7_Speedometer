#pragma once
#include "CTRPluginFramework.hpp"
#include "Math.hpp"
#include "MarioKartFramework.hpp"

namespace CTRPluginFramework {

    class VisualControl
    {
    public:
        struct MessageString
        {
            const u16* data;
            bool usesLocalData;
            u16 localData[0x10];

            MessageString(const u16* src, bool makeCopy = false);
            MessageString(const char* str);
            MessageString(const std::string& str) : MessageString(str.c_str()) {}
            ~MessageString() { if (!usesLocalData) delete (u16*)data;}
        };

         struct NwlytControlSight;

        struct NwlytControlSightVtable {
            void(*getRuntimeTypeInfo)(NwlytControlSight* obj);                                                                                          // 0x00
            u32 null;                                                                                                                                   // 0x04
            void(*_NwlytControlSight__deallocating)(NwlytControlSight* obj);                                                                            // 0x08
            void(*build)(NwlytControlSight* obj, u32* createArg);                                                                                       // 0x0C
            void(*calc)(NwlytControlSight* obj);                                                                                                        // 0x10
            void(*draw)(NwlytControlSight* obj);                                                                                                        // 0x14
            u32(*getElementHandle)(NwlytControlSight* obj, const MarioKartFramework::SafeStringBase& element, u32 elementType);                         // 0x18
            u32(*getConstElementHandle)(NwlytControlSight* obj, const MarioKartFramework::SafeStringBase& element, u32 elementType);                    // 0x1C
            void(*setPosImpl)(NwlytControlSight* obj, NwlytControlSight* elementHandle, const Vector3& position);                                       // 0x20
            Vector3&(*getPosImpl)(NwlytControlSight* obj, u32 elementHandle);                                                                           // 0x24
            u32 null0;                                                                                                                                   // 0x28
            Vector3&(*getSizeImpl)(NwlytControlSight* obj, u32 elementHandle);                                                                          // 0x2C
            u32 null1;                                                                                                                                  // 0x30
            u32 null2;                                                                                                                                  // 0x34
            u32 null3;                                                                                                                                  // 0x38
            u32 null4;                                                                                                                                  // 0x3C
            u32 null5;                                                                                                                                  // 0x40
            u32 null6;                                                                                                                                  // 0x44
            void*(*getGlobalMtxImpl)(NwlytControlSight* obj, u32 elementHandle);                                                                        // 0x48
            void(*setAlphaImpl)(NwlytControlSight* obj, u32 elementHandle, u8 amount);                                                                  // 0x4C
            u32 null7;                                                                                                                                  // 0x50
            u8(*getGlobalAlphaImpl)(NwlytControlSight* obj, u32 elementHandle);                                                                         // 0x54
            void(*setVisibleImpl)(NwlytControlSight* obj, u32 elementHandle, bool visible);                                                             // 0x58
            u32 null8;                                                                                                                                  // 0x5C
            bool(*getGlobalVisibleImpl)(NwlytControlSight* obj, u32 elementHandle);                                                                     // 0x60
            u32 null9;                                                                                                                                  // 0x64
            void*(*getPane)(NwlytControlSight* obj, u32 elementHandle);                                                                                 // 0x68
            u32 null10;                                                                                                                                 // 0x6C
            void(*replaceMessageImpl)(NwlytControlSight* obj, u32 elementHandle, const MessageString& message, void* messageArg, void* letterStepper);  // 0x70
            void(*replaceGraphicImpl)(NwlytControlSight* obj, u32 elementHandle, const MarioKartFramework::SafeStringBase& graphic);                    // 0x74
            u32 null11;                                                                                                                                 // 0x78
            u32 null12;                                                                                                                                 // 0x7C
            void(*setRootPosImpl)(NwlytControlSight* obj, const Vector3& pos);                                                                          // 0x80
            Vector3&(*getRootPosImpl)(NwlytControlSight* obj);                                                                                          // 0x84
            void(*setRootMtxImpl)(NwlytControlSight* obj, const void* matrix);                                                                          // 0x88
            u32 null13;                                                                                                                                 // 0x8C
            void*(*getGlobalRootMtxImpl)(NwlytControlSight* obj);                                                                                       // 0x90
            void(*setRootAlphaImpl)(NwlytControlSight* obj, u8 amount);                                                                                 // 0x94
            u32 null14;                                                                                                                                 // 0x98
            u8(*getGlobalRootAlphaImpl)(NwlytControlSight* obj);                                                                                        // 0x9C
            void(*setRootVisibleImpl)(NwlytControlSight* obj, bool visible);                                                                            // 0xA0
            bool(*getRootVisibleImpl)(NwlytControlSight* obj);                                                                                          // 0xA4
            bool(*getGlobalRootVisibleImpl)(NwlytControlSight* obj);                                                                                    // 0xA8
            u32 null15;                                                                                                                                 // 0xAC
            u32 null16;                                                                                                                                 // 0xB0
            u32 null17;                                                                                                                                 // 0xB4
            void*(*getLayoutInfo)(NwlytControlSight* obj);                                                                                              // 0xB8
            void*(*getRootPane)(NwlytControlSight* obj);                                                                                                // 0xBC
            void*(*getRootPaneConst)(NwlytControlSight* obj);                                                                                           // 0xC0
            void*(*getParentGlobalVisible)(NwlytControlSight* obj);                                                                                     // 0xC4
        };

        struct NwlytControlAnimator;
        struct NwlytControlAnimatorVtable {
            u32 null;
            u32 null1;
            u32 null2;
            void(*applyAnimation)(NwlytControlAnimator* obj);
            void* nwlytAnimationFamilyCons;
            u32 null3;
            u32 null4;
        };

        struct NwlytControlSight
        {
            NwlytControlSightVtable* vtable;
            u32 data[];
        };

        struct NwlytControlAnimator
        {
            NwlytControlAnimatorVtable* vtable;
            u32 data[];
            void ApplyAnimation() {
                vtable->applyAnimation(this);
            }
        };

        struct AnimationFamily {
            void SetAnimation(u32 subAnimationID, float frame);
            void ChangeAnimation(u32 subAnimationID, float frame);
            void ChangeAnimationByRate(u32 subAnimationID, float frame);
        };

        struct GameVisualControl;

        struct GameVisualControlVtable {
            void*(*getDTIClassInfo)(GameVisualControl* obj);                               // 0x00
            void*(*getDTIClass)(GameVisualControl* obj);                                   // 0x04
            u32 null;                                                       // 0x08
            void(*_deallocating)(GameVisualControl* obj);                    // 0x0C
            void(*create)(GameVisualControl* obj, void* createArg);                        // 0x10
            void(*init)(GameVisualControl* obj);                                           // 0x14
            void(*calc)(GameVisualControl* obj);                                           // 0x18
            void(*render)(GameVisualControl* obj);                                         // 0x1C
            void(*renderMainL)(GameVisualControl* obj);                                    // 0x20
            void(*renderMainR)(GameVisualControl* obj);                                    // 0x24
            void(*renderSub)(GameVisualControl* obj);                                      // 0x28
            u32 null1;                                                      // 0x2C
            void(*accept)(GameVisualControl* obj, void* actorVisitor);                     // 0x30
            void(*callbackInvokeEventID)(GameVisualControl* obj, int eventID);             // 0x34
            u32 null2;                                                      // 0x38
            void(*createOuter)(GameVisualControl* obj, void* data);                        // 0x3C
            void(*initOuter)(GameVisualControl* obj);                                      // 0x40
            u32 null3;                                                      // 0x44
            void(*forceCameraDir)(GameVisualControl* obj);                                 // 0x48
            void(*onCreate)(GameVisualControl* obj, void* createArg);                      // 0x4C
            void(*reset)(GameVisualControl* obj);                                          // 0x50
            void(*readyFadein)(GameVisualControl* obj, int something);                     // 0x54
            void(*readyFadeout)(GameVisualControl* obj, int something);                    // 0x58
            void(*fadeStep)(GameVisualControl* obj);                                       // 0x5C
            bool(*isFadeComplete)(GameVisualControl* obj);                                 // 0x60
            void(*draw)(GameVisualControl* obj, u32 drawScreen);                           // 0x64
            void*(*getRootPane)(GameVisualControl* obj);                                   // 0x68
            void(*generateFader)(GameVisualControl* obj);                                  // 0x6C
            void(*onReset)(GameVisualControl* obj);                                         // 0x70
            void(*onCalc)(GameVisualControl* obj);                                         // 0x74
            void(*onCalcPostAnim)(GameVisualControl* obj);                                 // 0x78
            void(*animMenuIn)(GameVisualControl* obj);                                     // 0x7C
            void(*animMenuOut)(GameVisualControl* obj);                                    // 0x80
            VisualControl* visualControl;                                                  // 0x84
            void* userData;                                                                // 0x88
            u32 null5;                                                                     // 0x8C
        };

        struct GameVisualControl {
            GameVisualControlVtable* vtable;
            u32 data[];

            NwlytControlSight* GetNwlytControl() {
                return (NwlytControlSight*)data[(0x68-0x4)/4];
            }

            NwlytControlAnimator* GetNwlytAnimator() {
                return (NwlytControlAnimator*)data[(0x64-0x4)/4];
            }

            VisualControl* GetVisualControl() {
                return vtable->visualControl;
            }

            AnimationFamily* GetAnimationFamily(u32 animationID) {
                u32* animFamilyList = (u32*)data[(0x64-0x4)/4];
                u32 count = animFamilyList[1];
                u32* animList = (u32*)animFamilyList[2];
                if (animationID < count) {
                    return (AnimationFamily*)animList[animationID];
                } else {
                    return (AnimationFamily*)animList[0];
                }
            }

            void EnableCalc(bool enable) {
                ((bool*)data)[(0x28-4)] = enable;
            }

            void AnimOff() {
                ((void(*)(GameVisualControl*))(GameFuncs::BaseFastControlAnimOff))(this);
            }

            void CalcAnim(u32 &elementHandle) {
                ((void(*)(GameVisualControl*, u32&))GameFuncs::BaseFastControlCalcAnimEl)(this, elementHandle);
            }
        };

        struct AnimationDefine;

        struct AnimationDefineVtable {
            void(*defineAnimation)(AnimationDefine* obj);
            u32 null;
            u32 null1;
        };

        struct AnimationDefine {
            AnimationDefineVtable* vtable;
            u32 data[];

            enum class AnimationKind {
                NOPLAY = -1,
                ONCE = 0,
                LOOP = 1
            };

            void InitAnimationFamilyList(int animationCount);
            void InitAnimationFamily(int animationID, const char* affectedGroup, int unknwownCount);
            void InitAnimation(int subAnimationID, const char* animationName, AnimationKind kind);
            void InitAnimationStopByRate(int subAnimationID, const char* animationName, float rate);
            void InitAnimationReverse(int subAnimationID, const char* animationName, AnimationKind kind);

            VisualControl* GetVisualControl() {return lastLoadVisualControl;}
        };

        struct CreateArg;

        struct CreateArgVtable {
            u32 null;
            void(*userDataDefine)(CreateArg* obj);
            u32 null1;
            AnimationDefine*(*getAnimationDefine)(CreateArg* obj);
            u32 null2;
            u32 null3;
        };

        struct CreateArg
        {
            CreateArgVtable* vtable;
            u32 data[];
        };

        VisualControl(const char* controlName);
        ~VisualControl();

        void Load();
        u32 GetLayoutElementHandle(const char* paneName);
        GameVisualControl* GetGameVisualControl() {return gameVisualControl;};
        void SetUserData(void* userData) {gameVisualControlVtable.userData = userData;}
        void* GetUserData() {return gameVisualControlVtable.userData;}

        void SetAnimationDefineCallback(void(*callback)(AnimationDefine*)) {animationDefineVtable.defineAnimation = callback;}

        void SetOnCreateCallback(void (*callback)(GameVisualControl*, void*)) {gameVisualControlVtable.onCreate = callback;}
        void SetOnResetCallback(void(*callback)(GameVisualControl*)) {gameVisualControlVtable.onReset = callback;}
        void SetOnCalcCallback(void(*callback)(GameVisualControl*)) {gameVisualControlVtable.onCalc = callback;}

        void SetDeallocateCallback(void(*callback)(VisualControl*)) { deallocateCallback = callback; }
        void Deallocate() {originalDeallocate(gameVisualControl); gameVisualControl = nullptr;}

        class GameFuncs {
        public:
            static void* PointControlVtable;
            static u32 CreateArgCons;
            static u32 ControlAnimCons;
            static u32 VisualControlCons;
            static u32 InitCreateArgFunc;
            static u32 EndSetupControlFunc;
            static u32 BaseFastControlAnimOff;
            static u32 BaseFastControlCalcAnimEl;

            static u32 initAnimationFamilyList;
            static u32 initAnimationFamily;
            static u32 initAnimation;
            static u32 initAnimationStopByRate;
            static u32 initAnimationReverse;

            static u32 animFamilySetAnimation;
            static u32 animFamilyChangeAnimation;
            static u32 animFamilyChangeAnimationByRate;
        };
    private:        

        static void nullFunc();
        static VisualControl::AnimationDefine* getAnimationDefine(CreateArg* createArgs);
        static void OnReset(GameVisualControl* visualControl);
        static void OnDeallocate(GameVisualControl* control);

        const char* controlName;
        AnimationDefineVtable animationDefineVtable;
        CreateArgVtable createArgVtable;
        GameVisualControlVtable gameVisualControlVtable;
        
        GameVisualControl* gameVisualControl;

        void(*deallocateCallback)(VisualControl* control);
        void(*originalDeallocate)(GameVisualControl* control);

        static VisualControl* lastLoadVisualControl;        
    };
}