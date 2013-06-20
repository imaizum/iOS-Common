// http://qiita.com/yusuga_/items/3751cf2a0b0dbf2eefd8
// http://d.hatena.ne.jp/h_mori/20110707/1310001016

#ifdef DEBUG
    #define LOG(...) NSLog(__VA_ARGS__)
    #define LOG_FULL(A, ...) NSLog(@"DEBUG: %s:%d:%@", __PRETTY_FUNCTION__,__LINE__,[NSString stringWithFormat:A, ## __VA_ARGS__]);
    #define LOG_PRINTF(FORMAT, ...) printf("%s\n", [[NSString stringWithFormat:FORMAT, ##__VA_ARGS__] UTF8String]);
    #define LOG_METHOD NSLog(@"%s", __func__)
    #define LOG_METHOD_AND_ABORT LOG_METHOD; abort()

    #define LOG_CURRENT_METHOD NSLog(@"%@/%@", NSStringFromClass([self class]), NSStringFromSelector(_cmd))
    #define LOG_TIMER_START(...) fprintf(stderr,"TIMER start -- %s -- (%d)\n",__STRING(__VA_ARGS__),__LINE__);NSDate *__VA_ARGS__=[NSDate date]
    #define LOG_TIMER_END(...) fprintf(stderr,"TIMER end   -- %s -- (%d): %f s\n",__STRING(__VA_ARGS__),__LINE__,-[__VA_ARGS__ timeIntervalSinceNow])
    #define LOG_RETAINCOUNT(var) fprintf(stderr,"-- %s.retainCount=%d --\n",__STRING(var),[var retainCount])

    #define LINE() NSLog(@"%d",__LINE__)
    #define FUNC() NSLog(@"%s",__PRETTY_FUNCTION__)
    /*
    	 引数に入れた引数・返り値なしのblocksを同期的に処理します。
    	 デバッグビルドでのみ画面上にビルド番号を表示させたりできます。
    	 メモリリークには気をつけましょう。
    	 */
    #define DEBUGEXEC(__BLOCK,...) { dispatch_sync(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{ __BLOCK(__VA_ARGS__); });}

#else
    #define LOG(...)
    #define LOG_FULL(A, ...)
    #define LOG_PRINTF(FORMAT, ...) printf("%s\n", [[NSString stringWithFormat:FORMAT, ##__VA_ARGS__] UTF8String]);
    #define LOG_PRINTF(FORMAT, ...)
    #define LOG_METHOD
    #define LOG_METHOD_AND_ABORT

    #define LOG_CURRENT_METHOD 
    #define LOG_TIMER_START(...) 
    #define LOG_TIMER_END(...) 
    #define LOG_RETAINCOUNT(var)

    #define LINE()
    #define FUNC()
    #define DEBUGEXEC(__BLOCK,...) ;

#endif

#ifdef DEBUG
    #define LOG_POINT(p) NSLog(@"%f, %f", p.x, p.y)
    #define LOG_SIZE(p) NSLog(@"%f, %f", p.width, p.height)
    #define LOG_RECT(p) NSLog(@"%f, %f - %f, %f", p.origin.x, p.origin.y, p.size.width, p.size.height)
#else
    #define LOG_POINT(p)
    #define LOG_SIZE(p)
    #define LOG_RECT(p)
#endif

#if DEBUG
@interface UIView (DebugPrivate)
- (NSString*)recursiveDescription;
@end
#endif



// http://qiita.com/yuch_i/items/5da905e24dcc27205985

// AppDelegateの参照
#define APP_DELEGATE ((AppDelegate*)[[UIApplication sharedApplication] delegate])

// テストの時に便利なBundleの参照
#define BUNDLE  [NSBundle bundleForClass:[self class]]

// 画面サイズ
#define SCREEN_BOUNDS   ([UIScreen mainScreen].bounds)

// UIColorを簡単に書く
#define RGB(r, g, b) [UIColor colorWithRed:(r)/255.0 green:(g)/255.0 blue:(b)/255.0 alpha:1]
#define RGBA(r, g, b, a)    [UIColor colorWithRed:(r)/255.0 green:(g)/255.0 blue:(b)/255.0 alpha:(a)]

// max, min
#define MIN(a,b)    ((a) < (b) ? (a) : (b))
#define MAX(a,b)    ((a) > (b) ? (a) : (b))

// iPhone, iPad の確認
#define IS_IPHONE (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
#define IS_IPAD (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)

// Retina判定
#define IS_RETINA ([[UIScreen mainScreen] respondsToSelector:@selector(scale)] && [UIScreen mainScreen].scale > 1)

// 言語取得
#define LANGUAGE    ([NSLocale preferredLanguages][0])

// よく使う標準コントロールのサイズ
// UIStatusBar, UITabBar, UINavigationBar, UIToolbarの高さを定義しています。ランドスケープも対応する場合は別途調整が必要です。
#define STATUSBAR_H 20
#define TABBAR_H    48
#define NAVBAR_H    44
#define TOOLBAR_H   44

// http://qiita.com/shu223/items/dc1759fc9695cea27756

// iOSバージョン判定
#define SYSTEM_VERSION_LESS_THAN(v) ([[[UIDevice currentDevice] systemVersion] \
		compare:v options:NSNumericSearch] == NSOrderedAscending)




// http://qiita.com/sora0077@github/items/154f8d39f7189f22daa7

// 型の安全なキャスト
// -- [SafeCast(NSMutableURLRequest, request) setTimeoutInterval:30];

#define SafeCast(type, var) \
    ^type *(id obj, Class clazz) {\
        if ([obj isKindOfClass:clazz]) {\
            return obj;\
        }\
        return nil;\
    } (var, [type class])

// Blocks呼び出しのnilチェックのラッパー
// -- SafeBlockHandler(completion, arg0, arg1); // == completion(arg0, arg1);
#define SafeBlockHandler(block, ...) \
    do {\
        if (block) {\
            block(__VA_ARGS__);\
        }\
    } while (0)

// aNSUserDefaults読み書きのラッパー
// -- 実際はこのマクロを直接利用せず、型ごとにインライン関数を定義してそこから利用している
// e.g.
// static inline void NSUserDefaultsWriteObject(id aKey, id anObject)
// {
//     NSUserDefaults_Write(aKey, anObject, setObject);
// }
// static inline id NSUserDefaultsReadObject(id aKey)
// {
//     NSUserDefaults_Read(aKey, objectForKey);
// }
#define NSUserDefaults_Write(aKey, anObject, method) \
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];\
    if (anObject) {\
        [defaults method:anObject forKey:aKey];\
    } else {\
        [defaults removeObjectForKey:aKey];\
    }\
    [defaults synchronize]

#define NSUserDefaults_Read(aKey, method) \
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];\
    return [defaults method:aKey]
