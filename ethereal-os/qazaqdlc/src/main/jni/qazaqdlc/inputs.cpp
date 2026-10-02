struct MotionJNI {
    jclass cls = nullptr;
    jmethodID getActionMasked = nullptr;
    jmethodID getActionIndex  = nullptr;
    jmethodID getX_i = nullptr;
    jmethodID getY_i = nullptr;
    jmethodID getPointerCount = nullptr;
} me;

static bool EnsureMotionJNI(JNIEnv* env) {
    if (me.cls) return true;
    jclass local = env->FindClass(oxorany("android/view/MotionEvent"));
    if (!local || env->ExceptionCheck()) { env->ExceptionClear(); return false; }
    me.cls = (jclass)env->NewGlobalRef(local);
    env->DeleteLocalRef(local);
    if (!me.cls) return false;

    me.getActionMasked = env->GetMethodID(me.cls, oxorany("getActionMasked"), oxorany("()I"));
    me.getActionIndex = env->GetMethodID(me.cls, oxorany("getActionIndex"),  oxorany("()I"));
    me.getX_i = env->GetMethodID(me.cls, oxorany("getX"), oxorany("(I)F"));
    me.getY_i = env->GetMethodID(me.cls, oxorany("getY"), oxorany("(I)F"));
    me.getPointerCount = env->GetMethodID(me.cls, oxorany("getPointerCount"), oxorany("()I"));
    if (env->ExceptionCheck()) { env->ExceptionClear(); return false; }
    return me.getActionMasked && me.getActionIndex && me.getX_i && me.getY_i && me.getPointerCount;
}

enum TOUCH_ACTION { TOUCH_ACTION_DOWN=0, TOUCH_ACTION_UP, TOUCH_ACTION_MOVE, TOUCH_ACTION_CANCEL };
struct TOUCH_EVENT { TOUCH_ACTION action; float x,y; int pointers; float vx, vy; };
static TOUCH_EVENT g_LastTouchEvent = {TOUCH_ACTION_UP, 0,0, 0, 0,0};

static bool inputEvent(float x, float y, int pointers, int action) {
    ImGuiIO& io = ImGui::GetIO();

    float vy = (y - g_LastTouchEvent.y) * (1.0f / 100.0f);
    float vx = (x - g_LastTouchEvent.x) * (1.0f / 100.0f);

    g_LastTouchEvent = { (TOUCH_ACTION)action, x, y, pointers, vx, vy };

    io.MousePos = ImVec2(x, y);

    switch (action) {
        case TOUCH_ACTION_DOWN:
            io.MouseDown[0] = true;
            io.MouseWheel = 0.0f;
            break;
        case TOUCH_ACTION_UP:
        case TOUCH_ACTION_CANCEL:
            io.MouseDown[0] = false;
            io.MouseWheel   = 0.0f;
            break;
        case TOUCH_ACTION_MOVE:
            if (pointers > 1) {
                io.MouseDown[0] = false;
                io.MouseWheel   = vy;
            } else {
                io.MouseWheel   = 0.0f;
            }
            break;
    }
    return true;
}

static int (*original$$nativeInjectEvent)(JNIEnv*, jobject, jobject);
static int hook$$nativeInjectEvent(JNIEnv* env, jobject thiz, jobject event) {
    if (!EnsureMotionJNI(env) || !env->IsInstanceOf(event, me.cls)) return original$$nativeInjectEvent(env, thiz, event);

    jint action = env->CallIntMethod(event, me.getActionMasked);
    jint index  = env->CallIntMethod(event, me.getActionIndex);
    jint count  = env->CallIntMethod(event, me.getPointerCount);
    if (env->ExceptionCheck()) { env->ExceptionClear(); return original$$nativeInjectEvent(env, thiz, event); }

    jfloat x = env->CallFloatMethod(event, me.getX_i, index);
    jfloat y = env->CallFloatMethod(event, me.getY_i, index);
    if (env->ExceptionCheck()) { env->ExceptionClear(); return original$$nativeInjectEvent(env, thiz, event); }

    int act = TOUCH_ACTION_MOVE;
    switch (action) {
        case 0: act = TOUCH_ACTION_DOWN; break; //down
        case 1: act = TOUCH_ACTION_UP; break; //up
        case 2: act = TOUCH_ACTION_MOVE; break; //move
        case 3: act = TOUCH_ACTION_CANCEL; break; //cancel
        case 5: act = TOUCH_ACTION_DOWN; break; //ptr_down
        case 6: act = TOUCH_ACTION_UP; break; //ptr_up
        default: act = TOUCH_ACTION_MOVE; break;
    }

    inputEvent(x, y, (int)count, act);

    ImGuiIO& io = ImGui::GetIO();
#if IMGUI_VERSION_NUM >= 18900
    if (!io.MouseDownOwnedUnlessPopupClose[0]) return original$$nativeInjectEvent(env, thiz, event);
#else
    if (!io.WantCaptureMouse) return original$$nativeInjectEvent(env, thiz, event);
#endif
    return 0;
}

static jint (*original$$RegisterNatives)(JNIEnv*, jclass, JNINativeMethod*, jint);
static jint hook$$RegisterNatives(JNIEnv* env, jclass clazz, JNINativeMethod* methods, jint count) {
    for (int i=0; i<count; ++i) {
        if (!strcmp(methods[i].name, oxorany("nativeInjectEvent")))
			a64h(methods[i].fnPtr, (void*)hook$$nativeInjectEvent, (void**) &original$$nativeInjectEvent);
    }
    return original$$RegisterNatives(env, clazz, methods, count);
}

void registerNativesHook$$Install(JNIEnv* env) {
    a64h((void *)env -> functions -> RegisterNatives, (void *)hook$$RegisterNatives, (void **) &original$$RegisterNatives);
}
